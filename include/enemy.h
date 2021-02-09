#pragma once

#include "little3ds.h"
#include "player.h"
#include "enemySpawner.h"

#define ALIEN_MAX 21
#define SHOOTER_MAX 10

#define MOVEMENT_LIMIT_LEFT 40
#define MOVEMENT_LIMIT_RIGHT 360

typedef struct 
{
    Vector2D position;
    int velocity;
    CollisionBox alienBox;

    uint16_t movementTimer;

    bool alive;

    uint8_t railID;
    Sprite* alien_sprite;
} Alien;

typedef struct 
{
    Vector2D position;
    float velocity;
    CollisionBox shooterBox;

    uint16_t movementTimer;
    uint16_t shootingTimer;
    uint8_t animationCount;

    bool alive;

    uint8_t railID;
    Sprite* shooter_sprite;
} Shooter;

extern Alien aliens[ALIEN_MAX];
extern Shooter shooters[SHOOTER_MAX];

extern uint8_t alienCount;
extern uint8_t shooterCount;

extern C2D_SpriteSheet shooterAnimations;

Alien* newAlien(int prailID);
Shooter* newShooter(int prailID);

void killAlien(Alien* a);
void killShooter(Shooter* s);
void killAllEnemies();

void aliensProcess();
void shootersProcess();
