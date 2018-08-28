#include "ft_minishell.h"

int	ft_built_echo(t_lst *list, t_env *env)
{
	int	i;
	int	p;
	t_env	*h_env;

	h_env = env;
	i = 1;
	while (list->arg[i])
	{
		if (i > 1 && p == 1)
			ft_putchar(' ');
		if (ft_strnequ(list->arg[i], "$", 1))
		{
			while (env)
			{
				if (ft_strequ(list->arg[i] + 1, env->name))
				{
					p = 1;
					ft_putstr(env->arg);
					break;
				}
				env = env->next;
			}
			env = h_env;
		}
		else if (ft_strnequ(list->arg[i], "#", 1))
			p = 0;
		else
		{
			p = 1;
			ft_putstr(list->arg[i]);
		}
		i++;
	}
	ft_putchar(10);
	return (1);
}
