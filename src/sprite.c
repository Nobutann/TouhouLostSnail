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

void LoadBossSprites(PlayerSprites *player_sprites)
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

void UnloadBossSprites(PlayerSprites *player_sprites)
{
    UnloadTextureArray(player_sprites->idle.frames, player_sprites->idle.frame_count);
    UnloadTextureArray(player_sprites->fly_right.frames, player_sprites->fly_right.frame_count);
    UnloadTextureArray(player_sprites->fly_left.frames, player_sprites->fly_left.frame_count);
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