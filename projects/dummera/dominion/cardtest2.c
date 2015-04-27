#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

int testAdventurer(int currentPlayer, struct gameState *post) {
        //int i, result;
        //int j;
        //int k;
       // int x;
        //int index;
printf ("4.25\n");
        int saveHandCount = post->handCount[currentPlayer];
printf ("4.5\n");
        int handPos = floor(Random() * post->handCount[currentPlayer]);
        struct gameState pre;
printf ("6\n");
        memcpy(&pre, post, sizeof(struct gameState));
printf ("7\n");
        SelectStream(2);
        PutSeed(3);
printf ("8\n");
    //int result = cardEffect(adventurer, 0, 0, 0, post, handPos, 0);

        PutSeed(3);

     //   int currentPlayer = whoseTurn(state);
 int nextPlayer = currentPlayer + 1;

  int tributeRevealedCards[2] = {-1, -1};
  int temphand[MAX_HAND];// moved above the if statement
  int drawntreasure=0;
  int cardDrawn;
  int z = 0;

// assert (result == 0);

while(drawntreasure<2){//error here < to <=
  if (post->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
    shuffle(currentPlayer, post);
  }
  drawCard(currentPlayer, post);
  cardDrawn = post->hand[currentPlayer][post->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
  if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    drawntreasure++;
  else{
    temphand[z]=cardDrawn;
    post->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
    z++;
  }
      }
      while(z-1>=0){
  post->discard[currentPlayer][post->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
  z=z-1;
      }
      return 0;
    }

int main() {
        int i, p;
        //int n;
        struct gameState Game;

        printf ("--------------------------------\n");
        printf ("Testing cardEffect() with Adventurer card\n");
        printf ("RANDOM TESTS\n");

        SelectStream(3);
        PutSeed(3);

        printf ("2\n");

       // for (n = 0; n < 2000; n++) {
       //         SelectStream(3);
       //         for (i = 0; i < sizeof(struct gameState); i++) {
       //                 ((char*)&Game)[i] = floor(Random() * 256);
       //         }
        printf ("3\n");

        for (i = 0; i < sizeof(struct gameState); i++) {
                        ((char*)&Game)[i] = floor(Random() * 256);
                }
                p = floor(Random() * MAX_PLAYERS);
                Game.whoseTurn = p;
                Game.deckCount[p] = floor(Random() * MAX_DECK);
                Game.discardCount[p] = floor(Random() * MAX_DECK);
                Game.handCount[p] = floor(Random() * MAX_HAND);
                Game.playedCardCount = floor(Random() * MAX_DECK);
printf ("4\n");
                testAdventurer(p, &Game);
     //   }
                printf ("5\n");
        printf("ALL TESTS OK\n\n");
        return 0;
}
