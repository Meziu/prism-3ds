#pragma once

#include "sprite.h"
#include "vector2D.h"
#include "player.h"
#include "enemySpawner.h"
#include "collision.h"

#define ALIEN_MAX 21
#define SHOOTER_MAX 10

#define MOVEMENT_LIMIT_LEFT 40
#define MOVEMENT_LIMIT_RIGHT 360

typedef struct 
{
    Vector2D position;
    int velocity;
    CollisionBox alienBox;

    int movementTimer;

    bool alive;

    int railID;
    int alien_spriteID;
    int alienID;
} Alien;

typedef struct 
{
    Vector2D position;
    float velocity;
    CollisionBox shooterBox;

    int movementTimer;
    int shootingTimer;
    int animationCount;

    bool alive;

    int railID;
    int shooter_spriteID;
    int shooterID;
} Shooter;

extern Alien aliens[ALIEN_MAX];
extern Shooter shooters[SHOOTER_MAX];

extern size_t alienCount;
extern size_t shooterCount;

int newAlien(int prailID);
int newShooter(int prailID);

void killAlien(int p_alienID);
void killShooter(int p_shooterID);
void killAllEnemies();

void aliensProcess();
void shootersProcess();
