import SpaceShooter_IA
from model import *

import os
import numpy as np
import math
import tensorflow as tf
import keras
from keras import Sequential, layers, Input
from keras.layers import LeakyReLU
from keras.optimizers import Adam
from keras.losses import Huber
from keras import Model
from collections import deque
import datetime

"""

pip install tensorflow[and-cuda]
pip install tensorboard

tensorboard --logdir logs/spaceshooter/

"""

gpus = tf.config.list_physical_devices('GPU')
if gpus:
    try:
        for gpu in gpus:
            tf.config.experimental.set_memory_growth(gpu, True)
    except RuntimeError as e:
        print(e)

model = make_model()
model_target = make_model()

if os.path.isfile("python/ai_model.keras"):
    print("Loading model from", "python/ai_model.keras")
    model.load_weights("python/ai_model.keras")
    model_target.load_weights("python/ai_model.keras")
else:
    print("no model to load")

model.summary()

# Création de l'environnement du jeu
env = SpaceShooter_IA.Game()
env.showaiplay(False)

gamma = 0.99  # Discount factor for past rewards
epsilon = 1.0  # Epsilon greedy parameter
epsilon_min = 0.1  # Minimum epsilon greedy parameter
epsilon_max = 1.0  # Maximum epsilon greedy parameter
epsilon_interval = (
    epsilon_max - epsilon_min
)  # Rate at which to reduce chance of random action being taken
batch_size = 256  # Size of batch taken from replay buffer
max_steps_per_episode = 10000
max_episodes = 500000

running_reward = 0
episode_count = 0
frame_count = 0

# Nombre de frame ou une action aléatoire est prise
epsilon_random_frames = 100000
# Nombre de frame ou une action est prise par le model
epsilon_greedy_frames = 1500000
# Maximum replay length, valeur de la doc 100000
max_memory_length = 1000000
# Nombre d'action entre chaque update
update_after_actions = 4
# How often to update the target network
update_target_network = 5000

# Experience replay buffers
state_history = np.zeros((max_memory_length, num_parameters), dtype=np.float32)
state_next_history = np.zeros((max_memory_length, num_parameters), dtype=np.float32)
move_action_history = np.zeros(max_memory_length, dtype=np.int32)
shoot_action_history = np.zeros(max_memory_length, dtype=np.int32)
rewards_history = np.zeros(max_memory_length, dtype=np.float32)
done_history = np.zeros(max_memory_length, dtype=np.float32)

buffer_counter = 0
episode_reward_history = []

optimizer = keras.optimizers.Adam(learning_rate=0.00025, clipnorm=1.0)
loss_function = keras.losses.Huber()

current_time = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
train_log_dir = 'logs/spaceshooter/' + current_time
summary_writer = tf.summary.create_file_writer(train_log_dir)

