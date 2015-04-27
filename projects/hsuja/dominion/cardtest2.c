// Jason Hsu
// hsuja@onid.oregonstate.edu
// 4/26/15
// CS362-400

// test play_smithy()

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
	
	
    int handPos;
/*   
    int card_a;
    int card_b;
    int card_c;
    int card_a_handCount;
    int card_b_handCount;
    int card_c_handCount;
    int card_a_deckCount;
    int card_b_deckCount;
    int card_c_deckCount;
    int card_a_handDiff;
    int card_b_handDiff;
    int card_c_handDiff;
    int card_a_deckDiff;
    int card_b_deckDiff;
    int card_c_deckDiff;
*/

    int pre_handCount;
	
	
	 

    // Player 1
    g->deckCount[0] = 5;
    g->handCount[0] = 5;
    g->discardCount[0] = 5;

    g->deck[0][0] = silver;
    g->deck[0][1] = copper;
    g->deck[0][2] = estate;
    g->deck[0][3] = silver;
    g->deck[0][4] = village;

    g->hand[0][0] = copper;
    g->hand[0][1] = gold;
    g->hand[0][2] = copper;
    g->hand[0][3] = smithy;
    g->hand[0][4] = curse;

    g->discard[0][0] = smithy;
    g->discard[0][1] = province;
    g->discard[0][2] = estate;
    g->discard[0][3] = estate;
    g->discard[0][4] = copper;

    // Player 2
    g->deckCount[1] = 0;
    g->handCount[1] = 3;
    g->discardCount[1] = 5;
/*
    g->deck[1][0] = smithy;
    g->deck[1][1] = village;
    g->deck[1][2] = village;
    g->deck[1][3] = village;
    g->deck[1][4] = duchy;
*/
    g->hand[1][0] = adventurer;
    g->hand[1][1] = gold;
    g->hand[1][2] = smithy;

    g->discard[1][0] = copper;
    g->discard[1][1] = copper;
    g->discard[1][2] = estate;
    g->discard[1][3] = estate;
    g->discard[1][4] = estate;

    // Player 3
    g->deckCount[2] = 5;
    g->handCount[2] = 3;
    g->discardCount[2] = 5;

    g->deck[2][0] = smithy;
    g->deck[2][1] = village;
    g->deck[2][2] = silver;
    g->deck[2][3] = village;
    g->deck[2][4] = smithy;

    g->hand[2][0] = adventurer;
    g->hand[2][1] = gold;
    g->hand[2][2] = smithy;

    g->discard[2][0] = estate;
    g->discard[2][1] = copper;
    g->discard[2][2] = estate;
    g->discard[2][3] = estate;
    g->discard[2][4] = smithy;
   


    printf("\nTESTING play_smithy():\n\n");


    handPos = 3;
    pre_handCount = g->handCount[currentPlayer];

    play_smithy(&currentPlayer, g, &handPos);

    if(g->handCount[currentPlayer] == pre_handCount + 2){
        printf("play_smithy(): PASS - cards added to hand and smithy discarded\n");
    }else if(g->handCount[currentPlayer] == pre_handCount + 3){
        printf("play_smithy(): FAIL - cards added to hand but smithy not discarded\n");
    }else{
        printf("play_smith(): FAIL - unknown error");
    }

    handPos = 2;
    currentPlayer = 1;
    pre_handCount = g->handCount[currentPlayer];

    play_smithy(&currentPlayer, g, &handPos);

    if(g->handCount[currentPlayer] == pre_handCount + 2){
        printf("play_smithy(): PASS - cards added to hand and smithy discarded\n");
    }else if(g->handCount[currentPlayer] == pre_handCount + 3){
        printf("play_smithy(): FAIL - cards added to hand but smithy not discarded\n");
    }else{
        printf("play_smith(): FAIL - unknown error");
    }

    handPos = 2;
    currentPlayer = 2;
    pre_handCount = g->handCount[currentPlayer];

    play_smithy(&currentPlayer, g, &handPos);

    if(g->handCount[currentPlayer] == pre_handCount + 2){
        printf("play_smithy(): PASS - cards added to hand and smithy discarded\n");
    }else if(g->handCount[currentPlayer] == pre_handCount + 3){
        printf("play_smithy(): FAIL - cards added to hand but smithy not discarded\n");
    }else{
        printf("play_smith(): FAIL - unknown error");
    }



