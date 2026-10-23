/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:21:03 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 23:28:33 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <termios.h>

typedef struct s_shell	t_shell;
typedef struct s_ast	t_ast;

typedef enum e_token_kw
{
	EOFKW,
	REDIR_IN,
	REDIR_HD,
	REDIR_OUT,
	REDIR_APP,
	PIPE,
	L_PARENTH,
	R_PARENTH,
	AND,
	OR,
	SEMICOLON,
	D_SEMICOLON,
	AMPERSAND,
	WORD
}	t_token_kw;

typedef struct s_token
{
	t_token_kw		kw;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_kw		kw;
	char			*file;
	char			*eofkw;
	int				quoted;
	int				fd_in;
	int				fd_out;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

typedef enum e_ast_node
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
	AST_THEN
}	t_ast_node_type;

typedef struct s_ast
{
	t_ast_node_type	astkw;
	char			**args;
	struct s_redir	*redir;
	int				fd_in;
	int				fd_out;
	int				ko;
	pid_t			pid;
	int				status;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
	t_shell			*shell;
}					t_ast;

typedef struct s_shell
{
	char			**envp;
	char			*name;
	char			*name_err;
	int				status;
	int				exit;
	int				stdin_fd;
	int				stdout_fd;
	int				hd_fd;
	char			*line;
	int				line_cnt;
	int				tty;
	struct termios	original_termios;
	t_token			*tokens;
	t_ast			*ast;
}					t_shell;

#endif
