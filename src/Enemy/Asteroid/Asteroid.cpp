#include "Utils/Utils.hpp"
#include "Enemy/Asteroid/Asteroid.hpp"

Asteroid::Asteroid(int _width, int _height)
{
    int initPos = Utils::Random(1, 5);
    size = Utils::Random(1, 4);

    switch (initPos)
    {
    case 1: // gauche
    {
        position.x = 0;
        position.y = Utils::Random(0, 10);
        direction.x = Utils::Random(1, 10);
        direction.y = Utils::Random(-10, 10);
    }
    break;
    case 2: // droit
    {
        position.x = _width;
        position.y = Utils::Random(0, _height);
        direction.x = -Utils::Random(1, 10);
        direction.y = Utils::Random(-10, 10);
    }
    break;

    case 3: // haut
    {
        position.x = Utils::Random(0, _width);
        position.y = 0;
        direction.x = Utils::Random(-10, 10);
        direction.y = Utils::Random(1, 10);
    }
    break;
    case 4: // bas
    {
        position.x = Utils::Random(0, _width);
        position.y = _height;
        direction.x = Utils::Random(-10, 10);
        direction.y = -Utils::Random(1, 10);
    }
    break;

    default: // erreur
        std::cout << "erreur random incorrect" << std::endl;
        break;
    }
}

Asteroid::Asteroid(int _size, SDL_Point _position)
{
    size = _size;
    position = _position;
    direction = {Utils::Random(-10, 10), Utils::Random(-10, 10)};
}