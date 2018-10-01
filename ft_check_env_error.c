/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:11:55 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 15:59:23 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_put_setenv_error(int err)
{
	if (err == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (err == 2)
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (err == 3)
	{
		ft_putstr_fd("setenv: Variable name must contain", 2);
		ft_putendl_fd(" alphanumeric characters.", 2);
	}
	return (1);
}

int			ft_check_env_error(t_lst *list)
{
	int	i;

	i = 0;
	if (!ft_isalpha(list->arg[1][i]))
		return (ft_put_setenv_error(1));
	if (list->arg[3])
		return (ft_put_setenv_error(2));
	else if (list->arg[1])
	{
		while (list->arg[1][i])
		{
			if (!ft_isalnum(list->arg[1][i]))
				return (ft_put_setenv_error(3));
			i++;
		}
	}
	return (0);
}
