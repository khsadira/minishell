/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:05:33 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/27 15:59:35 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static  t_env	*ft_dupenv(t_env *env)
{
	t_env	*new;
	t_env	*head;
	t_env	*tmp;

	head = NULL;
	tmp = env;
	new = NULL;
	while (tmp)
	{
		if (!(new = (t_env *)malloc(sizeof(*new))))
			return (NULL);
		new->name = ft_strdup(tmp->name);
		new->arg = ft_strdup(tmp->arg);
		new->next = NULL;
		head = ft_addenv(head, new);
		tmp = tmp->next;
	}
	return (head);

}

void			ft_built_env(t_lst *list, t_env *l_env, int i, int a)
{
	t_env	*env;

	if (a)
		env = l_env;
	else
		env = ft_dupenv(l_env);
	while (list->arg[i])
	{
		if (ft_strequ(list->arg[i], "env"))
			return (ft_built_env(list, env, i + 1, 1));
		else if (ft_strequ(list->arg[i], "-i"))
		{
			ft_freeenv(env);
			return (ft_built_env(list, NULL, i + 1, 1));
		}
		i++;
	}
	ft_printenv(env);
	if (env)
		ft_freeenv(env);
}
