#ifndef __AI_DATA__
#define __AI_DATA__

#include <vector>

typedef struct AIDataInput
{
    std::vector<float> obs;
    float training_score = 0.0f;
    bool done = false;
} AIDataInput;

typedef struct AIDataOutput
{
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool shoot = false;
    float x = 0;
    float y = 0;
} AIDataOutput;

#endif