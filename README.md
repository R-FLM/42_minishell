*This project has been created as part of the 42 curriculum by flomulle and pifourni.*

# Minishell

## Description

Minishell is a lightweight shell implementation that replicates core functionality of a POSIX-compliant shell. It provides an interactive command-line interface where users can execute commands, manage input/output redirections, chain commands with pipes, and use control operators (AND, OR, semicolons). This project aims at learning lexical analysis and abstract syntax trees.

### It implements
- Interactive prompt with readline and command history
- Lexing → syntax → checking parsing → AST → execution
- Pipelines (cmd1 | cmd2) and subshells ( ... )
- Logical operators: &&, ||, and ;
- Redirections including heredocs
- Shell expansions: environment variables, quoting, backslashes, and globs (*)
- Builtin commands (cd, echo, env, exit, export, pwd, unset)
- Proper signal handling for SIGINT (Ctrl‑C) and SIGQUIT (Ctrl-\)
- Interactive and non-interactive modes

### It is not a full POSIX shell but aims to match bash behavior closely on our scope.

### Project structure (high‑level)
- **src/minishell.c**
Main entry point; main loop, integration of tokenization, parsing, execution, and final cleanup.
- **src/struct.h**
Global project data structures (t_shell, t_token, t_ast, t_redir, etc.).
- **src/0_initialization**
init_shell.c: environment duplication, prompt names, terminal initialization, initial signal setup.
- **src/1_tokenization**
1_1_tokens/: token creation and utilities.
1_2_syntax/: syntax checking, multiline input, incomplete constructs handling.
- **src/2_parsing_ast**
Parsing functions and AST utilities.
heredoc.c: heredoc collection and file management.
- **src/3_execution**
3_1_expansion/: environment/parameter expansion, quote/backslash removal, wildcard expansion.
3_2_cmd_parsing/: transforms AST commands into exec‑ready structures (args, paths).
3_3_ast_execution/: running commands, pipes, subshells, logical operators, waiting.
- **src/4_builtin_functions**
Builtin commands and their helpers.
- **src/5_signal_handling**
signal.c, signal_fork.c, signal_utils.c: interactive, child, heredoc signal behavior and termios helpers.
- **src/6_cleaning**
Shell cleanup, freeing allocations, closing descriptors.
- **src/7_error_handling**
Error and warning helpers for consistent messages and statuses.
- **libft/**
Custom library functions used throughout the project (string utils, lists, ft_get_next_line, etc.).

### The project implements a standard subset of bash builtins:
- **echo**: Supports at least -n and printing arguments.
- **cd**: Changes current directory. Updates environment variables such as PWD and OLDPWD (see implementation).
- **pwd**: Prints the current working directory.
- **env**: Prints the environment list.
- **export**: Adds or modifies environment variables. Handles VAR=value, VAR+=value, and plain VAR declarations.
- **unset**: Removes variables from the environment.
- **exit**: Exits the shell with the given status (or last status by default). Should behave like bash for numeric/non‑numeric arguments and multiple arguments, according to subject requirements.

### Limits and known deviations from full shells :
This project intentionally implements a restricted subset of bash functionality.

**Language and feature limitations**
No job control: No support for background jobs (&), fg, bg, jobs, or Ctrl-Z (SIGTSTP) management.
No advanced POSIX features: No for, while, if, case, or function syntax as in full shells.
No here‑strings (<<<), process substitution (<(...)), or advanced parameter expansion.
Simplified environment and export handling: Behavior is implemented to match subject requirements; some corner cases might differ from bash
Limited quoting / escaping edge cases: Standard basic usage is supported, but some rare edge cases around nested quotes, complex backslash rules in non‑POSIX modes, or locale‑dependent behavior may not be fully identical to bash.
Globbing: Implements * wildcard expansion; other patterns (?, [] character classes, brace expansion {a,b}) may not be supported or may behave differently.
No shell options: Commands like set, or configuration variables that change parsing behavior are not provided.

**Behavioral differences vs bash**
Signals in non‑interactive mode: Minishellduo uses default process signal behavior (no custom handlers), which can differ slightly from bash run in a script mode for certain edge cases.
Readline behavior: Prompt redraw and line clearing are designed to resemble bash, but details (e.g. multiline history, special keybindings) depend on system readline configuration and may differ.
Exit codes and status propagation: Foreground commands and pipelines return 128 + signal when killed, and logical operators &&/|| follow those statuses. Some rare or deeply nested combinations might not be exactly identical to bash behavior but follow the project spec and POSIX guidelines as much as practical.
Heredoc: in non-quoted heredoc, we decided to maintain the general logic that single quoted environment variables should not be expanded. This alloc to have an heredoc be interpreted as '$PATH'=/usr/bin for instance, which is not possible in posix bash.

**Resource and implementation limits**
No built‑in memory limit management, beyond what the OS provides.
The project assumes: A reasonably small number of concurrent pipelines / processes.
Maximum line length and token count bounds that depend on available memory.

## Instructions

### Compilation

The project uses a Makefile for compilation with clang:

```bash
make                # Compile with debug and sanitizer
make clean          # Remove object files
make fclean         # Remove all generated files
make re             # Full recompilation
```

### Testing

Basic command tests:

```bash
./minishell
> ls -la
> pwd
> echo $HOME
> cat file.txt | grep pattern
> ls > output.txt
> cat < input.txt
> echo "line1\nline2" | wc -l
> cd ..
```

## Ressources

### Official Documentation

- [POSIX Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) - Standard shell behavior reference
- [Linux man pages](https://man7.org/) - System call documentation (fork, exec, wait, dup2)
- [The C Standard Library](https://en.cppreference.com/w/c/header) - Standard C functions

### AI Usage

AI was used to assist with:

1. **Code Documentation** (Header comments following libft style)
2. **Explaining Bash nonsense**

**Note**: All core logic, algorithms, parsing, execution, code was written by the project authors.
