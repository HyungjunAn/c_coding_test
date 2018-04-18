#include <stdio.h>

#define TEST_CASE 10
#define STUDENTS 1000

int main()
{
	int scores[101];
	int score;
	int case_num;
	int max;
	int max_score;
	for (int i = 0; i < TEST_CASE; ++i) {
		max = 0;
		scanf("%d", &case_num);
		for (int j = 0; j <= 100; ++j) {
			scores[j] = 0;
		}
		for (int j = 0; j < STUDENTS; ++j) {
			scanf("%d", &score);
			scores[score] += 1;
		}
		for (int j = 0; j <= 100; ++j) {
			if (max < scores[j]) {
				max = scores[j];
				max_score = j;
			} else if (max == scores[j] && max_score < j) {
                max_score = j;
            }
		}
		printf("#%d %d\n", case_num, max_score);
	}
}
