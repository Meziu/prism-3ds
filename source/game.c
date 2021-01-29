#include "game.h"

int arcade_currentLevel;
int arcade_currentScore;
int arcade_currentKillCounter;
int arcade_currentKillNeeded;
int arcade_currentLives;
int arcade_currentCoins;

int game_chosenDifficulty;
int game_highScore;
int game_totalCoins;

int intermissionTimer;

Text* scoreText;
char scoreTextStr[20];

Text* killCounterText;
char killCounterTextStr[30];

Text* roundCounterText;
char roundCounterTextStr[20];

void setDefaultArcadeValues()
{
    arcade_currentLevel = 0;
    arcade_currentScore = 0;
    arcade_currentKillCounter = 0;
    arcade_currentKillNeeded = 5;
    arcade_currentLives = 3;
    arcade_currentCoins = 0;
}

void readGameValues()
{
    FILE* savefile_r;
    savefile_r = fopen("sdmc:/3ds/prism_savedata.txt", "r");

    if (savefile_r == NULL)
    {
        game_chosenDifficulty = DIF_NORMIE;
        game_highScore = 0;
        game_totalCoins = 0;

        fclose(savefile_r);
        
        storeGameValues();
        return;
    }

    char readData[100];
    fgets(readData, sizeof(readData), savefile_r);
    sscanf(readData, "%d %d %d", &game_chosenDifficulty, &game_highScore, &game_totalCoins);
    fclose(savefile_r);
}

void storeGameValues()
{
    FILE* savefile_w;
    savefile_w = fopen("sdmc:/3ds/prism_savedata.txt", "w");

    char writeData[100];

    if (game_highScore < arcade_currentScore)
        game_highScore = arcade_currentScore;

    game_totalCoins+=arcade_currentCoins;

    sprintf(writeData, "%d %d %d", game_chosenDifficulty, game_highScore, game_totalCoins);

    fputs(writeData, savefile_w);
    fclose(savefile_w);
}

void endMatch()
{
    storeGameValues();

    clearColor = ENDSCREEN_BG_COLOR;

    newText(createVector2D(TOP_SCREEN_WIDTH/2,50), 1.0f, TOP_SCREEN, WHITE_TEXT, C2D_AlignCenter, "YOU LOST YOU 4th\nDIMENSIONAL PIECE OF\nUNEXPLORED SPACE", 0, true);
    newText(createVector2D(TOP_SCREEN_WIDTH/2,180), 0.6f, TOP_SCREEN, WHITE_TEXT, C2D_AlignCenter, scoreTextStr, 0, true);

    newText(createVector2D(BOT_SCREEN_WIDTH/2, 100), 0.8f, BOT_SCREEN, WHITE_TEXT, C2D_AlignCenter, "Press B to go\nback to the menu", 0, true);
}

void endMatchProcess()
{
    if (kDown & KEY_B)
        changeScene(SCENE_MENU);
}


void intermissionWait()
{
    clearColor = INTERMISSION_BG_COLOR;

    char finishedRoundText[50];
    sprintf(finishedRoundText, "YOU'VE FINISHED ROUND %d", arcade_currentLevel);

    char nextRoundText[50];
    sprintf(nextRoundText, "PREPARE FOR ROUND %d", arcade_currentLevel+1);

    newText(createVector2D(TOP_SCREEN_WIDTH/2, 60), 0.6f, TOP_SCREEN, WHITE_TEXT, C2D_AlignCenter, finishedRoundText, 0, true);
    newText(createVector2D(TOP_SCREEN_WIDTH/2, 170), 0.6f, TOP_SCREEN, WHITE_TEXT, C2D_AlignCenter,  nextRoundText, 0, true);
}

void intermissionProcess()
{
    if (intermissionTimer-- <= 0)
    {
        arcade_currentLevel++;
        changeScene(SCENE_GAME);
    }
}



void calculateKillNeeded()
{
    arcade_currentKillNeeded = 5 + (arcade_currentLevel*5);
}

void gameInit()
{
    updateLimits();

    intermissionTimer = 180;

    clearColor = GAME_BG_COLOR;
    initPlayer();

    arcade_currentKillCounter = 0;
    calculateKillNeeded();

    sprintf(scoreTextStr, "Score: %d", arcade_currentScore);
    scoreText = newText(createVector2D(15, 10), 0.5f, TOP_SCREEN, YELLOW_TEXT, C2D_AlignLeft, scoreTextStr, 0, false);

    sprintf(killCounterTextStr, "Kills: %d/%d", arcade_currentKillCounter, arcade_currentKillNeeded);
    killCounterText = newText(createVector2D(BOT_SCREEN_WIDTH-15, 10), 0.5f, BOT_SCREEN, YELLOW_TEXT, C2D_AlignRight, killCounterTextStr, 0, false);

    sprintf(roundCounterTextStr, "Round: %d", arcade_currentLevel);
    roundCounterText = newText(createVector2D(15, 10), 0.5f, BOT_SCREEN, YELLOW_TEXT, C2D_AlignLeft, roundCounterTextStr, 0, true);
}

void gameProcess()
{
    playerProcess();
    enemySpawner();
    aliensProcess();
    shootersProcess();

    C2D_TextBufClear(g_dynamicBuf);

    sprintf(scoreTextStr, "Score: %d", arcade_currentScore);
    changeTextStr(scoreText, scoreTextStr);

    sprintf(killCounterTextStr, "Kills: %d/%d", arcade_currentKillCounter, arcade_currentKillNeeded);
    changeTextStr(killCounterText, killCounterTextStr);

    bulletsProcess();

    if (arcade_currentKillCounter >= arcade_currentKillNeeded)
        changeScene(SCENE_INTERMISSION);
}
