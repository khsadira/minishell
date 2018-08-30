#include "ft_minishell.h"

void	ft_freedstr(char **arg)
{
	int	i;

	i = 0;
	printf("here1\n");
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	printf("here2\n");
	if (arg)
		free(arg);
	printf("here3\n");
}

void	ft_freelst(t_lst *list)
{
	t_lst	*tmp;

	while (list)
	{
		free(list->path);
		free(list->cmd);
		ft_freedstr(list->arg);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	ft_freeenv(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		free(list->name);
		free(list->arg);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
