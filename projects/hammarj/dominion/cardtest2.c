#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void loadDeck(int player) {
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
    state->discardCount[player1] = 0;
    int handpos = 0;
    int res;      //return value of function
    
    //play village card when it's the only card in the player's hand
    state->hand[player][0] = village;
    state->handCount[player1] = 1;
    state->numActions = 1;
    loadDeck(player);
    res = cardVillage(handpos, state);
    assert(res == 0);
    assert(state->deckCount[player] == 4);
    assert(state->discardCount[player] == 1);
    assert(state->handCount[player] == 1);
    assert(state->numActions == 3);
    
    return 0;
}