#pragma once

#include "graphics.h"
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

    Sprite* bullet_sprite;
} Bullet;

extern Bullet bulletList[MAX_BULLETS];
extern size_t bulletCount;

Bullet* newBullet(Vector2D pos, bool p_friendly, bool p_screen);

void bulletsProcess();
void bulletCheckCollisions(Bullet* b);

void killBullet(Bullet* b);
void killAllBullets();
