#include "enemy.h"

Alien aliens[ALIEN_MAX];
Shooter shooters[SHOOTER_MAX];

uint8_t alienCount;
uint8_t shooterCount;

C2D_SpriteSheet shooterAnimations;

Alien* newAlien(int p_railID)
{
    for (size_t i=0; i<ALIEN_MAX; i++)
    {
        if (!aliens[i].alive)
        {
            Alien* nAlien = &aliens[i];

            nAlien->position.y = alienRails[p_railID].y_pos;
            alienRails[p_railID].counter++;
            
            if ((float)rand()/(float)RAND_MAX < 0.5f)
            {
                nAlien->position.x = -30;
                nAlien->velocity = 2;
            }
            else
            {
                nAlien->position.x = 430;
                nAlien->velocity = -2;
            }

            nAlien->alien_sprite = newSprite(TOP_SCREEN, &general_spritesheet, ALIEN_SPRITE, nAlien->position, 0);

            nAlien->alienBox = newCollisionBox(nAlien->position, createVector2D(32, 32));

            nAlien->alive = true;
            nAlien->movementTimer = 120;
            nAlien->railID = p_railID;

            alienCount++;
            return nAlien;
        }
    }
    return NULL;
}

Shooter* newShooter(int p_railID)
{
    for (size_t i=0; i<SHOOTER_MAX; i++)
    {
        if (!shooters[i].alive)
        {
            Shooter* nShooter = &shooters[i];

            nShooter->position.y = shooterRails[p_railID].y_pos;
            shooterRails[p_railID].counter++;
            
            if ((float)rand()/(float)RAND_MAX < 0.5f)
            {
                nShooter->position.x = -30;
                nShooter->velocity = 2;
            }
            else
            {
                nShooter->position.x = 430;
                nShooter->velocity = -2;
            }

            nShooter->shooter_sprite = newSprite(TOP_SCREEN, &shooterAnimations, 0, nShooter->position, 0);

            nShooter->shooterBox = newCollisionBox(nShooter->position, createVector2D(32, 32));

            nShooter->alive = true;
            nShooter->movementTimer = ((float)rand()/(float)RAND_MAX)*120;
            nShooter->shootingTimer = 102;
            nShooter->animationCount = 0;
            nShooter->railID = p_railID;

            shooterCount++;
            return nShooter;
        }
    }
    return NULL;
}


void updateAlienSprite(Alien* a)
{
    C2D_SpriteSetPos(&a->alien_sprite->spr, (int)a->position.x, (int)a->position.y);
}

void updateShooterSprite(Shooter* s)
{   
    s->animationCount = 0;
    
    if (s->shootingTimer <= 22)
    {
        s->animationCount = 22-(s->shootingTimer);
    }

    C2D_SpriteFromSheet(&s->shooter_sprite->spr, shooterAnimations, s->animationCount/2);
    C2D_SpriteSetCenter(&s->shooter_sprite->spr, 0.5f, 0.5f);
    C2D_SpriteSetPos(&s->shooter_sprite->spr, (int)s->position.x, (int)s->position.y);
}

int alienMove(Alien* a)
{
    if (shooterCount == 0)
    {
        return (((float)rand()/(float)RAND_MAX)<0.5 ? -1 : 1);
    }
    
    float lowest = 400;
    for (size_t i=0; i<SHOOTER_MAX; i++)
    {
        if (shooters[i].alive)
        {
            float relative = shooters[i].position.x - a->position.x;
            if (abs(lowest) > abs(relative))
            {
                lowest = relative;
            }
        }
    }
    return sign(lowest);
}

void aliensProcess()
{
    for (size_t i=0; i<ALIEN_MAX; i++)
    {
        if (aliens[i].alive)
        {
            Alien* curAlien = &aliens[i];

            if (curAlien->movementTimer == 0)
            {
                curAlien->velocity = alienMove(curAlien);
                curAlien->movementTimer = 120;
            }
            curAlien->movementTimer--;
            curAlien->position.x += curAlien->velocity;
            

            int rightLimit = MOVEMENT_LIMIT_RIGHT - (curAlien->alien_sprite->spr.params.pos.w / 2.0f);

            if ((curAlien->position.x > rightLimit) && (curAlien->velocity > 0))
            {
                curAlien->position.x = rightLimit;
            }

            
            int leftLimit = MOVEMENT_LIMIT_LEFT + (curAlien->alien_sprite->spr.params.pos.w / 2.0f);

            if ((curAlien->position.x < leftLimit) && (curAlien->velocity < 0))
            {
                curAlien->position.x = leftLimit;
            }

            updateAlienSprite(curAlien);
            curAlien->alienBox.position = curAlien->position;

        }
    }
}

void shootersProcess()
{
    for (size_t i=0; i<SHOOTER_MAX; i++)
    {
        if (shooters[i].alive)
        {
            Shooter* curShooter = &shooters[i];

            if (curShooter->movementTimer-- == 0)
            {
                curShooter->velocity = sign(player.position.x - curShooter->position.x) * 0.5f;
                curShooter->movementTimer = 120;
            }

            if (curShooter->shootingTimer-- == 0)
            {
                newBullet(createVector2D(curShooter->position.x, curShooter->position.y+20), false, TOP_SCREEN);
                curShooter->shootingTimer = 102;
                nathanPlaySound(&enemyShoot, CHN_ENEMY_SHOOT);
            }

            curShooter->position.x += curShooter->velocity;

            
            int rightLimit = MOVEMENT_LIMIT_RIGHT - (curShooter->shooter_sprite->spr.params.pos.w / 2.0f);

            if ((curShooter->position.x > rightLimit) && (curShooter->velocity > 0))
            {
                curShooter->position.x = rightLimit;
            }
            
            int leftLimit = MOVEMENT_LIMIT_LEFT + (curShooter->shooter_sprite->spr.params.pos.w / 2.0f);

            if ((curShooter->position.x < leftLimit) && (curShooter->velocity < 0))
            {
                curShooter->position.x = leftLimit;
            }
            
            
            updateShooterSprite(curShooter);
            curShooter->shooterBox.position = curShooter->position;
        }
    }
}


void killAlien(Alien* a)
{
    a->alive = false;
    killSprite(a->alien_sprite);
    alienCount--;

    alienRails[a->railID].counter--;
}

void killShooter(Shooter* s)
{
    s->alive = false;
    killSprite(s->shooter_sprite);
    shooterCount--;

    shooterRails[s->railID].counter--;
}

void killAllEnemies()
{
    for (int i=0; i<ALIEN_MAX; i++)
    {
        if (aliens[i].alive)
            killAlien(&aliens[i]);
    }
    for (int i=0; i<SHOOTER_MAX; i++)
    {
        if (shooters[i].alive)
            killShooter(&shooters[i]);
    }
}
