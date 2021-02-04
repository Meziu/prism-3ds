#include "player.h"

Player player;
Sprite* lives[3];

void initPlayer()
{
    player.position = createVector2D(BOT_SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    player.prism_sprite = newSprite(BOT_SCREEN, PLAYER_SPRITE, player.position, 0);
    player.shootingTimer = 40;
    player.hitBox = newCollisionBox(player.position, createVector2D(32,22));

    lives[0] = newSprite(TOP_SCREEN, LIFE_SPRITE, createVector2D(360, 20), 0);
    
    if (arcade_currentLives > 1)
        lives[1] = newSprite(TOP_SCREEN, LIFE_SPRITE, createVector2D(330, 20), 0);
    if (arcade_currentLives > 2)
        lives[2] = newSprite(TOP_SCREEN, LIFE_SPRITE, createVector2D(300, 20), 0);
    
}

void playerProcess()
{
    touchPosition touch;
    hidTouchRead(&touch);

    circlePosition pad;
    hidCircleRead(&pad);
    Vector2D padVec = createVector2D(pad.dx, pad.dy);
    
    if (touch.px != 0 && touch.py != 0)
    {
        Vector2D relativeTouch = {touch.px - player.position.x,
                                  touch.py - player.position.y};

        Vector2D velocity = {getVector2DNormalized(&relativeTouch).x * 2,
                             getVector2DNormalized(&relativeTouch).y * 2};

        if (abs(relativeTouch.x) > 3)
        {
            player.position.x += velocity.x;
        }
        if (abs(relativeTouch.y) > 3)
        {
            player.position.y += velocity.y;
        }
    }
    else if (getVector2DLength(&padVec) > 30)
    {
        Vector2D padVec = createVector2D(pad.dx, pad.dy);

        Vector2D velocity = {getVector2DNormalized(&padVec).x * 2,
                             getVector2DNormalized(&padVec).y * 2};

        player.position.x += velocity.x;
        player.position.y -= velocity.y;
    }

    if (player.position.y > SCREEN_HEIGHT)
        player.position.y = SCREEN_HEIGHT;
    else if (player.position.y < 0)
        player.position.y = 0;
    
    if (player.position.x > BOT_SCREEN_WIDTH)
        player.position.x = BOT_SCREEN_WIDTH;
    else if (player.position.x < 0)
        player.position.x = 0;
    

    player.hitBox.position = player.position;

    player.shootingTimer--;
    if (player.shootingTimer == 0)
    {
        player.shootingTimer = 40;
        newBullet(createVector2D(player.position.x, player.position.y-10) , true, BOT_SCREEN);
        nathanPlaySound(&playerShoot, CHN_PLAYER_SHOOT);
    }

    C2D_SpriteSetPos(&player.prism_sprite->spr, (int)player.position.x, (int)player.position.y);
}

void playerHit()
{
    arcade_currentLives--;
    killSprite(lives[arcade_currentLives]);
    if (arcade_currentLives <= 0)
    {
        changeScene(SCENE_ENDGAME);
        return;
    }
    nathanPlaySound(&playerHurt, CHN_PLAYER_HURT);
}
