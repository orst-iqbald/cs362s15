#include "testings.h"

int test_isGameOver(){
	srand(time(NULL));

	int i = 0,
		j = 0,
		provinceNum = 0,
		passes = 0,
		fails = 0,
		tests = 0;

	int supplyNums[27] = {0};

	printf("TESTING isGameOver():\n");

	for(provinceNum = 0; provinceNum < 10; provinceNum++){
		for(i = 0; i < 10; i++){
			struct gameState *state = newGame();
			int zeros = 0;
			for(j = 0; j < 25; j++){
				if(j == province)
					continue;

				int r = rand() % 10;
				if(r == 0)
					zeros++;

				supplyNums[j] = r;
				state->supplyCount[j] = r;
			}
			
			printf("Test province # = %d zeros # = %d\n",provinceNum,zeros);

			supplyNums[province] = provinceNum;
			state->supplyCount[province] = provinceNum;

			int exp = zeros >= 3 || provinceNum == 0 ? 1 : 0;

			int res = isGameOver(state);

			printf("Result = %d, expected = %d\n",res,exp);

			if(exp == res)
				passes++;
			else
				fails++;
			tests++;

			printf("%s\n",(exp == res ? STR_PASS : STR_FAIL));

			free(state);
		}
	}
	printf(SUMMARY,passes,fails,tests);

	return 0;
}
