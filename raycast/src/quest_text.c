/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** quest_text
*/

#include "../include/my.h"

sfText *generate_name(char *name)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("raycast/assets/arial.ttf");

    sfText_setFont(text, font);
    sfText_setString(text, name);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f){10, 10});
    return text;
}

sfText *generate_desc(char *desc)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("raycast/assets/arial.ttf");

    sfText_setFont(text, font);
    sfText_setString(text, desc);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f){10, 40});
    return text;
}

sfText *generate_obj(char *obj)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("raycast/assets/arial.ttf");

    sfText_setFont(text, font);
    sfText_setString(text, obj);
    sfText_setCharacterSize(text, 20);
    sfText_setPosition(text, (sfVector2f){10, 70});
    return text;
}
