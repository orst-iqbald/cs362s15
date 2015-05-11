#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//random tester for adventurer card
int checkAdventurer(int p, struct gameState *post, int *failCounter){
    
    int z = 0;
    int drawnTreasure = 0;
    int cardDrawn, r, localFails = 0;
    int temphand[MAX_HAND]; 
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int choice1 = floor(Random() * 256);
    int choice2 = floor(Random() * 256);
    int choice3 = floor(Random() * 256);

    r = cardEffect(adventurer, choice1, choice2, choice3, post, 0, 0);

    while(drawnTreasure < 2){
      if(pre.deckCount[p] < 1){//if deck is empty shuffle card and add to deck
	shuffle(p, &pre);
      }
      drawCard(p, &pre);
      cardDrawn = pre.hand[p][pre.handCount[p]-1];//top card is most recent drawn

      if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
	drawnTreasure++;
      }else{
	temphand[z] = cardDrawn;
	pre.handCount[p]--;// remove top card (card drwan)
        z++;
      }
    }
 
    while(z - 1 >= 0){
      pre.discard[p][pre.discardCount[p]++] = temphand[z-1];
      z = z -1;
    } 
     
    if(pre.deckCount[p] != post->deckCount[p])
      localFails++; 
    if(pre.handCount[p] != post->handCount[p])
      localFails++;
    if(pre.discardCount[p] != post->discardCount[p])
      localFails++;
    assert(r == 0);
    if(memcmp(&pre, post, sizeof(struct gameState)) != 0)
      localFails++;
    
    if(localFails > 0)
      *failCounter = *failCounter + 1;

return 0;
}
int main(){

    int i, n, p;
    int fails = 0;
    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf("Testing adventurer card\n");
    printf("Random tests\n");

    for(n = 0; n < 2000; n++){
      for(i = 0; i < sizeof(struct gameState); i++){
	((char*)&G)[i] = floor(Random() * 256);
      }
      p = floor(Random() * 2);
      G.whoseTurn = p;
      G.deckCount[p] = MAX_HAND;
      G.discardCount[p] = floor(Random() * MAX_HAND);
      G.handCount[p] = floor(Random() * MAX_HAND);
      G.playedCardCount = floor(Random() * MAX_HAND);

      //populate the hand, discard and deck with random cards
      for(i = 0; i < G.handCount[p]; i++){
	G.hand[p][i] = floor(Random() * (treasure_map + 1));
      }
      for(i = 0; i < G.discardCount[p]; i++){
        G.discard[p][i] = floor(Random() * (treasure_map + 1));
      }
      for(i = 0; i < G.deckCount[p]; i++){
        G.deck[p][i] = floor(Random() * (treasure_map + 1));
      }
      for(i = 0; i < G.playedCardCount; i++){
        G.playedCards[p] = floor(Random() * (treasure_map + 1));
      }
      checkAdventurer(p, &G, &fails);
      
    }
       
    if(fails == 0){
      printf("All tests passed!\n");
    }else{
      printf("Tests ran 2000 times, failed %d time(s)\n", fails);
    }

return 0;
}


