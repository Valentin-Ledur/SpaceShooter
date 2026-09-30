import SpaceShooter_IA

import os
import tensorflow as tf
import keras
from keras import Sequential, layers, Input
from keras.layers import LeakyReLU
from keras.optimizers import Adam
from keras.losses import Huber
from keras import Model
from collections import deque
import numpy as np
import math

gpus = tf.config.list_physical_devices('GPU')
if gpus:
    try:
        for gpu in gpus:
            tf.config.experimental.set_memory_growth(gpu, True)
    except RuntimeError as e:
        print(e)

gamma = 0.99  # Discount factor for past rewards
epsilon = 1.0  # Epsilon greedy parameter
epsilon_min = 0.1  # Minimum epsilon greedy parameter
epsilon_max = 1.0  # Maximum epsilon greedy parameter
epsilon_interval = (
    epsilon_max - epsilon_min
)  # Rate at which to reduce chance of random action being taken
batch_size = 32  # Size of batch taken from replay buffer
max_steps_per_episode = 10000
max_episodes = 1000

"""
Actions :
ne pas bouger,
Haut,
Haut Droite,
Droite,
Bas Droite,
Bas,
Bas Gauche,
Gauche,
Haut Gauche,

37 positions de tire
"""

num_move_actions = 9
num_shoot_actions = 37

num_parameters = 54

def make_model():
    inputs = Input(shape=(num_parameters,))

    x = layers.Dense(64)(inputs)
    x = LeakyReLU()(x)
    x = layers.Dense(128)(x)
    x = LeakyReLU()(x)

    move = layers.Dense(64)(x)
    move = LeakyReLU()(move)

    shoot = layers.Dense(64)(x)
    shoot = LeakyReLU()(shoot)

    move_output = layers.Dense(num_move_actions, activation="linear")(move)
    shoot_output = layers.Dense(num_shoot_actions, activation="linear")(shoot)

    model = Model(inputs=inputs, outputs=[move_output, shoot_output])

    return model

def OutputDataFromActions(move_action, shoot_action):
    output = SpaceShooter_IA.AIDataOutput()

    if (move_action == 1):
        output.up = True
    elif(move_action == 2):
        output.up = True
        output.right = True
    elif(move_action == 3):
        output.right = True
    elif(move_action == 4):
        output.down = True
        output.right = True
    elif(move_action == 5):
        output.down = True
    elif(move_action == 6):
        output.down = True
        output.left = True
    elif(move_action == 7):
        output.left = True
    elif(move_action == 8):
        output.up = True
        output.left = True

    if (shoot_action != 0):
        output.shoot = True

        angle_deg = shoot_action * 10.0
        angle_rad = math.radians(angle_deg)

        output.x = math.cos(angle_rad)
        output.y = math.sin(angle_rad)
    else:
        output.shoot = False
        output.x = 0
        output.y = 0

    return output

model = make_model()
model_target = make_model()

if os.path.isfile("ai_model.keras"):
    print("Loading model from", "ai_model.keras")
    model.load_weights("ai_model.keras")
    model_target.load_weights("ai_model.keras")
else:
    print("no model to load")

# Création de l'environnement du jeu
env = SpaceShooter_IA.Game()
env.showaiplay(False)

running_reward = 0
episode_count = 0
frame_count = 0

# Nombre de frame ou une action aléatoire est prise
epsilon_random_frames = 50000
# Nombre de frame ou une action est prise par le model
epsilon_greedy_frames = 10000
# Maximum replay length, valeur de la doc 100000
max_memory_length = 1000000
# Nombre d'action entre chaque update
update_after_actions = 4
# How often to update the target network
update_target_network = 10000

# Experience replay buffers
move_action_history = deque(maxlen=max_memory_length)
shoot_action_history = deque(maxlen=max_memory_length)
state_history = deque(maxlen=max_memory_length)
state_next_history = deque(maxlen=max_memory_length)
rewards_history = deque(maxlen=max_memory_length)
done_history = deque(maxlen=max_memory_length)
episode_reward_history = []