/*
    handPos = 3;
    pre_handCount = g->handCount[currentPlayer];

    card_a = g->deck[currentPlayer][g->deckCount[currentPlayer] - 1]; //village
    card_b = g->deck[currentPlayer][g->deckCount[currentPlayer] - 2]; //silver
    card_c = g->deck[currentPlayer][g->deckCount[currentPlayer] - 3]; //estate

    card_a_handCount = card_handCount(currentPlayer, card_a, g);
    card_b_handCount = card_handCount(currentPlayer, card_b, g);
    card_c_handCount = card_handCount(currentPlayer, card_c, g);

    card_a_deckCount = card_deckCount(currentPlayer, card_a, g);
    card_b_deckCount = card_deckCount(currentPlayer, card_b, g);
    card_c_deckCount = card_deckCount(currentPlayer, card_c, g);


    play_smithy(&currentPlayer, g, &handPos);

    printf("card_a = %d\n", card_a);
    printf("card_b = %d\n", card_b);
    printf("card_c = %d\n", card_c);

    card_a_handDiff = card_handCount(currentPlayer, card_a, g) - card_a_handCount;
    card_b_handDiff = card_handCount(currentPlayer, card_b, g) - card_b_handCount;
    card_c_handDiff = card_handCount(currentPlayer, card_c, g) - card_c_handCount;

    card_a_deckDiff = card_a_deckCount - card_deckCount(currentPlayer, card_a, g);
    card_b_deckDiff = card_b_deckCount - card_deckCount(currentPlayer, card_b, g);
    card_c_deckDiff = card_c_deckCount - card_deckCount(currentPlayer, card_c, g);
   
   
    if(card_a == smithy) card_a_deckDiff--;
    if(card_b == smithy) card_b_deckDiff--;
    if(card_c == smithy) card_c_deckDiff--;
    
    if(card_a_handDiff == card_a_deckDiff && card_b_handDiff == card_b_deckDiff && card_c_handDiff == card_c_deckDiff && card_a_handDiff != 0 && card_b_handDiff != 0 && card_c_handDiff != 0 && g->handCount[currentPlayer] == pre_handCount + 2){
        printf("play_smithy(): PASS - cards added to hand and smithy discarded\n\n");
    }else{
        printf("play_smithy(): FAIL - cards not added to hand and/or smithy not discarded\n\n");
    }


    handPos = 2;
    currentPlayer = 1;
    pre_handCount = g->handCount[currentPlayer];

    card_a = g->deck[currentPlayer][g->deckCount[currentPlayer] - 1]; 
    card_b = g->deck[currentPlayer][g->deckCount[currentPlayer] - 2]; 
    card_c = g->deck[currentPlayer][g->deckCount[currentPlayer] - 3]; 

    card_a_handCount = card_handCount(currentPlayer, card_a, g);
    card_b_handCount = card_handCount(currentPlayer, card_b, g);
    card_c_handCount = card_handCount(currentPlayer, card_c, g);

    if(g->deckCount[currentPlayer] == 0){
        card_a_deckCount = card_discardCount(currentPlayer, card_a, g);
        card_b_deckCount = card_discardCount(currentPlayer, card_b, g);
        card_c_deckCount = card_discardCount(currentPlayer, card_c, g);
    }else{
        card_a_deckCount = card_deckCount(currentPlayer, card_a, g);
        card_b_deckCount = card_deckCount(currentPlayer, card_b, g);
        card_c_deckCount = card_deckCount(currentPlayer, card_c, g);
    }

    


    play_smithy(&currentPlayer, g, &handPos);

    printf("card_a = %d\n", card_a);
    printf("card_b = %d\n", card_b);
    printf("card_c = %d\n", card_c);

    card_a_handDiff = card_handCount(currentPlayer, card_a, g) - card_a_handCount;
    card_b_handDiff = card_handCount(currentPlayer, card_b, g) - card_b_handCount;
    card_c_handDiff = card_handCount(currentPlayer, card_c, g) - card_c_handCount;

    card_a_deckDiff = card_a_deckCount - card_deckCount(currentPlayer, card_a, g);
    card_b_deckDiff = card_b_deckCount - card_deckCount(currentPlayer, card_b, g);
    card_c_deckDiff = card_c_deckCount - card_deckCount(currentPlayer, card_c, g);
   
   
    if(card_a == smithy) card_a_deckDiff--;
    if(card_b == smithy) card_b_deckDiff--;
    if(card_c == smithy) card_c_deckDiff--;
    
    if(card_a_handDiff == card_a_deckDiff && card_b_handDiff == card_b_deckDiff && card_c_handDiff == card_c_deckDiff && card_a_handDiff != 0 && card_b_handDiff != 0 && card_c_handDiff != 0 && g->handCount[currentPlayer] == pre_handCount + 2){
        printf("play_smithy(): PASS - cards added to hand and smithy discarded\n\n");
    }else{
        printf("play_smithy(): FAIL - cards not added to hand and/or smithy not discarded\n\n");
    }








    handPos = 2;
    currentPlayer = 2;
    pre_handCount = g->handCount[currentPlayer];

    card_a = g->deck[currentPlayer][g->deckCount[currentPlayer] - 1]; 
    card_b = g->deck[currentPlayer][g->deckCount[currentPlayer] - 2]; 
    card_c = g->deck[currentPlayer][g->deckCount[currentPlayer] - 3]; 

    card_a_handCount = card_handCount(currentPlayer, card_a, g);
    card_b_handCount = card_handCount(currentPlayer, card_b, g);
    card_c_handCount = card_handCount(currentPlayer, card_c, g);

    card_a_deckCount = card_deckCount(currentPlayer, card_a, g);
    card_b_deckCount = card_deckCount(currentPlayer, card_b, g);
    card_c_deckCount = card_deckCount(currentPlayer, card_c, g);


    play_smithy(&currentPlayer, g, &handPos);

    printf("card_a = %d\n", card_a);
    printf("card_b = %d\n", card_b);
    printf("card_c = %d\n", card_c);

    card_a_handDiff = card_handCount(currentPlayer, card_a, g) - card_a_handCount;
    card_b_handDiff = card_handCount(currentPlayer, card_b, g) - card_b_handCount;
    card_c_handDiff = card_handCount(currentPlayer, card_c, g) - card_c_handCount;

    card_a_deckDiff = card_a_deckCount - card_deckCount(currentPlayer, card_a, g);
    card_b_deckDiff = card_b_deckCount - card_deckCount(currentPlayer, card_b, g);
    card_c_deckDiff = card_c_deckCount - card_deckCount(currentPlayer, card_c, g);
   
   
    if(card_a == smithy) card_a_deckDiff--;
    if(card_b == smithy) card_b_deckDiff--;
    if(card_c == smithy) card_c_deckDiff--;
    
    if(card_a_handDiff == card_a_deckDiff && card_b_handDiff == card_b_deckDiff && card_c_handDiff == card_c_deckDiff && card_a_handDiff != 0 && card_b_handDiff != 0 && card_c_handDiff != 0 && g->handCount[currentPlayer] == pre_handCount + 2){
        printf("play_smithy(): PASS - cards added to hand and smithy discarded\n\n");
    }else{
        printf("play_smithy(): FAIL - cards not added to hand and/or smithy not discarded\n\n");
    }
*/


    printf("Tests complete.\n");

    free(g);

    return 0;
}







