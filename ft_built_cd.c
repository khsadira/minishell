/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:59:06 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/11 09:59:13 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_check_opts(char **arg)
{
	int	i;
	int	opts;
	int	j;

	opts = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i][0] != '-' || ft_strequ("--", arg[i]))
			return (opts);
		j = 1;
		while (arg[i][j])
		{
			if (arg[i][j] == 'P')
				opts = 1;
			j++;
		}
		i++;
	}
	return (opts);
}

static t_lst	*ft_creat_arg(t_lst *list, t_env *env)
{
	char	*buf;
	char	**tab;
	char	*name;

	name = ft_search_env("HOME", env);
	buf = ft_strdup("cd ");
	buf = ft_strfjoin(&buf, name);
	tab = ft_strsplit(buf, ' ');
	ft_freedstr(list->arg);
	free(buf);
	list->arg = tab;
	return (list);
}

static char	*ft_lnk(char *path)
{
	char	link[255];
	int	rl;
	char	*ret;
	char	*tmp;

	rl = 0;
	if ((rl = readlink(path, link, 255)))
		link[rl] = '\0';
	tmp = ft_strdup(link);
	ret = ft_strdup("/");
	ret = ft_strfjoin(&ret, tmp);
	free(tmp);
	return (ret);
}

static char	*ft_creat_cd_lnk(char *str, t_env *env)
{
	char		*ret;
	struct stat	buf;
	char		*path;

	path = NULL;
	if (str[0] != '/')
	{
		path = ft_strdup(ft_search_env("PWD", env));
		path = ft_strfjoin(&path, str);
	}
	else
		path = ft_strdup(str);
	if (lstat(path, &buf))
	{
		free(path);
		return (str);
	}
	if (!S_ISLNK(buf.st_mode))
		return (str);
	ret = ft_lnk(path);
	free(str);
	free(path);
	return (ret);
}

int				ft_built_cd(t_lst *list, t_env **env)
{
	char	*dir;
	int	i;
	int	opts;

	if ((i = ft_check_cd_error(list->arg)) == -1)
		return (1);
	else if (ft_strequ(list->arg[i], "-"))
	{
		if (!(dir = ft_search_env("OLDPWD", *env)))
			return (ft_print_cd_error(3, NULL));
		free(list->arg[i]);
		list->arg[i] = ft_strdup(dir);
		ft_putendl(list->arg[i]);
	}
	opts = ft_check_opts(list->arg);
	if (list->arg[i] == NULL && (i = 1))
		list = ft_creat_arg(list, *env);
	if (opts == 1)
		list->arg[i] = ft_creat_cd_lnk(list->arg[i], *env);
	if (access(list->arg[i], R_OK) == 0)
	{
		ft_setenv_char("OLDPWD", *env);
		printf("%s\n", list->arg[i]);
		chdir(list->arg[i]);
		ft_setenv_char("PWD", *env);
		return (1);
	}
	return (ft_print_cd_error(2, list->arg[i]));
}
