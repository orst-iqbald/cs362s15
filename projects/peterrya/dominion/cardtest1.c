//test smithy
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main(){
    //build test objects
    int player1 = 0;
    int i;
    struct gameState *state = newGame();
    int* kcards = kingdomCards(1,2,3,4,5,6,7,8,9,10);

    initializeGame(4 ,kcards , 321654, state);

    //begin tests
    state->hand[player1][0] = smithy;
    smithyEffect(state,0,player1);
    if(state->handCount[player1] != 8){
        printf("F| smithy fails\n");
    }
    else{
        printf("S| smithy succeeds\n");
    }

    //put deck into discard
    for (i = 0; i < state->deckCount[player1]; i++){
        state->discard[player1][i + state->discardCount[player1]] = state->deck[player1][i];
        state->deck[player1][i] = -1;
    }
    state->discardCount[player1] += state->deckCount[player1];
    state->deckCount[player1] = 0;

    //test smithy
        state->hand[player1][0] = smithy;
    smithyEffect(state,0,player1);
    if(state->handCount[player1] != 8){
        printf("F| smithy fails\n");
    }
    else{
        printf("S| smithy succeeds\n");
    }
    return 0;
}
