#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

int main (int argc, char **argv) {

  int NUM_TESTS = 10000;
  int numDraws = 0;
  int fails = 0;
  int j, i, n, p, r;

  struct gameState G;
  struct gameState post;
  SelectStream(2);
  PutSeed(3);


    for (n = 0; n < NUM_TESTS; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char *) &G)[i] = floor(Random() * 256);
        }
        //printf("Drawcard test %d of %d \n", n, NUM_TESTS);


        numDraws = floor(Random() * 10);
        numDraws++;
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        /*
        printf("\tPlayer        = %d\n", p);
        printf("\tDeckcount     = %d\n", G.deckCount[p]);
        printf("\tDiscardCount  = %d\n", G.discardCount[p]);
        printf("\tHandCount     = %d\n", G.handCount[p]);
        printf("\tNumDraws      = %d\n", numDraws);
        */

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));

        post.handCount[p] += numDraws;

        for(j = 0; j < numDraws; j++){
            //printf("\t Drawing card %d of %d....\n", j, numDraws);
            r = drawCard (p, &G);
            if(r == -1){
             //   printf("\tPossible failure....\n");
            }
        }   
        
        /*
        printf("Test %d of %d with %d draws......", n, NUM_TESTS, numDraws);
        printf("\t\t Expected %d - Recived %d......\n", post.handCount[p], G.handCount[p]);
        */

        if(G.handCount[p] != post.handCount[p]){
            fails++;
           // printf("FAILED!\n");
            //printf("\t\t Expected %d - Recived %d......\n", post.handCount[p], G.handCount[p]);
        }else{
            //printf("PASSED\n");
        }
    } 
    
    printf("Num fails %d of %d tests\n", fails, NUM_TESTS);


    return 0;

}



