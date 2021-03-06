/*
    Testing getCost() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
  printf ("TESTING getCost() function:\n");
  int i, value;
  for(i=0; i<28; i++){
    value = getCost(i);
    switch(i){
      case 0:
        assert(value==0);
        printf("\tReturned correct value for curse card of %d.\n", value);
        break;
      case 1:
        assert(value==2);
        printf("\tReturned correct value for estate card of %d.\n", value);
        break;
      case 2:
        assert(value==5);
        printf("\tReturned correct value for duchy card of %d.\n", value);
        break;
      case 3:
        assert(value==8);
        printf("\tReturned correct value for province card of %d.\n", value);
        break;
      case 4:
        assert(value==0);
        printf("\tReturned correct value for copper card of %d.\n", value);
        break;
      case 5:
        assert(value==3);
        printf("\tReturned correct value for silver card of %d.\n", value);
        break;
      case 6:
        assert(value==6);
        printf("\tReturned correct value for gold card of %d.\n", value);
        break;
      case 7:
        assert(value==6);
        printf("\tReturned correct value for adventurer card of %d.\n", value);
        break;
      case 8:
        assert(value==5);
        printf("\tReturned correct value for council card of %d.\n", value);
        break;
      case 9:
        assert(value==4);
        printf("\tReturned correct value for feast card of %d.\n", value);
        break;
      case 10:
        assert(value==4);
        printf("\tReturned correct value for gardens card of %d.\n", value);
        break;
      case 11:
        assert(value==5);
        printf("\tReturned correct value for mine card of %d.\n", value);
        break;
      case 12:
        assert(value==4);
        printf("\tReturned correct value for remodel card of %d.\n", value);
        break;
      case 13:
        assert(value==4);
        printf("\tReturned correct value for smithy card of %d.\n", value);
        break;
      case 14:
        assert(value==3);
        printf("\tReturned correct value for village card of %d.\n", value);
        break;
      case 15:
        assert(value==4);
        printf("\tReturned correct value for baron card of %d.\n", value);
        break;
      case 16:
        assert(value==3);
        printf("\tReturned correct value for great hall card of %d.\n", value);
        break;
      case 17:
        assert(value==5);
        printf("\tReturned correct value for minion card of %d.\n", value);
        break;
      case 18:
        assert(value==3);
        printf("\tReturned correct value for steward card of %d.\n", value);
        break;
      case 19:
        assert(value==5);
        printf("\tReturned correct value for tribute card of %d.\n", value);
        break;
      case 20:
        assert(value==3);
        printf("\tReturned correct value for ambassador card of %d.\n", value);
        break;
      case 21:
        assert(value==4);
        printf("\tReturned correct value for cutpurse card of %d.\n", value);
        break;
      case 22:
        assert(value==2);
        printf("\tReturned correct value for embargo card of %d.\n", value);
        break;
      case 23:
        assert(value==5);
        printf("\tReturned correct value for outpost card of %d.\n", value);
        break;
      case 24:
        assert(value==4);
        printf("\tReturned correct value for salvager card of %d.\n", value);
        break;
      case 25:
        assert(value==4);
        printf("\tReturned correct value for sea hag card of %d.\n", value);
        break;
      case 26:
        assert(value==4);
        printf("\tReturned correct value for treasure map card of %d.\n", value);
        break;
      default:
        printf("\tReturned -1 error from function.\n");
    }
  }  
  printf ("FINISHED getCost() function:\n\n");

  return 0;
}