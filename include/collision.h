#pragma once

#include "vector2D.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    Vector2D position;
    Vector2D boundaries; // width and height
} CollisionBox;

CollisionBox newCollisionBox(Vector2D p_pos, Vector2D p_bounds);
bool checkCollision(CollisionBox* box1, CollisionBox* box2);
