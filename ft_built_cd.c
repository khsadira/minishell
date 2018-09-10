#include "ft_minishell.h"

/*static char	*ft_replace_tild(char *str, char *tild)
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
*/

static char	*ft_creat_arg(t_lst *list, t_env *env)
{
i	ft_str	

	return (list);
}

int	ft_built_cd(t_lst *list, t_env **env)
{
	char	*dir;

/*	if (!list->arg[1])
		list->arg[1] = ft_strdup("~/");
	else */
	if (!list->arg[1])
		list->arg = ft_creat_arg(list->arg, env);
	else if (list->arg[2])
	{
		ft_putstr_fd("cd : string not in pwd: ", 2);
		ft_putendl_fd(list->arg[1], 2);
		return (0);
	}
	else if (ft_strequ(list->arg[1], "-"))
	{
		if (!(dir = ft_search_env("OLDPWD", *env)))
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (0);
		}
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
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(list->arg[1], 2);
	return (0);
}
