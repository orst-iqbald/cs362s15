/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: unittest2.c
- Description: A unit test of the kingdomCards() function in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm unittest2.c dominion.o rngs.o -o unittest2
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
   // adventurer - treasure_map // Card 27
   int tempArray[NUM_K_CARDS]; // 
   int *t;
   int *kc;
   int fail = 0;
   int failcount = 0;
   
   srand(99);
   
      
   // initialize tempArray with unique values in the range adventurer to treasure_map
   for (int i = 0; i < NUM_K_CARDS; i++) {
      int exists = 1;
      int r;
      while (exists) {
         exists = 0;
         r = rand() % (treasure_map - adventurer) + adventurer;
         assert(r <= treasure_map && r >= adventurer);
         for (int f = 0; f < i; f++) {
            if (r == tempArray[i]) {
               exists = 1;
               break;
            }
         }
      }
      tempArray[i] = r;
   }
   
   // Test expected range of inputs
   t = tempArray;
   kc = kingdomCards(t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8], t[9]);
   for (int i = 0; i < NUM_K_CARDS; i++) {
      if (t[i] != kc[i] || kc[i] < adventurer || kc[i] > treasure_map){
         fail = 1;
         failcount++;
         printf("FAIL: Card %d of kingdomCards failed to initialize correctly.\n", i);
      }
   }
   // Test out of range inputs
   for (int i = 0; i < NUM_K_CARDS; i++) {
      if (i % 2 == 0) 
         t[i] = INT_MAX;
      else
         t[i] = INT_MIN;
   }
   kc = kingdomCards(t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8], t[9]);
   for (int i = 0; i < NUM_K_CARDS; i++) {
      if (t[i] != kc[i] || kc[i] < adventurer || kc[i] > treasure_map){
         fail = 1;
         failcount++;
         printf("FAIL: Card %d of kingdomCards failed to check for out of range input.\n", i);
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d kingdomCards tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All kingdomCards tests PASSED\n");
   #endif
   return 0;
}