/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:05:12 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:39:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H

# include "./src/struct.h"

# define FAIL 1
# define SUCCESS 0

/**
 * Checks if a character is a shell whitespace.
 * @param {char} c - Character to test.
 * @returns {int} 1 if whitespace, otherwise 0.
 */
int		isshspace(char c);

/**
 * Checks if a character breaks a word token.
 * @param {char} c - Character to test.
 * @returns {int} 1 if break character, otherwise 0.
 */
int		isshbreak(char c);

/**
 * Checks if a character starts a shell keyword/operator.
 * @param {char} c - Character to test.
 * @returns {int} 1 if keyword, otherwise 0.
 */
int		isshellkw(char c);

/**
 * Adds a keyword token at the current index.
 * @param {t_shell *} sh - Shell context.
 * @param {ssize_t} i - Current index in input line.
 * @returns {ssize_t} New index after consuming keyword.
 */
ssize_t	add_key_token(t_shell *sh, ssize_t i);

/**
 * Adds a token to the token list.
 * @param {t_shell *} sh - Shell context.
 * @param {char *} token - Token string.
 * @param {t_token_kw} kw - Token kind.
 * @returns {int} SUCCESS or FAIL.
 */
int		add_token(t_shell *sh, char *token, t_token_kw kw);

#endif
