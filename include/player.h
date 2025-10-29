#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player
{
    int health;
    Vector2 velocity;
    Vector2 position;
    float speed;
} Player;

void initPlayer(Player *player);

void updatePlayer(Player *player, float dt);

#endif