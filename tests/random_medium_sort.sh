#!/usr/bin/env bash

set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BIN_TARGET="tests/medium_test"
BIN="$ROOT_DIR/$BIN_TARGET"
CASES="${1:-50}"
SIZE="${2:-50}"
MIN_VALUE="${3:--1000}"
MAX_VALUE="${4:-1000}"

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
		printf '[NG] random medium case %d failed\n' "$i"
		printf '%s\n' "$output"
		exit 1
	fi
	steps="$(printf '%s\n' "$output" | sed -n 's/.*steps=\([0-9][0-9]*\).*/\1/p' | tail -n 1)"
	size="$(printf '%s\n' "$output" | sed -n 's/.*size=\([0-9][0-9]*\).*/\1/p' | tail -n 1)"
	disorder="$(printf '%s\n' "$output" | sed -n 's/.*disorder=\([0-9][0-9]*\.[0-9][0-9]*\).*/\1/p' | tail -n 1)"
	if [ -z "$steps" ] || [ -z "$size" ] || [ -z "$disorder" ]; then
		printf '[NG] random medium case %d: could not read test metrics\n' "$i"
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
	printf '[OK] random medium case %d: size=%d disorder=%s steps=%d\n' \
		"$i" "$size" "$disorder" "$steps"
	i=$((i + 1))
done

printf 'All %d random medium_sort tests passed. size=%d range=[%d,%d] min=%d max=%d avg=%d\n' \
	"$CASES" "$SIZE" "$MIN_VALUE" "$MAX_VALUE" "$min_steps" "$max_steps" \
	$((total_steps / CASES))
