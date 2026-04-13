# Binary Search — From C to MASM Assembly

## Overview

This project contains two C implementations of **binary search** on a sorted array of 10 integers. Your assignment is to **convert these C programs into MASM (x86) assembly language**.

The two versions are designed to help you make the transition from high-level C to low-level assembly:

| File | Description |
|------|-------------|
| `binary_search_for.c` | Binary search using a standard **for loop** |
| `binary_search_goto.c` | Binary search using **goto statements and labels** (no loops) |

## Why Two Versions?

Assembly language has **no for loops, while loops, or structured control flow**. Instead, it uses:

- **Labels** — named locations in code (like addresses in memory)
- **CMP** — compare two values
- **Conditional jumps** — `JE` (jump if equal), `JG` (jump if greater), `JL` (jump if less)
- **Unconditional jumps** — `JMP` (always jump to a label)

The **goto version** maps almost directly to assembly. Each `goto label` becomes a `JMP` instruction, and each `if (...) goto` becomes a `CMP` + conditional jump.

### Progression Path

```
for-loop version  →  goto version  →  MASM assembly
   (familiar)        (intermediate)     (target)
```

1. **Read `binary_search_for.c`** first to understand the algorithm.
2. **Study `binary_search_goto.c`** to see how the same logic works with jumps and labels.
3. **Write your MASM assembly** by translating each goto/label into assembly instructions.

## Key Design Decisions (Important for Assembly)

- **All global variables** — no local variables are used. In MASM, these go in the `.data` or `.data?` section.
- **No function parameters** — the search function reads and writes global variables directly, just like assembly routines access memory locations.
- **Array of 10 integers** — stored globally, accessed by index.

## C-to-Assembly Cheat Sheet

| C Code | MASM Equivalent |
|--------|-----------------|
| `int x = 5;` | `x DWORD 5` (in `.data`) |
| `x = y + 1;` | `MOV EAX, y` / `ADD EAX, 1` / `MOV x, EAX` |
| `if (a == b)` | `MOV EAX, a` / `CMP EAX, b` / `JE label` |
| `if (a < b)` | `MOV EAX, a` / `CMP EAX, b` / `JL label` |
| `goto label;` | `JMP label` |
| `arr[mid]` | `MOV ESI, mid` / `MOV EAX, [arr + ESI*4]` |
| `printf(...)` | Use Irvine32 library or `invoke` with msvcrt |

## Building the C Versions

A Makefile is provided. On Linux:

```bash
make            # compile both versions
make run        # compile and run both
make clean      # remove executables
```

Or compile manually:

```bash
gcc -Wall -g -o binary_search_for binary_search_for.c
gcc -Wall -g -o binary_search_goto binary_search_goto.c
```

## Expected Output (Both Versions)

```
Sorted array: 5 12 18 25 33 41 56 72 89 100

Searching for 56 ...
Found 56 at index 6

Searching for 42 ...
42 was NOT found in the array.

Searching for 5 ...
Found 5 at index 0

Searching for 100 ...
Found 100 at index 9
```

Your MASM assembly program should produce the **same output** for the same test cases.

## Your Task

1. Study both C files and understand the binary search algorithm.
2. Pay special attention to the **goto version** — it is your blueprint for assembly.
3. Write a MASM assembly program (`binary_search.asm`) that implements the same logic.
4. Your assembly version should:
   - Declare all variables in the `.data` section
   - Use the same sorted array: `5, 12, 18, 25, 33, 41, 56, 72, 89, 100`
   - Search for the same test values and print the results
   - Use labels and jump instructions (no high-level `.IF` / `.WHILE` MASM directives)

Good luck!
