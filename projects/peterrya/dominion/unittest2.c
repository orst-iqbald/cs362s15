//testing scoreFor
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int main(){
    //build test objects
    int player1 = 0;
    struct gameState *state = newGame();
    int* kcards = kingdomCards(1,2,3,4,5,6,7,8,9,10);

    initializeGame(4 ,kcards , 321654, state);

    //begin tests
    if(scoreFor(player1,state) != 3){
        printf("F| scoring cards in deck fails\n");
    }
    else{
        printf("S| scoring cards in deck succeeds\n");;
    }
    int i;
    //set player1's deck to the discard
    for (i = 0; i < state->deckCount[player1]; i++){
        state->discard[player1][i + state->discardCount[player1]] = state->deck[player1][i];
        state->deck[player1][i] = -1;
    }
    state->discardCount[player1] += state->deckCount[player1];
    state->deckCount[player1] = 0;

    //test discard
    if(scoreFor(player1,state) != 3){
        printf("F| scoring cards in discard fails\n");
    }
    else{
        printf("S| scoring cards in discard succeeds\n");
    }

    //put estates in players hand
    while(state->handCount[player1] < 10){
        drawCard(player1,state);
    }

    //test hand
    if(scoreFor(player1,state) != 3){
        printf("F| scoring cards in hand fails\n");
    }
    else{
        printf("S| scoring cards in hand succeeds\n");
    }

    //put hand back in deck
    while(state->handCount[player1] > 0){
        state->deck[player1][state->deckCount[player1]] = state->hand[player1][state->handCount[player1] - 1];
        state->deckCount[player1]++;
        state->handCount[player1]--;
    }

    //add other victory cards to deck
    state->deck[player1][state->deckCount[player1]] = curse;
    state->deckCount[player1]++;
    state->deck[player1][state->deckCount[player1]] = duchy;
    state->deckCount[player1]++;
    state->deck[player1][state->deckCount[player1]] = province;
    state->deckCount[player1]++;
    state->deck[player1][state->deckCount[player1]] = great_hall;
    state->deckCount[player1]++;

    //test hand
    if(scoreFor(player1,state) != 10){
        printf("F| scoring additional cards fails\n");
    }
    else{
        printf("S| scoring additional cards succeeds\n");
    }
    return 0;
}
