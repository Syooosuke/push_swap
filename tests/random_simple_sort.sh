#!/usr/bin/env bash

set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN_TARGET="tests/stack_test"
BIN="$ROOT_DIR/$BIN_TARGET"
CASES="${1:-50}"
SIZE="${2:-10}"
MIN_VALUE="${3:--100}"
MAX_VALUE="${4:-100}"

if [ "$SIZE" -lt 1 ]; then
	printf 'SIZE must be greater than 0\n' >&2
	exit 1
fi
if [ "$CASES" -lt 1 ]; then
	printf 'CASES must be greater than 0\n' >&2
	exit 1
fi
if [ "$MIN_VALUE" -gt "$MAX_VALUE" ]; then
	printf 'MIN_VALUE must be less than or equal to MAX_VALUE\n' >&2
	exit 1
fi
if [ "$SIZE" -gt $((MAX_VALUE - MIN_VALUE + 1)) ]; then
	printf 'SIZE is too large for the requested unique number range\n' >&2
	exit 1
fi

make -s -C "$ROOT_DIR" "$BIN_TARGET"

make_numbers()
{
	local -A seen
	local nums=()
	local n
	local span

	span=$((MAX_VALUE - MIN_VALUE + 1))
	while [ "${#nums[@]}" -lt "$SIZE" ]; do
		n=$((RANDOM % span + MIN_VALUE))
		if [ -z "${seen[$n]+x}" ]; then
			seen[$n]=1
			nums+=("$n")
		fi
	done
	printf '%s\n' "${nums[*]}"
}

i=1
total_steps=0
min_steps=
max_steps=0
while [ "$i" -le "$CASES" ]; do
	numbers="$(make_numbers)"
	if ! output="$("$BIN" $numbers 2>&1)"; then
		printf '[NG] random case %d failed\n' "$i"
		printf 'input: %s\n' "$numbers"
		printf '%s\n' "$output"
		exit 1
	fi
	steps="$(printf '%s\n' "$output" | sed -n 's/.*total=\([0-9][0-9]*\).*/\1/p' | tail -n 1)"
	if [ -z "$steps" ]; then
		printf '[NG] random case %d: could not read operation count\n' "$i"
		printf 'input: %s\n' "$numbers"
		printf '%s\n' "$output"
		exit 1
	fi
	total_steps=$((total_steps + steps))
	if [ -z "$min_steps" ] || [ "$steps" -lt "$min_steps" ]; then
		min_steps="$steps"
	fi
	if [ "$steps" -gt "$max_steps" ]; then
		max_steps="$steps"
	fi
	printf '[OK] random case %d: steps=%d input: %s\n' "$i" "$steps" "$numbers"
	i=$((i + 1))
done

printf 'All %d random simple_sort tests passed. size=%d range=[%d,%d] min=%d max=%d avg=%d\n' \
	"$CASES" "$SIZE" "$MIN_VALUE" "$MAX_VALUE" "$min_steps" "$max_steps" \
	$((total_steps / CASES))
