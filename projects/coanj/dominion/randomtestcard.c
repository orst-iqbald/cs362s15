/*
	Program: randomtestadventure.c
	Author: James Coan
	
	Testing the Baron Card
	+1 Buy. You may discard an Estate card. 
	If you do, +$4. Otherwise, gain an Estate card.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

int main() {
	int iterations = 50;
	int x,y;
	srand(time(NULL));
    int numPlayer = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState g;
	
	printf ("TESTING newBaron() card:\n");
	for(x=0; x<iterations; x++){
		int choice;
		int estateCount1 = 0;
		int estateCount2 = 0;
	    int seed = (rand() % 123456789)+1;
		printf("\nIteration #%d\tSeed #%d\n\n",x,seed);
	    initializeGame(numPlayer, k, seed, &g);
        int handTop = g.handCount[0];
	    
	    int buy1 = g.numBuys;
	    int coins1 = g.coins;
	    	            
        //	count estate cards in hand
        for(y=0; y< g.handCount[0]; y++)
        	if(g.hand[0][y] == estate)
                estateCount1++;
	   	
        // Add baron card to hand
        g.hand[0][handTop] = baron;
        g.handCount[0]++;
        
        //	Display game state and player hand
        printState(&g);
        printHand(0, &g);
        
        printf("Playing baron Card...\n");
        
        //	If there is an estate card, discard it
        if(estateCount1 != 0){
        	choice = 1;
	        printf("Discard an estate card.\n\n");
        } else {
        	choice = 0;
	        printf("No estate card to discard.\n");
	        
		    //	50% chance supply count for estate is 0
		    if( ((rand()%2)+1) == 2 )
		    	g.supplyCount[estate] = 0;
		    printf("Estate Supply = %d\n\n",g.supplyCount[estate]);
        }
        
        // 	play baron card
        playCard(handTop, choice, 0, 0, &g);
        discardCard(handTop, 0, &g, 0);
        
        
        //	Display game state and player hand
        printState(&g);
        printHand(0, &g);
        
        //	count estate cards in hand
        for(y=0; y< g.handCount[0]; y++)
        	if(g.hand[0][y] == estate)
                estateCount2++;
        
        if(choice == 1 && (estateCount2 != estateCount1-1))
        	printf("Failed - Estate card not discarded properly. Expected estates= %d, Returned estates= %d\n", estateCount1-1, estateCount2);
        
        if(choice == 0 && g.supplyCount[estate] > 0 &&  (estateCount2 != estateCount1+1))
        	printf("Failed - Estate card not gained properly. Expected estates= %d, Returned estates= %d\n", estateCount1+1, estateCount2);
        	
	    int coins2 = g.coins;
	    if(choice == 1 && (coins2 != coins1+4))
        	printf("Failed - Coins not incremented properly after estate discard. Expected = %d, Returned = %d\n", coins1+4, coins2);
	    
        int buy2 = g.numBuys;
        if(buy2 != buy1+1)
        	printf("Failed - Buy count not incremented properly. Expected = %d, Returned = %d\n", buy1+1, buy2);
        
	}
    printf ("\nFINISHED newBaron() card:\n\n");
	
	return 0; 
}