#include "ft_minishell.h"

int	ft_check_env_err(char **arg)
{
	int	i;
	int	stock;

	stock = 0;
	i = 0;
	while (arg[i])
	{
		if (ft_strequ(arg[i], "env"))
		{
			stock = 1;
			i++;
		}
		else if (ft_strequ(arg[i], "-i") && stock == 1)
		{
			stock = 1;
			i++;
		}
		else if (ft_strchr(arg[i], '=') && (stock == 1 || stock == 2))
		{
			stock = 2;
			i++;
		}
		else
			return (i);

	}
	return (i);
}
