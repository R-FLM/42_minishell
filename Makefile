.PHONY: all clean fclean re test leaks norm check

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LIB = libft/libft.a -lreadline 
SRC = 	./src/minishell.c \
		./src/0_initialization/init_shell.c \
		./src/1_tokenization/1_1_tokens/put_token.c \
		./src/1_tokenization/1_1_tokens/tokens_add.c \
		./src/1_tokenization/1_1_tokens/tokens_lst_utils.c \
		./src/1_tokenization/1_1_tokens/tokens_utils.c \
		./src/1_tokenization/1_1_tokens/tokens.c \
		./src/1_tokenization/1_2_syntax/syntax_complete.c \
		./src/1_tokenization/1_2_syntax/syntax_p1.c \
		./src/1_tokenization/1_2_syntax/syntax_p2.c \
		./src/1_tokenization/1_2_syntax/syntax_quote.c \
		./src/1_tokenization/1_2_syntax/syntax_utils.c \
		./src/2_parsing_ast/ast_utils.c \
		./src/2_parsing_ast/heredoc.c \
		./src/2_parsing_ast/expand_and_heredoc.c \
		./src/2_parsing_ast/parsing_cmd.c \
		./src/2_parsing_ast/parsing_redir.c \
		./src/2_parsing_ast/parsing_utils.c \
		./src/2_parsing_ast/parsing.c \
		./src/3_execution/3_1_expansion/expand_custom_split.c \
		./src/3_execution/3_1_expansion/expand_args_split.c \
		./src/3_execution/3_1_expansion/expand_env.c \
		./src/3_execution/3_1_expansion/expand_rm_backslash.c \
		./src/3_execution/3_1_expansion/expand_rm_quotes.c \
		./src/3_execution/3_1_expansion/expand_utils.c \
		./src/3_execution/3_1_expansion/expand_wildcards_utils.c \
		./src/3_execution/3_1_expansion/expand_var.c \
		./src/3_execution/3_1_expansion/expand_wildcards.c \
		./src/3_execution/3_1_expansion/expand.c \
		./src/3_execution/3_2_cmd_parsing/parser_cmd.c \
		./src/3_execution/3_2_cmd_parsing/utils_parse_cmd.c \
		./src/3_execution/3_3_ast_execution/exec_cmd_utils.c \
		./src/3_execution/3_3_ast_execution/exec_cmd.c \
		./src/3_execution/3_3_ast_execution/exec_redir.c \
		./src/3_execution/3_3_ast_execution/exec_utils.c \
		./src/3_execution/3_3_ast_execution/exec_wait.c \
		./src/3_execution/3_3_ast_execution/exec.c \
		./src/3_execution/3_3_ast_execution/pipe.c \
		./src/4_builtin_functions/cd.c \
		./src/4_builtin_functions/echo.c \
		./src/4_builtin_functions/env.c \
		./src/4_builtin_functions/exit.c \
		./src/4_builtin_functions/export_append.c \
		./src/4_builtin_functions/export_no_eq.c \
		./src/4_builtin_functions/export_utils.c \
		./src/4_builtin_functions/export.c \
		./src/4_builtin_functions/func_utils.c \
		./src/4_builtin_functions/pwd.c \
		./src/4_builtin_functions/unset.c \
		./src/5_signal_handling/signal_fork.c \
		./src/5_signal_handling/signal_utils.c \
		./src/5_signal_handling/signal.c \
		./src/6_cleaning/clean_shell.c \
		./src/6_cleaning/clean_utils.c \
		./src/7_error_handling/err_syntax.c \
		./src/7_error_handling/err_utils.c \
		./src/7_error_handling/err.c

OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	$(CC) -o $(NAME) $(OBJ) $(LIB)

libft/libft.a:
	$(MAKE) -C libft

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

test: $(NAME)
	@bash test/run_suites.sh ./$(NAME) $(if $(VERBOSE),-v)

leaks: $(NAME)
	@bash test/valgrind_test.sh ./$(NAME)

norm:
	@command -v norminette > /dev/null || { echo "norminette is not installed"; exit 1; }
	@out="$$(norminette src libft 2>&1)"; \
	if printf '%s\n' "$$out" | grep -q ': Error!$$'; then \
		printf '%s\n' "$$out" | grep -v ': OK!$$'; exit 1; fi; \
	echo "norminette: $$(printf '%s\n' "$$out" | grep -c ': OK!$$') files OK"

check: norm leaks test
