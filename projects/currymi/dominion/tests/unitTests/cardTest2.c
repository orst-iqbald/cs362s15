#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

int main (int argc, char **argv) {

  int NUM_TESTS = 2000;
  int numDraws = 0;
  int j, i, n, p, r;
  int handPos, fails = 0;

  struct gameState G;
  struct gameState post;
  SelectStream(2);
  PutSeed(3);

    for (n = 0; n < NUM_TESTS; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char *) &G)[i] = floor(Random() * 256);
        }
        printf("Adventuer test %d of %d \n", n, NUM_TESTS);


        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        handPos = floor(Random() * G.handCount[p]);

        /* Make card at handPos a smithy card */
        G.hand[p][handPos] = smithy;

        /*
        printf("\tPlayer        = %d\n", p);
        printf("\tDeckcount     = %d\n", G.deckCount[p]);
        printf("\tDiscardCount  = %d\n", G.discardCount[p]);
        printf("\tHandCount     = %d\n", G.handCount[p]);
        printf("\tHandpos       = %d\n", handPos);
        */

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));

        adventuererEffect(p, &G);

        post.handCount[p] += 2; //added three more cards

        /*
        printf("\t\tHandCount Post  = %d\n", post.handCount[p]);
        printf("\t\tHandCount  G    = %d\n", G.handCount[p]);
        printf("\t\tDiscardCount Post  = %d\n", post.discardCount[p]);
        printf("\t\tDiscardCount  G    = %d\n", G.discardCount[p]);
        */
        
       // printf("\t\tSmithy test %d of %d .....", n, NUM_TESTS);
        if(post.handCount[p] != G.handCount[p]){
        //    printf("\n\t\tFAILED!!");
         //   printf("AT HAND COUNT!\n");
            fails++;
        }
        if(post.discardCount[p] != G.discardCount[p]){
          //  printf("\n\t\tFAILED!!\n");
           // printf("AT DISCARD COUNT!\n");
            fails++;
        }
        if(fullDeckCount(p, 0, &G) != fullDeckCount(p, 0, &post)){
            //printf("\n\t\tFAILED!!\n");
            //printf("\t\tAT FULLDECK COUNT!\n");
            fails++;
        }

        printf("%d num of total fails out of %d!\n", fails, NUM_TESTS); 
        

    } 


    return 0;

}



