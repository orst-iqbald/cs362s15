// Jason Hsu
// hsuja@onid.oregonstate.edu
// 4/26/15
// CS362-400
// test fulldeckcount

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){


	//set cards in deck, hand, and discard for each player, then count particular cards for each player

    struct gameState* g = malloc(sizeof(struct gameState));

    int result;

    g->deckCount[0] = 5;
    g->handCount[0] = 6;
    g->discardCount[0] = 6;

    g->deck[0][0] = smithy;
    g->deck[0][1] = village;
    g->deck[0][2] = village;
    g->deck[0][3] = great_hall;
    g->deck[0][4] = feast;

    g->hand[0][0] = copper;
    g->hand[0][1] = gold;
    g->hand[0][2] = copper;
    g->hand[0][3] = copper;
    g->hand[0][4] = curse;
    g->hand[0][5] = feast;

    g->discard[0][0] = smithy;
    g->discard[0][1] = province;
    g->discard[0][2] = estate;
    g->discard[0][3] = estate;
    g->discard[0][4] = copper;
    g->discard[0][5] = feast;
    g->discard[0][6] = smithy; // exceeds discardCount

    printf("TESTING fullDeckCount():\n");

    result = fullDeckCount(0, great_hall, g);
    printf("Count = %d, expected = %d\n", result, 1);
    assert(result == 1);

    result = fullDeckCount(0, curse, g);
    printf("Count = %d, expected = %d\n", result, 1);
    assert(result == 1);

    result = fullDeckCount(0, estate, g);
    printf("Count = %d, expected = %d\n", result, 2);
    assert(result == 2);
    
    result = fullDeckCount(0, copper, g);
    printf("Count = %d, expected = %d\n", result, 4);
    assert(result == 4);

    result = fullDeckCount(0, feast, g);
    printf("Count = %d, expected = %d\n", result, 3);
    assert(result == 3);

    result = fullDeckCount(0, adventurer, g);
    printf("Count = %d, expected = %d\n", result, 0);
    assert(result == 0);

    result = fullDeckCount(0, smithy, g);
    printf("Count = %d, expected = %d\n", result, 2);
    assert(result == 2);

	printf("Tests complete.\n");

	free(g);

	return 0;
}