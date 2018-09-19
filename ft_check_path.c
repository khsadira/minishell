/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 10:29:36 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/19 15:07:33 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*ft_to_command(char *str)
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

static t_lst	*ft_up_list(char *path, char *cmd, t_lst *list, int built)
{
	t_lst	*new_ele;

	new_ele = NULL;
	if (built == 2)
	{
		new_ele = ft_newele(ft_strdup(cmd));
		new_ele->built = 0;
	}
	else if (built == 0)
	{
		new_ele = ft_newele(ft_strdup(path));
		new_ele->built = 0;
	}
	else
	{
		new_ele = ft_newele(ft_strdup(cmd));
		new_ele->built = 1;
	}
	list = ft_addlist(list, new_ele);
	return (list);
}

static t_lst	*ft_check_cmd(char **path_tab, t_lst *list, char *cmd)
{
	int		i;
	char	*path;
	int		com;

	com = 0;
	i = 0;
	while (path_tab[i])
	{
		path = ft_creat_path(path_tab[i], cmd);
		if (ft_acces(cmd, path) == 1)
		{
			com = 1;
			list = ft_up_list(path, cmd, list, 0);
			free(path);
			break ;
		}
		free(path);
		i++;
	}
	return (list);
}

static t_lst	*ft_path_cmd(t_lst *list, char *cmd, char *cmd_word)
{
	if ((access(cmd, X_OK)) == 0)
	{
		list = ft_up_list(NULL, cmd, list, 2);
		return (list);
	}
	return (NULL);
}

t_lst			*ft_check_path(char **path_tab, char *cmd_word, int i, int j)
{
	t_lst	*list;
	char	*cmd;
	char	*tmp;

	list = NULL;
	if (ft_strlen(cmd_word) == 0)
		return (NULL);
	cmd = ft_to_command(cmd_word);
	if (ft_strnequ(cmd, "./", 2) || ft_strnequ(cmd, "/", 1) || ft_strnequ(cmd, "..", 2))
		list = ft_path_cmd(list, cmd, cmd_word);
	else if (ft_check_built(cmd) >= 0)
		list = ft_up_list(NULL, cmd, list, 1);
	else if (path_tab)
		list = ft_check_cmd(path_tab, list, cmd);
	if (!list)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Command not found.", 2);
		free(cmd);
		return (NULL);
	}
	list->cmd = cmd;
	list->arg = ft_strsplit(cmd_word, ' ');
	return (list);
}
