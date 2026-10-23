#!/bin/bash

# Runs every automated case file through bash --posix and through minishell,
# each in a fresh temporary copy of this directory, then prints the commands
# whose output, errors or exit status differ, and a summary.
# Known differences are documented in the README, so this script reports them
# instead of failing: it only exits with an error if a suite cannot run.

YELLOW='\033[1;33m'
GREEN='\033[1;32m'
RED='\033[1;31m'
BOLD='\033[1m'
NC='\033[0m'
USAGE="Usage: bash run_suites.sh <path_to_executable minishell> [-v]"
SUITES="test_passed test_cmd 666_test_cmds"

if [ $# -lt 1 ] || [ $# -gt 2 ] || [ ! -x "$1" ]; then
	echo "$USAGE"
	exit 1
fi

MINISHELL=$(realpath "$1")
VERBOSE=$2
TEST_DIR=$(cd "$(dirname "$0")" && pwd)
WORK=$(mktemp -d)
trap 'rm -rf -- "$WORK"' EXIT

total=0
passed=0

for suite in $SUITES; do
	copy="$WORK/$suite"
	mkdir "$copy"
	cp -r "$TEST_DIR"/. "$copy"/
	(cd "$copy" && bash flm_test_err.sh "$MINISHELL" "$suite") \
		| sed 's/\x1b\[[0-9;]*m//g' > "$WORK/$suite.log"
	suite_total=$(sed -n 's/^Total tests : //p' "$WORK/$suite.log")
	suite_passed=$(sed -n 's/^Passed tests : //p' "$WORK/$suite.log")
	if [ -z "$suite_total" ] || [ -z "$suite_passed" ]; then
		echo -e "${RED}$suite: could not run${NC}"
		exit 1
	fi
	total=$((total + suite_total))
	passed=$((passed + suite_passed))
	if [ "$suite_passed" -eq "$suite_total" ]; then
		echo -e "${GREEN}$suite: $suite_passed / $suite_total identical to bash${NC}"
	else
		echo -e "${YELLOW}$suite: $suite_passed / $suite_total identical to bash${NC}"
	fi
	if [ "$VERBOSE" = "-v" ]; then
		sed '/^Total tests : /,$d' "$WORK/$suite.log"
	else
		sed -n 's/^\$> \(.*\) $/  differs: \1/p' "$WORK/$suite.log" | cut -c1-100
	fi
done

echo -e "${BOLD}Total: $passed / $total cases identical to bash${NC}"
