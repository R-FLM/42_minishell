/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:18:30 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/07 09:46:17 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# define SUCCESS 0
# define FAIL 1
# define PROMPT_HD "> "
# define HEREDOC "/tmp/minishell_heredoc"

# include "./src/struct.h"

/**
 * Check all nodes to collect sequentially heredocs
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} node - if node is a command, then check if there is a
 * heredoc redir entry to collect.
 */
void	handle_heredocs(t_shell *sh, t_ast *current_node);

#endif
