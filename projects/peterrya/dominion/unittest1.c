//testing drawCard
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
    int ncard = state->deck[player1][state->deckCount[player1] - 1];
    drawCard(player1, state);
    if(state->hand[player1][state->handCount[player1] - 1] != ncard){
        printf("F| drawing first card fails\n");
    }
    else{
        printf("S| drawing first card succeeds\n");
    }

    ncard = state->deck[player2][state->deckCount[player2] - 1];
    drawCard(player2, state);
    if(state->hand[player2][state->handCount[player2] - 1] != ncard){
        printf("F| player2 drawing fail\n");
    }
    else{
        printf("S| player2 drawing succeeds\n");
    }

    ncard = state->deck[player1][state->deckCount[player1] - 1];
    drawCard(player1, state);
    if(state->hand[player1][state->handCount[player1] - 1] != ncard){
        printf("F| drawing another card from player1 fails\n");
    }
    else{
        printf("S| drawing another card from player1 succeeds\n");
    }

    ncard = state->deck[player1][state->deckCount[player1] - 1];
    drawCard(player1, state);
    if(state->hand[player1][state->handCount[player1] - 1] != ncard){
        printf("F| drawing a third card from player1 fails\n");
    }
    else{
        printf("S| drawing a third card from player1 succeeds\n");
    }

    //set player1's deck to the discard
    int i;
    for (i = 0; i < state->deckCount[player1]; i++){
        state->discard[player1][i + state->discardCount[player1]] = state->deck[player1][i];
        state->deck[player1][i] = -1;
    }
    state->discardCount[player1] += state->deckCount[player1];
    state->deckCount[player1] = 0;

    //test drawing cards
    ncard = state->handCount[player1];
    drawCard(player1, state);
    if(state->handCount[player1] != ncard + 1){
        printf("F| drawing a card from player1 while the deck is empty fails\n");
    }
    else{
        printf("S| drawing a card from player1 while the deck is empty succeeds\n");
    }
    return 0;
}
