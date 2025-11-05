#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "sprite.h"

typedef struct
{
    int health;
    Vector2 position;
    float speed;
    PlayerSprites sprites;
} Player;

void InitPlayer(Player *player, Vector2 initial_pos, float speed);
void UpdatePlayer(Player *player, float dt);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);

#endif