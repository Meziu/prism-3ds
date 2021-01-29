#include "main_menu.h"

char splash[46][100] = {
"Ready to storm Area 51 >:(",
"It is dangerous to go alone.\nGo to space instead",
"In a galaxy ruled by labelSpaziatori...",
"Marciello! This is not how to use a Limone!",
"Don't bother the holy Barrell",
"Totally different from Minecraft.\nPlay it though",
"Will the Prism be with you!",
"Stupid who reads",
"This is an amazingly low-budget game!",
"Aliens have failed the Vibe-Check",
"Now with 100% more bugs!!!",
"Too much time spent working on this,\nbut worth it",
"Completely peanut butter free!",
"Stonks and Baby Yoda weren't\nMemes of the Decade",
"Shhh... Sleep now...",
"Frick it, I don't wanna die young",
"Rich, like a label",
"Mathematically centered",
"Watch out for file matryoshkas!",
"Splashscreens weren't necessary,\nnow that I think about it...",
"What if... haha jk... unless...",
"More viral than Corona",
"Magikarp, use SplashScreen!\nOh, no, it's useless...",
"Not means no",
"Autoload is differentfrom AutoLoad,\ndon't make_dir()",
"Optimization at its finest!",
"They just need to touch",
"Kick 'em in da butt",
"There's no choice",
"Nothing to see here,\njust aliens flickerin' around",
"Arrays don't start from 0",
"It's going to die lol",
"We got to do it in C#",
"I'm the globals man,\nmy globals are delicious",
"WOOOOHOOOOO, COLORS",
"& Knuckles!",
"Gotta check 'em all",
"Going to discover something\nthat doesn't exist",
"Deep down we all know\nthere is a platypus controlling us",
"Bouncin' bouncin',\naw such a good time",
"Wow, porting this wasn't easy",
"The compilation was fine,\nbut the logic isn't working...",
"AAAAAAAAAAAAAAAAAAAAAAAAAAAA",
"I am alone, so I can finally\nprogram as bad as I want to...",
"Finally on a dead console!",
"Those .rsf are weeeeird..."
};

int randSplashScreen()
{
    return (int)(((float)rand()/(float)RAND_MAX)*46);
}


void mainMenuInit()
{
    readGameValues();
    setDefaultArcadeValues();

    setLimits();

    currentScene = SCENE_MENU;
    clearColor = MAIN_MENU_BG_COLOR;

    newText(createVector2D(TOP_SCREEN_WIDTH/2, 80), 1.0f, TOP_SCREEN, WHITE_TEXT, C2D_AlignCenter, "Prism - The Game 3D", 0, true);

    newText(createVector2D(TOP_SCREEN_WIDTH/2, 110), 0.6f, TOP_SCREEN, LIGHT_BLUE_TEXT, C2D_AlignCenter, splash[randSplashScreen()], 0, true);

    char high_score[20];
    sprintf(high_score, "Highscore: %d", game_highScore);
    newText(createVector2D(TOP_SCREEN_WIDTH/2, 160), 0.6f, TOP_SCREEN, YELLOW_TEXT, C2D_AlignCenter, high_score, 0, true);

    char coins[20];
    sprintf(coins, "Coins: %d", game_totalCoins);
    newText(createVector2D(TOP_SCREEN_WIDTH/2, 180), 0.6f, TOP_SCREEN, YELLOW_TEXT, C2D_AlignCenter, coins, 0, true);

    newText(createVector2D(10, SCREEN_HEIGHT-20), 0.6f, TOP_SCREEN, LIGHT_BLUE_TEXT, C2D_AlignLeft, "By Meziu210", 0, true);


    newText(createVector2D(BOT_SCREEN_WIDTH/2, 110), 0.8f, BOT_SCREEN, YELLOW_TEXT, C2D_AlignCenter, "PRESS A TO PLAY", 0, true);
}

void mainMenuProcess()
{
    if (kDown & KEY_A)
    {
        changeScene(SCENE_GAME);
    }
}
