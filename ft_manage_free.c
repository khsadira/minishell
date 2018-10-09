/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:48:59 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/08 15:43:23 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_freedstr(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
	{
		ft_strdel(&arg[i]);
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
		ft_strdel(&(list->path));
		ft_strdel(&(list->cmd));
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
		ft_strdel(&(list->name));
		ft_strdel(&(list->arg));
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	ft_free_one_env(t_env *list)
{
	ft_strdel(&(list->name));
	ft_strdel(&(list->arg));
	list->next = NULL;
	free(list);
}

void	ft_freeall_exit(char **path_tab, t_lst *list,
						char **gnl_word, char **env)
{
	ft_freedstr(path_tab);
	ft_freelst(list);
	ft_freedstr(env);
	ft_freedstr(gnl_word);
	exit(1);
}

void	ft_freeall(char **path_tab, t_lst *list, char **env)
{
	int		i;

	i = 0;
	ft_freedstr(path_tab);
	ft_freedstr(env);
	ft_freelst(list);
}
