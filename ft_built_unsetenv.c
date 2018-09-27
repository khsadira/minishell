/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_unsetenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 15:18:42 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/27 15:20:42 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env	*ft_unsetenv(t_lst *list, t_env *l_env)
{
	t_env	*h_env;
	t_env	*tmp;

	if (ft_strequ(list->arg[1], "HOME"))
		return (l_env);
	h_env = l_env;
	while (l_env)
	{
		if (ft_strequ(l_env->name, list->arg[1]))
		{
			tmp->next = l_env->next;
			l_env->next = NULL;
			ft_freeenv(l_env);
		}
		tmp = l_env;
		l_env = l_env->next;
	}
	return (h_env);
}
