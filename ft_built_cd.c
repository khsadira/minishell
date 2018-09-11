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

static int		ft_print_cd_error(int nb_error, char *rep)
{
	if (nb_error == 1)
		ft_putstr_fd("cd : string not in pwd: ", 2);
	else if (nb_error == 2)
		ft_putstr_fd("cd : no such file or directory: ", 2);
	else if (nb_error == 3)
		ft_putstr_fd("cd: OLDPWD not set", 2);
	if (rep)
		ft_putstr_fd(rep, 2);
	ft_putchar_fd(10, 2);
	return (0);
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

	if (!list->arg[1])
		list = ft_creat_arg(list, *env);
	else if (list->arg[2])
		return (ft_print_cd_error(1, list->arg[1]));
	else if (ft_strequ(list->arg[1], "-"))
	{
		if (!(dir = ft_search_env("OLDPWD", *env)))
			return (ft_print_cd_error(3, NULL));
		free(list->arg[1]);
		list->arg[1] = ft_strdup(dir);
		ft_putendl(list->arg[1]);
	}
	if (access(list->arg[1], R_OK) == 0)
	{
		ft_setenv_char("OLDPWD", *env);
		chdir(list->arg[1]);
		return (1);
	}
	return (ft_print_cd_error(2, list->arg[1]));
}
