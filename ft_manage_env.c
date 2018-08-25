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
	int	len;
	int	i;
	int	nb;

	nb = ft_atoi(arg);
	i = 0;
	nb++;
	free(arg);
	ret = ft_itoa(nb);
	return (ret);
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
