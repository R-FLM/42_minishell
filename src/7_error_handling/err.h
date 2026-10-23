/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:06:39 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 17:06:50 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "./src/struct.h"
# include <errno.h>
# include <string.h>

# define SUCCESS 0
# define FAIL 1
# define MALLOC_FULL_ERR "minishell: malloc: Memory allocation failed"
# define QUOTE_ERR "expected end-quote"
# define AMB_REDIR "ambiguous redirect"
# define CMD_NOT_FND 127
# define CMD_NOT_FND_ERR "command not found"
# define CMD_PERM_DND 126
# define MISUSE 2
# define ISDIR "Is a directory"
# define SIG_BASE 128
# define WARNING "warning: "
# define SIGQUIT_STATUS 131
# define SIGSEGV_STATUS 139

/**
 * Reports a syntax quote error and updates shell status.
 * @param {t_shell *} sh - Shell context.
 * @param {char *} character that caused the syntax error.
 */
void	quote_error(t_shell *sh, char *c);

/**
 * Reports a syntax error and updates shell status.
 * @param {t_shell *} sh - Shell context.
 * @param {t_token_kw} kw - Token that caused the syntax error.
 * @param {int} exitno - Exit status to set.
 */
void	syntax_error(t_shell *sh, t_token_kw kw, int exitno);

void	syntax_error_word(t_shell *sh, char *word, int exitno);

/**
 * Reports an error with context and updates shell status.
 * @param {t_shell *} shell - Shell context.
 * @param {char *} context - Error context (command or component).
 * @param {char *} why - Error description.
 * @param {int} exitno - Exit status to set.
 */
void	error(t_shell *shell, char *context, char *why, int exitno);

/**
 * @brief Prints a warning when ctrl D is used to close an here_doc,
 * precising the line number.
 * @param sh
 */
void	warning_hd(t_shell *sh);

/**
 * @brief Helper function that return the line count for errors in non
 * interactive terminals.
 */
char	*error_non_tty(t_shell *sh);

/**
 * @brief Helper function for error
 */
char	*join_err(t_shell *sh, char *context, char *why);

/**
 * @brief Create error message for export.
 */
void	export_msg(t_shell *sh, char *context);

void	close_std_fds(void);

#endif
