#include "../include/ft_ls.h"

t_arch	*arch_new(char *dir_name)
{
	t_arch	*node;

	if (!dir_name)
		return (NULL);
	node = malloc(sizeof(t_arch));
	if (!node)
		return (NULL);
	node->dirName = ft_strdup(dir_name);
	if (!node->dirName)
	{
		free(node);
		return (NULL);
	}
	node->files = NULL;
	node->sub = NULL;
	return (node);
}

void	archAddFiles(t_arch *arch, t_list *files)
{
	if (!arch)
		return ;
	arch->files = files;
}

void archPushBackFiles(t_arch *arch, t_list *files) {
	if (!arch)
		return ;
	if (!arch->files) {
		arch->files = files;
		return ;
	}
	t_list *last = arch->files;
	while (last->next)
		last = last->next;
	last->next = files;
}

t_arch *getArchNodeByDirName(t_arch *root, char *dirName) {
    while (root) {
        if (ft_strcmp(root->dirName, dirName) == 0) {
            return root;
        }
        root = root->sub;
    }
    return NULL;
}

t_arch *insertFilesInArch(t_arch *arch, t_list *files) {
	t_arch *node = NULL;
	t_arch *cursor = arch;
	t_list *tmpFiles = files;
	while (tmpFiles) {
		t_file *file = (t_file *)tmpFiles->content;
		char **pathParts = ft_split(file->path, '/');
		cursor = getArchNodeByDirName(cursor, pathParts[size_tab(pathParts) - 2]);
		archPushBackFiles(cursor, ft_lstnew(file));
		free_tab(pathParts);
		tmpFiles = tmpFiles->next;
	}
	return node;
}

void buildArch(t_arch **root, t_list *dir) {
    t_list *tmp = dir;

    while (tmp) {
		t_file *file = (t_file *)tmp->content;
		char *path = file->path;
		char **pathParts = ft_split(path, '/');
        t_arch *current = *root;

		if (!pathParts)
			return ;
		for (int i = 0; pathParts[i]; i++) {
			if (!current) {
				// ft_printf("Adding arch node: %s\n", pathParts[i]);
				*root = arch_new(pathParts[i]);
				current = *root;
				continue;
			}
			if (ft_strcmp(current->dirName, pathParts[i]) == 0)
				continue;

			t_arch *child = current->sub;
			t_arch *prev = NULL;

			while (child) {
				if (ft_strcmp(child->dirName, pathParts[i]) == 0)
					break;
				prev = child;
				child = child->sub;
			}
			if (!child) {
				// ft_printf("Adding arch node: %s\n", pathParts[i]);
				child = arch_new(pathParts[i]);
				if (!prev)
					current->sub = child;
				else
					prev->sub = child;
			}
			current = child;
		}
        free_tab(pathParts);
        tmp = tmp->next;
    }
}