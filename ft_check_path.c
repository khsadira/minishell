/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:29:36 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/11 11:13:27 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*ft_to_command(char *str)
{
	char	*cmd;
	int		i;
	int		j;

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

static t_lst	*ft_up_list(char *cmd, t_lst *list, int built)
{
	t_lst	*new_ele;

	new_ele = NULL;
	new_ele = ft_newele(ft_strdup(cmd));
	new_ele->cmd = ft_strdup(cmd);
	if (built == 0)
		new_ele->built = 0;
	else if (ft_strnequ(cmd, "./", 2))
		new_ele->built = 0;
	else
		new_ele->built = 1;
	list = ft_addlist(list, new_ele);
	return (list);
}

static char		*ft_creat_path(char *path_tab, char *cmd)
{
	char *path;

	path = NULL;
	path = ft_strjoin(path_tab, "/");
	path = ft_strfjoin(&path, cmd);
	return (path);
}

static int		ft_acces(char *cmd, char *path)
{
	if (!ft_strequ(cmd, ".") &&
		!ft_strequ(cmd, "..") &&
		access(path, R_OK || X_OK) == 0)
		return (1);
	return (0);
}

t_lst	*ft_check_path(char **path_tab, char **cmd_word, int i, int j)
{
	t_lst	*list;
	char	*cmd;
	char	*path;

	list = NULL;
	while (cmd_word[j])
	{
		cmd = ft_to_command(cmd_word[j]);
		if (ft_check_built(cmd) >= 0)
			list = ft_up_list(cmd, list, 1);
		else if (cmd && cmd[0] && path_tab)
		{
			i = 0;
			while (path_tab[i])
			{
				path = ft_creat_path(path_tab[i], cmd);
				if (ft_acces(cmd, path))
					list = ft_up_list(cmd, list, 0);
				free(path);
				i++;
			}
		}
		free(cmd);
		j++;
	}
	return (list);
}

t_lst	*ft_check_if_right(char **path_tab, char **cmd_word)
{
	int	i;
	int	j;
	char	*path;
	char	*cmd;
	int		com;
	t_lst	*list;
	t_lst	*new_ele;

	list = ft_check_path(path_tab, cmd_word, 0, 0);
	return (list);
	/*
	new_ele = NULL;
	path = NULL;
	j = 0;
	com = 0;
	while (cmd_word[j])
	{
		cmd = ft_to_command(cmd_word[j]);
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
			i = 0;
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
*/}
