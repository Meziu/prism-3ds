#include "main.h"

int currentScene;
int clearColor;

C3D_RenderTarget* top_screen;
C3D_RenderTarget* bottom_screen;

u32 kDown;

// prints debug info
void checkSystemStatus()
{
	printf("\x1b[1;1HSprites: %zu/%u\x1b[K", numSprites, MAX_SPRITES);
	printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
	printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
}


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

void renderScene()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(bottom_screen, clearColor);
	C2D_TargetClear(top_screen, clearColor);

	C2D_SceneBegin(top_screen);
	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		if (sprites[i].used && sprites[i].screen == TOP_SCREEN)
			C2D_DrawSprite(&sprites[i].spr);
	}
	renderScreenText(TOP_SCREEN);
		
	C2D_SceneBegin(bottom_screen);
	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		if (sprites[i].used && sprites[i].screen == BOT_SCREEN)
			C2D_DrawSprite(&sprites[i].spr);
	}
	renderScreenText(BOT_SCREEN);
	C3D_FrameEnd(0);
}


int main()
{
	srand(time(NULL));
	
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	//consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	top_screen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom_screen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);


	initTextEnv();

	mainMenuInit();

	// Main loop
	while (aptMainLoop())
	{

		hidScanInput();

		// Respond to user input
		kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		checkSystemStatus();

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

	// Delete graphics
	C2D_SpriteSheetFree(spriteSheet);

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}
