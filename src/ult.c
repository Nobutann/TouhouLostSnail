#include "ult.h"
#include "bullets.h"
#include "boss.h"
#include <stdlib.h>
#include <stdio.h>

#define ULT_DURATION 4.2f
#define ULT_COOLDOWN 2.0f
#define FRAME_DURATION 0.3f
#define TOTAL_FRAMES 14
#define MAX_ULTS 3
#define ULT_DAMAGE 30

static Ultimate g_ultimate;
static bool g_ult_initialized = false;

void InitUltimate(void)
{
    g_ultimate.head = NULL;
    g_ultimate.current = NULL;
    g_ultimate.totalFrames = TOTAL_FRAMES;
    g_ultimate.usesLeft = MAX_ULTS;
    g_ultimate.active = false;
    g_ultimate.frameTimer = 0.0f;
    g_ultimate.cooldownTimer = 0.0f;
    g_ultimate.cooldownActive = false;

    // Create linked list of frames
    for (int i = 0; i < TOTAL_FRAMES; i++)
    {
        UltFrame *newFrame = (UltFrame *)malloc(sizeof(UltFrame));
        if (newFrame == NULL)
        {
            printf("Error: Failed to allocate memory for UltFrame\n");
            return;
        }
        newFrame->frameIndex = i;
        newFrame->next = NULL;

        if (g_ultimate.head == NULL)
        {
            g_ultimate.head = newFrame;
            g_ultimate.current = newFrame;
        }
        else
        {
            UltFrame *temp = g_ultimate.head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newFrame;
        }
    }

    // Load frame textures
    for (int i = 0; i < TOTAL_FRAMES; i++)
    {
        char path[256];
        sprintf(path, "assets/sprites/ult/ult-frame-%d.png", i);
        g_ultimate.frames[i] = LoadTexture(path);
    }

    g_ult_initialized = true;
}

void StartUltimate(void)
{
    if (!g_ult_initialized)
    {
        printf("Error: Ultimate not initialized\n");
        return;
    }

    if (g_ultimate.usesLeft <= 0)
    {
        printf("No ULTs remaining\n");
        return;
    }

    if (g_ultimate.active)
    {
        printf("ULT already active\n");
        return;
    }

    if (g_ultimate.cooldownActive)
    {
        printf("ULT on cooldown\n");
        return;
    }

    // Activate ULT
    g_ultimate.active = true;
    g_ultimate.usesLeft--;
    g_ultimate.frameTimer = 0.0f;
    g_ultimate.current = g_ultimate.head;

    // Clear all bullets and disable bullet system
    ClearAllBullets();
    DisableBullets();

    // Deal damage to boss
    BossTakeUltDamage(ULT_DAMAGE);
}

void UpdateUltimate(float dt)
{
    if (!g_ult_initialized)
    {
        return;
    }

    // Update cooldown timer
    if (g_ultimate.cooldownActive)
    {
        g_ultimate.cooldownTimer -= dt;
        if (g_ultimate.cooldownTimer <= 0.0f)
        {
            g_ultimate.cooldownActive = false;
            g_ultimate.cooldownTimer = 0.0f;
            EnableBullets();
        }
    }

    // Update active ULT
    if (g_ultimate.active)
    {
        g_ultimate.frameTimer += dt;

        // Check if we need to advance to next frame
        if (g_ultimate.frameTimer >= FRAME_DURATION)
        {
            g_ultimate.frameTimer -= FRAME_DURATION;

            if (g_ultimate.current != NULL && g_ultimate.current->next != NULL)
            {
                g_ultimate.current = g_ultimate.current->next;
            }
            else
            {
                // ULT animation finished
                g_ultimate.active = false;
                g_ultimate.frameTimer = 0.0f;
                g_ultimate.current = g_ultimate.head;

                // Start cooldown
                g_ultimate.cooldownActive = true;
                g_ultimate.cooldownTimer = ULT_COOLDOWN;
            }
        }
    }
}

void DrawUltimate(void)
{
    if (!g_ult_initialized || !g_ultimate.active || g_ultimate.current == NULL)
    {
        return;
    }

    int frameIndex = g_ultimate.current->frameIndex;
    if (frameIndex < 0 || frameIndex >= TOTAL_FRAMES)
    {
        return;
    }

    Texture2D currentTexture = g_ultimate.frames[frameIndex];

    // Calculate position to center the ULT in the playable area
    // Playable area is x: 0-960, y: 0-800
    float scale = 3.2f;
    float w = currentTexture.width * scale;
    float h = currentTexture.height * scale;

    float ultX = (960.0f - w) / 2.0f;
    ultX -= 60.0f;  // Shift left
    float ultY = (800.0f - h) / 2.0f;

    DrawTextureEx(currentTexture, (Vector2){ ultX, ultY }, 0.0f, scale, WHITE);
}

void UnloadUltimate(void)
{
    if (!g_ult_initialized)
    {
        return;
    }

    // Free linked list
    UltFrame *current = g_ultimate.head;
    while (current != NULL)
    {
        UltFrame *next = current->next;
        free(current);
        current = next;
    }

    // Unload textures
    for (int i = 0; i < TOTAL_FRAMES; i++)
    {
        UnloadTexture(g_ultimate.frames[i]);
    }

    g_ultimate.head = NULL;
    g_ultimate.current = NULL;
    g_ult_initialized = false;
}

int GetRemainingUlts(void)
{
    if (!g_ult_initialized)
    {
        return 0;
    }
    return g_ultimate.usesLeft;
}
