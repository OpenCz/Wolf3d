/*
** EPITECH PROJECT, 2026
** weapon
** File description:
** weapon
*/

#include "../../include/wolf3d.h"

static void manage_inventory(window_t *win, inv_t *inv)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win->window);
    sfFloatRect rect;

    for (int i = 0; i < 8; i++)
        inv->slot[i].selected = sfFalse;
    for (int i = 1; i < 9; i++) {
        rect = sfRectangleShape_getGlobalBounds(inv->rect[i]);
        if (!sfFloatRect_contains(&rect, pos.x, pos.y))
            continue;
        inv->slot[i - 1].selected = sfTrue;
    }
}

static void equip_item(player_t *player, inv_t *inv)
{
    if (!sfKeyboard_isKeyPressed(sfKeySpace))
        return;
    for (int i = 0; i < 8; i++) {
        if (!inv->slot[i].selected)
            return;
        player->weapon = (weapon_t *)inv->slot[i].item.data;
        inv->slot[i].selected = sfFalse;
    }
}

void check_inventory(wolf_t *wolf, inv_t *inv)
{
    if (sfMouse_isButtonPressed(sfMouseLeft))
        manage_inventory(wolf->window_data, inv);
    equip_item(wolf->player, inv);
    draw_selected_item(wolf->window_data, inv);
}

void draw_inventory_item(window_t *win, inv_t *inv, int i)
{
    sfVector2f pos;
    sfSprite *sprite;
    sfFloatRect bounds;
    sfVector2f origin;

    if (!inv->slot[i - 1].item.data)
        return;
    sprite = inv->slot[i - 1].item.entity->sprite;
    pos = sfRectangleShape_getPosition(inv->rect[i]);
    bounds = sfSprite_getLocalBounds(sprite);
    origin = (sfVector2f){bounds.width / 2, bounds.height / 2};
    sfSprite_setOrigin(sprite, origin);
    sfSprite_setPosition(sprite, (sfVector2f){pos.x, pos.y});
    sfRenderWindow_drawSprite(win->window, sprite, NULL);
}

void draw_selected_item(window_t *win, inv_t *inv)
{
    char *str = NULL;

    for (int i = 0; i < 8; i++) {
        if (!inv->slot[i].selected)
            continue;
        str = inv->slot[i].item.name;
    }
    if (!str)
        return;
    sfText_setString(inv->text, str);
    sfText_setCharacterSize(inv->text, 30);
    sfText_setPosition(inv->text,
        (sfVector2f){win->width / 3.1, win->height / 1.63});
    sfRenderWindow_drawText(win->window, inv->text, NULL);
    sfText_setString(inv->text, "Press space to equip");
    sfText_setPosition(inv->text,
        (sfVector2f){win->width / 2, win->height / 1.63});
    sfRenderWindow_drawText(win->window, inv->text, NULL);
}

void open_inventory(wolf_t *wolf, sfEvent event, inv_t *inv)
{
    if (iskeypressed(sfKeyE, event)) {
        inv->open = !inv->open;
        sfRenderWindow_setMouseCursorVisible(wolf->window_data->window,
            inv->open ? sfTrue : sfFalse);
        sfMouse_setPositionRenderWindow((sfVector2i){wolf->window_data->width
                / 2, wolf->window_data->height / 2}, wolf->window_data->window);
        for (int i = 0; i < 8; i++)
            inv->slot[i].selected = sfFalse;
    }
    if (inv->open)
        check_inventory(wolf, inv);
}
