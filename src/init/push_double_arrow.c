/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/init
** File description:
** push_double_arrow
*/

#include "wolf3d.h"

void push_double_arrow(wolf_t *wolf, triangle_t **triangles)
{
    for (int i = 0; i < 2; i++)
        if (triangles[i])
            push_front(&wolf->list[SETTINGS][TRIANGLE], triangles[i]);
}