optimizer = keras.optimizers.Adam(learning_rate=0.00025, clipnorm=1.0)
loss_function = keras.losses.Huber()

while True:
    model_inputs = SpaceShooter_IA.AIDataInput()
    model_inputs = env.reset()

    state = model_inputs.obs
    episode_reward = 0

    if episode_count % 50 == 0:
        model.save("ai_model.keras")

    for timestep in range(1, max_steps_per_episode):
        frame_count += 1

        if frame_count < epsilon_random_frames or epsilon > np.random.rand(1)[0]:
            move_action = np.random.choice(num_move_actions)
            shoot_action = np.random.choice(num_shoot_actions)
        else:
            state_tensor = keras.ops.convert_to_tensor(state)
            state_tensor = keras.ops.expand_dims(state_tensor, 0)
            move_action_probs, shoot_action_probs = model(state_tensor, training=False)

            move_action = np.array((keras.ops.argmax(move_action_probs[0])))
            shoot_action = np.array((keras.ops.argmax(shoot_action_probs[0])))

        if frame_count > epsilon_random_frames:
            epsilon -= epsilon_interval / epsilon_greedy_frames
            epsilon = max(epsilon, epsilon_min)

        step_inputs = env.step(OutputDataFromActions(move_action, shoot_action))
        state_next = step_inputs.obs
        state_next= np.array(state_next)
        reward = step_inputs.training_score
        done = step_inputs.done

        episode_reward += reward
        
        move_action_history.append(move_action)
        shoot_action_history.append(shoot_action)
        state_history.append(state)
        state_next_history.append(state_next)
        done_history.append(done)
        rewards_history.append(reward)
        state = state_next

        if frame_count % update_after_actions == 0 and len(done_history) > batch_size:
            indices = np.random.choice(range(len(done_history)), size=batch_size)

            state_sample = np.array([state_history[i] for i in indices])
            state_next_sample = np.array([state_next_history[i] for i in indices])
            reward_sample = [rewards_history[i] for i in indices]
            move_action_sample = [move_action_history[i] for i in indices]
            shoot_action_sample = [shoot_action_history[i] for i in indices]
            done_sample = keras.ops.convert_to_tensor([
                float(done_history[i])  for i in indices
            ])

            future_reward_move, future_reward_shoot = model_target(state_next_sample, training=False)

            move_updated_q_values = reward_sample + (1.0 - done_sample) * gamma * keras.ops.amax(future_reward_move, axis=1)
            shoot_updated_q_values = reward_sample + (1.0 - done_sample) * gamma * keras.ops.amax(future_reward_shoot, axis=1)

            move_masks = keras.ops.one_hot(move_action_sample, num_move_actions)
            shoot_masks = keras.ops.one_hot(shoot_action_sample, num_shoot_actions)

            with tf.GradientTape() as tape:
                move_q_values, shoot_q_values = model(state_sample)

                move_q_action = keras.ops.sum(keras.ops.multiply(move_q_values, move_masks), axis=1)
                shoot_q_action = keras.ops.sum(keras.ops.multiply(shoot_q_values, shoot_masks), axis=1)

                move_loss = loss_function(move_updated_q_values, move_q_action)
                shoot_loss = loss_function(shoot_updated_q_values,shoot_q_action)

                loss = move_loss + shoot_loss

            grads = tape.gradient(loss, model.trainable_variables)
            optimizer.apply_gradients(zip(grads, model.trainable_variables))

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

    episode_count += 1

    if running_reward > 40:  # Condition to consider the task solved
        print("Solved at episode {}!".format(episode_count))
        break

    if (max_episodes > 0 and episode_count >= max_episodes):  # Maximum number of episodes reached
        print("Stopped at episode {}!".format(episode_count))
        break