/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:06:41 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/11 10:07:25 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_printenv(t_env *list)
{
	while (list)
	{
		ft_putstr(list->name);
		ft_putchar('=');
		ft_putendl(list->arg);
		list = list->next;
	}
}
