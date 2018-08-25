#include "ft_minishell.h"

static char	**ft_manage_arg(char **arg)
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
	i = 0;
	return (arg);
}

t_lst	*ft_put_cmd(t_lst *list, char **arg)
{
	t_lst	*head;
	char	*cmd;
	int	i;

	head = list;
	arg = ft_manage_arg(arg);
	i = 0;
	while (list)
	{
		list->arg = ft_strsplit(arg[i], ' ');
		i++;
		list = list->next;
	}
	return (head);
}
