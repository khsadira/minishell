/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:49:10 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/27 15:37:41 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		**ft_get_path(t_env *env)
{
	while (env)
	{
		if (ft_strequ(env->name, "PATH"))
			return (ft_strsplit(env->arg, ':'));
		env = env->next;
	}
	return (NULL);
}

static int	ft_start_prog(char **gnl_word, char **env, t_env *l_env, int i)
{
	int		builtin;
	t_lst	*list;
	char	**path_tab;

	while (gnl_word[i])
	{
		path_tab = ft_get_path(l_env);
		list = ft_check_path(path_tab, gnl_word[i], 0, 0);
		if (list && list->built == 1)
		{
			if ((builtin = ft_check_built(list->cmd)) == 0)
				ft_freeall_exit(path_tab, list, gnl_word);
			else if (builtin >= 1 && builtin <= 3)
				l_env = ft_check_env(list, l_env, builtin, env);
			else if (builtin == 4)
				ft_built_echo(list, l_env);
			else if (builtin == 5)
				ft_built_cd(list, &l_env);
		}
		else if (list)
			ft_exec(list, env);
		ft_freeall(path_tab, list);
		i++;
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	char	**gnl_word;
	t_env	*l_env;

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
		ft_start_prog(gnl_word, env, l_env, 0);
		ft_freedstr(gnl_word);
	}
}
