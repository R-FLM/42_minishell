/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:57:08 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/07 10:10:50 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# define _GNU_SOURCE
# include "./src/struct.h"
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <unistd.h>

# define SIGINT_STATUS 130

extern volatile sig_atomic_t	g_signal;

/**
 * @brief Configures signal handling for a terminal (TTY) environment.
 * This function sets up custom signal handlers for SIGINT (Ctrl+C)
 * and SIGQUIT (Ctrl+\) when the program is running in a terminal (tty != 0).
 * The behavior is as follows:
 * - SIGINT (interrupt signal): Redirects to a custom signal_handler function.
 * - SIGQUIT (quit signal): Ignores the signal (SIG_IGN).
 * Both signals are configured with SA_RESTART flag to automatically restart
 * system calls that might be interrupted by these signals.
 * @param tty If 0, the function does nothing (non-terminal environment).
 *            If non-zero, signal handlers are configured for terminal mode.
 */
void	setup_signals(t_shell *shell);
/**
 * @brief Configures signal handling specifically for heredoc input mode.
 * This function sets up custom signal handlers for SIGINT (Ctrl+C)
 * and SIGQUIT (Ctrl+\) when the shell is processing a heredoc input.
 * The behavior is:
 * - SIGINT (interrupt signal): Redirects to heredoc_signal_handler,
 * which typically handles heredoc interruption
 * (e.g., cleaning up temporary files and exiting).
 * - SIGQUIT (quit signal): Ignores the signal (SIG_IGN) to prevent accidental
 * termination.
 * Both signals are configured with the SA_RESTART flag to automatically restart
 * system calls that might be interrupted by these signals.
 */
void	setup_heredoc_signals(void);
/**
 * @brief Configures default signal handling for child processes.
 * This function resets signal handlers for SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\)
 * to their default behaviors (SIG_DFL) when called in a child process.
 * The behavior is:
 * - SIGINT: Restored to default action (terminate process)
 * - SIGQUIT: Restored to default action (terminate process and dump core)
 * Both signals are configured with the SA_RESTART flag to automatically restart
 * system calls that might be interrupted by these signals.
 */
void	setup_child_signals(t_shell *shell);
/**
 * @brief Configures the shell to ignore interrupt and quit signals.
 * This function sets both SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to be ignored
 * (SIG_IGN).
 * This is typically used during critical operations where signal interruption
 * could cause inconsistent state or data corruption.
 * Both signals are configured with the SA_RESTART flag to automatically restart
 * system calls that might be interrupted by these signals.
 */
void	ignore_signals(void);
/**
 * @brief Restores the terminal's original settings.
 * This function restores the terminal attributes to their original state as
 * saved in the shell structure. It should be called before the shell exits
 * or when returning control to the parent shell.
 * @param shell Pointer to the shell structure containing the original
 * terminal settings.
 * Note: Only restores settings if the shell is running in a terminal
 * (shell->tty != 0).
 * The restoration uses TCSANOW to apply changes immediately.
 */
void	restore_terminal_settings(t_shell *shell);
/**Turn off echo of control characters */
void	disable_echoctl(void);

#endif
