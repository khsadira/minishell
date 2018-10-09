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

static t_env	*ft_call_builtin(t_lst *list, t_env *l_env, int builtin)
{
	if (builtin == 4)
		ft_built_echo(list, l_env);
	else if (builtin == 5)
		l_env = ft_built_cd(list, l_env);
	return (l_env);
}

t_env		*ft_start_prog(char **gnl_word, char **env, t_env *l_env, int i)
{
	int		builtin;
	t_lst	*list;
	char	**path_tab;

	while (gnl_word[i])
	{
		env = ft_list_to_env(l_env);
		path_tab = ft_get_path(l_env);
		list = ft_check_path(path_tab, gnl_word[i]);
		if (list && list->built == 1)
		{
			if ((builtin = ft_check_built(list->cmd)) == 0)
				ft_freeall_exit(path_tab, list, gnl_word, env);
			else if (builtin >= 1 && builtin <= 3)
				l_env = ft_check_env(list, l_env, builtin);
			else
				l_env = ft_call_builtin(list, l_env, builtin);
		}
		else if (list)
			ft_exec(list, env);
		ft_freeall(path_tab, list, env);
		i++;
	}
	return (l_env);
}

