/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** quest_action
*/

#include "../include/my.h"

char *int_to_char(int num, int int_to_add)
{
    char *str = malloc(sizeof(char) * 10);
    char *tmp = malloc(sizeof(char) * 10);

    sprintf(tmp, "%d", num);
    strcpy(str, tmp);
    sprintf(tmp, "/%d", int_to_add);
    strcat(str, tmp);
    free(tmp);
    return str;
}

static char **my_str_to_word_array(char *str, char *delimiter)
{
    char **array = malloc(sizeof(char *) * (strlen(str) + 1));
    char *tmp = strtok(str, delimiter);
    int i = 0;

    while (tmp != NULL) {
        array[i] = strdup(tmp);
        tmp = strtok(NULL, delimiter);
        i++;
    }
    array[i] = NULL;
    return array;
}

static void quest_id_counted(quest_t **quests, int *index, char **tab)
{
    quests[*index]->id_counted = malloc(sizeof(int) * atoi(tab[4]));
    for (int i = 0; i < atoi(tab[4]); i++)
        quests[*index]->id_counted[i] = 0;
}

static void init_quests_content(quest_t **quests, FILE *file,
    int *index, char **tab)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        tab = my_str_to_word_array(line, ":");
        quests[*index] = malloc(sizeof(quest_t));
        quests[*index]->next_free_index = 0;
        quests[*index]->name_quest = strdup(tab[0]);
        quests[*index]->description = strdup(tab[1]);
        quests[*index]->ojbectif_int = strdup(tab[2]);
        quests[*index]->progress_str = strdup(tab[3]);
        quests[*index]->ojb_progress = atoi(tab[3]);
        quests[*index]->end_ojb = atoi(tab[4]);
        quest_id_counted(quests, index, tab);
        quests[*index]->name_text = &generate_name;
        quests[*index]->desc_text = &generate_desc;
        quests[*index]->obj_text = &generate_obj;
        quests[*index]->progress_text = &generate_obj;
        (*index)++;
    }
}

quest_t **init_quests_st(void)
{
    quest_t **quests = malloc(sizeof(quest_t *) * 5);
    FILE *file = fopen("raycast/quests/quests.txt", "r");
    char **tab = NULL;
    int index = 0;

    init_quests_content(quests, file, &index, tab);
    quests[index] = NULL;
    return quests;
}
