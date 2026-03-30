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
            // TO DO If -a options is on, disable this if
            if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
                continue; 
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
        if (S_ISDIR(file->st.st_mode))
        {
            ft_lstadd_back(&dir, ft_lstnew(file));
        }
        tmp = tmp->next;
    }

    return dir;
}

t_list *getDirectoriesHidden(t_list *files) {
    t_list *tmp = files;
    t_list *dir = NULL;
    while (tmp) {
        t_file *file = (t_file *)tmp->content;
        if (file->name[0] == '.')
            continue ;
        if (S_ISDIR(file->st.st_mode))
        {
            ft_lstadd_back(&dir, ft_lstnew(file));
        }
        tmp = tmp->next;
    }

    return dir;
}

t_list *loopDiscovery(t_list **dirFiles, t_arch **archRoot, char *dirName, bool hidden) {
    t_list *files = getFiles(dirName);
    t_list *dir = NULL;
    if (hidden) {
        dir = getDirectories(files);
    } else {
        dir = getDirectoriesHidden(files);
    }
    // print_list(files, print_file);
    buildArch(archRoot, dir);
    insertFilesInArch(*archRoot, files);
    // print_list(dir, print_fileName);
    if (ft_lstsize(dir) > 0) {
        while (dir) {
            t_file *current = (t_file*)dir->content;
            t_list *filesDiscovered = loopDiscovery(
                dirFiles,
                archRoot,
                current->path,
                hidden
            );
            // archAddFiles(getArchNodeByDirName(*archRoot, current->name), files);
            ft_lstadd_back(dirFiles, filesDiscovered);
            dir = dir->next;
        }
    }
    return files;
}

/*
    Return une t_list * de t_file * 
*/
t_list *dirDiscovery(t_cmd *cmd) {
    t_list *tmp = cmd->dirList;
    t_list *arch = NULL;
    t_arch *archNode = NULL;
    if (tmp == NULL) {
        // print_list(getFiles("."), print_file);
        // return getFiles(".");
        t_list *DefaultContent = ft_lstnew(".");
        print_list(DefaultContent, print_string);
        tmp = DefaultContent;
    }
    // else {
        t_list *dirTarget = malloc(sizeof(t_list));
        dirTarget->content = tmp->content;
        dirTarget->next = NULL;
        while(tmp) {
            if (cmd->opt->recursive) {
                // L'option ajoute les fichiers qui commencent par '.'
                t_list *files = loopDiscovery(
                    &arch,
                    &archNode,
                    (char *)tmp->content,
                    cmd->opt->h_file
                );
                ft_lstadd_back(&arch, files);
                print_arch(archNode);
                return arch;
            } else {
                t_list *files = getFiles((char *)tmp->content);
                print_list(files, print_file);
                return files;
            }
            tmp = tmp->next;
        }
    // }
    return NULL;
}