#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests cardAdventurer()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->whoseTurn = player;
    int handpos = 0;
    int res;      //return value of function
    
    //play an Adventurer card with a deck consisting of just two treasure cards
    state->discardCount[player] = 0;
    state->deck[player][0] = silver;
    state->deck[player][1] = gold;
    state->deckCount[player] = 2;
    state->hand[player][handpos] = adventurer;
    state->handCount[player] = 1;
    res = cardAdventurer(state, handpos);
    assert(res == 0);
    assert(state->discardCount[player] == 1);
    assert(state->deckCount[player] == 0);
    assert(state->handCount[player] == 2);
    
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
    assert(state->discardCount[player] == 2);
    assert(state->deckCount[player] == 0);
    assert(state->handCount[player] == 2);
    
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
    assert(state->discardCount[player] == 2);
    assert(state->deckCount[player] == 1);
    assert(state->handCount[player] == 2);
    
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
    assert(state->discardCount[player] == 3);
    assert(state->deckCount[player] == 0);
    assert(state->handCount[player] == 1);
    
    return 0;
}