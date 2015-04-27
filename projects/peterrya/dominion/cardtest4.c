//test embargo
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
    struct gameState *state = newGame();
    int* kcards = kingdomCards(1,2,3,4,5,6,7,8,9,10);

    initializeGame(4 ,kcards , 321654, state);

    //begin tests
    state->hand[player1][0] = embargo;
    cardEffect(embargo,duchy,0,0,state,0,0);
    if(state->embargoTokens[duchy] != 1){
        printf("F| embargo fails\n");
    }
    else{
        printf("S| embargo succeeds\n");
    }

    state->supplyCount[duchy] = -1;
    if(cardEffect(embargo,duchy,0,0,state,0,0) != -1){
            printf("F| not in play embargo fails\n");
    }
    else{
        printf("S| not in play embargo succeeds\n");
    }
    return 0;
}
