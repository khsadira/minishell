#include "ft_minishell.h"

static void	ft_printenv(t_env *list)
{
	while (list)
	{
		ft_putstr(list->name);
		ft_putchar('=');
		ft_putendl(list->arg);
		list = list->next;
	}
}

static	t_env	*ft_unsetenv(t_lst *list, t_env *l_env)
{
	t_env	*h_env;
	t_env	*tmp;

	if (ft_strequ(list->arg[1], "HOME"))
		return (l_env);
	h_env = l_env;
	while (l_env)
	{
		if (ft_strequ(l_env->name, list->arg[1]))
		{
			tmp->next = l_env->next;
			l_env->next = NULL;
			ft_freeenv(l_env);
		}
		tmp = l_env;
		l_env = l_env->next;
	}
	return (h_env);
}

t_env	*ft_setenv_char(char *name, t_env *env)
{
	t_env	*h_env;

	h_env = env;
	while (env)
	{
		if (ft_strequ(env->name, name) == 1)
		{
			if (env->arg)
				free(env->arg);
			env->arg = getcwd(NULL, 0);
			return (h_env);
		}
		env = env->next;
	}
	env = ft_newenv(ft_strdup(name), getcwd(NULL, 0));
	h_env = ft_addenv(h_env, env);
	return (h_env);
}

t_env	*ft_setenv(t_lst *list, t_env *l_env)
{
	t_env	*h_env;

	h_env = l_env;
	if (!list->arg[1])
		return (h_env);
	if (!list->arg[2])
		list->arg[2] = ft_strdup("");
	while (l_env)
	{
		if (ft_strequ(l_env->name, list->arg[1]))
		{
			free(l_env->arg);
			l_env->arg = ft_strdup(list->arg[2]);
			return (h_env);
		}
		l_env = l_env->next;
	}
	l_env = ft_newenv(ft_strdup(list->arg[1]), ft_strdup(list->arg[2]));
	h_env = ft_addenv(h_env, l_env);
	return (h_env);
}

t_env	*ft_built_env(t_lst *list, t_env *l_env, int builtin, char **env)
{
	if (builtin == 1)
		ft_printenv(l_env);
	else if (builtin == 2)
		ft_setenv(list, l_env);
	else if (builtin == 3)
		ft_unsetenv(list, l_env);
	return (l_env);
}
