#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

typedef enum
{
    MENU_SCREEN,
    GAME_SCREEN,
    CREDITS_SCREEN,
    EXIT_SCREEN
} GameScreen;

GameScreen menu(Music menu_music, Texture2D background);

#endif