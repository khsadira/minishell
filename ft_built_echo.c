/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:03:15 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/02 13:43:25 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_built_echo(t_lst *list, t_env *env)
{
	int		i;
	int		n;
	t_env	*h_env;

	h_env = env;
	n = 0;
	if (list->arg[1] && ft_strequ(list->arg[1], "-n"))
	{
		n = 1;
		i = 2;
	}
	else
		i = 1;
	while (list->arg[i])
	{
		if (i != 1)
			ft_putchar(' ');
		ft_putstr(list->arg[i++]);
	}
	if (!n)
		ft_putchar(10);
	return (1);
}
