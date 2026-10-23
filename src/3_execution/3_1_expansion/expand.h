/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:03:22 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/08 08:35:05 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "./libft/libft.h"
# include "./src/7_error_handling/err.h"
# include "./src/struct.h"
# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>

// expand.c
/**
 * Expands variables in the AST node arguments.
 * @param {t_shell *} sh - Shell context.
 * @param {t_ast *} current_node - AST node to expand.
 */
int		expand_cmd(t_shell *sh, t_ast *current_node);

// expand_var
/**
 * Expands variables and special tokens in a string.
 * Processes the input string to expand:
 * - Environment variables (prefixed with '$' followed by alphanumeric /
 * underscore)
 * - Exit status (represented by '$?')
 * Expansions only occur outside single quotes. The original string is not
 * modified. Allocates and returns a new string with expansions applied.
 * @param sh The shell context containing environment and exit status.
 * @param s The input string to expand.
 * @return A newly allocated string with expansions, or NULL on allocation
 * failure.
 */
char	*expand_str(t_shell *sh, char *s);

// expand_wildcards.c
/**
 * Expands wildcard patterns in command arguments.
 * Processes each argument in the AST node's argument list. If an argument
 * contains unquoted wildcards ('*'), expands it to match files in the current
 * directory (excluding hidden files). Non-wildcard arguments are preserved
 * as-is. The original arguments array is freed and replaced with the expanded
 * version.
 * @param sh The shell context.
 * @param current_node The AST node containing arguments to process.
 */
void	expand_wildcards_arg(t_shell *sh, t_ast *current_node);

/**
 * Expands a wildcard pattern in a redirection filename if present.
 * Checks if the redirection's filename contains an unquoted wildcard ('*').
 * If found, expands it to match files in the current directory. If the
 * expansion results in exactly one match, replaces the filename with the
 * matched file. If multiple matches are found, reports an ambiguous
 * redirection error.
 * @param sh The shell context.
 * @param current_redir The redirection node to process.
 * @return 1 on success or no expansion needed, 0 on error or
 * ambiguous redirection.
 */
int		expand_wildcard_redir_file(t_shell *sh, t_redir *current_redir);

// expand_env.c
/**
 * Retrieves an environment variable value from the shell context.
 * @param {t_shell *} sh - Shell context.
 * @param {char *} var_name - Variable name to look up.
 * @returns {char*} Newly allocated value or NULL if not found.
 */
char	*collect_env_var(t_shell *sh, char *var_name);

// expand_utils.c
/**
 * Removes all unescaped quotes from each string in a NULL-terminated array.
 * Processes each string in the input array by stripping single ('\'') and
 * double ('"') quotes, provided they are not nested within the opposite type
 * of quote. The original array is freed, and a new array with the modified
 * strings is allocated and assigned to the input pointer.
 * @param arr A pointer to a NULL-terminated array of strings to process.
 * @return 1 on success, 0 on allocation failure (original array remains
 * unchanged).
 */
int		arr_rm_quotes(char ***arr);
/**
 * Creates a duplicate of a string with all unescaped quotes removed.
 * Allocates and returns a new string where single and double
 * quotes are stripped, provided they are not nested within the opposite type
 * of quote. The original string remains unchanged.
 * @param s The input string to process.
 * @return A newly allocated string with quotes removed, or NULL on allocation
 * failure.
 */

/**
 * @brief Check if a string comtains quoted, either single or double, and
 * returns the sum of quotes.
 * @param s - string.
 * @return int - sum of single and double quotes.
 */
int		is_quoted(char *s);

char	*strdup_rm_quotes(char *s);

int		arr_rm_backslash(char ***arr);

// expand_wildcards_utils.c
/**
 * Checks if a string contains at least one unquoted wildcard character ('*')
 * that is not enclosed within single ('\'') or double ('"') quotes.
 * @param s The string to check for unquoted wildcards.
 * @return 1 if an unquoted wildcard is found, 0 otherwise.
 */
int		include_wildcard(char *s);

void	sort_ascii_case_insensitive(char **s);

int		is_dquoted(char *s, size_t pos);

int		is_squoted(char *s, size_t pos);

int		is_backslashed(char *s, size_t pos);

char	*expand_redir_str(t_shell *sh, t_redir *redir, char *s);

#endif
