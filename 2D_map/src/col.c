/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** col
*/

#include "../include/my.h"

void set_col2(collisions_t *col)
{
    col->rect[5].size = (sfVector2f){130, 20};
    col->rect[5].position = (sfVector2f){310, 290};
    sfRectangleShape_setSize(col->rect[5].rect, col->rect[5].size);
    sfRectangleShape_setPosition(col->rect[5].rect, col->rect[5].position);
    col->rect[6].size = (sfVector2f){120, 100};
    col->rect[6].position = (sfVector2f){0, 550};
    sfRectangleShape_setSize(col->rect[6].rect, col->rect[6].size);
    sfRectangleShape_setPosition(col->rect[6].rect, col->rect[6].position);
    col->rect[7].size = (sfVector2f){20, 100};
    col->rect[7].position = (sfVector2f){400, 610};
    sfRectangleShape_setSize(col->rect[7].rect, col->rect[7].size);
    sfRectangleShape_setPosition(col->rect[7].rect, col->rect[7].position);
    col->rect[8].size = (sfVector2f){100, 20};
    col->rect[8].position = (sfVector2f){495, 720};
    sfRectangleShape_setSize(col->rect[8].rect, col->rect[8].size);
    sfRectangleShape_setPosition(col->rect[8].rect, col->rect[8].position);
    col->rect[9].size = (sfVector2f){20, 20};
    col->rect[9].position = (sfVector2f){650, 660};
    sfRectangleShape_setSize(col->rect[9].rect, col->rect[9].size);
    sfRectangleShape_setPosition(col->rect[9].rect, col->rect[9].position);
}

void set_col3(collisions_t *col)
{
    col->rect[10].size = (sfVector2f){170, 75};
    col->rect[10].position = (sfVector2f){1070, 350};
    sfRectangleShape_setSize(col->rect[10].rect, col->rect[10].size);
    sfRectangleShape_setPosition(col->rect[10].rect, col->rect[10].position);
    col->rect[11].size = (sfVector2f){50, 40};
    col->rect[11].position = (sfVector2f){1130, 430};
    sfRectangleShape_setSize(col->rect[11].rect, col->rect[11].size);
    sfRectangleShape_setPosition(col->rect[11].rect, col->rect[11].position);
    col->rect[12].size = (sfVector2f){170, 30};
    col->rect[12].position = (sfVector2f){1380, 630};
    sfRectangleShape_setSize(col->rect[12].rect, col->rect[12].size);
    sfRectangleShape_setPosition(col->rect[12].rect, col->rect[12].position);
    col->rect[13].size = (sfVector2f){470, 40};
    col->rect[13].position = (sfVector2f){920, 710};
    sfRectangleShape_setSize(col->rect[13].rect, col->rect[13].size);
    sfRectangleShape_setPosition(col->rect[13].rect, col->rect[13].position);
    col->rect[14].size = (sfVector2f){170, 30};
    col->rect[14].position = (sfVector2f){1690, 630};
    sfRectangleShape_setSize(col->rect[14].rect, col->rect[14].size);
    sfRectangleShape_setPosition(col->rect[14].rect, col->rect[14].position);
}

void set_col4(collisions_t *col)
{
    col->rect[15].size = (sfVector2f){50, 200};
    col->rect[15].position = (sfVector2f){1800, 300};
    sfRectangleShape_setSize(col->rect[15].rect, col->rect[15].size);
    sfRectangleShape_setPosition(col->rect[15].rect, col->rect[15].position);
    col->rect[16].size = (sfVector2f){160, 110};
    col->rect[16].position = (sfVector2f){1690, 900};
    sfRectangleShape_setSize(col->rect[16].rect, col->rect[16].size);
    sfRectangleShape_setPosition(col->rect[16].rect, col->rect[16].position);
    col->rect[17].size = (sfVector2f){130, 50};
    col->rect[17].position = (sfVector2f){1700, 820};
    sfRectangleShape_setSize(col->rect[17].rect, col->rect[17].size);
    sfRectangleShape_setPosition(col->rect[17].rect, col->rect[17].position);
    col->rect[18].size = (sfVector2f){140, 100};
    col->rect[18].position = (sfVector2f){1700, 690};
    sfRectangleShape_setSize(col->rect[18].rect, col->rect[18].size);
    sfRectangleShape_setPosition(col->rect[18].rect, col->rect[18].position);
    col->rect[19].size = (sfVector2f){20, 20};
    col->rect[19].position = (sfVector2f){1650, 800};
    sfRectangleShape_setSize(col->rect[19].rect, col->rect[19].size);
    sfRectangleShape_setPosition(col->rect[19].rect, col->rect[19].position);
}

