import SpaceShooter_IA

from keras import Sequential, layers, Input, Model
from keras.layers import LeakyReLU
import math

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
# num_shoot_actions = 37
num_shoot_actions = 9

num_parameters = 54

def make_model():
    inputs = Input(shape=(num_parameters,))

    x = layers.Dense(256)(inputs)
    x = LeakyReLU()(x)
    x = layers.Dense(256)(x)
    x = LeakyReLU()(x)

    x = layers.Dense(128)(x)
    x = LeakyReLU()(x)

    move = layers.Dense(128)(x)
    move = LeakyReLU()(move)

    shoot = layers.Dense(128)(x)
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

        angle_deg = shoot_action * 45.0 # avant 10
        angle_rad = math.radians(angle_deg)

        output.x = math.cos(angle_rad)
        output.y = math.sin(angle_rad)
    else:
        output.shoot = False
        output.x = 0
        output.y = 0

    return output