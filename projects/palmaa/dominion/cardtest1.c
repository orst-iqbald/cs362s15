/* -----------------------------------------------------------------------
 * test for play card smithy in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest1:cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    
    struct gameState *G;
    int player = 0;
	int all_smiths[MAX_HAND];
	int i;
	
	// initial hand, deck, discard values
	int init_handCount = 3;
	int init_deckCount = 25;
	int init_discardCount = 7;
	
	// set to init false - meaning not okay
	int bool_handCount = 0;
	int bool_deckCount = 0;
	int bool_discardCount = 0;
	
	for (i=0; i < MAX_HAND; i++) {
	    all_smiths[i] = smithy;
	}
	    
    printf ("TESTING smithy card play\n");
    
    
    // had to do it this way to avoid segfault error without going through other game code
    G = (struct gameState*)calloc(1, sizeof(struct gameState));   // calloc a game struct
    
    G->whoseTurn = player;
    G->handCount[player] = init_handCount;
    G->deckCount[player] = init_deckCount;
    G->discardCount[player] = init_discardCount;
    
    memcpy(G->hand[player], all_smiths, G->handCount[player] * sizeof(int));  //set all cards to smithy
    
    //play smithy
    cardEffect(smithy, 1, 1, 1, G, 0, NULL);
    //pcdSmithy(G, player, 1);

    // comparisons of actual to expected values for hand, deck, discard values
    if (G->handCount[player] == init_handCount + 3 -1) bool_handCount = 1;
    if (G->deckCount[player] == init_deckCount - 3) bool_deckCount = 1;
    if (G->discardCount[player] == init_discardCount + 1) bool_deckCount = 1;
    
    // output results
#if (NOISY_TEST == 1)
    printf("act handCount: %d, exp handCount: %d\n", G->handCount[player], init_handCount + 3 -1);
    printf("act deckCount: %d, exp deckCount: %d\n", G->deckCount[player], init_deckCount - 3);
    printf("act discardCount: %d, exp discardCount: %d\n", G->discardCount[player], init_discardCount+1);
#endif 

	if (bool_handCount) printf("smithy card play handCount: PASS\n");
	else  printf("smithy card play handCount: FAIL\n"); 
	if (bool_deckCount) printf("smithy card play deckCount: PASS\n");
	else  printf("smithy card play deckCount: FAIL\n");
	if (bool_discardCount) printf("smithy card play discardCount: PASS\n");
	else  printf("smithy card play discardCount: FAIL\n");
	       
	free(G);
	
    return 0;
}
