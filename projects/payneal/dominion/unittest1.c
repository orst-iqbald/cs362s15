/* -----------------------------------------------------------------------
* a unit test for getCost() in dominion.c
* Include the following lines in your makefile:
*
* unittest1: unittest1.c dominion.o rngs.o
*      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

//number of cards to check
const int amount= 27;

//  if number of chards changed please updat test

//will hold the cards name and value
struct cardandvalue
{
    char* cardName[amount];
    int functionValue[amount];
    int realValue[amount];
};


int main() {
    
    // check to see if amount is correct if not this is invaild test and is no longer valid
    assert(amount == 27);
    
    
    int functionCost[amount] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    int actualCost[amount]= {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    char* name[amount] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    
    struct cardandvalue check;
    
    int i;
    for (i = 0; i < amount; i++)
    {
        check.cardName[i] = name[i];
        check.functionValue[i] = functionCost[i];
        check.realValue[i] = actualCost[i];
    }
    
    #if (NOISY_TEST == 1)
        printf ("TESTING updateCoins():\n");
    #endif
    
    int numbFailed=0;
    int numbPassed=0;
    
    for (i = 0; i < amount; i++)
    {
        if ( check.realValue[i] == getCost(check.functionValue[i]) )
        {
           
                numbPassed++;
             #if (NOISY_TEST == 1)
                printf("the value of %s PASSED \n", check.cardName[i]);
            #endif
        }
        else
        {
            
                numbFailed++;
            #if (NOISY_TEST == 1)
                printf("the value of %s Failed \n", check.cardName[i]);
            #endif
            
        }
    }

    #if (NOISY_TEST == 1)
        printf("%i cards where of the wrong value\n", numbFailed);
        printf("%i cards where of the correct vale\n", numbPassed);
    #endif
    
    if( numbPassed == amount)
    {
            #if (NOISY_TEST == 1)
                printf("All tests passed!\n");
            #endif
    }
    else
    {
        #if (NOISY_TEST == 1)
            printf("Not all test failed see above which cards hard incorrect value\n");
        #endif
        return -1;
        
    }
    
    return 0;
}