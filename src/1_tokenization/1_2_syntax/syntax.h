/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:04:47 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:39:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "./src/struct.h"

# define FAIL 1
# define SUCCESS 0

/**
 * Open secondary prompt to keep typing
 * @param {t_shell *} sh - Shell context.
 * @returns {int} SUCCESS or FAIL.
 */
int	backslash_syntax(t_shell *sh);

/**
 * Validates the token list syntax.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} SUCCESS or FAIL.
 */
int	check_syntax(t_shell *sh);

/**
 * Validates the quoting syntax.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} 0 on error, 1 on success.
 */
int	quote_syntax(t_shell *sh);

int	semicolon_syntax(t_shell *sh, t_token *current);

int	or_syntax(t_shell *sh, t_token *current);

int	ampersand_syntax(t_shell *sh, t_token *current);

int	and_syntax(t_shell *sh, t_token *current);

int	syntax_completion(t_shell *sh);

int	is_redir(t_token *token);

#endif
