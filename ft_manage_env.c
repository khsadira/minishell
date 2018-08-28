#include "ft_minishell.h"

static	char	*ft_return_arg(char *str)
{
	char	*arg;
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	arg = ft_strdup(str + i);
	return (arg);
}

static	char	*ft_return_name(char *str)
{
	char	*name;
	int	j;

	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	name = ft_strsub(str, 0, j);
	return (name);
}

static char	*ft_up_shlvl(char *arg)
{
	char	*ret;
	int	nb;

	nb = ft_atoi(arg);
	nb++;
	free(arg);
	ret = ft_itoa(nb);
	return (ret);
}

char	**ft_push_shlvl(char **env)
{
/*	int	i;
	int	j;
	int	nb;
	char	*ret;
	int	len;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], "SHLVL", 5))
		{
			len = ft_strlen(env[i]);
			nb = ft_atoi(env[i] + 6);
			nb++;
			ret = ft_itoa(nb);
			//ret = ft_strdup("SHLVL=");
			//ret = ft_strfjoin(&ret, ft_itoa(nb));
			if (env[i][len - 1])
			{
				if (env[i][len - 2] != '=')
					env[i][len - 2]++;
			}
			env[i][ft_strlen(env[i]) - 1]++;
		}
		printf("%s\n", env[i]);
		i++;
	}*/
	return (env);
}

char		*ft_search_env(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strequ(env->name, str) == 1)
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_creat_env(char **env, t_env *l_env)
{
	char	*name;
	char	*arg;
	int	i;
	t_env	*new_ele;

	i = 0;
	while (env[i])
	{
		name = ft_return_name(env[i]);
		arg = ft_return_arg(env[i]);
		if (ft_strequ(name, "SHLVL"))
			arg = ft_up_shlvl(arg);
		new_ele = ft_newenv(name, arg);
		l_env = ft_addenv(l_env, new_ele);
		i++;
	}
	return (l_env);
}
