/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** quest
*/

#pragma once

#include "my.h"
#include <SFML/Graphics.h>
#include <stddef.h>

sfText *generate_name(char *);
sfText *generate_desc(char *);
sfText *generate_obj(char *);
sfText *generate_progress(char *);

typedef struct quest_s {
    char *name_quest;
    char *description;
    char *ojbectif_int;
    char *progress_str;
    int ojb_progress;
    int end_ojb;
    int *id_counted;
    int next_free_index;
    sfText *(*name_text)(char *);
    sfText *(*desc_text)(char *);
    sfText *(*obj_text)(char *);
    sfText *(*progress_text)(char *);
} quest_t;

quest_t **init_quests_st(void);
