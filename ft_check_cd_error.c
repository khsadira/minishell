#include "ft_minishell.h"

int		ft_print_cd_error(int nb_error, char *rep)
{
	if (nb_error == 1)
		ft_putstr_fd("cd : string not in pwd: ", 2);
	else if (nb_error == 2)
		ft_putstr_fd("cd : no such file or directory: ", 2);
	else if (nb_error == 3)
		ft_putstr_fd("cd: OLDPWD not set", 2);
	if (rep)
		ft_putstr_fd(rep, 2);
	ft_putchar_fd(10, 2);
	return (0);
}

static int	ft_check_cd_pars(char *str)
{
	int	i;
	
	if (ft_strequ("--", str))
			return (2);
	if (ft_strequ("-", str))
			return (1);
	if (str[0] != '-')
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'L' && str[i] != 'P')
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_cd_error(char **arg)
{
	int	i;
	int	len;
	int	stock;

	stock = 0;
	len = 0;
	while (arg[len])
		len++;
	i = 1;
	while (arg[i])
	{
		if ((stock = ft_check_cd_pars(arg[i])))
			break;
		i++;
	}
	if (stock == 2)
		i++;
	if (i + 1 < len)
	{
		ft_print_cd_error(1, arg[i]);
		return (-1);
	}
	return (i);
}
