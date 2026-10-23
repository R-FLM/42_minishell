/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:21:54 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 14:32:31 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "./src/struct.h"

void	ft_exit(t_shell *sh, char **args);
int		echo(char **args, t_shell *sh);
int		pwd(char **args, t_shell *sh);
int		cd(t_shell *sh, char **args);
int		env(char **args, t_shell *sh);
int		export(char **args, t_shell *sh);
int		unset(char **args, t_shell *sh);

/**
 * @brief compile an error message, ex : program "cd", argument strerror(errno)
 * gives "cd: error: "
 */
char	*error_mess(char *program, char *argument);

char	*get_cwd(t_shell *sh);

void	sort_ascii(char **s);

int		varcmp(char *s1, char *s2);

char	*create_entry(t_shell *sh, char *var, char *value);

int		is_valid_var_name(t_shell *sh, char *s);

int		printout_env_line(t_shell *sh, char *s);

char	*export_err_var(char *s);

int		append_env_var(t_shell *sh, char *arg);

int		new_entry_to_env(t_shell *sh, char *var, char *value);

int		add_no_eq_to_env(t_shell *sh, char *var);

int		printout_env_line_no_eq(t_shell *sh, char *s);

#endif
