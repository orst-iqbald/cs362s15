/* -----------------------------------------------------------------------
 * unittest2 for int isGameOver() in dominion.c
 * Include the following lines in your makefile:
 *
 * unittest2:unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int i, retvalue;

    printf ("TESTING isGameOver():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state

    // set gameState->supplyCount[i]=1 for i in range 0 to 24
    for (i =0; i < 25; i++) G.supplyCount[i] = 1;
    // set gameState.supplyCount[0] = gameState.supplyCount[24] = 0
    G.supplyCount[0] = 0;
    G.supplyCount[24] = 0;
    retvalue = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("supplyCount[province] = %d, num supplyCount[i] == 0 is %d, expect %d\n",
    G.supplyCount[province], 2, 0);
#endif
    assert(retvalue == 0);
    
    // set gameState->supplyCount[province]=0 
    G.supplyCount[province] = 0;
    G.supplyCount[0] = 1;
    retvalue = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("supplyCount[province] = %d, num supplyCount[i] == 0 is %d, expect %d\n",
    G.supplyCount[province], 2, 1);
#endif
    assert(retvalue == 1);
    
    // set gameState->supplyCount[province]=1 
    G.supplyCount[province] = 1;
    // inc num of supplyCount[i] == 0 to 3
    G.supplyCount[0] = 0;
    G.supplyCount[11] = 0;
    retvalue = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("supplyCount[province] = %d, num supplyCount[i] == 0 is %d, expect %d\n",
    G.supplyCount[province], 3, 1);
#endif
    assert(retvalue == 1);

    // gameState->supplyCount[province]>0 and num supplyCount[i] == 0 is 4
    G.supplyCount[20] = 0;
    retvalue = isGameOver(&G);
#if (NOISY_TEST == 1)
    printf("supplyCount[province] = %d, num supplyCount[i] == 0 is %d, expect %d\n",
    G.supplyCount[province], 4, 1);
#endif
    assert(retvalue == 1);


    printf("All isGameOver() tests passed!\n");

    return 0;
}
