/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:43:24 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 12:03:58 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

//#define PATH_MAX 1000

//int 	g_status;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				export;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out;
	int				fd_in;
	int				fd_old_in;
	int				fd_old_out;
	int				pipe_n;
	int				is_ignore;
	struct s_cmd	*next;
}	t_cmd;

//--------------------------------//


//utils.c
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *st1, const char *st2, size_t x);
size_t	ft_strlcat(char *to, const char *from, size_t tosize);
int		ft_strequ(const char *s1, const char *s2);
int 	ft_strlen(const char *string);

//utils.c

//--------------------------------//

//utils2.c

int		ft_strncmp(const char *st1, const char *st2, size_t x);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);

//utils2.c

//--------------------------------//

//utils3.c
void	*ft_realloc(void *ptr, size_t size);
void	*ft_memcpy(void *to, const void *from, size_t n);
int		ft_atoi(const char *str);

//utils3.c

//--------------------------------//

//ft_itoa.c

static int	ft_sign(long int n);
static char	*ft_null(int n, char *res);
static int	ft_getlen(long int n);
char		*ft_itoa(int n);

//ft_itoa.c

//--------------------------------//

//ft_split.c

static int	ft_count_words(const char *str, char c);
static char	*ft_write_words(const char *str, char c);
static void	ft_free_words(int i, char **pptr);
static int	ft_free(int counter, char **pptr);
char	**ft_split(char const *s, char c);

//ft_split.c

//--------------------------------//

// int		check_existence(char **env, char *str);
// int		check_name(char *str);
// void		print_name(char *str);
// void		print_value(char *str);

//--------------------------------//

//export_utils.c

int		is_meta_builtin(char c);
void	free_strings(char *s1, char *s2);
void	export_identifier_error(char *command);

//export_utils.c

//--------------------------------//

//export_utils2.c

int	check_export_type(char *cmd);
char	*get_key(char *command);
int	get_value_len(char *command);
char	*get_value(char *command);
void	print_export_value(char *value);

//export_utils2.c

//--------------------------------//

//environ_utils.c

t_env	*env_lstnew(char **envp);
t_env	*env_lstlast(t_env *envs);
void	env_lstadd_back(t_env **environ, t_env *new);
void	env_lstclear(t_env *environ);
int	env_lstlen(t_env *environ);

// environ_utils.c

//--------------------------------//

//environ

char	*get_env(t_env *environ, char *key);
char	**get_environ(t_env *environ);
void	delete_environ(t_env *environ, char *key);
void	add_environ(t_env *environ, char *key, char *val, int export);
t_env	*set_environ(char **envp);

//environ

#endif