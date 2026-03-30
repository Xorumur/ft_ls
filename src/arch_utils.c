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

t_arch	*arch_last(t_arch *arch)
{
	if (!arch)
		return (NULL);
	while (arch->sub)
		arch = arch->sub;
	return (arch);
}

int	arch_size(t_arch *arch)
{
	int	size;

	size = 0;
	while (arch)
	{
		size++;
		arch = arch->sub;
	}
	return (size);
}

void	arch_pushback(t_arch **arch, t_arch *new_node)
{
	t_arch	*last;

	if (!arch || !new_node)
		return ;
	if (!*arch)
	{
		*arch = new_node;
		return ;
	}
	last = arch_last(*arch);
	last->sub = new_node;
}

void	archAddFiles(t_arch *arch, t_list *files)
{
	if (!arch)
		return ;
	arch->files = files;
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