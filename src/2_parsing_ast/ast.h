/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:02:38 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 00:46:44 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "./src/struct.h"

/**
 * Allocates and initializes a new AST node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast_node_type} astkw - AST node type.
 * @returns {t_ast*} Newly allocated node or NULL on failure.
 */
t_ast	*create_ast_node(t_shell *sh, t_ast_node_type astkw);

#endif
