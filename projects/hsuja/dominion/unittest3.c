// Jason Hsu
// hsuja@onid.oregonstate.edu
// 4/26/15
// CS362-400
// test getWinners()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){


    //set cards in deck, hand, and discard for each player, then count particular cards for each player

    struct gameState* g = malloc(sizeof(struct gameState));

    //int result;

    // Player 1
    g->deckCount[0] = 5;
    g->handCount[0] = 5;
    g->discardCount[0] = 5;

    g->deck[0][0] = smithy;
    g->deck[0][1] = village;
    g->deck[0][2] = village;
    g->deck[0][3] = great_hall;
    g->deck[0][4] = feast;

    g->hand[0][0] = copper;
    g->hand[0][1] = gold;
    g->hand[0][2] = copper;
    g->hand[0][3] = copper;
    g->hand[0][4] = curse;

    g->discard[0][0] = smithy;
    g->discard[0][1] = province;
    g->discard[0][2] = estate;
    g->discard[0][3] = estate;
    g->discard[0][4] = copper;

    // Player 2
    g->deckCount[1] = 5;
    g->handCount[1] = 3;
    g->discardCount[1] = 5;

    g->deck[1][0] = smithy;
    g->deck[1][1] = village;
    g->deck[1][2] = village;
    g->deck[1][3] = village;
    g->deck[1][4] = duchy;

    g->hand[1][0] = adventurer;
    g->hand[1][1] = gold;
    g->hand[1][2] = duchy;

    g->discard[1][0] = duchy;
    g->discard[1][1] = province;
    g->discard[1][2] = estate;
    g->discard[1][3] = estate;
    g->discard[1][4] = smithy;

    // Player 3
    // No victory cards
    g->deckCount[2] = 3;
    g->handCount[2] = 4;
    g->discardCount[2] = 3;

    g->deck[2][0] = smithy;
    g->deck[2][1] = village;
    g->deck[2][2] = village;

    g->hand[2][0] = copper;
    g->hand[2][1] = gold;
    g->hand[2][2] = copper;
    g->hand[2][3] = copper;
    
    g->discard[2][0] = smithy;
    g->discard[2][1] = copper;
    g->discard[2][2] = feast;

    // Player 4
    // Only curse cards (negative score)
    g->deckCount[3] = 3;
    g->handCount[3] = 4;
    g->discardCount[3] = 3;

    g->deck[3][0] = smithy;
    g->deck[3][1] = village;
    g->deck[3][2] = curse;

    g->hand[3][0] = copper;
    g->hand[3][1] = gold;
    g->hand[3][2] = curse;
    g->hand[3][3] = copper;
    
    g->discard[3][0] = smithy;
    g->discard[3][1] = copper;
    g->discard[3][2] = feast;

    printf("TESTING getWinners():\n");

    g->numPlayers = 4;
    g->whoseTurn = 0;
    //g->numPlayers = 3;

    int players[MAX_PLAYERS];
    int i;
    int winner;

   

    getWinners(players, g);

    for(i = 0; i < MAX_PLAYERS; i++){
        if(players[i] == 1){
            winner = i;
        }
    }

    printf("Current Player: %d\n", whoseTurn(g) + 1);
    printf("score for Player 1: %d\n", scoreFor(0, g));
    printf("score for Player 2: %d\n", scoreFor(1, g));
    printf("score for Player 3: %d\n", scoreFor(2, g));
    printf("score for Player 4: %d\n", scoreFor(3, g));
    printf("Winner: Player %d, Expected: Player %d\n", winner + 1, 2);
    if(winner == 1){
        printf("getWinners(): PASS\n\n");
    }else{
        printf("getWinners(): FAIL\n\n");
    }


    g->numPlayers = 3;

    g->discard[1][0] = smithy;
    g->discard[1][1] = smithy;
    //g->discard[1][2] = smithy;

   
    getWinners(players, g);

    for(i = 0; i < MAX_PLAYERS; i++){
        if(players[i] == 1){
            winner = i;
        }
    }

    printf("Current Player: %d\n", whoseTurn(g) + 1);
    printf("score for Player 1: %d\n", scoreFor(0, g));
    printf("score for Player 2: %d\n", scoreFor(1, g));
    printf("score for Player 3: %d\n", scoreFor(2, g));
    printf("Winner: Player %d, Expected: Player %d\n", winner + 1, 2);
    if(winner == 1){
        printf("getWinners(): PASS\n\n");
    }else{
        printf("getWinners(): FAIL\n\n");
    }

    g->discard[1][1] = duchy;
    g->discard[1][4] = estate;
    g->hand[2][2] = province;
    g->hand[2][3] = province;

    
    getWinners(players, g);

    for(i = 0; i < MAX_PLAYERS; i++){
        if(players[i] == 1){
            winner = i;
        }
    }

    printf("Current Player: %d\n", whoseTurn(g) + 1);
    printf("score for Player 1: %d\n", scoreFor(0, g));
    printf("score for Player 2: %d\n", scoreFor(1, g));
    printf("score for Player 3: %d\n", scoreFor(2, g));
    printf("Winner: Player %d, Expected: Player %d\n", winner + 1, 3);
    if(winner == 2){
        printf("getWinners(): PASS\n\n");
    }else{
        printf("getWinners(): FAIL\n\n");
    }
    
    printf("Tests complete.\n");

    free(g);

    return 0;
}