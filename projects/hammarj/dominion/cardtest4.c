#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests cardAdventurer()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->whoseTurn = player;
    int handpos = 0;
    int res;      //return value of function
		
		printf("\ncardtest4\n");
    
    //play an Adventurer card with a deck consisting of just two treasure cards
    state->playedCardCount = 0;
    state->deck[player][0] = silver;
    state->deck[player][1] = gold;
    state->deckCount[player] = 2;
    state->hand[player][handpos] = adventurer;
    state->handCount[player] = 1;
    res = cardAdventurer(state, handpos);
    assert(res == 0);
    if (state->playedCardCount != 1)
				printf("26: playedCardCount = %i, expected 1\n", state->playedCardCount);
    assert(state->deckCount[player] == 0);
    if (state->handCount[player] != 2)
				printf("29: handCount = %i, expected 2\n", state->handCount[player]);
    
    //same as above but deck has one non-treasure card as well
    state->discardCount[player] = 0;
    state->deck[player][0] = silver;
    state->deck[player][1] = duchy;
    state->deck[player][2] = gold;
    state->deckCount[player] = 3;
    state->hand[player][handpos] = adventurer;
    state->handCount[player] = 1;
    res = cardAdventurer(state, handpos);
    assert(res == 0);
		if (state->playedCardCount != 1)
				printf("42: playedCardCount = %i, expected 1\n", state->playedCardCount);
    assert(state->discardCount[player] == 1);
    assert(state->deckCount[player] == 0);
    if (state->handCount[player] != 2)
				printf("46: handCount = %i, expected 2\n", state->handCount[player]);
    
    //same as above but deck now has two non-treasure cards
    state->discardCount[player] = 0;
    state->deck[player][0] = duchy;
    state->deck[player][1] = silver;
    state->deck[player][2] = remodel;
    state->deck[player][3] = gold;
    state->deckCount[player] = 4;
    state->hand[player][handpos] = adventurer;
    state->handCount[player] = 1;
    res = cardAdventurer(state, handpos);
    assert(res == 0);
		if (state->playedCardCount != 1)
				printf("60: playedCardCount = %i, expected 1\n", state->playedCardCount);
    if (state->discardCount[player] != 1)
				printf("62: discardCount = %i, expected 1\n", 
								state->discardCount[player]);
    if (state->deckCount[player] != 1)
				printf("65: deckCount = %i, expected 1\n", state->deckCount[player]);
    if (state->handCount[player] != 2)
				printf("67: handCount = %i, expected 2\n", state->handCount[player]);
    
    //play Adventurer card with only one treasure card in deck/discard pile
    state->discardCount[player] = 0;
    state->deck[player][0] = duchy;
    state->deck[player][1] = silver;
    state->deck[player][2] = remodel;
    state->deckCount[player] = 3;
    state->hand[player][handpos] = adventurer;
    state->handCount[player] = 1;
    res = cardAdventurer(state, handpos);
    assert(res == 0);
		if (state->playedCardCount != 1)
				printf("80: playedCardCount = %i, expected 1\n", state->playedCardCount);
    assert(state->discardCount[player] == 2);
    assert(state->deckCount[player] == 0);
    if (state->handCount[player] != 1)
				printf("84: handCount = %i, expected 1\n", state->handCount[player]);
    
    return 0;
}