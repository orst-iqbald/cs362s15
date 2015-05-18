/*
	Program: randomtestadventure.c
	Author: James Coan
	
	Testing the Adventurer Card
    Reveal cards from your deck until you reveal 2 Treasure cards.
    Put those Treasure cards in your hand and discard the other revealed cards.	
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
	
	printf ("TESTING newAdventurer() card:\n");
	for(x=0; x<iterations; x++){
	    int seed = (rand() % 123456789)+1;
		printf("\nIteration #%d\tSeed #%d\n\n",x,seed);
	    initializeGame(numPlayer, k, seed, &g);
	    int treasure1 = 0;
	    int treasure2 = 0;
	    int inc = 0;
	    
        //	possible empty deck
    	int emptyDeck = (rand() % 10)+1;
    	if(emptyDeck>8){
    		g.deckCount[0]=0;
    		printf("Deck was empty, shuffling.\n");
    	}
        
        //	possible treasure cards added to deck
        for(y=0; y<3; y++){
	        int deckTop = g.deckCount[0];
	        switch ((rand() % 4)+1){
	        	case 1:
			        g.deck[0][deckTop] = copper;
			        g.deckCount[0]++;
			        break;
	        	case 2:
	        		g.deck[0][deckTop] = silver;
			        g.deckCount[0]++;
			        break;
	        	case 3:
		        	g.deck[0][deckTop] = gold;
			        g.deckCount[0]++;
			        break;
	        }
        }
        
        //	count treasure cards in deck
        for(y=0; y< g.deckCount[0]; y++)
        	if(g.deck[0][y] == copper || g.deck[0][y] == silver || g.deck[0][y] == gold)
                inc++;
            
        //	if there are more treasure cards in deck than 2, inc = 2
        if(inc>2)
        	inc=2;
        
        //	count treasure cards in hand
        for(y=0; y< g.handCount[0]; y++){
        	if(g.hand[0][y] == copper || g.hand[0][y] == silver || g.hand[0][y] == gold){
                treasure1++;
            }
        }
        
        //	add adventurer card to player hand
        int handTop = g.handCount[0];
        g.hand[0][handTop] = adventurer;
        g.handCount[0]++;
        
        printDeck(0, &g);
        printHand(0, &g);
        printf("Playing Adventure Card...\n\n");
        playCard(handTop, 0, 0, 0, &g);
        discardCard(handTop, 0, &g, 0);
        printHand(0, &g);
        
        //	after adventurer played, how many treasure cards in hand
        for(y=0; y< g.handCount[0]; y++)
        	if(g.hand[0][y] == copper || g.hand[0][y] == silver || g.hand[0][y] == gold)
                treasure2++;
        
        //	compare treasure cards in hand before and after
        if(treasure2 != treasure1+inc)
            printf("Failed - Number of treasure cards incorrect. Expected = %d, Returned = %d\n", treasure1+inc, treasure2);
	}
    printf ("FINISHED newAdventurer() card:\n\n");
	
	return 0; 
}