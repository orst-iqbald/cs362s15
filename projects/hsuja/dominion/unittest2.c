// Jason Hsu
// hsuja@onid.oregonstate.edu
// 4/26/15
// CS362-400
// test scoreFor()

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
    g->handCount[0] = 5;
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

    g->discard[0][0] = smithy;
    g->discard[0][1] = province;
    g->discard[0][2] = estate;
    g->discard[0][3] = estate;
    g->discard[0][4] = copper;
    g->discard[0][5] = feast;
    g->discard[0][6] = smithy; // exceeds discardCount

    g->deckCount[1] = 5;
    g->handCount[1] = 3;
    g->discardCount[1] = 5;

    g->deck[1][0] = smithy;
    g->deck[1][1] = village;
    g->deck[1][2] = village;
    g->deck[1][3] = village;
    g->deck[1][4] = gardens;

    g->hand[1][0] = adventurer;
    g->hand[1][1] = gold;
    g->hand[1][2] = duchy;

    g->discard[1][0] = duchy;
    g->discard[1][1] = province;
    g->discard[1][2] = estate;
    g->discard[1][3] = estate;
    g->discard[1][4] = gardens;

    // No victory cards
    g->deckCount[2] = 5;
    g->handCount[2] = 4;
    g->discardCount[2] = 3;

    g->deck[2][0] = smithy;
    g->deck[2][1] = village;
    g->deck[2][2] = village;
    g->deck[2][3] = village;
    g->deck[2][4] = feast;

    g->hand[2][0] = copper;
    g->hand[2][1] = gold;
    g->hand[2][2] = copper;
    g->hand[2][3] = copper;
    
    g->discard[2][0] = smithy;
    g->discard[2][1] = copper;
    g->discard[2][2] = feast;

    // Only curse cards (negative score)

    g->deckCount[3] = 5;
    g->handCount[3] = 4;
    g->discardCount[3] = 3;

    g->deck[3][0] = smithy;
    g->deck[3][1] = village;
    g->deck[3][2] = curse;
    g->deck[3][3] = feast;
    g->deck[3][4] = feast;

    g->hand[3][0] = copper;
    g->hand[3][1] = gold;
    g->hand[3][2] = curse;
    g->hand[3][3] = copper;
    
    g->discard[3][0] = smithy;
    g->discard[3][1] = copper;
    g->discard[3][2] = feast;

    printf("TESTING scoreFor():\n");

    result = scoreFor(0, g);
    printf("Score = %d, expected = %d\n", result, 8);
    if(result == 8){
        printf("scoreFor(): PASS player 1\n");
    }else{
        printf("scoreFor(): FAIL player 1\n");
    }

    result = scoreFor(1, g);
    printf("Score = %d, expected = %d\n", result, 16);
    if(result == 16){
        printf("scoreFor(): PASS player 2\n");
    }else{
        printf("scoreFor(): FAIL player 2\n");
    }

    result = scoreFor(2, g);
    printf("Score = %d, expected = %d\n", result, 0);
    if(result == 0){
        printf("scoreFor(): PASS player 3\n");
    }else{
        printf("scoreFor(): FAIL player 3\n");
    }

    result = scoreFor(3, g);
    printf("Score = %d, expected = %d\n", result, -2);
    if(result == -2){
        printf("scoreFor(): PASS player 4\n");
    }else{
        printf("scoreFor(): FAIL player 4\n");
    }

   
	printf("Tests complete.\n");

	free(g);

	return 0;
}