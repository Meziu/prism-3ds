#pragma once

#include "sprite.h"
#include "vector2D.h"
#include "collision.h"
#include "enemy.h"
#include "game.h"

#define MAX_BULLETS 30

typedef struct
{
    Vector2D position;
    CollisionBox bulletBox;

    bool friendly;

    bool fired;

    bool currentScreen;

    int bullet_spriteID;
    int bulletID;
} Bullet;

extern Bullet bulletList[MAX_BULLETS];
extern size_t bulletCount;

int newBullet(Vector2D pos, bool p_friendly, bool p_screen);
void bulletsProcess();
void bulletCheckCollisions(int p_bulletID);

void killBullet(int p_bulletID);
void killAllBullets();
