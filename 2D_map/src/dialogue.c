/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dialogue_writing
*/

#include "../include/my.h"

static void initialize_write_func_data(text_t *data, int nbrtext)
{
    data->font = sfFont_createFromFile("2D_map/assets/kongtext.ttf");
    for (int i = 0; i < 3; ++i) {
        data->texts[i] = sfText_create();
        sfText_setFont(data->texts[i], data->font);
        sfText_setCharacterSize(data->texts[i], 24);
        sfText_setColor(data->texts[i], sfWhite);
    }
    data->clock = sfClock_create();
    data->delay = 0.1;
    for (int i = 0; i < 3; ++i) {
        data->currentTexts[i][0] = '\0';
        data->currentLengths[i] = 0;
    }
    data->activeText = 0;
    data->nbrtext = nbrtext;
}

int handle_event_p1(sfEvent *event, text_t *text_data,
    int *scene)
{
    int change_scene = 0;

    if (event->type == sfEvtMouseButtonPressed) {
        if (event->mouseButton.button == sfMouseLeft &&
            text_data->nbrtext > 1) {
            text_data->activeText = (text_data->activeText + 1) % 3;
            text_data->currentLengths[text_data->activeText] = 0;
            text_data->nbrtext--;
            change_scene = 1;
        }
        if (change_scene == 0 &&
            sfClock_getElapsedTime(text_data->clock).microseconds / 1000000.0 >
                text_data->delay) {
            sfText_setString(text_data->texts[text_data->activeText], NULL);
            *scene = 1;
            return 0;
        }
    }
    return 1;
}

static void clock_action(text_t *text_data, const char **strings)
{
    sfClock *clock = text_data->clock;
    sfText *text = NULL;
    int activeText = text_data->activeText;
    size_t currentLengths = 0;

    if (sfClock_getElapsedTime(clock).microseconds / 1000000.0 >
        text_data->delay) {
        if (text_data->currentLengths[activeText] <
            strlen(strings[activeText])) {
            text = text_data->texts[activeText];
            currentLengths = text_data->currentLengths[activeText];
            text_data->currentTexts[activeText][currentLengths] =
                strings[activeText][currentLengths];
            text_data->currentTexts[activeText][currentLengths + 1] = '\0';
            text_data->currentLengths[activeText]++;
            sfText_setString(text, text_data->currentTexts[activeText]);
            sfClock_restart(clock);
        }
    }
}

void disp_txt_screen(text_t *text_data, game_t *data)
{
    sfFloatRect bounds;

    bounds = sfText_getGlobalBounds(text_data->texts[text_data->activeText]);
    sfText_setPosition(text_data->texts[text_data->activeText],
        (sfVector2f){(data->mode.width - bounds.width - 200) / 2,
        (data->mode.height - bounds.height + 10) / 2});
    sfRenderWindow_clear(data->window, sfBlack);
    sfRenderWindow_drawText(data->window,
        text_data->texts[text_data->activeText], NULL);
    sfRenderWindow_display(data->window);
}

static int text_event(game_t *data, sfEvent *event, text_t *text_data,
    int *scene)
{
    while (sfRenderWindow_pollEvent(data->window, event)) {
        if (handle_event_p1(event, text_data, scene) == 0)
            return 0;
    }
    return 1;
}

int write_func(const char **strings, int nbrtext, game_t *data,
    int *scene)
{
    sfEvent event;
    text_t *text_data = malloc(sizeof(text_t));

    initialize_write_func_data(text_data, nbrtext);
    while (sfRenderWindow_isOpen(data->window)) {
        if (text_event(data, &event, text_data, scene) == 0)
            return 0;
        clock_action(text_data, strings);
        disp_txt_screen(text_data, data);
    }
    return 0;
}