static void set_col5(collisions_t *col)
{
    col->rect[20].size = (sfVector2f){3, 350};
    col->rect[20].position = (sfVector2f){915, 670};
    sfRectangleShape_setSize(col->rect[20].rect, col->rect[20].size);
    sfRectangleShape_setPosition(col->rect[20].rect, col->rect[20].position);
    col->rect[21].size = (sfVector2f){80, 50};
    col->rect[21].position = (sfVector2f){915, 930};
    sfRectangleShape_setSize(col->rect[21].rect, col->rect[21].size);
    sfRectangleShape_setPosition(col->rect[21].rect, col->rect[21].position);
    col->rect[22].size = (sfVector2f){20, 20};
    col->rect[22].position = (sfVector2f){915, 830};
    sfRectangleShape_setSize(col->rect[22].rect, col->rect[22].size);
    sfRectangleShape_setPosition(col->rect[22].rect, col->rect[22].position);
    col->rect[23].size = (sfVector2f){100, 100};
    col->rect[23].position = (sfVector2f){1380, 930};
    sfRectangleShape_setSize(col->rect[23].rect, col->rect[23].size);
    sfRectangleShape_setPosition(col->rect[23].rect, col->rect[23].position);
    col->rect[24].size = (sfVector2f){20, 20};
    col->rect[24].position = (sfVector2f){1015, 750};
    sfRectangleShape_setSize(col->rect[24].rect, col->rect[24].size);
    sfRectangleShape_setPosition(col->rect[24].rect, col->rect[24].position);
}

static void set_col6(collisions_t *col)
{
    col->rect[1].size = (sfVector2f){750, 50};
    col->rect[1].position = (sfVector2f){0, 500};
    sfRectangleShape_setSize(col->rect[1].rect, col->rect[1].size);
    sfRectangleShape_setPosition(col->rect[1].rect, col->rect[1].position);
    col->rect[2].size = (sfVector2f){630, 130};
    col->rect[2].position = (sfVector2f){0, 0};
    sfRectangleShape_setSize(col->rect[2].rect, col->rect[2].size);
    sfRectangleShape_setPosition(col->rect[2].rect, col->rect[2].position);
    col->rect[3].size = (sfVector2f){560, 180};
    col->rect[3].position = (sfVector2f){785, 0};
    sfRectangleShape_setSize(col->rect[3].rect, col->rect[3].size);
    sfRectangleShape_setPosition(col->rect[3].rect, col->rect[3].position);
    col->rect[4].size = (sfVector2f){10, 40};
    col->rect[4].position = (sfVector2f){600, 170};
    sfRectangleShape_setSize(col->rect[4].rect, col->rect[4].size);
    sfRectangleShape_setPosition(col->rect[4].rect, col->rect[4].position);
    col->rect[25].size = (sfVector2f){50, 50};
    col->rect[25].position = (sfVector2f){60, 940};
    sfRectangleShape_setSize(col->rect[25].rect, col->rect[25].size);
    sfRectangleShape_setPosition(col->rect[25].rect, col->rect[25].position);
}

void set_col(collisions_t *col)
{
    col->rect[0].size = (sfVector2f){2000, 100};
    col->rect[0].position = (sfVector2f){0, 0};
    sfRectangleShape_setSize(col->rect[0].rect, col->rect[0].size);
    sfRectangleShape_setPosition(col->rect[0].rect, col->rect[0].position);
    set_col2(col);
    set_col3(col);
    set_col4(col);
    set_col5(col);
    set_col6(col);
}

bool check_collisions(collisions_t *col, sfSprite *player)
{
    sfFloatRect player_rect;
    sfFloatRect rect;

    player_rect = sfSprite_getGlobalBounds(player);
    for (int i = 0; i < 27; ++i) {
        rect = sfRectangleShape_getGlobalBounds(col->rect[i].rect);
        if (sfFloatRect_intersects(&player_rect, &rect, NULL))
            return false;
    }
    return true;
}
