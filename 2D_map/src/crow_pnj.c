/*
** EPITECH PROJECT, 2024
** drag and drop
** File description:
** crow_pnj
*/

#include "../include/my.h"

static void dialogue_2(game_t *game, int *i)
{
    const char *dialogue2[3] =
        {"Viens, ecoute-moi", "Ramene moi un gateau,",
        "Tu seras recompense"};

    sfSprite_setPosition(game->textbox2, (sfVector2f){650, 900});
    sfRenderWindow_drawSprite(game->window, game->dialogue_line, NULL);
    *i = 0;
    draw_text(game, game->textsf, dialogue2, *i);
    *i = 2;
}

static void dialogue_0(game_t *game, int *i)
{
    const char *dialogue1[3] =
        {"Hein ?", "Bizarre ...", " Surement un reve"};

    sfRenderWindow_drawSprite(game->window, game->dialogue_line, NULL);
    draw_text(game, game->textsf, dialogue1, *i);
}

static void dialogue_1(game_t *game, int *i)
{
    const char *dialogue1[3] =
        {"Je suis le corbeau,\nviens", "Interagis avec 'E'",
        "et 'ZQSD' pour \nte deplacer"};

    sfSprite_setPosition(game->textbox2, (sfVector2f){650, 900});
    sfRenderWindow_drawSprite(game->window, game->dialogue_line, NULL);
    *i = 0;
    draw_text(game, game->textsf, dialogue1, *i);
    *i = 1;
}

static void dialogue_3(game_t *game, int *i)
{
    const char *dialogue6[3] =
        {"On m'a dit que\nton pote etait malade", "j'ai une solution\npour ca", "Fait moi confiance :)"};

    sfSprite_setPosition(game->textbox2, (sfVector2f){650, 900});
    sfRenderWindow_drawSprite(game->window, game->dialogue_line, NULL);
    *i = 0;
    draw_text(game, game->textsf, dialogue6, *i);
    *i = 3;
}

void dialogue_crow(game_t *game, int *i)
{
    switch (*i) {
        case 0:
            dialogue_0(game, i);
            break;
        case 1:
            dialogue_1(game, i);
            break;
        case 2:
            dialogue_2(game, i);
            break;
        case 3:
            dialogue_3(game, i);
            break;
    }
}
