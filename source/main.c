#include "main.h"

int currentScene;

u32 kDown;

void killEverything()
{
	killAllEnemies();
	killAllBullets();
	killAllText();
	killAllSprites();
}

void changeScene(int new_scene)
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

	NathanMusic senzanome;
	nathanLoadSoundEffect(&senzanome, "romfs:/audio/senza_nome.ogg");

	nathanInit3dsChannel(1);
	nathanMakeChannelMono(1);
	nathanPlaySound(&senzanome, 1);

	newFont("romfs:/gfx/arcade.bcfnt");
	initAllGraphics();

	mainMenuInit();

	// Main loop
	while (aptMainLoop())
	{

		hidScanInput();

		// Respond to user input
		kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

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

	nathanFreeMusic(&senzanome);
	ndspExit();
	destroyAllGraphics();
	romfsExit();
	return 0;
}
