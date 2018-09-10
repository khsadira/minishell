#include "ft_minishell.h"

static char	**ft_manage_arg(char **arg)
{
	int	i;
	int	j;
	int	k;
	int	q;
	int	dq;

	dq = 0;
	q = 0;
	i = 0;
	while (arg[i])
	{
		j = 0;
		k = 0;
		while (arg[i][j] && arg[i][j] == ' ')
			j++;
		while (arg[i][j])
		{
			if (arg[i][j] == '"' && q == 0)
			{
				if (dq == 0)
					dq = 1;
				else
					dq = 0;
			}
			else if (arg[i][j] == '\'' && dq == 0)
			{
				if (q == 0)
					q = 1;
				else
					q = 0;
			}
			else if (arg[i][j] == ' ' && dq == 0 && q == 0)
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
}

t_lst	*ft_put_cmd(t_lst *list, char **arg, t_env *env)
{
	t_lst	*head;
	int		i;

	head = list;
	arg = ft_manage_arg(arg);

	i = 0;
	while (list)
	{
		if (ft_strequ(arg[i], ""))
				i++;
		list->arg = ft_strsplit(arg[i], ' ');
		i++;
		list = list->next;
	}
	return (head);
}
