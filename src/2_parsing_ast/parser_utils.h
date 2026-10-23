/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:01:36 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:39:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define FAIL 1
# define SUCCESS 0

# include "./src/struct.h"

/**
 * Parses redirections for an AST node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} ast_node - AST node to fill.
 * @param {t_token **} token - Current token pointer.
 * @returns {int} SUCCESS or FAIL.
 */
int	parse_redir(t_shell *sh, t_ast *ast_node, t_token **token);

/**
 * Parses command arguments into an AST node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST node to fill.
 * @param {t_token **} tokens - Current token pointer.
 * @returns {int} SUCCESS or FAIL.
 */
int	parse_command_args(t_shell *sh, t_ast *node, t_token **tokens);

#endif
