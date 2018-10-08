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
		ft_strdel(&list->path);
		ft_strdel(&list->cmd);
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

void	ft_freeall_exit(char **path_tab, t_lst *list,
						char **gnl_word, char **env)
{
	if (path_tab)
		ft_freedstr(path_tab);
	ft_freelst(list);
	if (env)
		ft_freedstr(env);
	if (gnl_word)
		ft_freedstr(gnl_word);
	exit(1);
}

void	ft_freeall(char **path_tab, t_lst *list, char **env)
{
	int		i;

	i = 0;
	if (path_tab)
		ft_freedstr(path_tab);
	if (env)
		ft_freedstr(env);
	ft_freelst(list);
}
