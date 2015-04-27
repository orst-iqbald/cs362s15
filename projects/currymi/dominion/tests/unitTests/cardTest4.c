#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"


int main (int argc, char **argv) {

  int NUM_TESTS = 100;
  int numDraws = 0;
  int j, i, n, p, r;
  int handPos, fails = 0;

  struct gameState G;
  struct gameState post;
  SelectStream(2);
  PutSeed(3);

    for (r = 0; r < NUM_TESTS; r++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char *) &G)[i] = floor(Random() * 256);
        }
  //      printf("Village Room test %d of %d \n", r, NUM_TESTS);

        G.numPlayers = MAX_PLAYERS;
        G.numBuys = floor(Random() * 15);
        G.numActions = floor(random() * 15);
        G.playedCardCount = floor(Random() * 20);

        /* Randomly assign Counts to each player */
        for(n = 0; n <= G.numPlayers; n++){
            G.handCount[n] = floor(Random() * MAX_HAND);
            G.deckCount[n] = floor(Random() * MAX_DECK);
            G.discardCount[n] = floor(Random() * MAX_DECK);

            /* Randomly Assign Cards to each player */
            for (i = 0; i < G.handCount[n]; i++){
                G.hand[n][i] = floor(Random() * 26);
            }
            for (i = 0; i < G.discardCount[p]; i++){
                G.discard[n][i] = floor(Random() * 26);
            }
            for (i = 0; i < G.discardCount[p]; i++){
                G.deck[n][i] = floor(Random() * 26);
            }
            
        }
        
        G.whoseTurn = floor(Random() * 4);
        p = G.whoseTurn;

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));

        post.handCount[p];
        post.numActions = post.numActions + 2;

        cardEffect(village, 0, 0, 0, &G, 0, 0);
        
    
        if(post.handCount[p] != G.handCount[p]){
        //    printf("FAILED!\n");
            fails++;
        }
        if(post.numActions != G.numActions){
         //   printf("FAILED!\n");
            fails++;
        }

        

    } 

    printf("%d num of fails out of %d!\n", fails, NUM_TESTS); 


    return 0;
}



