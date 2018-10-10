/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:35:30 by khsadira          #+#    #+#             */
/*   Updated: 2018/10/10 09:37:00 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "./libft/libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_lst
{
	char			*path;
	char			*cmd;
	char			**arg;
	int				value;
	int				built;
	struct s_lst	*next;
}				t_lst;

typedef struct	s_env
{
	char			*name;
	char			*arg;
	struct s_env	*next;
}				t_env;

int				ft_is_term(void);
int				ft_regnl(char **str);
int				ft_dstrlen(char **arg);
void			ft_sig_handler(int signo);
void			ft_aff_prompt(void);
void			ft_no_such_file_or_dir(char *name, char *arg);
void			ft_not_dir(char *name, char *arg);
void			ft_permission_denied(char *name, char *arg);
char			*ft_get_env(t_env *env, char *name);
t_env			*ft_start_prog(char **gnl_word, char **env,
								t_env *l_env, int i);
char			**ft_list_to_env(t_env *env);
int				ft_check_env_err(char **arg, int stock, int i);
t_env			*ft_dupenv(t_env *env);
t_env			*ft_setenv_c(char *name, char *arg, t_env *env);
char			**ft_get_path(t_env *env);
void			ft_built_env(t_lst *list, t_env *l_env, int i, int a);
t_env			*ft_unsetenv(t_lst *list, t_env *l_env);
char			*ft_creat_cd_lnk(char *str, t_env *env);
int				ft_check_cd_error(char **arg);
int				ft_print_cd_error(int nb_error, char *rep);
char			*ft_creat_path(char *path_tab, char *cmd);
int				ft_acces(char *cmd, char *path);
void			ft_compare_list(t_lst *l1, t_lst *l2);
void			ft_signal(int signo);
void			ft_exec(t_lst *list, char **env);
void			ft_freeall(char **path_tab, t_lst *list, char **env);
void			ft_freeall_exit(char **path_tab, t_lst *list,
								char **gnl_word, char **env);
char			**ft_rework_cmd(char **arg, t_env *env);
t_env			*ft_setenv_char(char *name, t_env *env);
char			*ft_search_env(char *str, t_env *env);
t_env			*ft_setenv(t_lst *list, t_env *l_env);
void			ft_freeenv(t_env *list);
t_env			*ft_creat_env(char **env, t_env *l_env);
t_env			*ft_check_env(t_lst *list, t_env *l_env, int builtin);
int				ft_built_echo(t_lst *list, t_env *env);
t_env			*ft_built_cd(t_lst *list, t_env *env);
t_env			*ft_addenv(t_env *list, t_env *new_ele);
t_env			*ft_newenv(char *name, char *arg);
int				ft_check_built(char *name);
t_lst			*ft_put_cmd(t_lst *list, char **arg);
t_lst			*ft_addlist(t_lst *list, t_lst *new_ele);
t_lst			*ft_newele(char *name);
void			ft_freedstr(char **arg);
char			**ft_push_shlvl(char **env);
void			ft_freelst(t_lst *list);
void			ft_free_env(char **env);
void			ft_printenv(t_env *list);
int				ft_check_env_error(t_lst *list);
t_lst			*ft_check_path(char **path_tab, char *cmd_word);
#endif
