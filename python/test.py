import SpaceShooter_IA
from model import *

import os
import numpy as np
import math
import tqdm
import tensorflow as tf
import keras
from keras import Sequential, layers, Input
from keras.layers import LeakyReLU
from keras.optimizers import Adam
from keras.losses import Huber
from keras import Model
from collections import deque


gpus = tf.config.list_physical_devices('GPU')
if gpus:
    try:
        for gpu in gpus:
            tf.config.experimental.set_memory_growth(gpu, True)
    except RuntimeError as e:
        print(e)

model = make_model()

if os.path.isfile("python/ai_model.keras"):
    print("Loading model from", "python/ai_model.keras")
    model.load_weights("python/ai_model.keras")
else:
    print("no model to load")

env = SpaceShooter_IA.Game()
env.showaiplay(True)

model_inputs = SpaceShooter_IA.AIDataInput()
model_inputs = env.reset()
tensor = keras.ops.convert_to_tensor(model_inputs.obs)
tensor = keras.ops.expand_dims(tensor, 0)
move_output, shoot_output = model(tensor, training=False)
move_output = np.array((keras.ops.argmax(move_output[0])))
shoot_output = np.array((keras.ops.argmax(shoot_output[0])))

while True:
    model_inputs = env.step(OutputDataFromActions(move_output, shoot_output))
    tensor = keras.ops.convert_to_tensor(model_inputs.obs)
    tensor = keras.ops.expand_dims(tensor, 0)
    move_output, shoot_output = model(tensor, training=False)
    move_output = np.array((keras.ops.argmax(move_output[0])))
    shoot_output = np.array((keras.ops.argmax(shoot_output[0])))






