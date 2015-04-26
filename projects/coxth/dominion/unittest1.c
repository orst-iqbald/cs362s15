/******************************
* unittest3.c 
* Thomas Cox
* updateCoins - This program test the updateCoins() function.
* 4/23/2015
******************************/
#include "dominion.h"
#include "interface.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>


int main(int argc, char** argv){
  struct gameState g;
  int i,j;
  srand(time(NULL));
  int randomPlayer;
  int randomCardNumber;
  int randomBonus;
  int coinSum;
  int randomHandCount;
  
  for(i = 0; i < 10; i++){
  
	  coinSum = 0;
	  randomHandCount = (rand() % 100);
	  randomBonus = (rand() % 20);
	  randomPlayer = (rand() % 6);
	  randomCardNumber = (rand() % 20);
	  
	  g.handCount[randomPlayer] = randomHandCount;
	  
	  for(j = 0; j < randomHandCount; j++){
		  if(randomCardNumber == 4){
			  coinSum += 1;
		  }
		  if(randomCardNumber == 5){
			  coinSum += 2;
		  }
		  if(randomCardNumber == 6){
			  coinSum += 3;
		  }
		  g.hand[randomPlayer][j] = randomCardNumber;
	  
	  }
	  
	  coinSum += randomBonus;
	  
	  updateCoins(randomPlayer, &g, randomBonus);
	  
	  printf("Number of coins = %d.\n", g.coins);
	  printf("Coinsum = %d.\n",coinSum);
	  printf("random bonus = %d \n", randomBonus);
	  printf("randomHandCount = %d.\n", randomHandCount);
	  printf("randomPlayer = %d.\n",randomPlayer);
	  printf("randomCardNumber = %d \n", randomCardNumber);
	  
	  //if the last card is either copper, silver, or gold and there are four players there is a failure
	  
	  if(g.coins != coinSum){
	    printf("error coins %d does not = %d coin sum\n",g.coins,coinSum);
	  }
  }
  return 0;
}