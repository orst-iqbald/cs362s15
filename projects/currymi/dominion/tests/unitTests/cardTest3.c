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
//        printf("Council Room test %d of %d \n", r, NUM_TESTS);

        G.numPlayers = MAX_PLAYERS;
        G.numBuys = floor(Random() * 15);
        G.playedCardCount = floor(Random() * 20);

        /* Randomly assign Counts to each player */
        for(n = 0; n <= G.numPlayers; n++){
            G.handCount[n] = floor(Random() * MAX_HAND);
            G.deckCount[n] = floor(Random() * MAX_DECK);
            G.discardCount[n] = floor(Random() * MAX_DECK);

            /*
            printf("\tPlayer %d HandCount = %d\n", n, G.handCount[n]);
            printf("\t\t DiscardCount= %d\n", G.discardCount[n]);
            printf("\t\t DeckCount= %d\n\n", G.deckCount[n]);
            */

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

        

        handPos = floor(Random() * G.handCount[p]);
        p = floor(Random() * 4);

        /*
        printf("\tPlayer        = %d\n", p);
        printf("\tDeckcount     = %d\n", G.deckCount[p]);
        printf("\tDiscardCount  = %d\n", G.discardCount[p]);
        printf("\tHandpos       = %d\n", handPos);
        printf("\tNumBuys       = %d\n", G.numBuys);
        */

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));



        for(n = 0; n <= G.numPlayers; n++){
            if(n == p){
                post.handCount[p] += 4; //added four cards
            }else{
                post.handCount[n]++;
            }
        }
        post.numBuys += 1;

        councilRoomEffect(1, handPos, &G);
        
//        printf("Expected Buys %d, reecived %d\n", post.numBuys, G.numBuys);

        for(n = 0; n <= G.numPlayers; n++){
            if(post.handCount[n] != G.handCount[n]){
                //printf("\t\t\tFAILED!\n");
                fails++;
            }
            if(post.numBuys != G.numBuys){
                //printf("\t\t\tFAILED NUM BUYS!\n");
                fails++;
            }
        }

        

    } 


        printf("%d num of fails out of %d!\n", fails, NUM_TESTS); 


    return 0;
}



