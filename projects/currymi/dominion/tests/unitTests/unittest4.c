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
  
  int j, i, n, p, q, r, s, t;
  int trash, numCards, handPos;
  int fails = 0;
  int score;

  SelectStream(2);
  PutSeed(3);

  struct gameState G;
  struct gameState post;

    for (n = 0; n < NUM_TESTS; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&G)[i] = floor(Random() * 256);
        }
        //printf("Get Score Test %d of %d \n", n, NUM_TESTS);
        score = 0;
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
        /* Randomize Discard */
        for(j = 0; j < G.discardCount[p]; j++){
            G.hand[p][j] = floor(Random() * 26);
        }

        /* Randomize Deck */
        for(j = 0; j < G.deckCount[p]; j++){
            G.hand[p][j] = floor(Random() * 26);
        }

        //printf("\tPlayer        = %d\n", p);
        //printf("\tDeckcount     = %d\n", G.deckCount[p]);
        //printf("\tDiscardCount  = %d\n", G.discardCount[p]);
        //printf("\tPlayedCardCount = %d\n", G.playedCardCount);
        //printf("\tHandCount     = %d\n", G.handCount[p]);
        //printf("\tNumDiscards   = %d\n", numCards);

        memcpy((void *) &post, (void *) &G, sizeof(struct gameState));
        
      for (i = 0; i < G.handCount[p]; i++)
        {
          if (G.hand[p][i] == curse) { score = score - 1; };
          if (G.hand[p][i] == estate) { score = score + 1; };
          if (G.hand[p][i] == duchy) { score = score + 3; };
          if (G.hand[p][i] == province) { score = score + 6; };
          if (G.hand[p][i] == great_hall) { score = score + 1; };
          if (G.hand[p][i] == gardens) { score = score + ( fullDeckCount(p, 0, &G) / 10 ); };
        }

      //score from discard
      for (i = 0; i < G.discardCount[p]; i++)
        {
          if (G.discard[p][i] == curse) { score = score - 1; };
          if (G.discard[p][i] == estate) { score = score + 1; };
          if (G.discard[p][i] == duchy) { score = score + 3; };
          if (G.discard[p][i] == province) { score = score + 6; };
          if (G.discard[p][i] == great_hall) { score = score + 1; };
          if (G.discard[p][i] == gardens) { score = score + ( fullDeckCount(p, 0, &G) / 10 ); };
        }

      //score from deck
      for (i = 0; i < G.discardCount[p]; i++)
        {
          if (G.deck[p][i] == curse) { score = score - 1; };
          if (G.deck[p][i] == estate) { score = score + 1; };
          if (G.deck[p][i] == duchy) { score = score + 3; };
          if (G.deck[p][i] == province) { score = score + 6; };
          if (G.deck[p][i] == great_hall) { score = score + 1; };
          if (G.deck[p][i] == gardens) { score = score + ( fullDeckCount(p, 0, &G) / 10 ); };
        }

        if(score != scoreFor(p, &G)){
          //  printf("Test FAILED!");
            fails++;
        }else{
           // printf("Test passed!\n");
        }

    }       

    printf("\n%d test failed out of %d!", fails, NUM_TESTS);

  return 0;
}


