#pragma once

#include <3ds.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "little3ds.h"

#include "enemy.h"
#include "enemySpawner.h"
#include "bullet.h"
#include "game.h"
#include "main_menu.h"
#include "ogg/ogg.h"

#define SCENE_MENU          0
#define SCENE_GAME          1
#define SCENE_ENDGAME       2
#define SCENE_INTERMISSION  4

extern int currentScene;

extern u32 kDown;

void changeScene(int new_scene);
void killEverything();
