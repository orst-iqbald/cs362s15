/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: unittest1.c
- Description: A unit test of the getCost() function in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm unittest1.c dominion.o rngs.o -o unittest1
*******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#define DEBUG 0
#define NOISY_TEST 1

int main(int argc, char *argv[])
{	
   int testCostArray[][2] = { // Reference data for card costs
      {curse, CURSE_COST}, // Card 0
      {estate, ESTATE_COST}, 
      {duchy, DUCHY_COST}, 
      {province, PROVINCE_COST}, 
      {copper, COPPER_COST}, 
      {silver, SILVER_COST}, 
      {gold, GOLD_COST}, 
      {adventurer, ADVENTURER_COST}, 
      {council_room, COUNCIL_ROOM_COST}, 
      {feast, FEAST_COST}, 
      {gardens, GARDEN_COST}, 
      {mine, MINE_COST}, 
      // {moneylender, MONEYLENDER_COST} // 4  -  Not implemented 
      {remodel, REMODEL_COST}, 
      {smithy, SMITHY_COST}, 
      {village, VILLAGE_COST}, 
      // {woodcutter, WOODCUTTER_COST} // 3  -  Not implemented 
      {baron, BARON_COST}, 
      {great_hall, GREAT_HALL_COST}, 
      {minion, MINION_COST}, 
      // {shanty_town, SHANTY_TOWN_COST} // 3  -  Not implemented 
      {steward, STEWARD_COST}, 
      {tribute, TRIBUTE_COST}, 
      // {wishing_well, WISHING_WELL_COST} // 3  -  Not implemented 
      {ambassador, AMBASSADOR_COST}, 
      {cutpurse, CUTPURSE_COST}, 
      {embargo, EMBARGO_COST}, 
      {outpost, OUTPOST_COST}, 
      {salvager, SALVAGER_COST}, 
      {sea_hag, SEA_HAG_COST}, 
      {treasure_map, TREASURE_MAP_COST}}; // Card 27
   
   int s = (sizeof(testCostArray)/sizeof(int))/(sizeof(*testCostArray)/sizeof(int));
   int fail = 0;
   int failcount = 0;
   
   // printf("Province card is 3 (value is: %d)\n", province);
   // printf("The size of the array is %d (should be 27)\n", s);
   for (int i = 0; i < s; i++) {
      assert(i == testCostArray[i][0]);
   }
   #if (NOISY_TEST == 1)
      printf("All card names in testCostArray[i][0] match enum CARD in dominion.h.\n");
   #endif
   // Test expected range of inputs
   for (int i = 0; i < s; i++) {
      int c = getCost(i);
      if (c != testCostArray[i][1]){
         fail = 1;
         failcount++;
         printf("FAILED: Cost for card %d returned:%d  Expected: %d.\n", 
            i, c, testCostArray[i][1]);
      }
   }
   // Test out of range inputs
   if (getCost(s) != -1) { // large values
      fail = 1;
      failcount++;
      printf("FAILED: getCost failed with input of %d.", s);
   }
   if (getCost(-1) != -1) { // negative values
      fail = 1;
      failcount++;
      printf("FAILED: getCost failed with input of -1.");
   }
   if (getCost('a') != -1) { // character input
      fail = 1;
      failcount++;
      printf("FAILED: getCost failed with input of 'a'.");
   }
   if (getCost(INT_MAX) != -1) { // INT_MAX input value
      fail = 1;
      failcount++;
      printf("FAILED: getCost failed with input of INT_MAX.");
   }
   if (getCost(INT_MIN) != -1) { // INT_MIN input value
      fail = 1;
      failcount++;
      printf("FAILED: getCost failed with input of INT_MIN.");
   }
   // Tests Complete
   if (fail) {
      printf("%d getCost tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All getCost tests PASSED\n");
   #endif
   return 0;
}