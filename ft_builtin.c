#include "ft_minishell.h"

void	ft_built_echo(t_lst *list)
{
}

void	ft_built_cd(t_lst *list, t_env *env)
{
	printf("%s\n", env->name);
	chdir(list->arg[1]);
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
