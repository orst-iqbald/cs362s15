// Jason Hsu
// hsuja@onid.oregonstate.edu
// 5/9/15
// CS362-400
// Random testing for play_adventurer()


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
   
  //int currentPlayer = 0;
  int temphand[MAX_HAND];
  int newdiscard[MAX_DECK];
  int newdiscard_z = 0; // counter for newdiscard
  int drawntreasure = 0;
  int cardDrawn;
  int z = 0;// this is the counter for the temp hand
  int i;
  int n;
  int p;
  int dis_idx;
  int rand_idx1;
  int rand_idx2;
  int holder;
  int treasure_card1 = -1;
  int treasure_card2 = -1;
  int treasure_count = 0;


  printf ("Testing play_adventurer()\n");

  printf ("RANDOM TESTS\n\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {

    printf("Test Iteration %d:\n", n + 1);

    treasure_card1 = -1;
    treasure_card2 = -1;
    newdiscard_z = 0;
    treasure_count = 0;
    

    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)g)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    //g->deckCount[p] = floor(Random() * MAX_DECK);
    g->deckCount[p] = floor(Random() * (MAX_DECK - 2)) + 2; //ensures at least 2
    g->discardCount[p] = floor(Random() * MAX_DECK);
    g->handCount[p] = floor(Random() * MAX_HAND);

    //fill hand with cards
    for(i = 0; i < g->handCount[p]; i++){
      g->hand[p][i] = floor(Random() * 26);
    }

    //fill deck with cards
    for(i = 0; i < g->deckCount[p]; i++){
      g->deck[p][i] = floor(Random() * 26);
      if(g->deck[p][i] == copper || g->deck[p][i] == silver || g->deck[p][i] == gold){
        treasure_count++;
      }
    }

    //insert a copper and silver into deck if less than 2 treasure cards in deck
    if(treasure_count < 2){
      
      do{
        if(g->deckCount[p] == 2){
          rand_idx1 = 0;
          rand_idx2 = 1;
        }else{
          rand_idx1 = floor(Random() * (g->deckCount[p] - 1));
          rand_idx2 = floor(Random() * (g->deckCount[p] - 1));
        }
      }while(rand_idx1 == rand_idx2);

      g->deck[p][rand_idx1] = copper;
      g->deck[p][rand_idx2] = silver;
    }

    //fill discard with cards
    for(i = 0; i < g->discardCount[p]; i++){
      g->discard[p][i] = floor(Random() * 26);
    }

    
    i = g->deckCount[p] - 1;
    while(i >= 0 && treasure_card2 < 0){

      holder = g->deck[p][i];

       //find treasure cards that will end up in hand
      if(holder == copper || holder == silver || holder == gold){
        if(treasure_card1 >= 0){
          treasure_card2 = holder;
          //printf("treasure_card2 = %d\n", treasure_card2);
        }else{
          treasure_card1 = holder;
          //printf("treasure_card1 = %d\n", treasure_card1);
        }
      }else{

        //find cards added to discard pile
 
        newdiscard[newdiscard_z] = holder;
        newdiscard_z++;

      }

      i--;
    }


    //call test function
    play_adventurer(&p, g, &cardDrawn, drawntreasure, &z, temphand);
    
    printf("Expected Treasure Card 1: %d\n", treasure_card1);
    printf("Actual Treasure Card 1 in Hand: %d\n", g->hand[p][g->handCount[p] - 2]);
    printf("Expected Treasure Card 2: %d\n", treasure_card2);
    printf("Actual Treasure Card 2 in Hand: %d\n", g->hand[p][g->handCount[p] - 1]);
    
    assert(g->hand[p][g->handCount[p] - 1] == treasure_card2);
    assert(g->hand[p][g->handCount[p] - 2] == treasure_card1);
 

    dis_idx = g->discardCount[p] - 1;

    for(i = 0; i < newdiscard_z; i++){
      assert(newdiscard[i] == g->discard[p][dis_idx]);
      dis_idx--;
    }

    printf("Non-treasure cards properly discarded.\n\n");

  }

  printf ("ALL TESTS OK\n");
   
  free(g);

  return 0;
}







