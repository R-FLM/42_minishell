/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:12:40 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/07 13:41:34 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/0_initialization/init_shell.h"
#include "./src/1_tokenization/1_1_tokens/tokens.h"
#include "./src/1_tokenization/1_2_syntax/syntax.h"
#include "./src/2_parsing_ast/parsing.h"
#include "./src/3_execution/3_3_ast_execution/exec.h"
#include "./src/5_signal_handling/signal_handling.h"
#include "./src/6_cleaning/clean_shell.h"
#include "./src/7_error_handling/err.h"
#include "./src/struct.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

volatile sig_atomic_t	g_signal = 0;

static void	signal_reset(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->status = SIGINT_STATUS;
		g_signal = 0;
	}
}

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	if (!*line)
		return (1);
	signal_reset(shell);
	shell->line = line;
	if (!tokenization(shell))
		return (clean_prompt(shell), 1);
	if (!check_syntax(shell))
		return (clean_prompt(shell), 1);
	tokens = shell->tokens;
	shell->ast = parser(shell, &tokens);
	if (!shell->ast || g_signal == SIGINT)
		return (clean_prompt(shell), 1);
	exec_root(shell, shell->ast);
	if (shell->status == SIGQUIT_STATUS)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else if (shell->status == SIGSEGV_STATUS)
		write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
	clean_prompt(shell);
	return (1);
}

static void	shell_process_non_tty(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		trim_newline(line);
		shell->line_cnt++;
		if (!process_line(shell, line))
			break ;
	}
}

static void	shell_process_tty(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signals(shell);
		line = readline(shell->name);
		if (!line)
		{
			write(2, "exit\n", 5);
			break ;
		}
		add_history(line);
		shell->line_cnt++;
		if (!process_line(shell, line))
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		status;

	(void)argc;
	initialize_shell(&shell, envp, argv);
	if (shell.tty)
		shell_process_tty(&shell);
	else
		shell_process_non_tty(&shell);
	status = shell.status;
	clean_shell(&shell);
	rl_clear_history();
	return (status);
}
