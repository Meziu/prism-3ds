#include "sprite.h"

C2D_SpriteSheet spriteSheet;
Sprite sprites[MAX_SPRITES];
size_t numSprites = 0;

int newSprite(bool pscreen, int usedFrame, Vector2D pos, int angle)
{
    for (int i = 0; i < MAX_SPRITES; i++)
	{
        if (!sprites[i].used)
        {
            Sprite* newSprite = &sprites[i];

            newSprite->used = true;
            newSprite->screen = pscreen;

            // Random image, position, rotation and speed
            C2D_SpriteFromSheet(&newSprite->spr, spriteSheet, usedFrame);
            C2D_SpriteSetCenter(&newSprite->spr, 0.5f, 0.5f);
            C2D_SpriteSetPos(&newSprite->spr, (int)pos.x, (int)pos.y);
            
            C2D_SpriteSetRotation(&newSprite->spr, C3D_Angle(angle));

            numSprites++;
            return i;
        }
    }
    svcBreak(USERBREAK_PANIC);
    return -1;
}

void killSprite(int spriteID)
{
    sprites[spriteID].used = false;
    numSprites--;
}

void killAllSprites()
{
    for (int i = 0; i < MAX_SPRITES; i++)
	{
        killSprite(i);
    }
}
