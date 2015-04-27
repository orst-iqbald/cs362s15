#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

/* Discard Card Unit Tests */

int main (int argc, char** argv[]) {

  int NUM_TESTS = 2000;
  int numDraws;
  
  /* Check handCount
   * Check playedCards if trashFlag is not set 
   * Check lastCard in players hand 
   */
        /* Discard Multiple cards during test */
            /* Either randomly trash or discard them */
            /* if trashed - playedCardCount not updated */
            /* if not trashed not updated */
        
        /* if trashed */
            /* deckCount + handCount + playedCards = changed */
            /* if not trashed -- not changed */

  int j, i, n, p, q, r, s, t;
  int trash, numCards, handPos;
  int fails = 0;

  SelectStream(2);
  PutSeed(3);

  struct gameState G;
  struct gameState post;

    for (n = 0; n < NUM_TESTS; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&G)[i] = floor(Random() * 256);
        }
        //printf("Discard Test %d of %d \n", n, NUM_TESTS);

        /* Randomize GameState stuff */
        p = floor(Random() * 4);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.playedCardCount = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        /* Randomize test stuff */
        //numCards = floor(Random() * 8) + 1;
        numCards = 1;

        /* Randomize Hand */
        for(j = 0; j < G.handCount[p]; j++){
            G.hand[p][j] = floor(Random() * 26);
        }
        
        /*
        printf("\tPlayer        = %d\n", p);
        printf("\tDeckcount     = %d\n", G.deckCount[p]);
        printf("\tDiscardCount  = %d\n", G.discardCount[p]);
        printf("\tPlayedCardCount = %d\n", G.playedCardCount);
        printf("\tHandCount     = %d\n", G.handCount[p]);
        printf("\tNumDiscards   = %d\n", numCards);
        */

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));



        /* Discard/Trash */
        //printf("\t\tDiscarding/trashing %d cards\n", numCards);
        for(j = 0; j < numCards; j++){
            handPos = floor(Random() * G.handCount[p]);
            //trash = floor(Random() * 2);
            /*
            printf("\t\t\tCard = %d", j);
            printf(" Handpos = %d", handPos);
            printf(" TrashFlag = %d\t", trash);
            */
            
            discardCard(handPos, p, &G, 0);

            //printf("Played Card Count %d\n", post.playedCardCount);
            //printf("Played Card Count %d\n", G.playedCardCount);
            if(G.playedCardCount == post.playedCardCount){
                //printf("\nDiscard Count wrong!\n");   
                //printf("FAIL!\n");
                fails++;
            }
            //printf("Test PASSED!\n");
            
        }

    }       

    printf("\n %d test of %d failed!", fails, NUM_TESTS);

  return 0;
}


