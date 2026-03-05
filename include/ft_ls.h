#ifndef FT_LST_H
#define FT_LST_H

# include <stddef.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "ft_printf.h"
# include "../lib/libft/libft.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct s_opt
{
    bool h_file;  //-a, --alldo not ignore entries starting with .
    bool l_list; //  -l     use a long listing format
    bool recursive; // -R, --recursive list subdirectories recursively
    bool t_sort; // -t     sort by time, newest first; see --time
    bool reverse; // -r, --reverse reverse order while sorting
} t_opt;

typedef struct s_cmd {
    bool hasPath;
    char *path;
    char **dir;
    t_opt *opt;
    int exitCode;
    t_list  *dirList;
} t_cmd;

typedef struct s_file {
    char    *name;
    char    *path;
    struct stat st;
} t_file;

// Libft Functions
int ft_strlen(char *string);
bool contains(char *av, char c);

int parse_arg(t_cmd *cmd, char **av);
void dirDiscovery(t_cmd *cmd);

// Debug
void printOpt(const t_opt *opt);
void ErrOptNotFound(char c);
void print_string(void *content);
void print_file(void *content);
void print_list(t_list *list, void (*print_content)(void *));
#endif