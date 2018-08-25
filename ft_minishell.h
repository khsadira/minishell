#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "./libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>

typedef struct	s_lst
{
	char	*path;
	char	*cmd;
	char	**arg;
	int	value;
	int	built;
	struct	s_lst *next;
}		t_lst;

typedef struct	s_env
{
	char		*name;
	char		*arg;
	struct s_env	*next;
}		t_env;

char	**ft_treat_line(char const *str);
void	ft_freeenv(t_env *list);
t_env	*ft_creat_env(char **env, t_env *l_env);
t_env	*ft_built_env(t_lst *list, t_env *l_env, int builtin, char **env);
int	ft_built_echo(t_lst *list);
int	ft_built_cd(t_lst *list, t_env *env);
t_env	*ft_addenv(t_env *list, t_env *new_ele);
t_env	*ft_newenv(char *name, char *arg);
int	ft_check_built(t_lst *list);
t_lst	*ft_put_cmd(t_lst *list, char **arg);
t_lst	*ft_addlist(t_lst *list, t_lst *new_ele);
t_lst	*ft_newele(char *name);
void	ft_freedstr(char **arg);
void	ft_freelst(t_lst *list);
#endif
