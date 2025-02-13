/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** text_updater
*/

#include "../include/my.h"

static void initialize_clock(sfClock **clock)
{
    if (!*clock)
        *clock = sfClock_create();
}

static void reset_text_state(sfText *text, text_t *dialogue)
{
    if (sfText_getString(text) && strlen(sfText_getString(text)) == 0) {
        for (int i = 0; i < 3; i++) {
            dialogue->currentTexts[i][0] = '\0';
            dialogue->currentLengths[i] = 0;
        }
        dialogue->activeText = 0;
    }
}

void next_text(text_t *dialogue)
{
    if (sfMouse_isButtonPressed(sfMouseLeft) && dialogue->activeText < 2) {
        dialogue->activeText = (dialogue->activeText + 1) % 3;
        dialogue->currentLengths[dialogue->activeText] = 0;
        memset(dialogue->currentTexts[dialogue->activeText], 0,
        sizeof(dialogue->currentTexts[dialogue->activeText]));
    }
}

void update_text(text_t *dialogue, sfText *text, sfClock *clock, float delay)
{
    if (dialogue->currentLengths[dialogue->activeText] <
        strlen(dialogue->strings[dialogue->activeText])) {
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > delay) {
            dialogue->currentTexts[dialogue->activeText]
            [dialogue->currentLengths[dialogue->activeText]] =
            dialogue->strings[dialogue->activeText][dialogue->currentLengths
            [dialogue->activeText]];
            dialogue->currentTexts[dialogue->activeText]
            [dialogue->currentLengths[dialogue->activeText] + 1] = '\0';
            dialogue->currentLengths[dialogue->activeText]++;
            sfText_setString(text, dialogue->currentTexts
            [dialogue->activeText]);
            sfClock_restart(clock);
        }
    } else {
        next_text(dialogue);
    }
}

static void set_text_properties(game_t *data, sfText *text, int i)
{
    sfText_setFont(text, data->font);
    sfText_setCharacterSize(text, 23);
    sfText_setColor(text, sfWhite);
    if (i == 0)
        sfText_setPosition(text, (sfVector2f){800, 930});
    else
        sfText_setPosition(text, (sfVector2f){-1000, -1000});
}

void draw_text(game_t *data, sfText *text, const char *strings[3], int i)
{
    static sfClock *clock = NULL;
    static float delay = 0.1;
    static text_t dialogue = {
        .strings = {NULL, NULL, NULL},
        .currentTexts = {{0}, {0}, {0}},
        .currentLengths = {0},
        .activeText = 0
    };

    dialogue.strings[0] = strings[0];
    dialogue.strings[1] = strings[1];
    dialogue.strings[2] = strings[2];
    initialize_clock(&clock);
    reset_text_state(text, &dialogue);
    update_text(&dialogue, text, clock, delay);
    set_text_properties(data, text, i);
    sfRenderWindow_drawText(data->window, text, NULL);
}
