/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:11:55 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/11 10:25:28 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_check_env_error(t_lst *list)
{
	int		i;

	i = 0;
	if (list->arg[3])
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (1);
	}
	else if (list->arg[2])
	{
		while (list->arg[2][i])
		{
			if (!(list->arg[2][i] >= 'a' && list->arg[2][i] <= 'z') ||
				!(list->arg[2][i] >= 'A' && list->arg[2][i] <= 'Z') ||
				!(list->arg[2][i] >= '0' && list->arg[2][i] <= '9'))
			{
				ft_putstr_fd("setenv: Variable name must contain", 2);
				ft_putendl_fd(" alphanumeric characters.", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
