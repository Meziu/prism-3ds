#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "player.h"
#include "enemySpawner.h"

#define GAME_BG_COLOR           C2D_Color32f(0.117f, 0.0f, 0.27f, 1.0f)
#define ENDSCREEN_BG_COLOR      C2D_Color32f(0.68627451f, 0.0f, 0.0f, 1.0f)
#define INTERMISSION_BG_COLOR   C2D_Color32f(0.0f, 0.68627451f, 0.0f, 1.0f)

#define DIF_EZ         0
#define DIF_NORMIE     1
#define DIF_PRO        2

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


void setDefaultArcadeValues();

void readGameValues();
void storeGameValues();

void gameInit();
void gameProcess();

void endMatch();
void endMatchProcess();

void intermissionWait();
void intermissionProcess();
