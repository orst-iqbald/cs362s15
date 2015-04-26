//************************************
//Tests for getcost() function
//************************************
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

int main () {

	printf ("TESTING getCost()...\n");

  int i;
  
  //array of cost values corresponding to each card enum in CARD; 
  //the last one tests for out of range, as getCosts() return -1
  int costs[28] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4,-1};
  
  for (i = curse; i <= treasure_map + 1; i++) {
    assert(getCost(i) == costs[i]);
  }

  printf ("ALL TESTS OK\n");

  return 0;
}
