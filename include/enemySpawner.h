#pragma once

#include "enemy.h"
#include "game.h"

#define ALIEN_CHANCE 0.08f
#define SHOOTER_CHANCE 0.03f

#define SHOOTER_TYPE false
#define ALIEN_TYPE true

#define RAIL_SHOOTER_1 55
#define RAIL_SHOOTER_2 95

#define RAIL_NORMAL_1 132
#define RAIL_NORMAL_2 164
#define RAIL_NORMAL_3 196


typedef struct
{
    int y_pos;
    bool enemyType;

    size_t counter;
} Rail;


extern Rail shooterRails[2];
extern Rail alienRails[3];

void enemySpawner();

void setLimits();
void updateLimits();
