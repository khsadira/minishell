#include "ft_minishell.h"

int	ft_built_echo(t_lst *list)
{
	return (1);
}


int	ft_check_built(t_lst *list)
{
	if (ft_strequ(list->cmd, "exit"))
		return (0);
	else if (ft_strequ(list->cmd, "env"))
		return (1);
	else if (ft_strequ(list->cmd, "setenv"))
		return (2);
	else if (ft_strequ(list->cmd, "unsetenv"))
		return (3);
	else if (ft_strequ(list->cmd, "echo"))
		return (4);
	else if (ft_strequ(list->cmd, "cd"))
		return (5);
	return (1);
}
