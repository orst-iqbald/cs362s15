/*
    Michael Rose
    rosem2
*/
/*
    Test for getCost()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main ()
{
    int i;
    int succ = 1;
    //Keep cost + names in order loaded in dominion.c
    char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
                                   "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
                                   "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"
                                  };
    int cardCost[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    printf("getCost test: \n");
    for(i = 0; i < 27; i++)
    {
        if(getCost(i) == cardCost[i])
        {
        }
        else
        {
            if(getCost(i) < 0)
            {
                printf("TEST FAILED -- Card %s could not be found.",cardNames[i]);
                succ = 0;
            }
            else{
            printf("Testing %s. Expected cost: %d\n",cardNames[i],cardCost[i]);
            printf("TEST FAILED -- Actual cost: %d\n",getCost(i));
            succ = 0;
            }
        }
    }
    if(succ == 1){
        printf("TEST SUCCEEDED -- All tests passed.\n");
    }
    printf("END TEST\n");
    return 0;
}
