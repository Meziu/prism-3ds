#include "enemySpawner.h"

size_t limits[3] = {4, 2, 0};

int alienTimer = 60;
int shooterTimer = 90;

Rail shooterRails[2] = {{RAIL_SHOOTER_1, SHOOTER_TYPE, 0},
                        {RAIL_SHOOTER_2, SHOOTER_TYPE, 0}};

Rail alienRails[3] = {{RAIL_NORMAL_1, ALIEN_TYPE, 0},
                      {RAIL_NORMAL_2, ALIEN_TYPE, 0},
                      {RAIL_NORMAL_3, ALIEN_TYPE, 0}};


void setLimits()
{
    if (game_chosenDifficulty == DIF_EZ)
    {
        limits[0] = 3;
        limits[1] = 1;
        limits[2] = 0;
    }
    else if (game_chosenDifficulty == DIF_NORMIE)
    {
        limits[0] = 4;
        limits[1] = 2;
        limits[2] = 0;
    }
    else if (game_chosenDifficulty == DIF_PRO)
    {
        limits[0] = 5;
        limits[1] = 2;
        limits[2] = 1;
    }
}

void updateLimits()
{
    if ((arcade_currentLevel % 2) == 0)
        limits[0] += 1;
    if ((arcade_currentLevel % 3) == 0)
        limits[1] += 1;
    if ((arcade_currentLevel % 5) == 0)
        limits[2] += 1;
}

int railFinder(bool type)
{
    if (type == ALIEN_TYPE)
    {
        if (alienRails[1].counter <= alienRails[0].counter && alienRails[2].counter < alienRails[0].counter)
        {
            if (alienRails[2].counter < alienRails[1].counter)
                return 2;
            else
                return 1;
        } 
        else
            return 0;
    }
    else if (type == SHOOTER_TYPE)
    {
        if (shooterRails[1].counter < shooterRails[0].counter)
            return 1;
        else
            return 0;
    }
    return -1;
}

void enemySpawner()
{
    float choice = (float)rand()/(float)RAND_MAX;

    if (alienTimer != 0)
        alienTimer--;

    if (shooterTimer != 0)
        shooterTimer--;
    

    if (choice < SHOOTER_CHANCE && shooterCount < limits[1] && shooterTimer == 0)
    {
        shooterTimer = 90;
        int chosenRail = railFinder(SHOOTER_TYPE);
        if (chosenRail != -1)
            newShooter(chosenRail);
    }
    else if (choice < ALIEN_CHANCE && alienCount < limits[0] && alienTimer == 0)
    {
        alienTimer = 60;
        int chosenRail = railFinder(ALIEN_TYPE);
        if (chosenRail != -1)
            newAlien(chosenRail);
    }
}
