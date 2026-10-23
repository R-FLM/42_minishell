/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:55:25 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/07 09:34:38 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/2_parsing_ast/heredoc.h"
#include "./src/3_execution/3_1_expansion/expand.h"
#include "./src/5_signal_handling/signal_handling.h"
#include "./src/struct.h"

int	expand_and_heredoc(t_shell *sh, t_ast *node)
{
	if (!node)
		return (0);
	if (node->left)
		expand_and_heredoc(sh, node->left);
	if (node->right)
		expand_and_heredoc(sh, node->right);
	if (node->astkw == AST_CMD || node->astkw == AST_SUBSHELL)
	{
		expand_cmd(sh, node);
		handle_heredocs(sh, node);
	}
	if (g_signal == SIGINT)
		return (0);
	return (1);
}
