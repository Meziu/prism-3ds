#include "bullet.h"

Bullet bulletList[MAX_BULLETS];
size_t bulletCount;

Bullet* newBullet(Vector2D pos, bool p_friendly, bool p_screen)
{
    for (size_t i=0; i<MAX_BULLETS; i++)
    {
        if (!bulletList[i].fired)
        {
            Bullet* newBullet = &bulletList[i];

            newBullet->position      = pos;
            newBullet->currentScreen = p_screen;
            newBullet->friendly      = p_friendly;
            
            if (p_friendly)
            {
                newBullet->bullet_sprite = newSprite(p_screen, &general_spritesheet, BULLET_SPRITE, pos, 0);
            }
            else
            {
                newBullet->bullet_sprite = newSprite(p_screen, &general_spritesheet, BULLET_E_SPRITE, pos, 0);
            }
            
            newBullet->bulletBox = newCollisionBox(pos, createVector2D(12, 20));

            newBullet->fired = true;

            bulletCount++;

            return newBullet;
        }
    }
    return NULL;
}


void updateBulletSprite(Bullet* b)
{
    C2D_SpriteSetPos(&b->bullet_sprite->spr, (int)b->position.x, (int)b->position.y);
    b->bullet_sprite->screen = b->currentScreen;
}

void bulletScreenWarp(Bullet* b)
{
    if (b->friendly)
    {
        if (b->position.y < -30)
        {
            if (b->currentScreen == TOP_SCREEN)
                killBullet(b);
            else if (b->currentScreen == BOT_SCREEN)
            {
                b->currentScreen = TOP_SCREEN;
                b->position.y = SCREEN_HEIGHT+10;
                b->position.x += 40;
            }
        }
    }
    else
    {
        if (b->position.y > SCREEN_HEIGHT+30)
        {
            if (b->currentScreen == TOP_SCREEN)
            {
                b->currentScreen = BOT_SCREEN;
                b->position.y = -10;
                b->position.x -= 40;
            }
            else if (b->currentScreen == BOT_SCREEN)
            {
                killBullet(b);
            }
        }
    }
}

void bulletsProcess()
{
    for (size_t i=0; i<MAX_BULLETS; i++)
    {
        if (bulletList[i].fired)
        {
            Bullet* curBullet = &bulletList[i];

            bulletScreenWarp(curBullet);

            if ((curBullet->currentScreen == TOP_SCREEN && curBullet->friendly) ||
                (curBullet->currentScreen == BOT_SCREEN && !curBullet->friendly))
            {
                bulletCheckCollisions(curBullet);
            }
            

            curBullet->friendly ? (curBullet->position.y -= 3) : (curBullet->position.y += 3);

            updateBulletSprite(curBullet);
        }
    }
}

void bulletCheckCollisions(Bullet* b)
{
    b->bulletBox.position = b->position;

    if (b->friendly)
    {
        for (size_t a=0; a<ALIEN_MAX; a++)
        {
            if (aliens[a].alive)
            {
                Alien* curHitAlien = &aliens[a];

                bool collision = checkCollision(&b->bulletBox, &curHitAlien->alienBox);
                if (collision)
                {
                    killAlien(curHitAlien);
                    nathanPlaySound(&explosion, CHN_EXPLOSION);
                    killBullet(b);
                    arcade_currentKillCounter++;
                    arcade_currentScore += 50;
                    return;
                }
            }
        }
        for (size_t s=0; s<SHOOTER_MAX; s++)
        {
            if (shooters[s].alive)
            {
                Shooter* curHitShooter = &shooters[s];

                bool collision = checkCollision(&b->bulletBox, &curHitShooter->shooterBox);
                if (collision)
                {
                    killShooter(curHitShooter);
                    killBullet(b);
                    nathanPlaySound(&explosion, CHN_EXPLOSION);
                    arcade_currentKillCounter++;
                    arcade_currentScore += 100;
                    return;
                }
            }
        }
    }
    else
    {
        bool collision = checkCollision(&b->bulletBox, &player.hitBox);
        if (collision)
        {
            killBullet(b);
            playerHit();
            return;
        }
    }
    
}

void killBullet(Bullet* b)
{
    killSprite(b->bullet_sprite);
    b->fired = false;

    bulletCount--;
}

void killAllBullets()
{
    for (int i=0; i<MAX_BULLETS; i++)
    {
        if (bulletList[i].fired)
            killBullet(&bulletList[i]);
    }
}
