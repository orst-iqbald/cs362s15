#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testGainCard() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int toFlag;
    int test1, test2, test3;
    int preDiscardCnt, preHandCnt, preDeckCnt;
    int p, r, handCount, s;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int supplyArr[MAX_HAND];
    supplyArr[0] = estate; 
    supplyArr[1] = adventurer;
    supplyArr[2] = copper;
    supplyArr[3] = smithy;
    supplyArr[4] = minion;

    int supplyPos[2];
    supplyPos[0] = gold;
    supplyPos[1] = minion;

    printf ("TESTING gainCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
    	printf("Test player %d\n", p);
        for (handCount = 1; handCount <= maxHandCount; handCount++) // 5 cards
        { 
        	
        	for (toFlag = 0; toFlag < 3; toFlag++) // go through 3 flags
        	{ 
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

                memcpy(G.hand[p], supplyArr, sizeof(int) * handCount); // 

                //get value of Counts before gainCard is run
                preDiscardCnt = G.discardCount[p];
                preHandCnt = G.handCount[p];
                preDeckCnt = G.deckCount[p];

                for(i=0; i < 2; i++) { //2 is supplyPos size
                	G.supplyCount[supplyPos[i]] = 5;
	                s = gainCard(supplyPos[i], &G, toFlag, p);
	           
	                //compare each deck, hand, or discard to the card that was gained & check if count has been incremented
	                if(toFlag == 0) {
	                	if((G.discard[p][ G.discardCount[p]-1 ] == supplyPos[i]) && (G.discardCount[p] == preDiscardCnt+1))
	                		test1 = 1;
	      				else
                			test1 = 0;
	                }
	                else if(toFlag == 1) {
	                	if((G.deck[p][ G.deckCount[p]-1 ] == supplyPos[i]) && (G.deckCount[p] == preDeckCnt+1))
	                		test2 = 1;
	      				else
                			test2 = 0;
	                }
	                else {
	                	if((G.hand[p][ G.handCount[p]-1 ] == supplyPos[i]) && (G.handCount[p] == preHandCnt+1))
	                		test3 = 1;
	      				else
                			test3 = 0;
	                }
	                preDiscardCnt++;
                	preHandCnt++;
                	preDeckCnt++;
                }
                
            }   
        }
        if(test1 == 0)
            printf("FAIL: gained to discard\n");
        else 
            printf("PASS: gained to discard\n");

        if(test2 == 0)
            printf("FAIL: gained to deck\n");
        else 
            printf("PASS: gained to deck\n");

        if(test3 == 0)
            printf("FAIL: gained to hand\n");
        else 
            printf("PASS: gained to hand\n");
    }
 
}

int main(int argc, char *argv[])
{
    testGainCard();

    return 0;
}