#ifndef __AI_DATA__
#define __AI_DATA__

#include <vector>

typedef struct AIDataInput
{
    std::vector<float> observation;
    float reward = 0.0f;
    bool done = false;
    int score = 0;
} AIDataInput;

typedef struct AIDataOutput
{
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool shoot = false;
    int x = 0;
    int y = 0;
} AIDataOutput;

#endif