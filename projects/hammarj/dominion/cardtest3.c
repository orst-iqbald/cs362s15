#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

//tests cardRemodel()
int main() {
    int player = 0;
    struct gameState* state = malloc(sizeof(struct gameState));
    state->whoseTurn = player;
    int cardToTrashPos;
    int cardToGain;
    int handpos = 0;
    int res;      //return value of function
    
    //remodel an estate into a smithy
    state->discardCount[player] = 0;
    state->hand[player][handpos] = remodel;
    state->hand[player][1] = estate;
    state->handCount[player1] = 2;
    cardToTrashPos = 1;
    cardToGain = smithy;
    res = cardRemodel(state, handpos, cardToTrashPos, cardToGain);
    assert(res == 0);
    assert(state->discardCount[player] == 1);
    assert(state->handCount[player] == 1);
    assert(state->hand[player][0] == smithy);
    
    //attempt to gain a card that is too expensive.  Should fail.
    state->discardCount[player] = 0;
    state->hand[player][handpos] = remodel;
    state->hand[player][1] = estate;    //worth 2 coins
    state->handCount[player1] = 2;
    cardToTrashPos = 1;
    cardToGain = duchy;       //worth 5 coins
    res = cardRemodel(state, handpos, cardToTrashPos, cardToGain);
    assert(res != 0);
    
    //attempt to trash the Remodel card that we're also playing. Should fail. 
    state->hand[player][handpos] = remodel;
    state->handCount[player] = 1;
    cardToTrashPos = 0;     //the remodel card we're playing
    cardToGain = silver;
    res = cardRemodel(state, handpos, cardToTrashPos, cardToGain);
    assert(res != 0);
    
    return 0;
}