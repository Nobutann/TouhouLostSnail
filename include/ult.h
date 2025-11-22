#ifndef ULT_H
#define ULT_H

#include "raylib.h"
#include <stdbool.h>

typedef struct UltFrame {
    int frameIndex;
    struct UltFrame *next;
} UltFrame;

typedef struct Ultimate {
    UltFrame *head;
    UltFrame *current;
    int totalFrames;
    int usesLeft;
    bool active;
    float frameTimer;
    float cooldownTimer;
    bool cooldownActive;
    Texture2D frames[14];
} Ultimate;

void InitUltimate(void);
void StartUltimate(void);
void UpdateUltimate(float dt);
void DrawUltimate(void);
void UnloadUltimate(void);
int GetRemainingUlts(void);

#endif
