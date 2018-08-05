#include "ft_minishell.h"

void	ft_freedstr(char **arg)
{
	int	i;

	i = 0;
	while ((arg)[i])
		free((arg)[i++]);
	free(arg);
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
