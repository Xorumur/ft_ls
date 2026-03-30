#include "libft.h"

void print_tab(void **tab) {
    int i = 0;
    while (tab[i]) {
        ft_putstr((char *)tab[i]);
        i++;
    }
}