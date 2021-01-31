#pragma once

#include <3ds.h>
#include "little3ds.h"
#include "bullet.h"

typedef struct 
{
    Vector2D position;
    CollisionBox hitBox;

    int shootingTimer;

    Sprite* prism_sprite;
} Player;

extern Player player;

void initPlayer();

void playerHit();

void playerProcess();
