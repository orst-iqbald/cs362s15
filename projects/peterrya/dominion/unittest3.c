//testing fullDeckCount
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main(){
    //build test objects
    int player1 = 0;
    int player2 = 1;
    int player3 = 2;
    int player4 = 3 ;
    int i;
    struct gameState *state = newGame();
    int* kcards = kingdomCards(1,2,3,4,5,6,7,8,9,10);

    initializeGame(4 ,kcards , 321654, state);

    //begin tests
    if(fullDeckCount(player1,estate,state) != 3){
        printf("F| deck count fails\n");
    }
    else{
        printf("S| deck count succeeds\n");
    }

    //put deck in discard
    for (i = 0; i < state->deckCount[player1]; i++){
        state->discard[player1][i + state->discardCount[player1]] = state->deck[player1][i];
        state->deck[player1][i] = -1;
    }
    state->discardCount[player1] += state->deckCount[player1];
    state->deckCount[player1] = 0;

    //test discard
    if(fullDeckCount(player1,copper,state) != 7){
        printf("F| discard count fails\n");
    }
    else{
        printf("S| discard count succeeds\n");
    }

    //put discard in hand
    while(state->discardCount[player1] > 0){
        state->hand[player1][state->handCount[player1]] = state->discard[player1][state->discardCount[player1] - 1];
        state->discardCount[player1]--;
        state->handCount[player1]++;
    }

    //test hand
        if(fullDeckCount(player1,copper,state) != 7){
        printf("F| hand count fails\n");
    }
    else{
        printf("S| hand count succeeds\n");
    }
    return 0;
}
