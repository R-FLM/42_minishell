/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:07:04 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:25:50 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

# define PROMPT_HD "> "
# define PROMPT_ERR ": "
# define STD_PROMPT "minishell> "
# define ERR_PROMPT "minishell: "

# include "./src/struct.h"

/**
 * Initializes the shell context and environment.
 * @param {t_shell *} shell - Shell context to initialize.
 * @param {char **} envp - Environment variables.
 * @param {char **} argv - Program arguments.
 */
void	initialize_shell(t_shell *shell, char **envp, char **argv);

/**
 * @brief Trim the newline at the end of each line from non interactive prompts.
 * @param line
 */
void	trim_newline(char *line);

#endif
