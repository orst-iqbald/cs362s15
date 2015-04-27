/*
    Michael Rose
    rosem2
*/
/*
    Test for kingdomCards()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NUMTESTS 10
int main ()
{
    int array[10];
    int *output;
    int i,j;
    int succ = 1;
    printf("kingdomCards test: \n");
    //do it 10 times.
    for(j = 0; j < NUMTESTS; j++)
    {
        for(i = 0; i < 10; i++)
        {
            array[i] =rand() %27;
        }
        output = kingdomCards(array[0],array[1],array[2],array[3],array[4],array[5],array[6],array[7],array[8],array[9]);
        for(i = 0;i < 10; i++)
        {
            if(output[i] != array[i])
            {
                printf("TEST FAILED -- kingdomCards is not setting the proper value. Expected : %d, Actual: %d\n",array[i],output[i]);
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
