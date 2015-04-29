#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests cardRemodel()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->whoseTurn = player;
		state->playedCardCount = 0;
    int cardToTrashPos;
    int cardToGain;
    int handpos = 0;
    int res;      //return value of function
		
		printf("\ncardtest3\n");
    
    //remodel an estate into a smithy
    state->discardCount[player] = 0;
    state->hand[player][handpos] = remodel;
    state->hand[player][1] = estate;
    state->handCount[player] = 2;
    cardToTrashPos = 1;
    cardToGain = smithy;
		state->supplyCount[smithy] = 1;
    res = cardRemodel(state, handpos, cardToTrashPos, cardToGain);
    assert(res == 0);
    assert(state->discardCount[player] == 1);
		assert(state->playedCardCount == 1);
    if (state->handCount[player] != 0)
				printf("32: handCount = %i, expected 0\n", state->handCount[player]);
    
    //attempt to gain a card that is too expensive.  Should fail.
    state->discardCount[player] = 0;
    state->hand[player][handpos] = remodel;
    state->hand[player][1] = estate;    //worth 2 coins
    state->handCount[player] = 2;
    cardToTrashPos = 1;
    cardToGain = duchy;       //worth 5 coins
    res = cardRemodel(state, handpos, cardToTrashPos, cardToGain);
    if (res == 0)
				printf("cardRemodel succeeded, expected failure\n");
    
    //attempt to trash the Remodel card that we're also playing. Should fail. 
    state->hand[player][handpos] = remodel;
    state->handCount[player] = 1;
    cardToTrashPos = 0;     //the remodel card we're playing
    cardToGain = silver;
    res = cardRemodel(state, handpos, cardToTrashPos, cardToGain);
    assert(res != 0);
    
    return 0;
}