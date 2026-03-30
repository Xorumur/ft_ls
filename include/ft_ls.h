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

typedef struct s_arch {
    char *dirName;
    t_list *files;

    struct s_arch *sub; 
} t_arch;

// Libft Functions
int ft_strlen(char *string);
bool contains(char *av, char c);

int parse_arg(t_cmd *cmd, char **av);
t_list *dirDiscovery(t_cmd *cmd);
t_list *getFiles(char *dirName);
t_list *getDirectories(t_list *files);
t_list *getDirectoriesHidden(t_list *files);

t_arch  *arch_new(char *dir_name);
void    archAddFiles(t_arch *arch, t_list *files);
void    arch_happend_child(t_arch **root, char *path, char *dirName, t_list *files);
void    buildArch(t_arch **root, t_list *dir);
t_arch *getArchNodeByDirName(t_arch *root, char *dirName);
t_arch *insertFilesInArch(t_arch *arch, t_list *files);
// Debug
void printOpt(const t_opt *opt);
void ErrOptNotFound(char c);
void print_string(void *content);
void print_file(void *content);
void print_list(t_list *list, void (*print_content)(void *));
void print_arch(t_arch *arch);
void print_fileName(void *content);

// printer
void    print_ls_long(void *content);

#endif