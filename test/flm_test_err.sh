#!/bin/bash

RED='\033[1;31m'
LIGHT_RED='\033[0;31m'
GREEN='\033[1;32m'
LIGHT_GREEN='\033[0;92m'
YELLOW='\033[1;33m'
NC='\033[0m'
BOLD='\033[1;0m'
GOOD="✓"
BAD="✗"
USAGE="Usage: ./test.sh <path_to_executable minishell> [test_file]"
total_tests=0
passed_tests=0
failed_tests=0

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
	echo "$USAGE"
	exit 1
fi

TEST_FILE="${2:-test_cmd}"

if [ ! -f "$TEST_FILE" ]; then
	echo "Error: Test file '$TEST_FILE' not found."
	exit 1
fi

MINISHELL=$1

error_stdout() {
	echo -e "  ${RED}STDOUT${NC}"
	echo -e "    ${LIGHT_RED}bash posix stdout:${NC} $1"
	echo -e "    ${LIGHT_RED}minishell  stdout:${NC} $2"

}

error_stderr() {
	echo -e "  ${RED}STDERR${NC}"
	echo -e "    ${LIGHT_RED}bash posix stderr:${NC} $1"
	echo -e "    ${LIGHT_RED}minishell  stderr:${NC} $2"
}

error_exitcode() {
	echo -e "  ${RED}EXIT CODE:${NC}"
	echo -e "    ${LIGHT_RED}bash posix exit:${NC}   $1"
	echo -e "    ${LIGHT_RED}minishell  exit:${NC}   $2"
}

pass() {
	echo -e "  ${GREEN}PASS ${GOOD}${NC}"
}
pass_stdout() {
	echo -e "  ${GREEN}STDOUT${NC}${LIGHT_GREEN} $1"
}
pass_stderr() {
	echo -e "  ${GREEN}STDERR${NC}${LIGHT_GREEN} $1"
}
pass_exitcode() {
	echo -e "  ${GREEN}EXIT${NC}${LIGHT_GREEN}   $1"
}


test_command() {

	cmd=$1

	bash_stdout_tmp=$(mktemp)
	mini_stdout_tmp=$(mktemp)
	bash_stderr_tmp=$(mktemp)
	mini_stderr_tmp=$(mktemp)

	# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=all --supressions=readline.supp


	<<<"$cmd" bash --posix >"$bash_stdout_tmp" 2>"$bash_stderr_tmp"

	expected_code=$?
	expected_stdout=$(cat "$bash_stdout_tmp")
	expected_stderr=$(cat "$bash_stderr_tmp" | sed 's/^bash: //')

	<<<"$cmd" "$MINISHELL" >"$mini_stdout_tmp" 2>"$mini_stderr_tmp"

	exit_code=$?
	actual_stdout=$(cat "$mini_stdout_tmp")
	actual_stderr=$(cat "$mini_stderr_tmp" | sed 's/^minishell: //')

	#expected_stderr_clean=$(echo "$expected_stderr" | sed 's/^bash: line [0-9]*: //')

	local failed=0

	if [ "$expected_code" -ne "$exit_code" ]; then
		failed=1
	fi
	# if [ "$expected_code" -eq "$exit_code" ]; then
	# 	pass_exitcode "$expected_code"
	# fi

	if [ "$expected_stdout" != "$actual_stdout" ]; then
		failed=1
	fi
	# if [ "$expected_stdout" = "$actual_stdout" ]; then
	# 	pass_stdout "$expected_stdout"
	# fi

	if [ "$expected_stderr" != "$actual_stderr" ]; then
		failed=1

	fi
	# if [ "$expected_stderr" = "$actual_stderr" ]; then
	# 	pass_stderr "$expected_stderr"
	# fi

	rm -f "$bash_stderr_tmp" "$mini_stderr_tmp" "$bash_stdout_tmp" "$mini_stdout_tmp"

	if [ "$failed" -eq 1 ]; then
		echo -e "${YELLOW}$> $1 ${NC}"
		error_exitcode "$expected_code" "$exit_code"
		error_stdout "$expected_stdout" "$actual_stdout"
		error_stderr "$expected_stderr" "$actual_stderr"
		failed_tests=$((failed_tests + 1))
		return 0
	fi
	passed_tests=$((passed_tests + 1))
	return 1
}

while IFS= read -r line; do
	if [[ -z "$line" ]]; then
		continue
	fi
	if [[ "$line" =~ ^[[:space:]]*# ]]; then
		continue
	fi
	if [[ "$line" =~ ^[[:space:]]*===== ]]; then
		echo -e "${BOLD} $line ${NC}"
		continue
	fi
	test_command "$line"
	total_tests=$((total_tests + 1))
done < "$TEST_FILE"

echo -e "${YELLOW}Total tests : $total_tests"
echo -e "${GREEN}Passed tests : $passed_tests"
echo -e "${RED}Failed tests : $failed_tests${NC}"

if [ "$failed_tests" -ne 0 ]; then
	exit 1
fi
