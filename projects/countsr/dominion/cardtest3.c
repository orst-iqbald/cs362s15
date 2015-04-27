#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testStewardFunc() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int c1, c2, c3;
    int coinCount;
    int p, r, handCount;
    int test1, test2, test3, test4;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int dummyHand[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        dummyHand[0] = curse; 
        dummyHand[1] = gold;
        dummyHand[2] = smithy;
        dummyHand[3] = adventurer;
        dummyHand[4] = village;
    }

    int handPos = 3; // location of card in hand to trash
    handCount = 5;

    int preCoins;
    int preHandCount;

    printf ("TESTING stewardFunc():\n");
    for (p = 0; p < numPlayer; p++)
    {
    	printf("Test player %d.\n", p);
        for (handCount = 1; handCount <= maxHandCount; handCount++) // 5 cards
        { 
                coinCount = 0;

                

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                
                //test +2 coins option
                G.handCount[p] = handCount;                 //  set the number of cards on hand
                preCoins = G.coins;
                stewardFunc(&G, p, handPos, 2, c2, c3); // choice is add 2 coins
                if(preCoins + 2 == G.coins)
                	test1 = 1;
                else
                	test1 = 0;

                //test +2 cards option
                G.handCount[p] = handCount;                 //  set the number of cards on hand
                preHandCount = G.handCount[p];
                stewardFunc(&G, p, handPos, 1, c2, c3); // choice is add 2 cards
                if(preHandCount + 1 == G.handCount[p]) // +1 because add 2 discard 1
                	test2 = 1;
                else
                	test2 = 0;

                //test trash 2 cards option
                memcpy(G.hand[p], dummyHand, sizeof(int) * handCount); 
                G.handCount[p] = handCount;                 //  set the number of cards on hand
                preHandCount = G.handCount[p];
                stewardFunc(&G, p, handPos, 3, 1, 2); // 3 choice is trash 2 cards - trash pos 1 and 2
                if(preHandCount - 3 == G.handCount[p]) // -3 because  discard 2 and discard played card
                	test3 = 1;
                else
                	test3 = 0;
                if(G.discard[p][G.discardCount[p]-2] == gold || G.discard[p][G.discardCount[p]-1] == smithy)
                	test4 = 0;
                else
                	test4 = 1;


                
        }  

        if(test1 == 0)
            printf("FAIL: +2 coins\n");
        else 
            printf("PASS: +2 coins\n");

        if(test2 == 0)
            printf("FAIL: +2 cards\n");
        else 
            printf("PASS: +2 cards\n");

        if(test3 == 0)
            printf("FAIL: 2 cards trashed from hand\n");
        else 
            printf("PASS: 2 cards trashed from hand\n"); 
        if(test4 == 0)
            printf("FAIL: 2 cards trashed from game\n");
        else 
            printf("PASS: 2 cards trashed from game\n");     
    }
}

int main(int argc, char *argv[])
{
    testStewardFunc();

    return 0;
}