#include "ft_minishell.h"

t_lst	*ft_put_cmd(t_lst *list, char **arg)
{
	t_lst	*head;
	int		i;
	char	*tmp;

	head = list;
	i = 0;
	while (arg[i])
	{
		tmp = arg[i];
		arg[i] = ft_strtrim(arg[i]);
		free(tmp);
		i++;
	}
	i = 0;
	while (list)
	{
		if (ft_strequ(arg[i], ""))
			i++;
		list->arg = ft_strsplit(arg[i], ' ');
		i++;
		list = list->next;
	}
	list = head;
	while (list)
	{
		printf("%s\n", list->cmd);
		list = list->next;
	}
	return (head);
}
