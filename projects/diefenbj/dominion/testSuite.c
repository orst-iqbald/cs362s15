#include <stdlib.h>
#include <stdio.h>

#include "unittest1.c"
#include "unittest2.c"
#include "unittest3.c"
#include "unittest4.c"
#include "cardtest1.c"
#include "cardtest2.c"
#include "cardtest3.c"

int main(){
	printf("STARTING TEST SUITE...\n");
	test_FullDeckCount();
	
	test_isGameOver();

	test_scoreFor();

	test_whoseTurn();

	test_Great_Hall();

	test_gardens();

	test_Smithy();
	printf("FINISHING TEST SUITE...\n");
	return 0;
}
