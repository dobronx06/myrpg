/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** create_scene
*/

#include "../include/menu.h"

void init_slider(menu_t *menu)
{
    menu->textureSlider =
    sfTexture_createFromFile("menu/assets/barre_son.png", NULL);
    menu->spriteSlider = sfSprite_create();
    sfSprite_setTexture(menu->spriteSlider, menu->textureSlider, sfTrue);
    sfSprite_setPosition(menu->spriteSlider, (sfVector2f){560, 550});
    sfSprite_setScale(menu->spriteSlider, (sfVector2f){0.5, 0.5});
    menu->knob = sfRectangleShape_create();
    sfRectangleShape_setSize(menu->knob, (sfVector2f){10, 25});
    sfRectangleShape_setFillColor(menu->knob, sfBlack);
    sfRectangleShape_setOrigin(menu->knob, (sfVector2f){10, 10});
    sfRectangleShape_setPosition(menu->knob, (sfVector2f){987, 695});
}

static void create_button_reso(menu_t *menu)
{
    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/1920x1080", (sfVector2f){500, 450},
        (sfVector2f){0.3, 0.3}));
    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/1600x900", (sfVector2f){810, 450},
        (sfVector2f){0.3, 0.3}));
    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/960x540", (sfVector2f){1125, 450},
        (sfVector2f){0.3, 0.3}));
    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/bouton_reso", (sfVector2f){770, 330},
        (sfVector2f){0.4, 0.4}));
    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/bouton_volume", (sfVector2f){820, 580},
        (sfVector2f){0.3, 0.3}));
}

void create_button_reglage(menu_t *menu)
{
    sfVector2f pos_mur_reglage =
    (sfVector2f){menu->windowSize.x / 2 - 600, 35};

    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/mur_reglage", pos_mur_reglage, (sfVector2f){2.2, 2.2}));
    add_button(&menu->button_settings, init_bouton(create_button(),
        "menu/assets/bouton_reglage", (sfVector2f){825, 125},
        (sfVector2f){0.3, 0.3}));
    create_button_reso(menu);
    init_slider(menu);
}

void create_button_main_menu(menu_t *menu)
{
    add_button(&menu->button_menu, init_bouton(create_button(),
        "menu/assets/bouton_jouer", (sfVector2f){menu->wSizeX / 2 - 150, 350},
        (sfVector2f){0.3, 0.3}));
    add_button(&menu->button_menu, init_bouton(create_button(),
        "menu/assets/bouton_reglage",
        (sfVector2f){menu->wSizeX / 2 - 150, 580}, (sfVector2f){0.3, 0.3}));
    add_button(&menu->button_menu, init_bouton(create_button(),
        "menu/assets/bouton_quitter",
        (sfVector2f){menu->wSizeX / 2 - 150, 750}, (sfVector2f){0.3, 0.3}));
}

void create_all_button(menu_t *menu)
{
    create_button_main_menu(menu);
    create_button_reglage(menu);
}
