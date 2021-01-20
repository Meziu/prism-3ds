#pragma once

#include <citro2d.h>
#include <3ds.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "vector2D.h"
#include "sprite.h"
#include "player.h"
#include "enemy.h"
#include "enemySpawner.h"
#include "bullet.h"
#include "collision.h"
#include "game.h"
#include "text.h"
#include "main_menu.h"

#define SCENE_MENU          0
#define SCENE_GAME          1
#define SCENE_ENDGAME       2
#define SCENE_INTERMISSION  4

extern int clearColor;
extern int currentScene;

extern u32 kDown;

void changeScene(int new_scene);
void killEverything();
