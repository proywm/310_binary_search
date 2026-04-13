/*
 * binary_search_goto.c
 * =====================
 * Binary Search using GOTO statements (no loops).
 *
 * This version replaces every loop with explicit goto jumps and labels.
 * This is closer to how a CPU actually executes code — assembly language
 * has no for/while loops, only conditional and unconditional jumps
 * (like JMP, JE, JL in x86 assembly).
 *
 * Mapping of C constructs to goto / assembly equivalents:
 *
 *   C loop                  goto equivalent             Assembly equivalent
 *   --------------------    ----------------------      -------------------
 *   for (init; cond; inc)   label: if (!cond) goto end  CMP + JGE (jump)
 *        { body; }          body; inc; goto label;       JMP label
 *        end:
 *
 * IMPORTANT: The array MUST be sorted in ascending order.
 *
 * This version uses ALL GLOBAL variables (no local variables).
 */

#include <stdio.h>

/* ---------------------------------------------------------------
 * GLOBAL VARIABLES — same as the for-loop version.
 * In assembly, these would be in the .data or .bss segment.
 * --------------------------------------------------------------- */

/* The sorted array of 10 integers to search through */
int arr[10] = {5, 12, 18, 25, 33, 41, 56, 72, 89, 100};

int target;    /* The value we are searching for                  */
int low;       /* Left boundary of the current search range       */
int high;      /* Right boundary of the current search range      */
int mid;       /* Middle index: (low + high) / 2                  */
int result;    /* Index where target was found, or -1 if not found */
int i;         /* Counter used for printing the array             */

/* ---------------------------------------------------------------
 * FUNCTION: binary_search_goto
 * Performs binary search using GOTO statements instead of loops.
 *
 * The logic is identical to the for-loop version, but every loop
 * is replaced with labels and goto jumps.
 *
 * Think of labels as ADDRESSES in memory.  "goto label" is like
 * the assembly instruction "JMP address".
 * --------------------------------------------------------------- */
void binary_search_goto(void)
{
    /*
     * Step 1: Initialize the search range.
     * This part is the same — no loop involved.
     */
    low = 0;
    high = 9;
    result = -1;  /* Assume not found */

    /*
     * Step 2: This label marks the TOP of our search loop.
     *
     * In assembly, this would be a label like:
     *   search_loop_start:
     *       CMP  low, high       ; compare low and high
     *       JG   search_done     ; if low > high, jump to done
     */
search_loop_start:

    /*
     * CHECK THE LOOP CONDITION: is low <= high?
     * If low > high, the search range is empty — jump to the end.
     *
     * This replaces the "low <= high" condition in the for loop.
     * In assembly: CMP low, high / JG search_done
     */
    if (low > high)
        goto search_done;

    /*
     * Step 3: Calculate the middle index.
     * Same as the for-loop version.
     */
    mid = (low + high) / 2;

    /*
     * Step 4: Compare arr[mid] with target.
     * We use goto to jump to the appropriate section.
     *
     * In assembly this would be:
     *   MOV  EAX, [arr + mid*4]   ; load arr[mid]
     *   CMP  EAX, target          ; compare with target
     *   JE   found_it             ; jump if equal
     *   JG   search_left          ; jump if arr[mid] > target
     *   JMP  search_right         ; otherwise go right
     */
    if (arr[mid] == target)
        goto found_it;

    if (target < arr[mid])
        goto search_left;

    /* Fall through to search_right (target > arr[mid]) */
    goto search_right;

    /*
     * TARGET FOUND — record the index and jump to the end.
     * In assembly: MOV result, mid / JMP search_done
     */
found_it:
    result = mid;
    goto search_done;

    /*
     * SEARCH LEFT HALF — target is smaller than arr[mid].
     * Narrow the range by setting high = mid - 1.
     * Then jump back to the top of the loop.
     *
     * In assembly:
     *   MOV  EAX, mid
     *   SUB  EAX, 1
     *   MOV  high, EAX
     *   JMP  search_loop_start
     */
search_left:
    high = mid - 1;
    goto search_loop_start;   /* Jump back to loop top */

    /*
     * SEARCH RIGHT HALF — target is larger than arr[mid].
     * Narrow the range by setting low = mid + 1.
     * Then jump back to the top of the loop.
     *
     * In assembly:
     *   MOV  EAX, mid
     *   ADD  EAX, 1
     *   MOV  low, EAX
     *   JMP  search_loop_start
     */
search_right:
    low = mid + 1;
    goto search_loop_start;   /* Jump back to loop top */

    /*
     * SEARCH DONE — we either found the target or exhausted the range.
     * 'result' holds the answer: index if found, -1 if not.
     *
     * In assembly, this is where the function would prepare the
     * return value and execute RET to return to the caller.
     */
search_done:
    return;  /* result is already set */
}

int main(void)
{
    /* ---- Print the array ---- */
    printf("=== Binary Search (GOTO version) ===\n\n");
    printf("Sorted array: ");

    /*
     * Even the print loop uses goto instead of a for loop.
     * Original for loop:  for (i = 0; i < 10; i++) { printf(...); }
     *
     * Goto equivalent:
     *   i = 0;                    (init)
     *   print_start:
     *     if (i >= 10) goto print_done;   (condition check)
     *     printf(...);            (body)
     *     i = i + 1;             (increment)
     *     goto print_start;      (jump back to top)
     *   print_done:
     */
    i = 0;
print_start:
    if (i >= 10)
        goto print_done;
    printf("%d ", arr[i]);
    i = i + 1;
    goto print_start;
print_done:

    printf("\n\n");

    /* --- Test 1: Search for a value that EXISTS in the array --- */
    target = 56;
    printf("Searching for %d ...\n", target);
    binary_search_goto();
    if (result != -1)
        goto test1_found;
    goto test1_not_found;
test1_found:
    printf("Found %d at index %d\n\n", target, result);
    goto test2;
test1_not_found:
    printf("%d was NOT found in the array.\n\n", target);
    goto test2;

    /* --- Test 2: Search for a value that DOES NOT exist --- */
test2:
    target = 42;
    printf("Searching for %d ...\n", target);
    binary_search_goto();
    if (result != -1)
        goto test2_found;
    goto test2_not_found;
test2_found:
    printf("Found %d at index %d\n\n", target, result);
    goto test3;
test2_not_found:
    printf("%d was NOT found in the array.\n\n", target);
    goto test3;

    /* --- Test 3: Search for the FIRST element --- */
test3:
    target = 5;
    printf("Searching for %d ...\n", target);
    binary_search_goto();
    if (result != -1)
        goto test3_found;
    goto test3_not_found;
test3_found:
    printf("Found %d at index %d\n\n", target, result);
    goto test4;
test3_not_found:
    printf("%d was NOT found in the array.\n\n", target);
    goto test4;

    /* --- Test 4: Search for the LAST element --- */
test4:
    target = 100;
    printf("Searching for %d ...\n", target);
    binary_search_goto();
    if (result != -1)
        goto test4_found;
    goto test4_not_found;
test4_found:
    printf("Found %d at index %d\n\n", target, result);
    goto all_done;
test4_not_found:
    printf("%d was NOT found in the array.\n\n", target);
    goto all_done;

all_done:
    return 0;
}
