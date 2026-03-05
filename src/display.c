#include "../include/ft_ls.h"
#include <stdio.h>

void printOpt(const t_opt *opt)
{
    if (opt == NULL)
    {
        printf("Error: opt pointer is NULL\n");
        return;
    }

    ft_printf("Options:\n");
    ft_printf("h_file    : %s\n", opt->h_file ? "true" : "false");
    ft_printf("l_list    : %s\n", opt->l_list ? "true" : "false");
    ft_printf("recursive : %s\n", opt->recursive ? "true" : "false");
    ft_printf("t_sort    : %s\n", opt->t_sort ? "true" : "false");
    ft_printf("recursive : %s\n", opt->reverse ? "true" : "false");
}

void ErrOptNotFound(char c) {
    ft_printf("ft_ls: invalid option -- '%c'\nTry 'ls --help' for more information.\n", c);
}


void print_string(void *content)
{
    printf("%s\n", (char *)content);
}

void    print_file(void *content)
{
    t_file *file = (t_file*)content;
    if (!file)
    {
        printf("FILE: NULL\n");
        return;
    }

    printf("------ FILE ------\n");
    printf("name  : %s\n", file->name);
    printf("path  : %s\n", file->path);
    printf("size  : %ld\n", file->st.st_size);
    printf("links : %ld\n", file->st.st_nlink);
    printf("uid   : %d\n", file->st.st_uid);
    printf("gid   : %d\n", file->st.st_gid);
    printf("mode  : %o\n", file->st.st_mode);
    printf("mtime : %s", ctime(&file->st.st_mtime));
    printf("------------------\n");
}

void    print_list(t_list *list, void (*print_content)(void *))
{
    t_list  *tmp;

    tmp = list;
    while (tmp)
    {
        print_content(tmp->content);
        tmp = tmp->next;
    }
}