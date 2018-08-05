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

static t_env	*ft_setenv(t_lst *list, t_env *l_env)
{
	int	i;
	t_env	*h_env;
	t_env	*tmp;

	h_env = l_env;
	i = 0;
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
	if (l_env == NULL)
		l_env = ft_creat_env(env, l_env);
	if (builtin == 1)
		ft_printenv(l_env);
	else if (builtin == 2)
		ft_setenv(list, l_env);
	else if (builtin == 3)
		ft_unsetenv(list, l_env);
	return (l_env);
}
