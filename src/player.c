#include "player.h"

void initPlayer(Player *player)
{
    player->position = (Vector2){400.0f, 300.0f};
    player->velocity = (Vector2){0.0f, 0.0f};
    player->speed = 200.0f;
    player->health = 100;
}

void updatePlayer(Player *player, float dt)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        player->position.x += player->speed * dt;
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        player->position.x -= player->speed * dt;
    }
    if (IsKeyDown(KEY_UP))
    {
        player->position.y -= player->speed * dt;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        player->position.y += player->speed * dt;
    }
}