#include "ft_minishell.h"

int	ft_check_built(char	*cmd)
{
	if (ft_strequ(cmd, "exit"))
		return (0);
	else if (ft_strequ(cmd, "env"))
		return (1);
	else if (ft_strequ(cmd, "setenv"))
		return (2);
	else if (ft_strequ(cmd, "unsetenv"))
		return (3);
	else if (ft_strequ(cmd, "echo"))
		return (4);
	else if (ft_strequ(cmd, "cd"))
		return (5);
	return (-1);
}
