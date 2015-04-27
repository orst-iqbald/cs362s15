// Jason Hsu
// hsuja@onid.oregonstate.edu
// 4/26/15
// CS362-400
// test gainCard()

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

    g->supplyCount[council_room] = 5;
    g->supplyCount[mine] = 5;
    g->supplyCount[remodel] = 5;
    g->supplyCount[baron] = 5;
    g->supplyCount[outpost] = 5;
    g->supplyCount[minion] = 0;

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

    int pre_supply;
    int post_supply;
    int result;


    printf("\nTESTING gainCard():\n\n");

    pre_supply = supplyCount(council_room, g);
    gainCard(council_room, g, 1, 0);
    post_supply = supplyCount(council_room, g);
   
	if(g->deck[0][g->deckCount[0] - 1] == council_room){
		printf("gainCard(): PASS - council_room added to deck\n");
	}else{
		printf("gainCard(): FAIL - council_room not added to deck\n");
	}
	if(post_supply == pre_supply - 1){
        printf("gainCard(): PASS - supply decremented\n\n");
    }else{
        printf("gainCard(): FAIL - supply not decremented\n\n");
    }
    

    pre_supply = supplyCount(mine, g);
    gainCard(mine, g, 2, 0);
    post_supply = supplyCount(mine, g);
   
	if(g->hand[0][g->handCount[0] - 1] == mine){
		printf("gainCard(): PASS - mine added to hand\n");
	}else{
		printf("gainCard(): FAIL - mine not added to hand\n");
	}
	if(post_supply == pre_supply - 1){
        printf("gainCard(): PASS - supply decremented\n\n");
    }else{
        printf("gainCard(): FAIL - supply not decremented\n\n");
    }

    pre_supply = supplyCount(remodel, g);
    gainCard(remodel, g, 3, 0);
    post_supply = supplyCount(remodel, g);
   
	if(g->discard[0][g->discardCount[0] - 1] == remodel){
		printf("gainCard(): PASS - remodel added to discard\n");
	}else{
		printf("gainCard(): FAIL - remodel not added to discard\n");
	}
	if(post_supply == pre_supply - 1){
        printf("gainCard(): PASS - supply decremented\n\n");
    }else{
        printf("gainCard(): FAIL - supply not decremented\n\n");
    }



    result = gainCard(minion, g, 2, 0);

    if(result == -1){
    	printf("gainCard(): PASS - supply < 1 detected\n\n");
    }else{
    	printf("gainCard(): FAIL - supply < 1 not detected\n\n");
    }
  
   

   


    
    
    printf("Tests complete.\n");

    free(g);

    return 0;
}