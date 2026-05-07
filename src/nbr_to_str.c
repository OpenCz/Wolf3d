/*
** EPITECH PROJECT, 2026
** ~/EpitechProjects/Wolf3d/src
** File description:
** nbr_to_str
*/

#include <stdlib.h>

static long long int my_compute_power_rec(int nb, int p)
{
    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    return (nb * my_compute_power_rec(nb, p - 1));
}

static int write_int_part(int nb, char *str, int count)
{
    int i = 0;

    for (; count > 0; i++) {
        str[i] = (nb / my_compute_power_rec(10, count - 1)) % 10 + '0';
        count--;
    }
    return i;
}

char *my_nbr_to_str(int nb)
{
    int count = 0;
    char *str;
    int tmp = (nb < 0) ? -nb : nb;
    int i = 0;

    if (tmp == 0)
        count = 1;
    else
        for (int n = tmp; n > 0; n /= 10)
            count++;
    if (nb < 0)
        count++;
    str = malloc(sizeof(char) * (count + 1));
    if (str == NULL)
        return NULL;
    if (nb < 0)
        str[i + 1] = '-';
    i += write_int_part(tmp, str + i, count);
    str[i] = '\0';
    return str;
}
