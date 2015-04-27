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

//tests cardSmithy()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->whoseTurn = player;
    state->discardCount[player] = 0;
    int handpos = 0;
    int res;      //return value of function
    
    //play smithy card when it's the only card in the player's hand
    state->hand[player][0] = smithy;
    state->handCount[player] = 1;
    loadDeck(state);
    res = cardSmithy(state, handpos);
    assert(res == 0);
    assert(state->deckCount[player] == 2);
    assert(state->discardCount[player] == 1);
    assert(state->handCount[player] == 3);
    
    return 0;
}