# Makefile for Binary Search C programs
# Usage:
#   make          - compile both versions
#   make for      - compile only the for-loop version
#   make goto     - compile only the goto version
#   make run      - compile and run both versions
#   make clean    - remove compiled executables

CC = gcc
CFLAGS = -Wall -g

all: for goto

for: binary_search_for.c
	$(CC) $(CFLAGS) -o binary_search_for binary_search_for.c

goto: binary_search_goto.c
	$(CC) $(CFLAGS) -o binary_search_goto binary_search_goto.c

run: all
	@echo "=== Running FOR loop version ==="
	@./binary_search_for
	@echo ""
	@echo "=== Running GOTO version ==="
	@./binary_search_goto

clean:
	rm -f binary_search_for binary_search_goto

.PHONY: all for goto run clean
