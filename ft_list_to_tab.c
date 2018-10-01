#include "ft_minishell.h"

static	int	ft_env_len(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static void	ft_compare(t_env *env, char **ret)
{
	int	i;
	int	len;
	char	*name;
	char	*arg;

	i = 0;
	while (ret[i])
	{
		len = ft_strlen(ret[i]);
		name = ft_strsub(ret[i], 0, ft_strichr(ret[i], '='));
		arg = ret[i] + ft_strichr(ret[i], '=') + 1;
		if (!ft_strequ(name, env->name) && !ft_strequ(arg, env->arg))
			printf("%s | %s\n", name, env->name);
		env = env->next;
		i++;
	}
}

static char	*ft_to_env(char *name, char *arg)
{
	char	*ret;
	int	i;
	int	j;
	int	len;

	ret = NULL;
	len = ft_strlen(name) + ft_strlen(arg) + 1;
	ret = ft_strnew(len);
	i = 0;
	j = 0;
	while (name[j])
		ret[i++] = name[j++];
	ret[i++] = '=';
	j = 0;
	while (arg[j])
		ret[i++] = arg[j++];
	ret[i] = '\0';
	return (ret);
}

char	**ft_list_to_env(t_env *env)
{
	char	**ret;
	int	len;
	int	i;

	i = 0;
	if (!(len = ft_env_len(env)))
		return (NULL);
	if (!(ret = malloc(sizeof(*ret) * (len + 1))))
		return (NULL);
	ret[len] = NULL;
	len = 0;
	while (env)
	{
		ret[i++] = ft_to_env(env->name, env->arg);
		env = env->next;
	}
	return (ret);
}
