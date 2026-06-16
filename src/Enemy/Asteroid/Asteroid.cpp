#include <cmath>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Enemy/Asteroid/AsteroidType.hpp"
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

    if (size == 1)
    {
        trail = true;
        type = BASIC_TRAIL;
        angle = atan2(direction.y, direction.x) * 180.0 / M_PI;

        int random_type = Utils::Random(0, 4) * 2;
        if (random_type == 0)
            type = BASIC_TRAIL;
        else if (random_type == 1)
            type = BROWN_TRAIL;
        else
            type = ICE_TRAIL;
    }
    else
    {
        int random_type = Utils::Random(0, 4);
        if (random_type == 0)
            type = BASIC;
        else if (random_type == 1)
            type = BROWN;
        else
            type = ICE;

        rotation_speed = Utils::Random(-5, 5);
    }
}

Asteroid::Asteroid(int _size, SDL_Point _position, AsteroidType _type)
{
    size = _size - 1;
    direction = {Utils::Random(-10, 10), Utils::Random(-10, 10)};

    if (size == 1)
    {
        trail = true;
        angle = atan2(direction.y, direction.x) * 180.0 / M_PI;

        switch (_type)
        {
        case BASIC:
            type = BASIC_TRAIL;
            break;

        case BROWN:
            type = BROWN_TRAIL;
            break;

        default:
            type = ICE_TRAIL;
            break;
        }
    }
    else
    {
        rotation_speed = Utils::Random(-5, 5);
        type = _type;
    }

    position = _position;
}

void Asteroid::Move()
{
    position.x += direction.x;
    position.y += direction.y;
    angle += rotation_speed;
}