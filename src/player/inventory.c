/*
** EPITECH PROJECT, 2026
** weapon
** File description:
** weapon
*/

#include "../../include/wolf3d.h"

void check_inventory(sfEvent event, inv_t *inv)
{
    if (iskeypressed(sfKeyE, event)) {
        inv->open = sfFalse;
        return;
    }
}

void open_inventory(sfEvent event, inv_t *inv)
{
    if (iskeypressed(sfKeyE, event))
        inv->open = !inv->open;
}
