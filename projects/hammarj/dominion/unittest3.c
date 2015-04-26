#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests discardCard()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    int handpos;
    int res;      //return value of function
    
    state->handCount[player] = 0;
    state->playedCardCount = 0;   
    
    //trash the only card in a player's hand
    state->hand[player][0] = mine;
    state->handCount[player] = 1;
    handpos = 0;
    res = discardCard(handpos, player, state, 1);
    assert(res == 0);
    assert(state->playedCardCount == 0);
    assert(state->handCount[player] == 0);
    
    //discard the only card in a player's hand
    state->hand[player][0] = village;
    state->handCount[player] = 1;
    handpos = 0;
    res = discardCard(handpos, player, state, 0);
    assert(res == 0);
    assert(state->playedCardCount == 1);
    assert(state->playedCards[0] == village);
    assert(state->handCount[player] == 0);
    
    //discard the second of two cards in a player's hand
    state->hand[player][0] = gold;
    state->hand[player][1] = mine;
    state->handCount[player] = 2;
    handpos = 1;
    res = discardCard(handpos, player, state, 0);
    assert(res == 0);
    assert(state->playedCardCount == 2);
    assert(state->playedCards[0] == village);
    assert(state->playedCards[1] == mine);
    assert(state->handCount[player] == 1);
    assert(state->hand[player][0] == gold);
    
    //discard the first of two cards in a player's hand
    state->hand[player][0] = adventurer;
    state->hand[player][1] = province;
    state->handCount[player] = 2;
    handpos = 0;
    res = discardCard(handpos, player, state, 0);
    assert(res == 0);
    assert(state->playedCardCount == 3);
    assert(state->playedCards[0] == village);
    assert(state->playedCards[1] == mine);
    assert(state->playedCards[2] == adventurer);
    assert(state->handCount[player] == 1);
    assert(state->hand[player][0] == province);
    
    return 0;
}