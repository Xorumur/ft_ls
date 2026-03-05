#include "../include/ft_ls.h"

// ca return le char qui ne correspond a aucune sinon 
static char *handleFlags(char *arg, t_opt *options) {

    for (int i = 0; arg[i]; i++) {
        switch (arg[i]) {
            case 'R':
                options->recursive = true;
                break;
            case 'l':
                options->l_list = true;
                break;
            case 'r': 
                options->reverse = true;
                break;
            case 'a':
                options->h_file = true;
                break;
            case 't':
                options->t_sort = true;
            default:
                return &arg[i];
        }

    }
    return NULL;
}

static bool    isFlags(char *arg) {
    if (arg[0] == '-')
        return true;
    return false;
}


int parse_arg(t_cmd *cmd, char **av) {
    for (int i = 1; av[i]; i++) {
        if (isFlags(av[i]) && ft_strlen(av[i]) > 1) {
            char *ret = handleFlags(&av[i][1], cmd->opt);
            if (ret != NULL) {
                ErrOptNotFound(*ret);
                free(cmd->opt);
                return 2;
            }
        }
        else {
            cmd->hasPath = true;
            ft_lstadd_back(&cmd->dirList, ft_lstnew(av[i]));
        }
    }
    printOpt(cmd->opt);
    print_list(cmd->dirList, print_string);
    return -1;
}