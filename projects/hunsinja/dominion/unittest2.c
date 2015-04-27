//normal includes
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//dominion includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"

int getCostTest(int cardNumber) {
	int i = getCost(cardNumber);
	switch (cardNumber) {
		case baron:
			if (i != 4)
				printf("Baron costs %d, it should be 4.", i);
			else 
				printf("Baron passes\n");
			break;
		case adventurer:
			if(i != 6)
				printf("Adventurer costs %d, it should be 6.", i);
			else 
				printf("Adventurer passes\n");
			break;	       
		case council_room:	
			if(i != 5)
				printf("Council_Room costs %d, it should be 5.", i);
			else 
				printf("Council room passes\n");
			break;
		case gardens:	
			if(i != 4)
				printf("Gardens costs %d, it should be 4.", i);
			else 
				printf("Gardens passes\n");
               break;
		case feast:	
			if(i != 4)
				printf("Feast costs %d, it should be 4.", i);
			else 
				printf("Feast passes\n");
               break;		
		case great_hall:	
                if(i != 3)
                	printf("Great_Hall costs %d, it should be 5.", i);
                else 
				 printf("Great hall passes\n");
                break;	
		case mine:	
			if(i != 5)
				printf("Mine costs %d, it should be 5.", i);
			else 
				printf("Mine passes\n");
			break;	
		case remodel:	
			if(i != 4)
				printf("Remodel costs %d, it should be 4.", i);
			else 
				printf("Remodel passes\n");
			break;	
		case smithy:	
               if(i != 4)
				printf("Smithy costs %d, it should be 4.", i);
			else 
				printf("Smithy passes\n");
			break;	
		case village:	
                if(i != 3)
				printf("Village costs %d, it should be 3.", i);
			else 
				printf("Village passes\n");
			break;	
        }
        return 0;	
}

int main () {
	int i;
     int k[10] = {baron, adventurer, council_room, gardens, feast, mine, great_hall, village, remodel, smithy};
    
     printf("Begin testing\n\n");           
     for(i = 0; i < 10; i++)
		getCostTest(k[i]);

	printf("\nEnd testing\n");
	return 0;
}