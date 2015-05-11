// Jason Hsu
// hsuja@onid.oregonstate.edu
// 5/9/15
// CS362-400
// Random testing for play_village()


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"


int main(){

  struct gameState* g = malloc(sizeof(struct gameState));
   
  int i;
  int n;
  int p;
  int rand_idx;
  int pre_handCount;
  int pre_deckCount;
  int pre_numActions;
  int pre_playedCardCount;
  int drawnCard;

  printf ("Testing play_village()\n");

  printf ("RANDOM TESTS\n\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {

    printf("Test Iteration %d:\n", n + 1);


    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)g)[i] = floor(Random() * 256);
    }


    g->numActions = floor(Random() * 100);
    g->playedCardCount = floor(Random() * 100);

    p = floor(Random() * 2);
    
    //g->deckCount[p] = floor(Random() * MAX_DECK);
    g->deckCount[p] = floor(Random() * (MAX_DECK - 1)) + 1; //ensures at least 1
    g->discardCount[p] = floor(Random() * MAX_DECK);
    //g->handCount[p] = floor(Random() * MAX_HAND); 
    g->handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1; //ensures at least 1 


    //fill hand with cards
    for(i = 0; i < g->handCount[p]; i++){
      g->hand[p][i] = floor(Random() * 26);
    }

    //insert village card into random hand position
    rand_idx = floor(Random() * (g->handCount[p] - 1));
    g->hand[p][rand_idx] = village;

    //fill deck with cards
    for(i = 0; i < g->deckCount[p]; i++){
      g->deck[p][i] = floor(Random() * 26);
    }

    //fill discard with cards
    for(i = 0; i < g->discardCount[p]; i++){
      g->discard[p][i] = floor(Random() * 26);
    }

    pre_handCount = g->handCount[p];
    pre_numActions = g->numActions;
    pre_playedCardCount = g->playedCardCount;
    pre_deckCount = g->deckCount[p];
    drawnCard = g->deck[p][g->deckCount[p] - 1];


    //call test function
    play_village(&p, g, &rand_idx);


    assert(g->deckCount[p] == pre_deckCount - 1);
    printf("deckCount properly decremented\n");
    assert(g->handCount[p] == pre_handCount);
    printf("handCount properly remains the same\n");


    printf("Expected numActions: %d\n", pre_numActions + 2);
    printf("Actual numActions: %d\n", g->numActions);
    assert(g->numActions == pre_numActions + 2);

    printf("Expected playedCardCount: %d\n", pre_playedCardCount + 1);
    printf("Actual playedCardCount: %d\n", g->playedCardCount);
    assert(g->playedCardCount == pre_playedCardCount + 1);

    if(rand_idx != g->handCount[p] - 1){
      
      printf("Expected card added to hand: %d\n", drawnCard);
      printf("Actual card added to hand: %d\n", g->hand[p][rand_idx]);
      assert(g->hand[p][rand_idx] == drawnCard);

    }else{

      printf("Expected card added to hand: %d\n", drawnCard);
      printf("Actual card added to hand: %d\n", g->hand[p][g->handCount[p] - 1]);
      assert(g->hand[p][g->handCount[p] - 1] == drawnCard);

    }

    printf("\n");

  }

  printf ("ALL TESTS OK\n");
   
  free(g);

  return 0;
}