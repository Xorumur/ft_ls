#include "../include/ft_ls.h"

t_arch	*arch_new(char *dir_name)
{
	t_arch	*node;

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
	node->next = NULL;
	return (node);
}

t_arch	*arch_last(t_arch *arch)
{
	if (!arch)
		return (NULL);
	while (arch->next)
		arch = arch->next;
	return (arch);
}

int	arch_size(t_arch *arch)
{
	int	size;

	size = 0;
	while (arch)
	{
		size++;
		arch = arch->next;
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
	last->next = new_node;
}

void	arch_add_files(t_arch *arch, t_list *files)
{
	if (!arch)
		return ;
	arch->files = files;
}