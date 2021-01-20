#include "enemy.h"

Alien aliens[ALIEN_MAX];
Shooter shooters[SHOOTER_MAX];

size_t alienCount;
size_t shooterCount;

int newAlien(int p_railID)
{
    for (size_t i=0; i<ALIEN_MAX; i++)
    {
        if (!aliens[i].alive)
        {
            aliens[i].position.y = alienRails[p_railID].y_pos;
            alienRails[p_railID].counter++;
            
            if ((float)rand()/(float)RAND_MAX < 0.5f)
            {
                aliens[i].position.x = -30;
                aliens[i].velocity = 2;
            }
            else
            {
                aliens[i].position.x = 430;
                aliens[i].velocity = -2;
            }

            aliens[i].alien_spriteID = newSprite(TOP_SCREEN, ALIEN_SPRITE, aliens[i].position, 0);

            aliens[i].alienBox = newCollisionBox(aliens[i].position, createVector2D(32, 32));

            aliens[i].alive = true;
            aliens[i].movementTimer = 120;
            aliens[i].railID = p_railID;

            alienCount++;
            return i;
        }
    }
    return -1;
}

int newShooter(int p_railID)
{
    for (size_t i=0; i<SHOOTER_MAX; i++)
    {
        if (!shooters[i].alive)
        {
            shooters[i].position.y = shooterRails[p_railID].y_pos;
            shooterRails[p_railID].counter++;
            
            if ((float)rand()/(float)RAND_MAX < 0.5f)
            {
                shooters[i].position.x = -30;
                shooters[i].velocity = 2;
            }
            else
            {
                shooters[i].position.x = 430;
                shooters[i].velocity = -2;
            }

            shooters[i].shooter_spriteID = newSprite(TOP_SCREEN, SHOOTER_SPRITE, shooters[i].position, 0);

            shooters[i].shooterBox = newCollisionBox(shooters[i].position, createVector2D(32, 32));

            shooters[i].alive = true;
            shooters[i].movementTimer = 120;
            shooters[i].shootingTimer = 102;
            shooters[i].animationCount = 0;
            shooters[i].railID = p_railID;

            shooterCount++;
            return i;
        }
    }
    return -1;
}


void updateAlienSprite(int p_alienID)
{
    C2D_SpriteSetPos(&sprites[aliens[p_alienID].alien_spriteID].spr, (int)aliens[p_alienID].position.x, (int)aliens[p_alienID].position.y);
}

void updateShooterSprite(int p_shooterID)
{   
    shooters[p_shooterID].animationCount = 0;
    
    if (shooters[p_shooterID].shootingTimer <= 11)
    {
        shooters[p_shooterID].animationCount = 11-shooters[p_shooterID].shootingTimer;
    }

    C2D_SpriteFromSheet(&sprites[shooters[p_shooterID].shooter_spriteID].spr, spriteSheet, shooters[p_shooterID].animationCount+SHOOTER_SPRITE);
    C2D_SpriteSetCenter(&sprites[shooters[p_shooterID].shooter_spriteID].spr, 0.5f, 0.5f);
    C2D_SpriteSetPos(&sprites[shooters[p_shooterID].shooter_spriteID].spr, (int)shooters[p_shooterID].position.x, (int)shooters[p_shooterID].position.y);
}

int alienMove(int p_alienID)
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
            float relative = shooters[i].position.x - aliens[p_alienID].position.x;
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
            if (aliens[i].movementTimer == 0)
            {
                aliens[i].velocity = alienMove(i);
                aliens[i].movementTimer = 120;
            }
            aliens[i].movementTimer--;
            aliens[i].position.x += aliens[i].velocity;
            

            int rightLimit = MOVEMENT_LIMIT_RIGHT - (sprites[aliens[i].alien_spriteID].spr.params.pos.w / 2.0f);

            if ((aliens[i].position.x > rightLimit) && (aliens[i].velocity > 0))
            {
                aliens[i].position.x = rightLimit;
            }

            
            int leftLimit = MOVEMENT_LIMIT_LEFT + (sprites[aliens[i].alien_spriteID].spr.params.pos.w / 2.0f);

            if ((aliens[i].position.x < leftLimit) && (aliens[i].velocity < 0))
            {
                aliens[i].position.x = leftLimit;
            }

            updateAlienSprite(i);
            aliens[i].alienBox.position = aliens[i].position;

        }
    }
}

void shootersProcess()
{
    for (size_t i=0; i<SHOOTER_MAX; i++)
    {
        if (shooters[i].alive)
        {
            if (shooters[i].movementTimer == 0)
            {
                shooters[i].velocity = sign(player.position.x - shooters[i].position.x) * 0.5f;
                shooters[i].movementTimer = 120;
            }
            shooters[i].movementTimer--;

            if (shooters[i].shootingTimer == 0)
            {
                newBullet(createVector2D(shooters[i].position.x, shooters[i].position.y+20), false, TOP_SCREEN);
                shooters[i].shootingTimer = 102;
            }
            shooters[i].shootingTimer--;

            shooters[i].position.x += shooters[i].velocity;

            
            int rightLimit = MOVEMENT_LIMIT_RIGHT - (sprites[shooters[i].shooter_spriteID].spr.params.pos.w / 2.0f);

            if ((shooters[i].position.x > rightLimit) && (shooters[i].velocity > 0))
            {
                aliens[i].position.x = rightLimit;
            }
            
            int leftLimit = MOVEMENT_LIMIT_LEFT + (sprites[shooters[i].shooter_spriteID].spr.params.pos.w / 2.0f);

            if ((shooters[i].position.x < leftLimit) && (shooters[i].velocity < 0))
            {
                shooters[i].position.x = leftLimit;
            }
            
            
            updateShooterSprite(i);
            shooters[i].shooterBox.position = shooters[i].position;

        }
    }
}


void killAlien(int p_alienID)
{
    aliens[p_alienID].alive = false;
    killSprite(aliens[p_alienID].alien_spriteID);
    alienCount--;

    alienRails[aliens[p_alienID].railID].counter--;
}

void killShooter(int p_shooterID)
{
    shooters[p_shooterID].alive = false;
    killSprite(shooters[p_shooterID].shooter_spriteID);
    shooterCount--;

    shooterRails[shooters[p_shooterID].railID].counter--;
}

void killAllEnemies()
{
    for (int i=0; i<ALIEN_MAX; i++)
    {
        if (aliens[i].alive)
            killAlien(i);
    }
    for (int i=0; i<SHOOTER_MAX; i++)
    {
        if (shooters[i].alive)
            killShooter(i);
    }
}
