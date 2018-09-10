/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:48:59 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/10 13:49:54 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_freedstr(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
}

void	ft_freelst(t_lst *list)
{
	t_lst	*tmp;

	while (list)
	{
		free(list->path);
		free(list->cmd);
		ft_freedstr(list->arg);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	ft_freeenv(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		free(list->name);
		free(list->arg);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	ft_freeall_exit(char **ret, char **gnl, t_lst *list, t_env *env)
{
	ft_freedstr(ret);
	ft_freedstr(gnl);
	ft_freelst(list);
	ft_freeenv(env);
	exit(1);
}
