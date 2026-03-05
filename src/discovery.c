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

t_list *getDirectories(t_list *files) {
    t_list *tmp = files;
    t_list *dir = NULL;
    while (tmp) {
        t_file *file = (t_file *)tmp->content;
        if (S_ISDIR(file->st.st_mode) \
            && ft_strcmp(file->name, ".") != 0 \
            && ft_strcmp(file->name, "..") != 0)
        {
            // ft_lstadd_back(&dir, ft_lstnew(tmp->content));
            ft_lstadd_back(&dir, ft_lstnew(file));
        }
        tmp = tmp->next;
    }

    return dir;
}

t_list *loopDiscovery(t_list *dirFiles, char *dirName) {
    t_list *files = getFiles(dirName);
    ft_lstadd_back(&dirFiles, ft_lstnew(files));
    t_list *dir = getDirectories(files);
    print_list(dir, print_string);
    while (dir) {
        t_file *current = (t_file*)dir->content;
        ft_lstadd_back(&dirFiles, loopDiscovery(dirFiles, current->path));
        dir = dir->next;
    }
    return dirFiles;
}

void dirDiscovery(t_cmd *cmd) {
    t_list *tmp = cmd->dirList;

    if (tmp == NULL) {
        print_list(getFiles("."), print_file);
    }
    else {
        while(tmp) {
            // t_list *files = getFiles((char *)tmp->content);
            // print_list(files, print_file);
            if (cmd->opt->recursive) {
                t_list *arch = NULL;
                loopDiscovery(arch, (char *)tmp->content);
                // print_list(loopDiscovery(arch, (char *)tmp->content), print_file);
            }
            tmp = tmp->next;
        }
    }
    return;
}