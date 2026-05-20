/*
** EPITECH PROJECT, 2026
** init
** File description:
** player
*/

#include "../../include/wolf3d.h"

static sfRectangleShape *set_slot_position(sfVector2f *size,
    sfVector2f *pos, sfColor *color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, *size);
    sfRectangleShape_setOrigin(rect,
        (sfVector2f){size->x / 2, size->y / 2});
    sfRectangleShape_setFillColor(rect, *color);
    sfRectangleShape_setOutlineThickness(rect, 3);
    sfRectangleShape_setOutlineColor(rect, sfBlack);
    sfRectangleShape_setPosition(rect, *pos);
    return rect;
}

static void create_slot_rect(window_t *win, inv_t *inv)
{
    sfVector2f size = {win->width / 2.5, win->height / 3};
    sfVector2f slot = {win->width / 12, win->height / 12};
    float x = win->width / 2 - ((slot.x * 4) + (20 * 3)) / 2 + slot.x / 2;
    float y = win->height / 2 - ((slot.y * 2) + 20) / 2 + slot.y / 2;

    inv->open = sfFalse;
    inv->rect[0] = set_slot_position(&size,
        &(sfVector2f){win->width / 2, win->height / 2},
        &(sfColor){110, 67, 32, 255});
    for (int i = 0; i < 8; i++) {
        size = (sfVector2f){x + i % 4 * (slot.x + 20),
            y + i / 4 * (slot.y + 20)};
        inv->rect[i + 1] = set_slot_position(&slot, &size, &sfWhite);
    }
    inv->rect[9] = set_slot_position(&(sfVector2f){win->width, win->height},
        &(sfVector2f){win->width / 2, win->height / 2},
        &(sfColor){120, 120, 120, 150});
}

static void create_item(item_t *item, void *data, char *name, wp_type_t type)
{
    item->name = strdup(name);
    item->data = data;
    item->type = type;
}

static void init_item(window_t *wn, inv_t *inv)
{
    sfVector2f p = {1, 1};

    create_item(&inv->item[0], init_weapon(GUN, 34, 9, create_entity("gun",
                "assets/gun.png", &(sfVector2f){wn->width / 2, wn->height},
                &(sfVector2f){1.7, 1.7})), "Gun", GUN);
    inv->item[0].entity = create_entity("icon", "assets/gun_icon.png", &p, &p);
    inv->slot[0].item = inv->item[0];
    create_item(&inv->item[1], init_weapon(SHOTGUN, 50, 1, create_entity("sgun",
                "assets/shotgun.png", &(sfVector2f){wn->width / 2, wn->height},
                &(sfVector2f){1.f, 1.f})), "Shotgun", SHOTGUN);
    inv->item[1].entity = create_entity("icon", "assets/sgun_icon.png", &p, &p);
    inv->slot[1].item = inv->item[1];
    create_item(&inv->item[2], init_weapon(VACUUM, 50, 1, create_entity("vac",
                "assets/vacuum.png", &(sfVector2f){wn->width / 2, wn->height},
                &(sfVector2f){1.f, 1.f})), "Vacuum", VACUUM);
    inv->item[2].entity = create_entity("icon", "assets/vac_icon.png", &p, &p);
    inv->slot[2].item = inv->item[2];
}

window_t *create_inv(data_t *data, window_t *win, inv_t *inv)
{
    inv->text = sfText_create();
    sfText_setFont(inv->text, data->font);
    sfText_setCharacterSize(inv->text, 3);
    create_slot_rect(win, inv);
    for (int i = 0; i < 8; i++) {
        inv->slot[i].item.data = NULL;
        inv->slot[i].index = i;
        inv->slot[i].selected = sfFalse;
    }
    init_item(win, inv);
    return win;
}
