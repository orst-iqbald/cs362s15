#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests gainCard()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    int card;
    int res;      //return value of function
    int toDiscard = 0;
    int toDeck = 1;
    int toHand = 2;
    
    state->discardCount[player] = 0;
    state->deckCount[player] = 0;
    state->handCount[player] = 0;
    
    //supply for card to be gained is empty
    card = adventurer;
    state->supplyCount[card] = 0;
    res = gainCard(card, state, toDiscard, player);
    assert(res == -1);
    assert(state->supplyCount[card] == 0);
    assert(state->discardCount[player] == 0);
    assert(state->deckCount[player] == 0);
    assert(state->handCount[player] == 0);
    
    //gain card to discard pile
    card = adventurer;
    state->supplyCount[card] = 1;
    res = gainCard(card, state, toDiscard, player);
    assert(res == 0);
    assert(state->supplyCount[card] == 0);
    assert(state->discardCount[player] == 1);
    assert(state->discard[player][0] == card);
    assert(state->deckCount[player] == 0);
    assert(state->handCount[player] == 0);
    
    //gain a different card to discard pile
    card = mine;
    state->supplyCount[card] = 1;
    res = gainCard(card, state, toDiscard, player);
    assert(res == 0);
    assert(state->supplyCount[card] == 0);
    assert(state->discardCount[player] == 2);
    assert(state->discard[player][0] == adventurer);
    assert(state->discard[player][1] == card);
    assert(state->deckCount[player] == 0);
    assert(state->handCount[player] == 0);
    
    //gain card to deck
    card = adventurer;
    state->supplyCount[card] = 2;
    res = gainCard(card, state, toDeck, player);
    assert(res == 0);
    assert(state->supplyCount[card] == 1);
    assert(state->discardCount[player] == 2);
    assert(state->discard[player][1] == mine);
    assert(state->deckCount[player] == 1);
    assert(state->deck[player][0] == card);
    assert(state->handCount[player] == 0);
    
    //gain card to hand
    card = adventurer;
    state->supplyCount[card] = 2;
    res = gainCard(card, state, toHand, player);
    assert(res == 0);
    assert(state->supplyCount[card] == 1);
    assert(state->discardCount[player] == 2);
    assert(state->deckCount[player] == 1);
    assert(state->deck[player][0] == adventurer);
    assert(state->handCount[player] == 1);
    assert(state->hand[player][0] == card);
    
    return 0;
}