/*
 * binary_search_recursive.c
 * ==========================
 * Binary Search using RECURSIVE function calls.
 *
 * Binary search is an efficient way to find a value in a SORTED array.
 * Instead of checking every element one by one (linear search),
 * binary search cuts the search area in half each time.
 *
 * How it works:
 *   1. Look at the middle element of the current search range.
 *   2. If it matches the target, we're done!
 *   3. If the target is smaller, search the LEFT half (recursive call).
 *   4. If the target is larger, search the RIGHT half (recursive call).
 *   5. Base case: if the range is empty (low > high), return -1.
 *
 * IMPORTANT: The array MUST be sorted in ascending order for binary search to work.
 *
 * This version uses RECURSION — the function calls itself with a
 * smaller search range each time.  In assembly language, each
 * recursive call pushes a new stack frame onto the call stack,
 * storing the return address, parameters, and local variables.
 *
 * This version uses ALL GLOBAL variables (no local variables)
 * to match the style of the for-loop and goto versions.
 */

#include <stdio.h>

/* ---------------------------------------------------------------
 * GLOBAL VARIABLES — everything is declared here, nothing inside
 * functions.  In assembly language, global variables live in the
 * .data or .bss section of memory.
 * --------------------------------------------------------------- */

/* The sorted array of 10 integers to search through */
int arr[10] = {5, 12, 18, 25, 33, 41, 56, 72, 89, 100};

int target;    /* The value we are searching for                  */
int low;       /* Left boundary of the current search range       */
int high;      /* Right boundary of the current search range      */
int mid;       /* Middle index: (low + high) / 2                  */
int result;    /* Index where target was found, or -1 if not found */
int i;         /* Loop counter used for printing the array        */

/* ---------------------------------------------------------------
 * FUNCTION: binary_search_recursive
 * Performs binary search using recursion.
 *
 * Before calling this function, set:
 *   - 'target' to the value you want to find
 *   - 'low'    to the left boundary (start with 0)
 *   - 'high'   to the right boundary (start with 9)
 * After it returns, check:
 *   - 'result' will be the index of target, or -1 if not found
 *
 * How the recursion works:
 *   - Each call checks the middle element of [low..high].
 *   - If found, set result = mid and return.
 *   - If not found, adjust low or high and call itself again.
 *   - If low > high, the range is empty — set result = -1 and return.
 *
 * In assembly, each recursive call:
 *   1. Pushes the return address onto the stack (CALL instruction).
 *   2. Executes the function body.
 *   3. Pops the return address and jumps back (RET instruction).
 * --------------------------------------------------------------- */
void binary_search_recursive(void)
{
    /*
     * BASE CASE: If low > high, the search range is empty.
     * The target is not in the array.
     *
     * In assembly, this is a compare-and-branch:
     *   CMP low, high
     *   JG  not_found      ; jump if low > high
     */
    if (low > high)
    {
        result = -1;
        return;  /* Return to caller (pops stack frame in assembly) */
    }

    /*
     * RECURSIVE CASE: Calculate the middle index.
     *
     *   mid = (low + high) / 2
     *
     * Example: if low=0 and high=9, mid = (0+9)/2 = 4
     */
    mid = (low + high) / 2;

    /*
     * Compare the middle element with the target.
     */
    if (arr[mid] == target)
    {
        /*
         * FOUND! Record the index and return.
         * No more recursive calls needed.
         */
        result = mid;
        return;
    }
    else if (target < arr[mid])
    {
        /*
         * Target is SMALLER than the middle element.
         * Search the LEFT half: [low .. mid-1]
         *
         * We update 'high' and make a RECURSIVE CALL.
         * In assembly, this is a CALL instruction that pushes
         * the return address onto the stack.
         *
         * Example: arr[mid]=33, target=18
         *   Before: low=0, high=9
         *   After:  low=0, high=3  → recursive call
         */
        high = mid - 1;
        binary_search_recursive();  /* Recursive call — search left half */
    }
    else
    {
        /*
         * Target is LARGER than the middle element.
         * Search the RIGHT half: [mid+1 .. high]
         *
         * We update 'low' and make a RECURSIVE CALL.
         *
         * Example: arr[mid]=33, target=72
         *   Before: low=0, high=9
         *   After:  low=5, high=9  → recursive call
         */
        low = mid + 1;
        binary_search_recursive();  /* Recursive call — search right half */
    }
}

int main(void)
{
    /* Print the array so the user can see what we're searching */
    printf("=== Binary Search (RECURSIVE version) ===\n\n");
    printf("Sorted array: ");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    /* --- Test 1: Search for a value that EXISTS in the array --- */
    target = 56;
    low = 0;
    high = 9;
    printf("Searching for %d ...\n", target);
    binary_search_recursive();
    if (result != -1)
    {
        printf("Found %d at index %d\n\n", target, result);
    }
    else
    {
        printf("%d was NOT found in the array.\n\n", target);
    }

    /* --- Test 2: Search for a value that DOES NOT exist --- */
    target = 42;
    low = 0;
    high = 9;
    printf("Searching for %d ...\n", target);
    binary_search_recursive();
    if (result != -1)
    {
        printf("Found %d at index %d\n\n", target, result);
    }
    else
    {
        printf("%d was NOT found in the array.\n\n", target);
    }

    /* --- Test 3: Search for the FIRST element --- */
    target = 5;
    low = 0;
    high = 9;
    printf("Searching for %d ...\n", target);
    binary_search_recursive();
    if (result != -1)
    {
        printf("Found %d at index %d\n\n", target, result);
    }
    else
    {
        printf("%d was NOT found in the array.\n\n", target);
    }

    /* --- Test 4: Search for the LAST element --- */
    target = 100;
    low = 0;
    high = 9;
    printf("Searching for %d ...\n", target);
    binary_search_recursive();
    if (result != -1)
    {
        printf("Found %d at index %d\n\n", target, result);
    }
    else
    {
        printf("%d was NOT found in the array.\n\n", target);
    }

    return 0;
}
