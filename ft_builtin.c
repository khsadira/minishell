/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:26:00 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 16:08:41 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env		*ft_check_env(t_lst *list, t_env *l_env, int builtin)
{
	int	a;

	if (builtin == 1)
	{
		a = ft_check_env_err(list->arg, 0, 0);
		ft_built_env(list, ft_dupenv(l_env), 0, a);
	}
	else if (builtin == 2)
		ft_setenv(list, l_env);
	else if (builtin == 3)
		ft_unsetenv(list, l_env);
	return (l_env);
}

int			ft_check_built(char *cmd)
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
