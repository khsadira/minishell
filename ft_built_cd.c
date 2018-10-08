/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:59:06 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/08 15:42:24 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char			*get_cd_path(t_env *env, char *arg)
{
	char	*tmp;

	if (arg == NULL)
	{
		if ((tmp = ft_get_env(env, "HOME")))
			return (tmp);
		else
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	else if (ft_strequ(arg, "-"))
	{
		if ((tmp = ft_get_env(env, "OLDPWD")) != NULL)
			return (tmp);
		else
		{
			ft_putendl_fd("minishell: cd : OLDPWD not set", 2);
			return (NULL);
		}
	}
	else
		return (arg);
}

static int			check_error_path(char *path, char *arg)
{
	struct stat		stbuf;
	DIR				*diropen;

	if (path == NULL)
		return (-1);
	if (lstat(path, &stbuf) == -1)
	{
		ft_no_such_file_or_dir("cd: ", arg);
		return (-1);
	}
	if (!S_ISDIR(stbuf.st_mode) && !S_ISLNK(stbuf.st_mode))
	{
		ft_not_dir("cd: ", arg);
		return (-1);
	}
	if (!(diropen = opendir(path)))
	{
		ft_permission_denied("cd: ", arg);
		return (-1);
	}
	else
		closedir(diropen);
	return (1);
}

static t_env		*init_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env = ft_setenv_c("PWD", cwd, env);
	return (env);
}

static int			ft_dstrlen(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

t_env				*ft_built_cd(t_lst *list, t_env *env)
{
	char	*path;
	char	*cwd;
	char	*pwd;

	if (ft_dstrlen(list->arg) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (env);
	}
	env = init_pwd(env);
	path = get_cd_path(env, list->arg[1]);
	if (check_error_path(path, list->arg[1]) == -1)
		return (env);
	if (path != NULL)
	{
		pwd = ft_get_env(env, "PWD");
		env = ft_setenv_c("OLDPWD", ft_strdup(pwd), env);
		chdir(path);
		cwd = getcwd(NULL, 0);
		env = ft_setenv_c("PWD", cwd, env);
	}
	return (env);
}
