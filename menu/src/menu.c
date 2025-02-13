/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** menu
*/

#include "../include/menu.h"
#include "../../2D_map/include/my.h"

void display_window(menu_t *menu)
{
    create_all_button(menu);
    sfMusic_setLoop(menu->music, sfTrue);
    sfMusic_play(menu->music);
    while (sfRenderWindow_isOpen(menu->window)) {
        if (menu->current_scene == 0)
            menu->cur_buttons = menu->button_menu;
        if (menu->current_scene == 1)
            menu->cur_buttons = menu->button_settings;
        if (menu->current_scene == 2)
            menu->cur_buttons = menu->button_credits;
        sfRenderWindow_clear(menu->window, sfBlack);
        while (sfRenderWindow_pollEvent(menu->window, &menu->event)) {
            resize(menu, &menu->event);
            handle_event(&menu->event, menu);
        }
        sfRenderWindow_drawSprite(menu->window, menu->spriteBg, NULL);
        display_buttons(menu->window, menu->cur_buttons, menu);
        sfRenderWindow_display(menu->window);
    }
    sfMusic_destroy(menu->music);
}

void init_menu(menu_t *menu)
{
    menu->button_menu = NULL;
    menu->button_settings = NULL;
    menu->current_scene = 0;
    menu->wSizeX = 1920;
    menu->wSizeY = 1080;
    menu->mode = (sfVideoMode){menu->wSizeX, menu->wSizeY, 32};
    menu->window = sfRenderWindow_create
    (menu->mode, "My RPG", sfFullscreen | sfClose, NULL);
    menu->spriteBg = sfSprite_create();
    menu->textureBg =
        sfTexture_createFromFile("menu/assets/bg_chambre.jpg", NULL);
    menu->music = sfMusic_createFromFile("menu/assets/music.ogg");
    menu->windowSize = sfRenderWindow_getSize(menu->window);
    menu->bgScaleX =
    (float)menu->windowSize.x / sfTexture_getSize(menu->textureBg).x;
    menu->bgScaleY =
    (float)menu->windowSize.y / sfTexture_getSize(menu->textureBg).y;
    sfSprite_setScale
    (menu->spriteBg, (sfVector2f){menu->bgScaleX, menu->bgScaleY});
    sfSprite_setTexture(menu->spriteBg, menu->textureBg, sfTrue);
}

int main(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    init_menu(menu);
    sfRenderWindow_setFramerateLimit(menu->window, 60);
    display_window(menu);
    sfRenderWindow_destroy(menu->window);
}
