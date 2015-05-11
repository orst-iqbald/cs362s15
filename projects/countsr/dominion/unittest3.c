#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



void testDiscardCard() {
    int i;
    int handPos;
    int seed = 1000;
    int numPlayer = 2;
    int cardRemoved=1;
    int p, r;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    //create dummy hand
    int cards[MAX_HAND];

    cards[0] = copper; 
    cards[1] = smithy; 
    cards[2] = adventurer; 
    cards[3] = estate; 
    cards[4] = minion; 
       
    printf ("TESTING discardCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        	printf("Test player %d.\n", p);

           	for(handPos = 0; handPos < maxHandCount; handPos++) {
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
               
                memcpy(G.hand[p], cards, sizeof(int) * maxHandCount); // set all the cards 
                discardCard(handPos, p, &G, 0);// remove card from each position
                //search for card in hand
                for(i=0; i < maxHandCount; i++) {
	                if(cards[handPos] == G.hand[p][i])
	                	cardRemoved = 0;
                }	
                printf("played %d\n", G.playedCards[handPos]);
                
                if(cardRemoved == 0)
                	printf("FAIL: card not removed\n");
                else 
                	printf("PASS: card successfully removed\n");
                	
            }       
    }
}

int main(int argc, char *argv[])
{
    testDiscardCard();

    return 0;
}