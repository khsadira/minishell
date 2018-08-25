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

int	ft_built_cd(t_lst *list, t_env *env, char **last_dir)
{
	if (!list->arg[1])
		list->arg[1] = ft_strdup("~/");
	if (list->arg[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(list->arg[1], 2);
		return (0);
	}
	else if (list->arg[1] && ft_strequ(list->arg[1], "-"))
	{
		printf("ici\n");
		if ((*last_dir) == NULL)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (0);
		}
		free(list->arg[1]);
		list->arg[1] = ft_strdup((*last_dir));
		ft_putendl(list->arg[1]);
	}
	else if (list->arg[1])
		list->arg[1] = ft_tild_cd(list->arg[1], env);
	if (access(list->arg[1], R_OK) == 0)
	{
		if (*last_dir)
		{
			free(*last_dir);
			free(last_dir);
		}
		chdir(list->arg[1]);
		(*last_dir) = getcwd(NULL, 0);
		return (1);
	}
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(list->arg[1], 2);
	return (0);
}
