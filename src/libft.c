#include "../include/ft_ls.h"

bool contains(char *av, char c) { 
    for (int i = 0; av[i]; i++) {
        if (av[i] == c)
            return true;
    }
    return false;
}