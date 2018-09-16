#include "ft_minishell.h"

/*static char	**ft_manage_arg(char **arg)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (arg[i])
	{
		j = 0;
		k = 0;
		while (arg[i][j] && arg[i][j] == ' ')
		j++;
		while (arg[i][j])
		{
			if (arg[i][j] == ' ')
			{
				while (arg[i][j] && arg[i][j] == ' ')
					j++;
				j--;
			}
			arg[i][k++] = arg[i][j++];
		}
		if (arg[i][k] && (arg[i][k - 1] == ' '))
			arg[i][k - 1] = '\0';
		while (arg[i][k])
			arg[i][k++] = '\0';
		i++;
	}
	arg[i] = 0;
	return (arg);
}*/

t_lst	*ft_put_cmd(t_lst *list, char **arg, t_env *env)
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
