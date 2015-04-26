#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void loadDeck(int player) {
    int i;
    for (i = 0; i < 5; ++1) {
        state->deck[player][i] = adventurer;
    }
    state->deckCount[player] = 5;
}

void checkState(struct gameState* state) {
    assert(state->outpostPlayed == 0);
    assert(state->phase == 0);
    assert(state->numActions == 1);
    assert(state->coins == 0);
    assert(state->numBuys == 1);
    assert(state->playedCardCount == 0);
    assert(state->handCount[state->whoseTurn] == 0);
}

//tests endTurn()
int main() {
    int player1 = 0;
    int player2 = 1;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;
    state->whoseTurn = player1;
    int res;      //return value of function
    
    //end the first player's turn, who has no cards in their hand
    state->discardCount[player1] = 0;
    state->handCount[player1] = 0;
    loadDeck(player2);
    res = endTurn(state);
    assert(res == 0);
    checkState(state);
    assert(state->whoseTurn == player2);
    assert(state->handCount[player2] == 5);
    
    //end the second player's turn, who has 1 card in their hand
    state->discardCount[player2] = 0;
    state->hand[player2][0] = mine;
    state->handCount[player2] = 1;
    loadDeck(player1);
    res = endTurn(state);
    assert(res == 0);
    checkState(state);
    assert(state->whoseTurn == player1);
    assert(state->handCount[player1] == 5);
    
    //end the first player's turn, who has 2 cards in their hand
    state->discardCount[player1] = 0;
    state->hand[player1][0] = village;
    state->hand[player1][1] = remodel;
    state->handCount[player1] = 2;
    loadDeck(player2);
    res = endTurn(state);
    assert(res == 0);
    checkState(state);
    assert(state->whoseTurn == player2);
    assert(state->handCount[player2] == 5);
    
    return 0;
}