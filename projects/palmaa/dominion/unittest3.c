/* -----------------------------------------------------------------------
 * unittest3 for int getCost() in dominion.c
 * Include the following lines in your makefile:
 *
 * unittest3:unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    
    int CardCost[] = { 0, 2, 5, 8, 0, 3, 6, 6, 5, 
    				   4, 4, 5, 4, 4, 3, 4, 3, 5,
    				   3, 5, 3, 4, 2, 5, 4, 4, 4 };
    int i;

    printf ("TESTING getCost():\n");
    
    // valid test cases
    for (i = 0; i < treasure_map; i++) {
#if (NOISY_TEST == 1)
    printf("enum card %d, expect %d\n", i, CardCost[i]);
#endif
    assert(getCost(i) == CardCost[i]);
    }
    
    // invalid test case
#if (NOISY_TEST == 1)
    printf("enum invalid card %d, expect %d\n", treasure_map + 100, -1);
#endif
    assert(getCost(treasure_map + 100) == -1);
  
    // invalid test case
#if (NOISY_TEST == 1)
    printf("enum invalid card %d, expect %d\n", -1 * treasure_map, -1);
#endif
    assert(getCost(treasure_map * -1) == -1);
        
    printf("All getCost() tests passed!\n");
  
    return 0;
}
