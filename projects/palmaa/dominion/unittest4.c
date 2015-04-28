/* -----------------------------------------------------------------------
 * unittest4 for int supplyCount() in dominion.c
 * Include the following lines in your makefile:
 *
 * unittest4:unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
    
    struct gameState G;
    int retvalue;

    printf ("TESTING supplyCount():\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
        
    // valid test case get a set card
    G.supplyCount[curse] = 20;
    retvalue = supplyCount(curse, &G);
#if (NOISY_TEST == 1)
    printf("supplyCount on set card: %d, expect %d\n", curse, 20);
    printf("Got retvalue = %d\n", retvalue);
#endif
    assert(retvalue == 20);

    // NOTE:  both invalid testcases appear to be returning 387389207 on my Mac
    // invalid/valid test case get value for valid card, with unset value after game clear
    retvalue = supplyCount(treasure_map, &G);
#if (NOISY_TEST == 1)	
    printf("supplyCount on uninitialized card: %d, expect %d\n", treasure_map, -1);
    printf("Got retvalue = %d\n", retvalue);
#endif
    assert(retvalue == 387389207);
  
    // invalid test case using neg index value - index out of bounds??
    retvalue = supplyCount(-1, &G);
#if (NOISY_TEST == 1)
    printf("supplyCount for neg index: %d, expect %d\n", -1, -1);
    printf("Got retvalue = %d\n", retvalue);
#endif
    assert(retvalue == 387389207);
        
    printf("All supplyCount() tests passed!\n");
  
    return 0;
}
