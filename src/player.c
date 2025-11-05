#include "player.h"
#include <math.h>

void InitPlayer(Player *player, Vector2 initial_pos, float speed)
{
    player->position = initial_pos;
    player->speed = speed;
    
    LoadPlayerSprites(&player->sprites);
}

void UpdatePlayer(Player *player, float dt)
{
    Vector2 input = {0, 0};

    if (IsKeyDown(KEY_UP))
    {
        input.y = -1;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        input.y = 1;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        input.x = 1;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        input.x = -1;
    }

    if (input.x != 0 && input.y != 0)
    {
        float length = sqrtf(input.x * input.x + input.y * input.y);
        input.x /= length;
        input.y /= length;
    }

    player->position.x += input.x * player->speed * dt;
    player->position.y += input.y * player->speed * dt;

    Animation *anim = &player->sprites.idle;

    if (input.x < 0)
    {
        anim = &player->sprites.fly_left;
    }
    else if (input.x > 0)
    {
        anim = &player->sprites.fly_right;
    }

    UpdateAnimation(anim, dt);
}

void DrawPlayer(Player *player)
{
    Animation *anim = &player->sprites.idle;

    if (IsKeyDown(KEY_LEFT))
    {
        anim = &player->sprites.fly_left;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        anim = &player->sprites.fly_right;
    }

    DrawAnimationFrame(anim, player->position, 2.0f, WHITE);
}

void UnloadPlayer(Player *player)
{
    UnloadPlayerSprites(&player->sprites);
}