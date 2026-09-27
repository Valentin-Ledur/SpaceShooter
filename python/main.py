import SpaceShooter_IA

import tensorflow as tf
from keras import Sequential, layers, Input
from keras.layers import LeakyReLU
from keras.optimizers import Adam
from collections import deque
import numpy as np
import random

env = SpaceShooter_IA.Game()
env.showaiplay(True)

model_tf = Sequential([
    Input(shape=(53,)),
    layers.Dense(64),
    LeakyReLU(),
    layers.Dense(128),
    LeakyReLU(),
    layers.Dense(64),
    LeakyReLU(),
    layers.Dense(7, activation="linear")
])

model_tf.compile(optimizer=Adam(learning_rate=0.001), loss='mse')
model_tf.summary()

epsilon = 1.0
epsilon_min = 0.05
epsilon_decay = 0.99
gamma = 0.95
batch_size = 32
memory = deque(maxlen=5000)

episodes = 500

for episode in range(episodes):
    print("Episode " + str(episode) + " starting...")
    input_data = env.reset()
    game_state = np.array(input_data[:53]).reshape(1, -1)
    is_game_over = bool(input_data[55])
    total_reward = 0

    if episode >= 400:
        env.showaiplay(True)

    while (not is_game_over):

        ai_action = np.zeros(7)
        if (np.random.rand() <= epsilon):
            ai_action = np.random.uniform(-1, 1, 7)
        else:
            ai_action = model_tf(game_state, training=False).numpy()[0]

        output = SpaceShooter_IA.AIDataOutput()

        output.up = ai_action[0] > 0
        output.down = ai_action[1] > 0
        output.right = ai_action[2] > 0
        output.left = ai_action[3] > 0
        output.shoot = ai_action[4] > 0
        output.x = int(ai_action[5]) 
        output.y = int(ai_action[6])

        next_data = env.step(output)
        next_game_state = np.array(next_data[:53]).reshape(1, -1)
        is_game_over = bool(next_data[55])
        reward = next_data[53]
        total_reward += reward

        memory.append((game_state, ai_action, reward, next_game_state, is_game_over))
        game_state = next_game_state

        if(len(memory) > batch_size):
            random_batch = random.sample(memory, batch_size)

            states = np.array([b[0][0] for b in random_batch])
            actions = np.array([b[1] for b in random_batch])
            rewards = np.array([b[2] for b in random_batch])
            next_states = np.array([b[3][0] for b in random_batch])
            dones = np.array([b[4] for b in random_batch])

            futur_preds = model_tf.predict(next_states, verbose=0)

            targets = np.copy(actions)

            for i in range(batch_size):
                if dones[i]:
                    target_reward = rewards[i]
                else:
                    target_reward = rewards[i] + gamma * np.max(futur_preds[i])

                targets[i] += target_reward * 0.1

            model_tf.fit(states, targets, epochs=1, verbose=0)

    if epsilon > epsilon_min:
        epsilon *= epsilon_decay

    print(f"Épisode: {episode+1}/{episodes} | Récompense: {total_reward} | Epsilon: {epsilon:.2f}")