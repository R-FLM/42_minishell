/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:32:12 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 14:05:21 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CMD_H
# define PARSER_CMD_H

# include "./src/struct.h"

/**
 * Resolves a command name into an executable path.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - AST command node.
 * @returns {char*} Allocated command path or NULL on failure.
 */
char	*parse_cmd(t_shell *sh, t_ast *node);

/**
 * Retrieves an environment variable value.
 * @param {t_shell *} sh - Shell context.
 * @param {char *} var_name - Variable name to look up.
 * @returns {char*} Allocated value or NULL if not found.
 */
char	*get_env(t_shell *sh, char *var_name);

/**
 * Checks if a command is a built-in shell command.
 * @param: cmd
 * @param: sh- Shell context, used for built-in commands that may need it.
 * @param: args - Arguments passed to the command, used for built-in commands
 * that may need it.
 * @returns: 1 if the command is a builtin, 0 otherwise
 */
int		is_builtin(t_shell *sh, t_ast *node, char **args, char *cmd);

int		is_builtin_main(t_shell *sh, t_ast *node, char **args, char *cmd);

#endif
