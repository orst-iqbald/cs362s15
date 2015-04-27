/* *****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four functions (not card implementations or cardEffect) in dominion.c. 
Check these tests in as unittest1.c,unittest2.c, unittest3.c, and unittest4.c. 

Unit test for getCost();
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int testGetCost(int cardNumber) {
        int x = getCost(cardNumber);
        switch (cardNumber) {
            case adventurer:
                if(x != 6)
                	printf("%s is %d, it should be %d.", "Adventurer", x, 6);
                else printf("Adventurer Good!\n");
                break;	
            case baron:
            	if (x != 4)
					printf("%s is %d, it should be %d.", "Baron", x, 4);
				else printf("Baron Good!\n");
                break;         
            case council_room:	
                if(x != 5)
                	printf("%s is %d, it should be %d.", "Council_Room", x, 5);
                else printf("Council Room Good!\n");
                break;	
            case feast:	
                if(x != 4)
                	printf("%s is %d, it should be %d.", "Feast", x, 4);
                else printf("Feast Good!\n");
                break;	
            case gardens:	
                if(x != 4)
                	printf("%s is %d, it should be %d.", "Gardens", x, 4);
                else printf("Gardens Good!\n");
                break;	
            case great_hall:	
                if(x != 3)
                	printf("%s is %d, it should be %d.", "Great_Hall", x, 3);
                else printf("Great Hall Good!\n");
                break;	
            case mine:	
               if(x != 5)
                	printf("%s is %d, it should be %d.", "Mine", x, 5);
                else printf("Mine Good!\n");
                break;	
            case remodel:	
               if(x != 4)
                	printf("%s is %d, it should be %d.", "Remodel", x, 4);
                else printf("Remodel Good!\n");
                break;	
            case smithy:	
               if(x != 4)
                	printf("%s is %d, it should be %d.", "Smithy", x, 4);
                else printf("Smithy Good!\n");
                break;	
            case village:	
                if(x != 3)
                	printf("%s is %d, it should be %d.", "Village", x, 3);
                else printf("Village Good!\n");
                break;	
        }
        return 0;	
}

int main () {
    int i;
    int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
    
    printf("Testing getCost()...\n");            
    for(i = 0; i < 10; i++)
        testGetCost(k[i]);

      printf("End testing getCost\n");
      return 0;
} // end main 