while True:
    model_inputs = SpaceShooter_IA.AIDataInput()
    model_inputs = env.reset()

    state = np.array(model_inputs.obs, dtype="float32")
    episode_reward = 0

    if episode_count % 50 == 0:
        model.save("python/ai_model.keras")

    for timestep in range(1, max_steps_per_episode):
        frame_count += 1

        can_shoot = (state[-1] > 0.5)

        if frame_count < epsilon_random_frames or epsilon > np.random.rand(1)[0]:
            move_action = np.random.choice(num_move_actions)

            if (can_shoot):
                shoot_action = np.random.choice(num_shoot_actions)
            else:
                shoot_action = 0
        else:
            state_tensor = keras.ops.convert_to_tensor(state)
            state_tensor = keras.ops.expand_dims(state_tensor, 0)

            move_q_values, shoot_q_values = model(state_tensor, training=False)

            move_action = int(keras.ops.argmax(move_q_values[0]))

            if (can_shoot):
                shoot_action = int(keras.ops.argmax(shoot_q_values[0]))
            else:
                shoot_action = 0

        if frame_count > epsilon_random_frames:
            epsilon -= epsilon_interval / epsilon_greedy_frames
            epsilon = max(epsilon, epsilon_min)

        step_inputs = env.step(OutputDataFromActions(move_action, shoot_action))
        state_next = step_inputs.obs
        state_next= np.array(state_next)
        reward = step_inputs.training_score
        done = step_inputs.done

        episode_reward += reward

        idx = buffer_counter % max_memory_length
        state_history[idx] = state
        state_next_history[idx] = state_next
        move_action_history[idx] = move_action
        shoot_action_history[idx] = shoot_action if can_shoot else -1
        rewards_history[idx] = reward
        done_history[idx] = float(done)
        buffer_counter += 1
        state = state_next

        current_buffer_size = min(buffer_counter, max_memory_length)

        if frame_count % update_after_actions == 0 and len(done_history) > batch_size:
            indices = np.random.choice(current_buffer_size, size=batch_size)

            state_sample = state_history[indices]
            state_next_sample = state_next_history[indices]
            reward_sample = rewards_history[indices]
            move_action_sample = move_action_history[indices]
            done_sample = done_history[indices]

            raw_shoot = shoot_action_history[indices]
            shoot_mask_valid = (raw_shoot != -1).astype(np.float32)
            valid_count = np.sum(shoot_mask_valid)
            normalized_shoot_weights = shoot_mask_valid * (batch_size / (valid_count + 1e-8))
            safe_shoot_actions = np.where(raw_shoot != -1, raw_shoot, 0)

            next_move_q_values, next_shoot_q_values = model_target(state_next_sample, training=False)
            max_next_move_q = keras.ops.amax(next_move_q_values, axis=1)
            max_next_shoot_q = keras.ops.amax(next_shoot_q_values, axis=1)

            target_move_q_values = reward_sample + (1.0 - done_sample) * gamma * max_next_move_q
            target_shoot_q_values = reward_sample + (1.0 - done_sample) * gamma * max_next_shoot_q

            move_masks = keras.ops.one_hot(move_action_sample, num_move_actions)
            shoot_masks = keras.ops.one_hot(safe_shoot_actions, num_shoot_actions)

            with tf.GradientTape() as tape:

                all_move_q, all_shoot_q = model(state_sample)

                predicted_move_q = keras.ops.sum(keras.ops.multiply(all_move_q, move_masks), axis=1)
                predicted_shoot_q = keras.ops.sum(keras.ops.multiply(all_shoot_q, shoot_masks), axis=1)

                move_loss = loss_function(target_move_q_values, predicted_move_q)
                shoot_loss = loss_function(
                    target_shoot_q_values, 
                    predicted_shoot_q, 
                    sample_weight=normalized_shoot_weights
                )

                loss = move_loss + shoot_loss

            grads = tape.gradient(loss, model.trainable_variables)
            optimizer.apply_gradients(zip(grads, model.trainable_variables))

            with summary_writer.as_default():
                tf.summary.scalar('Loss/Total', loss, step=frame_count)
                tf.summary.scalar('Loss/Move', move_loss, step=frame_count)
                tf.summary.scalar('Loss/Shoot', shoot_loss, step=frame_count)
                tf.summary.scalar('Metrics/Epsilon', epsilon, step=frame_count)

        if frame_count % update_target_network == 0:
            model_target.set_weights(model.get_weights())
            template = "running reward: {:.2f} at episode {}, frame count {}"
            print(template.format(running_reward, episode_count, frame_count))

        if done:
            break

    episode_reward_history.append(episode_reward)

    if len(episode_reward_history) > 100:
        del episode_reward_history[:1]

    running_reward = np.mean(episode_reward_history)

    with summary_writer.as_default():
        tf.summary.scalar('Score/Episode_Reward', episode_reward, step=episode_count)
        tf.summary.scalar('Score/Running_Reward', running_reward, step=episode_count)

    episode_count += 1

    if running_reward > 5000:  # Condition to consider the task solved
        print("Solved at episode {}!".format(episode_count))
        break

    if (max_episodes > 0 and episode_count >= max_episodes):  # Maximum number of episodes reached
        print("Stopped at episode {}!".format(episode_count))
        break