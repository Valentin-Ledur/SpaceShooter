import SpaceShooter_IA

env = SpaceShooter_IA.Game()
obs = env.reset()

print("Initialisation réussie !")
print(f"Taille du vecteur d'observation : {len(obs)}")
print(f"Contenu initial : {obs}")

# Test d'une action
action = SpaceShooter_IA.AIDataOutput()
action.up = True
action.shoot = False
action.x = 450
action.y = 450

next_obs = env.step(action)
print(f"Pas de simulation effectué. Données reçues : {next_obs[-3:]}")