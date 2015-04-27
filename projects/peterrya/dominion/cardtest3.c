//test sea_hag
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
    int tempd1 = state->discardCount[player1];
    int tempd2 = state->discardCount[player2];
    int tempd3 = state->discardCount[player3];
    int tempd4 = state->discardCount[player4];
    state->hand[player1][0] = sea_hag;
    cardEffect(sea_hag,0,0,0,state,0,0);
    if(tempd1 != state->discardCount[player1] || tempd2 != state->discardCount[player2] - 1 || tempd3 != state->discardCount[player3] - 1 || tempd4 != state->discardCount[player4] - 1 ){
        printf("F| sea_hag fails\n");
    }
    else{
        printf("S| sea_hag succeeds\n");
    }

    //set player2's deck to discard
    for (i = 0; i < state->deckCount[player2]; i++){
        state->discard[player2][i + state->discardCount[player1]] = state->deck[player2][i];
        state->deck[player2][i] = -1;
    }
    state->discardCount[player2] += state->deckCount[player2];
    state->deckCount[player2] = 0;

    //test sea_hag
    tempd2 = state->discardCount[player2];
    state->hand[player1][0] = sea_hag;
    cardEffect(sea_hag,0,0,0,state,0,0);
    if(state->discardCount[player2] != tempd2){
        printf("F| sea_hag no deck fails\n");
    }
    else{
        printf("S| sea_hag no deck succeeds\n");
    }
    return 0;
}
