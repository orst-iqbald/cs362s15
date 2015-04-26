//*************************************
//Tests for Adventurer Card
//************************************

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

    int seed = 1000;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};

    // start building game state
    struct gameState game;
    initializeGame(2, k, seed, &game);

    printf ("Testing Adventurer card...\n");  
    
    int test = 0;

    // place adventurer card first in deck
    game.hand[0][0] = adventurer;
    
    //store current hand count and treasures
    int curHandCount = game.handCount[0];
    int treasures = 0;

    int i = 0;
    for (i = 0; i < game.handCount[0]; i++){
        if (game.hand[0][i] == gold || game.hand[0][i] == silver || game.hand[0][i] == copper){
            treasures++;
        }
    }

    //play the card
    adventurerCard(0,0, &game);

    //collect treasure count after being played 
     for (i = 0; i < game.handCount[0]; i++){
        if (game.hand[0][i] == gold || game.hand[0][i] == silver || game.hand[0][i] == copper){
            test++;
        }
    }

    // compare before and after treasures
   if (test == treasures + 2)
   {
        printf("adventurerCard(): passed treasure count\n");
    }
    else
    {
        printf("adventurerCard(): failed treausure count\n");
   }

  // check that we have an extra card in hand
  if(game.handCount[0] == curHandCount + 1 )
  {
        printf("adventurerCard(): passed hand count\n");
    }
    else
    {
        printf("adventurerCard(): failed hand count\n");
  }
  return 0; 
}
