#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"


/* update coins unittest */

int main (int argc, char** argv[]) {

  int NUM_TESTS = 500;
  int numDraws;
  
  

  int j, i, n, p, q, r, s, t;
  int goldCount, copperCount, silverCount = 0;
  int fails = 0;
  int bonus;


  struct gameState G;
  struct gameState post;

    /*  Put a random number of cards in the players hand */
    /* Manually add up the number of treasure cards  */
    /* Call update coins function */
    /* Compare results */


    for (n = 0; n < NUM_TESTS; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&G)[i] = floor(Random() * 256);
        }
        //printf("Update Coin Test %d of %d \n", n, NUM_TESTS);

        numDraws = floor(Random());
        p = floor(Random() * 4);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        for(j = 0; j < G.handCount[p]; j++){
            G.hand[p][j] = floor(Random() * 26);
        }
        G.coins = 0;
        bonus = floor(Random() * 10);

        copperCount = 0;
        silverCount = 0;
        goldCount = 0;

        /*
        printf("\tPlayer        = %d\n", p);
        printf("\tDeckcount     = %d\n", G.deckCount[p]);
        printf("\tDiscardCount  = %d\n", G.discardCount[p]);
        printf("\tHandCount     = %d\n", G.handCount[p]);
        printf("\tNumDraws      = %d\n", numDraws);
        */

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));
        
        for(q = 0; q < G.handCount[p]; q++){
            if(G.hand[p][q] == copper){
                copperCount++;
            }
            else if(G.hand[p][q] == silver){
                silverCount++;
            }
            else if(G.hand[p][q] == gold){
                goldCount++;
            }
        }

        /* Number of treasure Cards */
        /*
        printf("\tCopper    = %d\n", copperCount);
        printf("\tSilver    = %d\n", silverCount);
        printf("\tGold      = %d\n", goldCount);
        printf("\tBonus     = %d\n", bonus);
        */
    
        post.coins += ((3 * goldCount) + (2 * silverCount) + copperCount + bonus);

        updateCoins(p, &G, bonus);
        //printf("\t\tTotal Coins Expected = %d Recived = %d\n", post.coins, G.coins);

        //printf("\t\t Test %d ------ ", i);
        if(post.coins != G.coins){
         //   printf("FAILED!\n");
            fails++;
        }
        if(post.coins == G.coins){
          //  printf("PASSED!\n");
        }

        
    }       

    printf("%d test failed out of %d!", fails, NUM_TESTS);

  return 0;
}


