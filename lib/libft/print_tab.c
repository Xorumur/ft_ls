#include "libft.h"

void print_tab(char **tab) {
    int i = 0;
    while (tab[i]) {
        ft_putstr((char *)tab[i]);
        i++;
    }
}

int size_tab(char **tab) {
    int i = 0;
    while (tab[i]) {
        i++;
    }
    return i;
}