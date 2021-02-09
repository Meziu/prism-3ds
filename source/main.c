#include "main.h"

uint8_t currentScene;

C2D_SpriteSheet general_spritesheet;

u32 kDown;

void killEverything()
{
	killAllEnemies();
	killAllBullets();
	killAllText();
	killAllSprites();
}

void changeScene(uint8_t new_scene)
{
	killEverything();
	
	currentScene = new_scene;

	if (new_scene == SCENE_MENU)
	{
		mainMenuInit();
		return;
	}
	else if (new_scene == SCENE_GAME)
	{
		gameInit();
		return;
	}
	else if (new_scene == SCENE_ENDGAME)
	{
		endMatch();
		return;
	}
	else if (new_scene == SCENE_INTERMISSION)
	{
		intermissionWait();
		return;
	}

	// in case the new scene's ID isn't recognized
	currentScene = SCENE_MENU;
	mainMenuInit();
}

int main()
{
	srand(time(NULL));

	romfsInit();
	nathanInit3dsSound();
	
	general_spritesheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	shooterAnimations = C2D_SpriteSheetLoad("romfs:/gfx/shootersprites.t3x");

	newFont("romfs:/gfx/arcade.bcfnt");
	initAllGraphics();

	mainMenuInit();

	// Main loop
	while (aptMainLoop())
	{

		hidScanInput();

		kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break to return to hbmenu

		if (currentScene == SCENE_MENU)
			mainMenuProcess();
		else if (currentScene == SCENE_GAME)
			gameProcess();
		else if (currentScene == SCENE_ENDGAME)
			endMatchProcess();
		else if (currentScene == SCENE_INTERMISSION)
			intermissionProcess();

		renderScene();
		
	}

	ndspExit();
	destroyAllGraphics();
	romfsExit();
	return 0;
}
