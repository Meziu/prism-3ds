#pragma once

#include <3ds.h>
#include "sprite.h"
#include "vector2D.h"
#include "bullet.h"
#include "collision.h"

typedef struct 
{
    Vector2D position;
    CollisionBox hitBox;

    int shootingTimer;

    int prism_spriteID;
} Player;

extern Player player;

void initPlayer();

void playerHit();

void playerProcess();