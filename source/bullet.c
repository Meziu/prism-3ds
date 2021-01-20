#include "bullet.h"

Bullet bulletList[MAX_BULLETS];
size_t bulletCount;

int newBullet(Vector2D pos, bool p_friendly, bool p_screen)
{
    for (size_t i=0; i<MAX_BULLETS; i++)
    {
        if (!bulletList[i].fired)
        {
            bulletList[i].position = pos;
            bulletList[i].currentScreen = p_screen;
            bulletList[i].bulletID = i;
            bulletList[i].friendly = p_friendly;
            
            if (p_friendly)
            {
                bulletList[i].bullet_spriteID = newSprite(p_screen, BULLET_SPRITE, pos, 0);
            }
            else
            {
                bulletList[i].bullet_spriteID = newSprite(p_screen, BULLET_E_SPRITE, pos, 0);
            }
            
            bulletList[i].bulletBox = newCollisionBox(pos, createVector2D(12, 20));

            bulletList[i].fired = true;

            bulletCount++;

            return i;
        }
    }
    return -1;
}


void updateBulletSprite(int p_bulletID)
{
    C2D_SpriteSetPos(&sprites[bulletList[p_bulletID].bullet_spriteID].spr, (int)bulletList[p_bulletID].position.x, (int)bulletList[p_bulletID].position.y);
    sprites[bulletList[p_bulletID].bullet_spriteID].screen = bulletList[p_bulletID].currentScreen;
}

void bulletScreenWarp(int p_bulletID)
{
    if (bulletList[p_bulletID].friendly)
    {
        if (bulletList[p_bulletID].position.y < -30)
        {
            if (bulletList[p_bulletID].currentScreen == TOP_SCREEN)
                killBullet(p_bulletID);
            else if (bulletList[p_bulletID].currentScreen == BOT_SCREEN)
            {
                bulletList[p_bulletID].currentScreen = TOP_SCREEN;
                bulletList[p_bulletID].position.y = SCREEN_HEIGHT+10;
                bulletList[p_bulletID].position.x += 40;
            }
        }
    }
    else
    {
        if (bulletList[p_bulletID].position.y > SCREEN_HEIGHT+30)
        {
            if (bulletList[p_bulletID].currentScreen == TOP_SCREEN)
            {
                bulletList[p_bulletID].currentScreen = BOT_SCREEN;
                bulletList[p_bulletID].position.y = -10;
                bulletList[p_bulletID].position.x -= 40;
            }
            else if (bulletList[p_bulletID].currentScreen == BOT_SCREEN)
            {
                killBullet(p_bulletID);
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
            bulletScreenWarp(i);

            if ((bulletList[i].currentScreen == TOP_SCREEN && bulletList[i].friendly) ||
                (bulletList[i].currentScreen == BOT_SCREEN && !bulletList[i].friendly))
            {
                bulletCheckCollisions(i);
            }
            

            bulletList[i].friendly ? (bulletList[i].position.y -= 3) : (bulletList[i].position.y += 3);

            updateBulletSprite(i);
        }
    }
}

void bulletCheckCollisions(int p_bulletID)
{
    bulletList[p_bulletID].bulletBox.position = bulletList[p_bulletID].position;

    if (bulletList[p_bulletID].friendly)
    {
        for (size_t a=0; a<ALIEN_MAX; a++)
        {
            if (aliens[a].alive)
            {
                bool collision = checkCollision(&bulletList[p_bulletID].bulletBox, &aliens[a].alienBox);
                if (collision)
                {
                    killAlien(a);
                    killBullet(p_bulletID);
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
                bool collision = checkCollision(&bulletList[p_bulletID].bulletBox, &shooters[s].shooterBox);
                if (collision)
                {
                    killShooter(s);
                    killBullet(p_bulletID);
                    arcade_currentKillCounter++;
                    arcade_currentScore += 100;
                    return;
                }
            }
        }
    }
    else
    {
        bool collision = checkCollision(&bulletList[p_bulletID].bulletBox, &player.hitBox);
        if (collision)
        {
            killBullet(p_bulletID);
            playerHit();
            return;
        }
    }
    
}

void killBullet(int p_bulletID)
{
    killSprite(bulletList[p_bulletID].bullet_spriteID);
    bulletList[p_bulletID].fired = false;

    bulletCount--;
}

void killAllBullets()
{
    for (int i=0; i<MAX_BULLETS; i++)
    {
        killBullet(i);
    }
}
