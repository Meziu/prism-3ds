#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "little3ds.h"
#include "main.h"
#include "player.h"
#include "enemySpawner.h"

#define GAME_BG_COLOR           C2D_Color32f(0.117f, 0.0f, 0.27f, 1.0f)
#define ENDSCREEN_BG_COLOR      C2D_Color32f(0.68627451f, 0.0f, 0.0f, 1.0f)
#define INTERMISSION_BG_COLOR   C2D_Color32f(0.0f, 0.68627451f, 0.0f, 1.0f)

#define DIF_EZ         0
#define DIF_NORMIE     1
#define DIF_PRO        2

#define CHN_ENEMY_SHOOT  1
#define CHN_PLAYER_HURT  2
#define CHN_EXPLOSION    3
#define CHN_PLAYER_SHOOT 4

#define PLAYER_SPRITE   0
#define ALIEN_SPRITE    1
#define BULLET_SPRITE   2
#define BULLET_E_SPRITE 3
#define LIFE_SPRITE     4
#define SHOOTER_SPRITE  5

// these values are divided in 2 categories, "arcade" and "game"
// arcade values are temporary values used for the current match that's being played
// game values are saved and stored values between matches in the savefile

extern int arcade_currentLevel;
extern int arcade_currentScore;
extern int arcade_currentKillCounter;
extern int arcade_currentCoins;
extern int arcade_currentLives;

extern int game_chosenDifficulty;
extern int game_highScore;
extern int game_totalCoins;

extern NathanMusic explosion;
extern NathanMusic enemyShoot;
extern NathanMusic playerShoot;
extern NathanMusic playerHurt;

void setDefaultArcadeValues();

void readGameValues();
void storeGameValues();

void gameInit();
void gameProcess();

void endMatch();
void endMatchProcess();

void intermissionWait();
void intermissionProcess();
