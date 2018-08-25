#include "ft_minishell.h"

static char	*ft_get_path(char **env, char *elem)
{
	int	a;
	int	b;
	int	k;

	a = 0;
	while (env[a])
	{
		b = 0;
		while (env[a][b])
		{
			if (env[a][b] == 'P' && env[a][b + 4] &&
				env[a][b + 1] == 'A' && env[a][b + 2] == 'T' &&
				env[a][b + 3] == 'H' && env[a][b + 4] == '=')
			{
				b += 5;
				k = b;
				while (env[a][k] && env[a][k] != '\n')
					k++;
				elem = ft_strsub(env[a], b, k);
				return (elem);
			}
			b++;
		}
		a++;
	}
	return (NULL);
}

static char	*ft_to_command(char *str)
{
	char	*cmd;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str[j] && str[j] == ' ')
		j++;
	cmd = NULL;
	i = j;
	while (str[i])
	{
		if (str[i] == ' ')
			return (ft_strsub(str, j, i - j));
		i++;
	}
	return (ft_strsub(str, j, i - j));
}

static t_lst	*ft_check_if_right(char **path_tab, char **cmd_word)
{
	int	i;
	int	j;
	char	*path;
	char	*cmd;
	int	com;
	t_lst	*list;
	t_lst	*new_ele;

	list = NULL;
	new_ele = NULL;
	path = NULL;
	j = 0;
	com = 0;
	while (cmd_word[j])
	{
		cmd = ft_to_command(cmd_word[j]);
		i = 0;
		if (ft_strequ(cmd, "exit") || ft_strequ(cmd, "env") || ft_strequ(cmd, "setenv") ||
			ft_strequ(cmd, "unsetenv") || ft_strequ(cmd, "cd") || ft_strequ(cmd, "echo"))
		{
			com = 1;
			new_ele = ft_newele(ft_strdup(cmd));
			new_ele->cmd = ft_strdup(cmd);
			new_ele->built = 1;
			list = ft_addlist(list, new_ele);
		}
		else
			while (path_tab[i])
			{
				path = ft_strjoin(path_tab[i], "/");
				path = ft_strfjoin(&path, cmd);
				if (!ft_strequ(cmd, "..") && !ft_strequ(cmd, ".") && access(path, R_OK || X_OK) == 0)
				{
					com = 1;
					new_ele = ft_newele(ft_strdup(path));
					new_ele->cmd = ft_strdup(cmd);
					new_ele->built = 0;
					list = ft_addlist(list, new_ele);
				}
				free(path);
				i++;
			}	
		if (com == 0)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(cmd);
		}
		com = 0;
		free(cmd);
		j++;
	}
	return (list);
}

static pid_t	ft_fork(char *path, char **arg, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, arg, env);
		return (0);
	}
	else if (pid < 0)
	{
		ft_putendl("fork error.");
		return (-1);
	}
	wait(&pid);
	return (1);
}

int 	main(int ac, char **av, char **env)
{
	char	*line;
	char	**gnl_word;
	char	*path;
	char	**path_tab;
	int	i;
	int	pid_value;;
	t_lst	*list;
	t_lst	*head;
	t_env	*l_env;
	t_env	*h_env;
	int	builtin;
	char	*current_dir;

	current_dir = NULL;
	path = NULL;
	line = NULL;
	gnl_word = NULL;
	path_tab = NULL;
	list = NULL;
	l_env = NULL;
	l_env = ft_creat_env(env, l_env);
	h_env = NULL;
	path = ft_get_path(env, path);
	path_tab = ft_strsplit(path, ':');
	free(path);
	while (1)
	{
		ft_putstr("$>");
		if (get_next_line(0, &line) > 0)
		{
			gnl_word = ft_treat_line(line);
			free(line);
		}
		else
			gnl_word = ft_treat_line(line);
		list = ft_put_cmd(ft_check_if_right(path_tab, gnl_word), gnl_word);
		head = list;
		while (list)
		{
			if (list->built == 1)
			{
				if ((builtin = ft_check_built(list)) == 0)
				{
					ft_freedstr(path_tab);
					ft_freedstr(gnl_word);
					ft_freelst(head);
					ft_freeenv(l_env);
					exit(1);
				}
				else if (builtin >= 1 && builtin <= 3)
					l_env = ft_built_env(list, l_env, builtin, env);
				else if (builtin == 4)
					ft_built_echo(list);
				else if (builtin == 5)
					ft_built_cd(list, l_env, &current_dir);
			}
			else
			{
				pid_value = ft_fork(list->path, list->arg, env);
				if (pid_value != 0 && pid_value != -1 && pid_value != -2)
					list->value = pid_value;
				pid_value = 0;
			}
			list = list->next;
		}
		ft_freedstr(gnl_word);
		ft_freelst(head);
	}
	ft_freedstr(path_tab);
}
