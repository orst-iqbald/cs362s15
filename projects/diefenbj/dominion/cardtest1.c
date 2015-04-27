#include "testings.h"

int test_gardens(){
	int exp = -1,
		res = 0;

	res = h_gardens();

	
	printf("TESTING h_gardens():\n");

	printf("%s\n",(res == exp ? STR_PASS : STR_FAIL));

	return 0;
}
