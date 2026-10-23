/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:08:20 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 00:46:38 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./src/struct.h"

/**
 * Executes the AST starting at the root node.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST root node.
 * @returns {int} Exit status of the executed pipeline.
 */
void	exec_root(t_shell *sh, t_ast *node);

void	clean_exit_forked_cmd(t_ast *node, char *cmd, char **args, char **envp);

#endif
