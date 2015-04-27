#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

#define TESTFUNC "getCost()"

int main(){

    int i;
    int numPlayers = 2;
    int seed = 1000;
    
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    //set up game state and player cards
    initializeGame(numPlayers, k, seed, &state);
   
   //Asserting the costs of each of the various cards
    printf("Asserting cost of copper. \n");
    assert(getCost(copper) == 0);

    printf("Asserting cost of silver.\n");
    assert(getCost(silver) == 3);

    printf("Asserting cost of gold.\n");
    assert(getCost(gold) == 6);

    printf("Asserting cost of adventurer.\n");
    assert(getCost(adventurer) == 6);

    printf("Asserting cost of smithy.\n");
    assert(getCost(smithy) == 4);
    
    printf("Asserting cost of ambassador.\n");
    assert(getCost(ambassador) == 3);

    printf("Asserting cost of baron.\n");
    assert(getCost(baron) == 4);

    printf("Asserting cost of council room.\n");
    assert(getCost(council_room) == 5);

    printf("Asserting cost of curse.\n");
    assert(getCost(curse) == 0);

    printf("Asserting cost of cutpurse.\n");
    assert(getCost(cutpurse) == 4);

    printf("Asserting cost of duchy.\n");
    assert(getCost(duchy) == 5);

    printf("Asserting cost of embargo.\n");
    assert(getCost(embargo) == 2);
    
    printf("Asserting cost of estate.\n");
    assert(getCost(estate) == 2);

    printf("Asserting cost of feast.\n");
    assert(getCost(feast) == 4);

    printf("Asserting cost of gardens.\n");
    assert(getCost(gardens) == 4);

    printf("Asserting cost of great hall.\n");
    assert(getCost(great_hall) == 3);

    printf("Asserting cost of mine.\n");
    assert(getCost(mine) == 5);

    printf("Asserting cost of minion.\n");
    assert(getCost(minion) == 5);

    printf("Asserting cost of outpost.\n");
    assert(getCost(outpost) == 5);
    
    printf("Asserting cost of province.\n");
    assert(getCost(province) == 8);

    printf("Asserting cost of remodel. \n");
    assert(getCost(remodel) == 4);
    
    printf("Asserting cost of salvager.\n");
    assert(getCost(salvager) == 4);

    printf("Asserting cost of sea hag.\n");
    assert(getCost(sea_hag) == 4);

    printf("Asserting cost of steward.\n");
    assert(getCost(steward) == 3);

    printf("Asserting cost of treasure map.\n");
    assert(getCost(treasure_map) == 4);

    printf("Asserting cost of tribute.\n");
    assert(getCost(tribute) == 5);
    
    printf("Asserting cost of village.\n");
    assert(getCost(village) == 3);

    //Asserting that cards can not cost negative values.
    printf("Negative unexpected numbers test.\n");
    for (i = -1; i >= -1000; i--) {
        assert(getCost(i) == -1);
    }
    for (i = treasure_map + 1; i <= 1000; i++) {
        assert(getCost(i) == -1);
    }
    
    printf("Testing finished.\n");
    
    return 0;
}