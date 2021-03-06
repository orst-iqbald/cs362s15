#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

void loadDeck(struct gameState* state) {
    int player = state->whoseTurn;
    
    int i;
    int card = adventurer;
    for (i = 0; i < 5; ++i) {
        state->deck[player][i] = card++;
    }
    state->deckCount[player] = 5;
}

//tests cardVillage()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->whoseTurn = player;
    state->playedCardCount = 0;
    int handpos = 0;
    int res;      //return value of function
    
    //play village card when it's the only card in the player's hand
    state->hand[player][0] = village;
    state->handCount[player] = 1;
    state->numActions = 1;
    loadDeck(state);
    res = cardVillage(state, handpos);
    assert(res == 0);
    assert(state->deckCount[player] == 4);
    assert(state->playedCardCount == 1);
    assert(state->handCount[player] == 1);
    assert(state->numActions == 3);
    
    return 0;
}