/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:49:10 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/10 14:19:26 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	**ft_get_path(t_env *env)
{
	while (env)
	{
		if (ft_strequ(env->name, "PATH"))
			return (ft_strsplit(env->arg, ':'));
		env = env->next;
	}
	return (NULL);
}

static char	*ft_to_command(char *str)
{
	char	*cmd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && str[j] == ' ')
		j++;
	cmd = NULL;
	i = j;
	while (str[i])
	{
		if (str[i] == ' ')
			return (ft_strsub(str, j, i - j));
		i++;
	}
	return (ft_strsub(str, j, i - j));
}

static t_lst	*ft_check_if_right(char **path_tab, char **cmd_word)
{
	int	i;
	int	j;
	char	*path;
	char	*cmd;
	int		com;
	t_lst	*list;
	t_lst	*new_ele;

	list = NULL;
	new_ele = NULL;
	path = NULL;
	j = 0;
	com = 0;

	while (cmd_word[j])
	{
		cmd = ft_to_command(cmd_word[j]);
		i = 0;
		if ((ft_strnequ(cmd, "./", 2)) || ft_strequ(cmd, "exit") || ft_strequ(cmd, "env") || ft_strequ(cmd, "setenv") ||
			ft_strequ(cmd, "unsetenv") || ft_strequ(cmd, "cd") || ft_strequ(cmd, "echo"))
		{
			com = 1;
			new_ele = ft_newele(ft_strdup(cmd));
			new_ele->cmd = ft_strdup(cmd);
			if (ft_strnequ(cmd, "./", 2))
				new_ele->built = 0;
			else
				new_ele->built = 1;
			list = ft_addlist(list, new_ele);
		}
		else if (cmd && cmd[0] && path_tab)
		{
			while (path_tab[i])
			{
				path = ft_strjoin(path_tab[i], "/");
				path = ft_strfjoin(&path, cmd);
				if (!ft_strequ(cmd, "..") && !ft_strequ(cmd, ".") && access(path, R_OK || X_OK) == 0)
				{
					com = 1;
					new_ele = ft_newele(ft_strdup(path));
					new_ele->cmd = ft_strdup(cmd);
					new_ele->built = 0;
					list = ft_addlist(list, new_ele);
				}
				free(path);
				i++;
			}	
		}
		if (com == 0 && cmd && cmd[0])
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(cmd);
		}
		com = 0;
		free(cmd);
		j++;
	}
	return (list);
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
				if ((builtin = ft_check_built(list)) == 0)
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
