/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:36:15 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:08:53 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_SHELL_H
# define CLEAN_SHELL_H

# include "./src/struct.h"

/**
 * Frees the current prompt line and related buffers.
 * @param {t_shell *} shell - Shell context.
 */
void	clean_prompt(t_shell *shell);

/**
 * Frees a redirection node and its fields.
 * @param {t_redir *} redir - Redirection node.
 */
void	clean_redir(t_redir *redir);

/**
 * Frees all shell resources for a clean exit.
 * @param {t_shell *} shell - Shell context.
 */
void	clean_shell(t_shell *shell);

/**
 * Clears a redirection list and frees each node.
 * @param {t_redir **} redir - Pointer to redirection list.
 * @param {void (*)(t_redir *)} del - Node free callback.
 */
void	redir_clear(t_redir **redir, void (*del)(t_redir *));

/**
 * Clears a token list and frees each node.
 * @param {t_token **} token - Pointer to token list.
 * @param {void (*)(t_token *)} del - Node free callback.
 */
void	tokens_clear(t_token **token, void (*del)(t_token *));

void	clean_token(t_token *tk);

#endif
