#include "../include/ft_ls.h"

t_file  *fileStats(char *path, char *name)
{
    t_file *file;

    file = malloc(sizeof(t_file));
    if (!file)
        return NULL;

    file->path = ft_strdup(path);
    file->name = ft_strdup(name);
    if (!file->path || !file->name)
        return NULL; /* à clean proprement ensuite */

    if (lstat(file->path, &file->st) == -1)
        perror(file->path);

    return file;
}

t_list *getFiles(char *dirName) {
    DIR     *dir;
    struct dirent *entry;
    t_list *files = NULL;

    dir = opendir(dirName);
    if (dir != NULL) {
        while ((entry = readdir(dir))) {
            char *tmp_path = ft_strjoin(dirName, "/");
            char *path = ft_strjoin(tmp_path, entry->d_name);
            ft_lstadd_back(&files, ft_lstnew(fileStats(path, entry->d_name)));
        }
    }
    else {
        ft_printf("ls: cannot access '%s': No such file or directory\n", dirName);
    }
    closedir(dir);
    return files;
}

void dirDiscovery(t_cmd *cmd) {
    t_list *tmp = cmd->dirList;

    if (tmp == NULL) {
        print_list(getFiles("."), print_file);
    }
    else {
        while(tmp) {
            t_list *files = getFiles((char *)tmp->content);
            print_list(files, print_file);
            tmp = tmp->next;
        }
    }

    return;
}