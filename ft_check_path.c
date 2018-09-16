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

/*
void	ft_compare_list(t_lst *l1, t_lst *l2)
{
	int i = 0;
	if (ft_strequ(l1->path, l2->path))
		printf("path = 1\n");
	else
	{
		printf("%s\n%s\n\n", l1->path, l2->path);
		printf("path = 2\n");
	}
	if (ft_strequ(l1->cmd, l2->cmd))
		printf("cmd = 1\n");
	else
		printf("cmd= 2\n");
	while (l1->arg[i] && l2->arg[i])
	{
		if (ft_strequ(l1->arg[i], l2->arg[i]))
			printf("arg = 1\n");
		else
			printf("arg = 2\n");
		i++;
	}
	printf("value = %d | %d\nbuilt = %d | %d\n", l1->value, l2->value, l1->built, l2->built);
}
*/

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

static t_lst	*ft_up_list(char *path, char *cmd, t_lst *list, int built)
{
	t_lst	*new_ele;

	new_ele = NULL;
	new_ele = ft_newele(ft_strdup(path));
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

static t_lst	*ft_check_cmd(char **path_tab, t_lst *list, char *cmd)
{
	int	i;
	char	*path;
	int	com;

	com = 0;
	i = 0;
	while (path_tab[i])
	{
		path = ft_creat_path(path_tab[i], cmd);
		if (ft_acces(cmd, path) == 1)
		{
			com = 1;
			list = ft_up_list(path, cmd, list, 0);
		}
		free(path);
		i++;
	}
	if (com == 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(cmd);
	}
	return (list);
}

t_lst	*ft_check_path(char **path_tab, char **cmd_word, int i, int j)
{
	t_lst	*list;
	char	*cmd;
	char	*path;
	t_lst	*list2;

	list = NULL;
	while (cmd_word[j])
	{
		cmd = ft_to_command(cmd_word[j]);
		if (ft_check_built(cmd) >= 0)
			list = ft_up_list(path, cmd, list, 1);
		else if (path_tab)
			list = ft_check_cmd(path_tab, list, cmd);
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
	t_lst	*new_ele;
	t_lst *list;

	new_ele = NULL;
	path = NULL;
	j = 0;
	com = 0;
	list = NULL;
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
}
