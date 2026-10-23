/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:09:07 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:39:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# define SUCCESS 0
# define FAIL 1

# include "./src/struct.h"

/**
 * Executes a command node (builtins or external).
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST command node.
 * @returns {int} Exit status.
 */
void	exec_cmd(t_shell *sh, t_ast *node);

/**
 * Forks the current process with error handling.
 * @param {t_shell *} sh - Shell context.
 * @returns {pid_t} Child PID or -1 on failure.
 */
pid_t	try_fork(t_shell *sh);

/**
 * Applies redirections for a command.
 * @param {t_shell *} sh - Shell context.
 * @param {t_redir *} redir - Redirection list.
 * @returns {int} SUCCESS or FAIL.
 */
int		redir(t_shell *sh, t_redir *redir);

/**
 * Waits for all processes in the AST and returns status.
 * @param {t_ast *} node - AST root node.
 * @returns {int} Final exit status.
 */
int		wait_ast(t_ast *node);

int		wait_pid(t_ast *node);

/**
 * Sets up a pipe between AST nodes.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST pipe node.
 * @returns {int} SUCCESS or FAIL.
 */
int		setup_pipe(t_shell *sh, t_ast *node);

/**
 * Checks whether a path points to a directory.
 * @param {char *} path - Path to check.
 * @returns {int} 1 if directory, otherwise 0.
 */
int		is_dir(char *path);

void	clean_exit_forked_cmd(t_ast *node, char *cmd, char **args, char **envp);

int		pipe_redir(t_shell *sh, t_ast *node);

#endif
