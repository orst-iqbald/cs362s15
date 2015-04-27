#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testScoreFor() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int score = 0;
    int test1Passed, test2Passed, test3Passed, test4Passed;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int curses[MAX_HAND];
    int estates[MAX_HAND];
    int gardens1[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        curses[i] = curse; //-1
        estates[i] = estate; //1
        gardens1[i] = gardens; // 1 for every 10 cards
    }

    printf ("TESTING scoreFor():\n");
    for (p = 0; p < numPlayer; p++)
    {
      printf("Test player %d.\n", p);

        for (handCount = 1; handCount <= maxHandCount; handCount++) // 5 cards
        { 
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 //  set the number of cards on hand
                G.deckCount[p] = handCount; 
                G.discardCount[p] = handCount; 

                //check the score for 3 different hands
                memcpy(G.hand[p], curses, sizeof(int) * handCount); // set all the cards to curses
                memcpy(G.deck[p], curses, sizeof(int) * handCount);
                memcpy(G.discard[p], curses, sizeof(int) * handCount);
                score = scoreFor(p, &G);
                if(score == -3 * handCount) // check if the score is correct
                	test1Passed = 1;
                else
                	test1Passed = 0;

                memcpy(G.hand[p], estates, sizeof(int) * handCount); // set all the cards to estates
                memcpy(G.deck[p], curses, sizeof(int) * handCount);
                memcpy(G.discard[p], gardens1, sizeof(int) * handCount);
                score = scoreFor(p, &G);
                if(score == (1 * handCount)+(-1 * handCount)+(handCount/10)) // check if the score is correct
                	test2Passed = 1;
                else
                	test2Passed = 0;

                memcpy(G.hand[p], gardens1, sizeof(int) * handCount); // set all the cards to estates
                memcpy(G.deck[p], gardens1, sizeof(int) * handCount);
                memcpy(G.discard[p], gardens1, sizeof(int) * handCount);
                score = scoreFor(p, &G);
                if(score == handCount/30) // check if the score is correct
                	test3Passed = 1;
                else
                	test3Passed = 0;
        }

        if(test1Passed)
            printf("PASS Score for first test is correct\n");
        else
            printf("FAIL Score for first test is incorrect\n");
        if(test2Passed)
            printf("PASS Score for second test is correct\n");
        else
            printf("FAIL Score for second test is incorrect\n");
        if(test3Passed)
            printf("PASS Score for third test is correct\n");
        else
            printf("FAIL Score for third test is incorrect\n");


        for (handCount = 10; handCount <= 30; handCount+=5) // start with 10 cards increment by 5 up to 10
        { 
        	memcpy(G.hand[p], gardens1, sizeof(int) * handCount); // set all the cards to gardens
            memcpy(G.deck[p], gardens1, sizeof(int) * handCount);
            memcpy(G.discard[p], gardens1, sizeof(int) * handCount);
            score = scoreFor(p, &G);
            if(score == handCount/30) // check if the score is correct
                test4Passed = 1;
            else
                test4Passed = 0;
        }
        if(test4Passed)
            printf("PASS Score for fourth test is correct\n");
        else
            printf("FAIL Score for fourth test is incorrect\n");
    }
}

int main(int argc, char *argv[])
{
    testScoreFor();

    return 0;
}
