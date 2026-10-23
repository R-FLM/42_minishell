/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:05:35 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 01:39:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "./src/struct.h"

# define FAIL 1
# define SUCCESS 0

/**
 * Tokenizes the current input line into a token list.
 * @param {t_shell *} sh - Shell context.
 * @returns {int} SUCCESS or FAIL.
 */
int		tokenization(t_shell *sh);

/**
 * Converts a token kind to its string representation.
 * @param {t_token_kw} kw - Token kind.
 * @returns {char*} Static string representation.
 */
char	*ft_token_to_char(t_token_kw kw);

#endif
