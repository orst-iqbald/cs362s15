// Jason Hsu
// hsuja@onid.oregonstate.edu
// 4/26/15
// CS362-400
// test play_adventurer()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main(){

    struct gameState* g = malloc(sizeof(struct gameState));

   
	int currentPlayer = 0;
	int temphand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
	int i;
	 

    // Player 1
    g->deckCount[0] = 5;
    g->handCount[0] = 5;
    g->discardCount[0] = 5;

    g->deck[0][0] = silver;
    g->deck[0][1] = copper;
    g->deck[0][2] = smithy;
    g->deck[0][3] = silver;
    g->deck[0][4] = village;

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

    g->discard[1][0] = copper;
    g->discard[1][1] = copper;
    g->discard[1][2] = estate;
    g->discard[1][3] = estate;
    g->discard[1][4] = smithy;

    // Player 3
    g->deckCount[2] = 5;
    g->handCount[2] = 3;
    g->discardCount[2] = 5;

    g->deck[2][0] = smithy;
    g->deck[2][1] = village;
    g->deck[2][2] = silver;
    g->deck[2][3] = village;
    g->deck[2][4] = duchy;

    g->hand[2][0] = adventurer;
    g->hand[2][1] = gold;
    g->hand[2][2] = duchy;

    g->discard[2][0] = estate;
    g->discard[2][1] = copper;
    g->discard[2][2] = estate;
    g->discard[2][3] = estate;
    g->discard[2][4] = smithy;
   


    printf("\nTESTING play_adventurer():\n\n");

    play_adventurer(&currentPlayer, g, &cardDrawn, drawntreasure, &z, temphand);

    if(g->deck[currentPlayer][0] == silver && g->deckCount[currentPlayer] == 1){
    	printf("play_adventurer(): PASS - cards removed from Player 1's deck\n");
    }else{
    	printf("play_adventurer(): FAIL - cards not properly removed from Player 1's deck\n");
    }
    if(g->hand[currentPlayer][g->handCount[currentPlayer] - 1] == copper && g->hand[currentPlayer][g->handCount[currentPlayer] - 2] == silver){
    	printf("play_adventurer(): PASS - treasure cards added to Player 1's hand\n");
    }else{
    	printf("play_adventurer(): FAIL - treasure cards not added to Player 1's hand properly\n");
    }
    if(g->discard[currentPlayer][g->discardCount[currentPlayer] - 1] == village && g->discard[currentPlayer][g->discardCount[currentPlayer] - 2] == smithy){
    	printf("play_adventurer(): PASS - cards added to Player 1's discard pile\n");
    }else{
    	printf("play_adventurer(): FAIL - cards not added to Player 1's discard pile properly\n");
    }

    printf("\n");

    currentPlayer = 1;
    drawntreasure = 0;
    z = 0;
    int test_flag = 0;

    play_adventurer(&currentPlayer, g, &cardDrawn, drawntreasure, &z, temphand);


    for(i = 0; i < g->deckCount[currentPlayer]; i++){
    	if(g->deck[currentPlayer][i] == copper){

    		printf("play_adventurer(): FAIL - cards not properly removed from Player 2's deck\n");
    		test_flag = 1;

    	}
    }
    if(test_flag != 1){
    	printf("play_adventurer(): PASS - cards removed from Player 2's deck\n");
    }
    

    if(g->hand[currentPlayer][g->handCount[currentPlayer] - 1] == copper && g->hand[currentPlayer][g->handCount[currentPlayer] - 2] == copper){
    	printf("play_adventurer(): PASS - treasure cards added to Player 2's hand\n");
    }else{
    	printf("play_adventurer(): FAIL - treasure cards not added to Player 2's hand properly\n");
    }
    
    printf("\n");

    currentPlayer = 2;
    drawntreasure = 0;
    z = 0;
    test_flag = 0;

    play_adventurer(&currentPlayer, g, &cardDrawn, drawntreasure, &z, temphand);


    for(i = 0; i < g->deckCount[currentPlayer]; i++){
    	if(g->deck[currentPlayer][i] == copper || g->deck[currentPlayer][i] == silver){

    		printf("play_adventurer(): FAIL - cards not properly removed from Player 3's deck\n");
    		test_flag = 1;

    	}
    }
    if(test_flag != 1){
    	printf("play_adventurer(): PASS - cards removed from Player 3's deck\n");
    }
    

    if(g->hand[currentPlayer][g->handCount[currentPlayer] - 1] == copper && g->hand[currentPlayer][g->handCount[currentPlayer] - 2] == silver){
    	printf("play_adventurer(): PASS - treasure cards added to Player 3's hand\n");
    }else{
    	printf("play_adventurer(): FAIL - treasure cards not added to Player 3's hand properly\n");
    }
 
    printf("Tests complete.\n");

    free(g);

    return 0;
}







