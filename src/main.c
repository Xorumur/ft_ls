#include "../include/ft_ls.h"


int main(int ac, char **av) {
    (void)ac;
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->opt   = malloc(sizeof(t_opt)); 
    
    int err = parse_arg(cmd, av);
    if (err > 0)
        return err;

    t_list *files = dirDiscovery(cmd);
    (void)files;
    // print_list(files, print_ls_long);
}