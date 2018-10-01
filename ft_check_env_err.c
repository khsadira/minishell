/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 16:02:37 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/01 16:04:22 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_check_env_err(char **arg, int stock, int i)
{
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
