#include "sprite.h"
#include <stdlib.h>

static Texture2D* LoadTextureArray(const char **filepaths, int count)
{
    Texture2D *textures = (Texture2D*)MemAlloc(sizeof(Texture2D) * count);

    for (int i = 0; i < count; i++)
    {
        textures[i] = LoadTexture(filepaths[i]);
    }

    return textures;
}

static void UnloadTextureArray(Texture2D *textures, int count)
{
    for (int i = 0; i < count; i++)
    {
        UnloadTexture(textures[i]);
    }

    MemFree(textures);
}

void LoadPlayerSprites(PlayerSprites *player_sprites)
{
    const char *idlepath[] = 
    {
        "assets/sprites/Player/reimuidle/reimuidle-1.png",
        "assets/sprites/Player/reimuidle/reimuidle-2.png",
        "assets/sprites/Player/reimuidle/reimuidle-3.png",
        "assets/sprites/Player/reimuidle/reimuidle-4.png",
        "assets/sprites/Player/reimuidle/reimuidle-5.png",
        "assets/sprites/Player/reimuidle/reimuidle-6.png",
        "assets/sprites/Player/reimuidle/reimuidle-7.png",
        "assets/sprites/Player/reimuidle/reimuidle-8.png",
    };

    int idle_frame_count = sizeof(idlepath) / sizeof(idlepath[0]);
    player_sprites->idle.frames = LoadTextureArray(idlepath, idle_frame_count);
    player_sprites->idle.frame_count = idle_frame_count;
    player_sprites->idle.frame_time = 0.15f;
    player_sprites->idle.current_frame = 0;
    player_sprites->idle.timer = 0.0f;

    const char *rightpath[] = 
    {
        "assets/sprites/Player/reimuright/reimuright-6.png",
        "assets/sprites/Player/reimuright/reimuright-7.png",
        "assets/sprites/Player/reimuright/reimuright-8.png",
    };

    int right_frame_count = sizeof(rightpath) / sizeof(rightpath[0]);
    player_sprites->fly_right.frames = LoadTextureArray(rightpath, right_frame_count);
    player_sprites->fly_right.frame_count = right_frame_count;
    player_sprites->fly_right.frame_time = 0.15;
    player_sprites->fly_right.current_frame = 0;
    player_sprites->fly_right.timer = 0.0f;

    const char *leftpath[] = 
    {
        "assets/sprites/Player/reimuleft/reimuleft-6.png",
        "assets/sprites/Player/reimuleft/reimuleft-7.png",
        "assets/sprites/Player/reimuleft/reimuleft-8.png",
    };

    int left_frame_count = sizeof(leftpath) / sizeof(leftpath[0]);
    player_sprites->fly_left.frames = LoadTextureArray(leftpath, left_frame_count);
    player_sprites->fly_left.frame_count = left_frame_count;
    player_sprites->fly_left.frame_time = 0.15f;
    player_sprites->fly_left.current_frame = 0;
    player_sprites->fly_right.timer = 0.0f;
}

void UnloadPlayerSprites(PlayerSprites *player_sprites)
{
    UnloadTextureArray(player_sprites->idle.frames, player_sprites->idle.frame_count);
    UnloadTextureArray(player_sprites->fly_right.frames, player_sprites->fly_right.frame_count);
    UnloadTextureArray(player_sprites->fly_left.frames, player_sprites->fly_left.frame_count);
}

void LoadBossSprites(BossSprites *boss_sprites)
{
    const char *idlepath[] = 
    {
        "assets/sprites/flandre/flandreidle/flandreidle1.png",
        "assets/sprites/flandre/flandreidle/flandreidle2.png",
        "assets/sprites/flandre/flandreidle/flandreidle3.png",
        "assets/sprites/flandre/flandreidle/flandreidle4.png",
    };

    int idle_frame_count = sizeof(idlepath) / sizeof(idlepath[0]);
    boss_sprites->idle.frames = LoadTextureArray(idlepath, idle_frame_count);
    boss_sprites->idle.frame_count = idle_frame_count;
    boss_sprites->idle.frame_time = 0.1f;
    boss_sprites->idle.current_frame = 0;
    boss_sprites->idle.timer = 0.0f;

    const char *directionpath[] = 
    {
        "assets/sprites/flandre/flandredirection/flandredirection1.png",
        "assets/sprites/flandre/flandredirection/flandredirection2.png",
    };

    int direction_frame_count = sizeof(directionpath) / sizeof(directionpath[0]);
    boss_sprites->direction.frames = LoadTextureArray(directionpath, direction_frame_count);
    boss_sprites->direction.frame_count = direction_frame_count;
    boss_sprites->direction.frame_time = 0.12f;
    boss_sprites->direction.current_frame = 0;
    boss_sprites->direction.timer = 0.0f;
}

void UnloadBossSprites(BossSprites *boss_sprites)
{
    UnloadTextureArray(boss_sprites->idle.frames, boss_sprites->idle.frame_count);
    UnloadTextureArray(boss_sprites->direction.frames, boss_sprites->direction.frame_count);
}

void LoadMapSprites(Animation *map)
{
    const char *mappath[] = 
    {
        "assets/sprites/map/background1.png",
        "assets/sprites/map/background2.png",
        "assets/sprites/map/background3.png",
        "assets/sprites/map/background4.png",
    };

    int map_frame_count = sizeof(mappath) / sizeof(mappath[0]);
    map->frames = LoadTextureArray(mappath, map_frame_count);
    map->frame_count = map_frame_count;
    map->frame_time = 0.15f;
    map->current_frame = 0;
    map->timer = 0.0f;
}

void UnloadMapSprites(Animation *map)
{
    UnloadTextureArray(map->frames, map->frame_count);
}

void UpdateAnimation(Animation *anim, float dt)
{
    anim->timer += dt;

    if (anim->timer >= anim->frame_time)
    {
        anim->timer = 0.0f;
        anim->current_frame++;
        if (anim->current_frame >= anim->frame_count)
        {
            anim->current_frame = 0;
        }
    }
}

void DrawAnimationFrame(Animation *anim, Vector2 position, float scale, Color tint)
{
    if (anim -> frames != NULL && anim->frame_count > 0)
    {
        DrawTextureEx(anim->frames[anim->current_frame], position, 0.0f, scale, tint);
    }
}