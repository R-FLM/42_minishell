#!/bin/bash

# Runs the session in valgrind_cmds under Valgrind, following every child
# process, and fails if minishell or one of its forks loses memory, makes a
# memory error or leaves a descriptor open at exit. Logs of the programs that
# minishell runs with execve are not checked: their memory is not ours.

GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m'
USAGE="Usage: bash valgrind_test.sh <path_to_executable minishell>"

if [ $# -ne 1 ] || [ ! -x "$1" ]; then
	echo "$USAGE"
	exit 1
fi
if ! command -v valgrind > /dev/null; then
	echo "valgrind is not installed"
	exit 1
fi

MINISHELL=$(realpath "$1")
TEST_DIR=$(cd "$(dirname "$0")" && pwd)
WORK=$(mktemp -d)
trap 'rm -rf -- "$WORK"' EXIT

mkdir "$WORK/logs" "$WORK/run"
touch "$WORK/run/a.c" "$WORK/run/b.c" "$WORK/run/no_exec"
(cd "$WORK/run" && valgrind --leak-check=full --show-leak-kinds=all \
	--trace-children=yes --track-fds=yes --log-file="$WORK/logs/%p.log" \
	"$MINISHELL" < "$TEST_DIR/valgrind_cmds" > /dev/null 2>&1)

checked=0
failed=0
for log in "$WORK"/logs/*.log; do
	# A fork that called execve continues as another program, without a summary
	grep -q "Command: $MINISHELL\$" "$log" || continue
	grep -q 'HEAP SUMMARY' "$log" || continue
	checked=$((checked + 1))
	if grep -qE '(definitely|indirectly|possibly) lost: [1-9]' "$log" \
		|| ! grep -q 'ERROR SUMMARY: 0 errors' "$log" \
		|| ! awk '/FILE DESCRIPTORS:/ { n = $4; s = 0;
			if (match($0, /\(([0-9]+) std\)/)) s = substr($0, RSTART + 1) + 0;
			else s = (n < 3) ? n : 3; ok = (n == s) }
			END { exit !ok }' "$log"; then
		failed=$((failed + 1))
		echo -e "${RED}--- $(basename "$log")${NC}"
		cat "$log"
	fi
done

if [ "$checked" -eq 0 ]; then
	echo -e "${RED}Valgrind: no minishell process could be checked${NC}"
	exit 1
fi
if [ "$failed" -ne 0 ]; then
	echo -e "${RED}Valgrind: $failed of $checked minishell processes leak or make errors${NC}"
	exit 1
fi
echo -e "${GREEN}Valgrind: $checked minishell processes checked, 0 bytes lost, 0 errors, no descriptor left open${NC}"
