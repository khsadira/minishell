#include "ft_minishell.h"

static char	*ft_replace_tild(char *str, char *tild)
{
	char	*ret;
	
	ret = ft_strdup(tild);
	ret = ft_strfjoin(&ret, (str + 1));	
	free(str);
	return (ret);
}

static char	*ft_tild_cd(char *str, t_env *env)
{
	if (str[0] && str[0] == '~' && str[1] && str[1] == '/')
	{
		while (env && !ft_strequ(env->name, "HOME"))
			env = env->next;
		str = ft_replace_tild(str, env->arg);
	}
	return (str);
}

int	ft_built_cd(t_lst *list, t_env *env)
{
	if (list->arg[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(list->arg[1], 2);
		return (0);
	}
	else
		list->arg[1] = ft_tild_cd(list->arg[1], env);
	if (access(list->arg[1], R_OK) == 0)
	{
		chdir(list->arg[1]);
		return (1);
	}
	ft_putstr_fd("cd : no such file or directory: ", 2);
	ft_putendl_fd(list->arg[1], 2);
	return (0);
}
