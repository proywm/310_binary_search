/*
 * binary_search_for.c
 * ====================
 * Binary Search using FOR loops.
 *
 * Binary search is an efficient way to find a value in a SORTED array.
 * Instead of checking every element one by one (linear search),
 * binary search cuts the search area in half each time.
 *
 * How it works:
 *   1. Look at the middle element of the current search range.
 *   2. If it matches the target, we're done!
 *   3. If the target is smaller, search the LEFT half.
 *   4. If the target is larger, search the RIGHT half.
 *   5. Repeat until found or the range is empty.
 *
 * IMPORTANT: The array MUST be sorted in ascending order for binary search to work.
 *
 * This version uses ALL GLOBAL variables (no local variables).
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
 * FUNCTION: binary_search_for
 * Performs binary search using a FOR loop.
 *
 * Before calling this function, set:
 *   - 'target' to the value you want to find
 * After it returns, check:
 *   - 'result' will be the index of target, or -1 if not found
 * --------------------------------------------------------------- */
void binary_search_for(void)
{
    /* Step 1: Initialize the search range to cover the entire array.
     *   low  = 0       (first index)
     *   high = 9       (last index, since array has 10 elements)
     */
    low = 0;
    high = 9;
    result = -1;  /* Assume not found until proven otherwise */

    /*
     * Step 2: Use a FOR loop to repeatedly narrow the search range.
     *
     * The loop runs as long as low <= high, meaning there is still
     * a valid range to search.  We use a dummy 'for' with the
     * condition only — the "increment" is handled inside the body
     * because we adjust low or high (not a simple counter).
     */
    for ( ; low <= high; )
    {
        /*
         * Step 3: Calculate the middle index.
         *
         *   mid = (low + high) / 2
         *
         * Example: if low=0 and high=9, mid = (0+9)/2 = 4
         *          (integer division truncates, so 4.5 becomes 4)
         */
        mid = (low + high) / 2;

        /*
         * Step 4: Compare the middle element with the target.
         */
        if (arr[mid] == target)
        {
            /* FOUND! Record the index and break out of the loop. */
            result = mid;
            break;
        }
        else if (target < arr[mid])
        {
            /*
             * Target is SMALLER than the middle element.
             * The target must be in the LEFT half.
             * Move 'high' down to mid - 1 to discard the right half.
             *
             * Example: arr[mid]=33, target=18
             *   Before: low=0, high=9
             *   After:  low=0, high=3   (search left half only)
             */
            high = mid - 1;
        }
        else
        {
            /*
             * Target is LARGER than the middle element.
             * The target must be in the RIGHT half.
             * Move 'low' up to mid + 1 to discard the left half.
             *
             * Example: arr[mid]=33, target=72
             *   Before: low=0, high=9
             *   After:  low=5, high=9   (search right half only)
             */
            low = mid + 1;
        }
    }
    /* When we get here, 'result' is either the found index or -1. */
}

int main(void)
{
    /* Print the array so the user can see what we're searching */
    printf("=== Binary Search (FOR loop version) ===\n\n");
    printf("Sorted array: ");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    /* --- Test 1: Search for a value that EXISTS in the array --- */
    target = 56;
    printf("Searching for %d ...\n", target);
    binary_search_for();
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
    printf("Searching for %d ...\n", target);
    binary_search_for();
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
    printf("Searching for %d ...\n", target);
    binary_search_for();
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
    printf("Searching for %d ...\n", target);
    binary_search_for();
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
