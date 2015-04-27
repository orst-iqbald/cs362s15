//test adventurer
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

    //begin  tests
    state->hand[player1][0] = adventurer;
    int precoin = updateCoins(player1,state,0);
    adventurerEffect(state,0);
    if(updateCoins(player1, state,0) <= precoin){
        printf("F| adventurer fails\n");
    }
    else{
        printf("S| adventurer succeeds\n");
    }

    //move deck to discard
    for (i = 0; i < state->deckCount[player1]; i++){
        state->discard[player1][i + state->discardCount[player1]] = state->deck[player1][i];
        state->deck[player1][i] = -1;
    }
    state->discardCount[player1] += state->deckCount[player1];
    state->deckCount[player1] = 0;


    //test adventurer
    state->hand[player1][0] = adventurer;
    precoin = updateCoins(player1,state,0);
    adventurerEffect(state,0);
    if(updateCoins(player1, state,0) <= precoin){
        printf("F| adventurer fails\n");
    }
    else{
        printf("S| adventurer succeeds\n");
    }
    return 0;
}
