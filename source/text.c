#include "text.h"

C2D_TextBuf g_staticBuf;
C2D_TextBuf g_dynamicBuf;
Text textList[MAX_TEXT_OBJECTS];
C2D_Font arcadeFont;

void initTextEnv()
{
    g_staticBuf = C2D_TextBufNew(MAX_TEXT);
    g_dynamicBuf = C2D_TextBufNew(MAX_TEXT);

    arcadeFont = C2D_FontLoad("romfs:/gfx/arcade.bcfnt");
}

int newText(Vector2D pos, float p_size, bool p_screen, int p_color, int p_align, char* str, bool buffer)
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        if (!textList[i].toWrite)
        {
            textList[i].toWrite = true;
            textList[i].position = pos;
            textList[i].textID = i;

            textList[i].size = p_size;
            textList[i].screen = p_screen;
            textList[i].color = p_color;
            textList[i].alignment = p_align;

            if (buffer)
                C2D_TextFontParse(&textList[i].text, arcadeFont, g_staticBuf, str);
            else
                C2D_TextFontParse(&textList[i].text, arcadeFont, g_dynamicBuf, str);
            return i;
        }
    }
    return -1;
}

void changeTextStr(int p_textID, char* str)
{
    C2D_TextFontParse(&textList[p_textID].text, arcadeFont, g_dynamicBuf, str);
}

void killText(int p_textID)
{
    textList[p_textID].toWrite = false;
}

void killAllText()
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        killText(i);
    }
    C2D_TextBufClear(g_staticBuf);
}

void renderScreenText(bool p_screen)
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        if ((textList[i].toWrite) && (textList[i].screen == p_screen))
        {
            C2D_DrawText(&textList[i].text, C2D_WithColor | textList[i].alignment, textList[i].position.x, textList[i].position.y, 0.5f, textList[i].size, textList[i].size, textList[i].color);
        }
    }
}
