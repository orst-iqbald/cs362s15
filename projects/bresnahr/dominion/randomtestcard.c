#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//random tester for smithy card
int checkSmithy(int p, struct gameState *post, int *failCounter){

    int i, r, localFails = 0;
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int choice1 = floor(Random() * 256);
    int choice3 = floor(Random() * 256);
    int choice2 = floor(Random() * 256);

    r = cardEffect(smithy, choice1, choice2, choice3, post, 0, 0);
    
    for(i = 0; i < 3; i++){
      drawCard(p, &pre);
    }

    discardCard(0, p, &pre, 0);

    if(pre.deckCount[p] != post->deckCount[p])
      localFails++;
    if(pre.handCount[p] != post->handCount[p])
      localFails++;
    if(pre.discardCount[p] != post->discardCount[p])
      localFails++;
    if(pre.playedCardCount != post->playedCardCount)
      localFails++;

    assert(r == 0);
    if(memcmp(&pre, post, sizeof(struct gameState)) != 0){
      localFails++;
    }

    if(localFails > 0)
      *failCounter = *failCounter + 1;
  
    return 0;
}
int main(){

    int i, n, p;
    int fails = 0;
    struct gameState G;

    SelectStream(1);
    PutSeed(3);

    printf("Testing smithy card\n");
    printf("Random tests\n");

    for(n = 0; n < 2000; n++){
      for(i = 0; i < sizeof(struct gameState); i++){
        ((char*)&G)[i] = floor(Random() * 256);
      }
      p = floor(Random() * 2);
      G.whoseTurn = p;
      G.playedCardCount = floor(Random() * MAX_HAND);//used in discardCard
      G.deckCount[p] = MAX_HAND;//use max hand;
      G.discardCount[p] = floor(Random() * MAX_HAND);
      G.handCount[p] = floor(Random() * MAX_HAND);

      //populate hand, discard, played cards and deck with random cards
      for(i = 0; i < G.handCount[p]; i++){
        G.hand[p][i] = floor(Random() * (treasure_map + 1));
      }
      for(i = 0; i < G.discardCount[p]; i++){
        G.discard[p][i] = floor(Random() * (treasure_map + 1));
       }
      for(i = 0; i < G.deckCount[p]; i++){
        G.deck[p][i] = floor(Random() * (treasure_map + 1));
      }
      for(i= 0; i < G.playedCardCount; i++){
        G.playedCards[p] = floor(Random() * (treasure_map + 1));
      }
      checkSmithy(p, &G, &fails);
    }

    if(fails == 0){
      printf("All tests passed!\n");
    }else{
      printf("Tests ran 2000 times, failed %d time(s)\n", fails);
    }

return 0;
}
