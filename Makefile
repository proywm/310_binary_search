# Makefile for Binary Search C programs
# Usage:
#   make          - compile all versions
#   make for      - compile only the for-loop version
#   make goto     - compile only the goto version
#   make recursive - compile only the recursive version
#   make run      - compile and run all versions
#   make clean    - remove compiled executables

CC = gcc
CFLAGS = -Wall -g

all: for goto recursive

for: binary_search_for.c
	$(CC) $(CFLAGS) -o binary_search_for binary_search_for.c

goto: binary_search_goto.c
	$(CC) $(CFLAGS) -o binary_search_goto binary_search_goto.c

recursive: binary_search_recursive.c
	$(CC) $(CFLAGS) -o binary_search_recursive binary_search_recursive.c

run: all
	@echo "=== Running FOR loop version ==="
	@./binary_search_for
	@echo ""
	@echo "=== Running GOTO version ==="
	@./binary_search_goto
	@echo ""
	@echo "=== Running RECURSIVE version ==="
	@./binary_search_recursive

clean:
	rm -f binary_search_for binary_search_goto binary_search_recursive

.PHONY: all for goto recursive run clean
