/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:46:22 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 00:45:18 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/0_initialization/init_shell.h"
#include "./src/5_signal_handling/signal_handling.h"
#include "./src/7_error_handling/err.h"
#include "./src/struct.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = 0;
	while (line[len])
		len++;
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static void	init_terminal(t_shell *shell)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		shell->tty = 1;
		tcgetattr(STDIN_FILENO, &shell->original_termios);
	}
	else
		shell->tty = 0;
}

static void	copy_envp(t_shell *shell, char **envp)
{
	if (!envp)
	{
		shell->envp = (char **)malloc(sizeof(*shell->envp));
		if (!shell->envp)
			error(shell, "malloc", strerror(errno), FAIL);
		shell->envp[0] = NULL;
		return ;
	}
	shell->envp = ft_strsdup(envp);
	if (!shell->envp)
		error(shell, "malloc", strerror(errno), FAIL);
}

static void	get_shell_name(t_shell *shell, char **argv)
{
	char	*tmp;

	shell->name = NULL;
	if (!argv || !*argv)
	{
		shell->name = STD_PROMPT;
		shell->name_err = ERR_PROMPT;
		return ;
	}
	tmp = ft_strrchr(*argv, '/');
	if (!tmp)
	{
		shell->name = ft_strjoin(*argv, PROMPT_HD);
		shell->name_err = ft_strjoin(*argv, PROMPT_ERR);
	}
	if (tmp && tmp[0] && tmp[1])
	{
		shell->name = ft_strjoin(tmp + 1, PROMPT_HD);
		shell->name_err = ft_strjoin(tmp + 1, PROMPT_ERR);
	}
	if (!shell->name)
	{
		shell->name = STD_PROMPT;
		shell->name_err = ERR_PROMPT;
	}
}

void	initialize_shell(t_shell *shell, char **envp, char **argv)
{
	copy_envp(shell, envp);
	shell->status = 0;
	shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdin_fd == -1)
		error(shell, "dup", strerror(errno), FAIL);
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdout_fd == -1)
		error(shell, "dup", strerror(errno), FAIL);
	shell->hd_fd = -1;
	shell->line_cnt = 0;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->ast = NULL;
	get_shell_name(shell, argv);
	init_terminal(shell);
	setup_signals(shell);
}
