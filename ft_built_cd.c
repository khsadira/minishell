/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 09:59:06 by khsadira          #+#    #+#             */
/*   Updated: 2018/09/27 14:26:49 by khsadira         ###   ########.fr       */
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

int				ft_built_cd(t_lst *list, t_env **env)
{
	char	*dir;
	int		i;

	if ((i = ft_check_cd_error(list->arg)) == -1)
		return (1);
	if (ft_check_opts(list->arg) == 0)
		list->arg[i] = ft_creat_cd_lnk(list->arg[i], *env);
	if (ft_strequ(list->arg[i], "-"))
	{
		if (!(dir = ft_search_env("OLDPWD", *env)))
			return (ft_print_cd_error(3, NULL));
		free(list->arg[i]);
		list->arg[i] = ft_strdup(dir);
		ft_putendl(list->arg[i]);
	}
	if (list->arg[i] == NULL && (i = 1))
		list = ft_creat_arg(list, *env);
	if (access(list->arg[i], R_OK) == 0)
	{
		ft_setenv_char("OLDPWD", *env);
		chdir(list->arg[i]);
		ft_setenv_char("PWD", *env);
		return (1);
	}
	return (ft_print_cd_error(2, list->arg[i]));
}
