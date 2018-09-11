/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:49:10 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/11 10:41:34 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	**ft_get_path(t_env *env)
{
	char	**tab;

	while (env)
	{
		if (ft_strequ(env->name, "PATH"))
			return (ft_strsplit(env->arg, ':'));
		env = env->next;
	}
	return (NULL);
}

int 	main(int ac, char **av, char **env)
{
	char	*line;
	char	**gnl_word;
	char	**path_tab;
	t_lst	*list;
	t_lst	*head;
	t_env	*l_env;
	int		builtin;

	line = NULL;
	list = NULL;
	l_env = ft_creat_env(env, l_env);
	while (1)
	{
		ft_signal();
		ft_putstr("$>");
		if (get_next_line(0, &line) > 0)
		{
			gnl_word = ft_rework_cmd(ft_strsplit(line, ';'), l_env);
			free(line);
		}
		else
			gnl_word = ft_rework_cmd(ft_strsplit(line, ';'), l_env);
		path_tab = ft_get_path(l_env);
		list = ft_put_cmd(ft_check_if_right(path_tab, gnl_word), gnl_word, l_env);
		head = list;
		while (list)
		{
			if (list->built == 1)
			{
				if ((builtin = ft_check_built(list->cmd)) == 0)
					ft_freeall_exit(path_tab, gnl_word, head, l_env);
				else if (builtin >= 1 && builtin <= 3)
					l_env = ft_built_env(list, l_env, builtin, env);
				else if (builtin == 4)
					ft_built_echo(list, l_env);
				else if (builtin == 5)
					ft_built_cd(list, &l_env);	
			}
			else
				ft_exec(list, env);
			list = list->next;
		}
		ft_freedstr(path_tab);
		ft_freedstr(gnl_word);
		ft_freelst(head);
	}
}
