/* -----------------------------------------------------------------------
 * unittest1 for int compare() in dominion.c
 * Include the following lines in your makefile:
 *
 * unittest1:unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    
    int val1 = 1, val2 = 0, val3 = 1;

    printf ("TESTING compare():\n");
    
    
#if (NOISY_TEST == 1)
    printf("a = %d, b = %d, expect %d\n", val1, val2, 1); 
#endif
    assert(compare(&val1, &val2) == 1);
#if (NOISY_TEST == 1)
    printf("a = %d, b = %d, expect %d\n", val2, val3, -1);
#endif
    assert(compare(&val2, &val3) == -1);
#if (NOISY_TEST == 1)
    printf("a = %d, b = %d, expect %d\n", val1, val3, 0);
#endif
    assert(compare(&val1, &val3) == 0);

    printf("All compare() tests passed!\n");

    return 0;
}
