#ifndef SCREENS_H
#define SCREENS_H

typedef enum
{
    MENU_SCREEN,
    GAME_SCREEN,
    CREDITS_SCREEN,
    EXIT_SCREEN
} GameScreen;

GameScreen menu();

#endif