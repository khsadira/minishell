/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:49:10 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/10 09:26:37 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_env		*ft_init(int ac, char **av, t_env *l_env, char **env)
{
	(void)ac;
	av++;
	l_env = ft_creat_env(env, l_env);
	return (l_env);
}

static t_env		*ft_prog(t_env *env)
{
	char	**cmd;
	char	*line;
	int		ret;

	ret = 0;
	line = NULL;
	cmd = NULL;
	if ((ret = ft_regnl(&line)))
	{
		cmd = ft_rework_cmd(ft_strsplit(line, ';'), env);
		free(line);
		env = ft_start_prog(cmd, NULL, env, 0);
		ft_freedstr(cmd);
	}
	else if (ret == 0)
		write(1, "\n", 1);
	else
		exit(1);
	return (env);
}

int					main(int ac, char **av, char **env)
{
	t_env	*l_env;
	int		fd_term;

	l_env = ft_init(ac, av, NULL, env);
	fd_term = ft_is_term();
	while (1)
	{
		if (fd_term)
			ft_aff_prompt();
		signal(SIGINT, ft_signal);
		l_env = ft_prog(l_env);
		if (!fd_term)
			break ;
	}
	return (0);
}
