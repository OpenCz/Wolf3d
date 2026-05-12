/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src/settings
** File description:
** apply
*/

#include "wolf3d.h"

void apply_settings(wolf_t *wolf)
{
    if (!wolf || !wolf->settings || !wolf->tmp_settings)
        return;
    memcpy(wolf->settings, wolf->tmp_settings, sizeof(settings_game_t));
}
