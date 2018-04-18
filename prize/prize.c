#include <stdio.h>

#define DIGIT 7

int tenExps[] = {1, 10, 100, 1000, 10000, 100000};

void num_switch(char numbers[DIGIT], int i1, int i2)
{
	char tmp = numbers[i1];
	numbers[i1] = numbers[i2];
	numbers[i2] = tmp;
}

int isRSorted(char numbers[DIGIT], int size)
{
	for (int i = 0; i < size - 1; ++i) {
		if (numbers[i] < numbers[i + 1])
			return 0;
	}
	return 1;
}
int isExistSameElement(char sorted_numbers[DIGIT], int size)
{
	for (int i = 0; i < size - 1; ++i) {
		if (sorted_numbers[i] == sorted_numbers[i+1])
			return 1;
	}
	return 0;
}
int isMax(char *numbers, int size, int value)
{
	for (int i = 0; i < size; ++i) {
		if (value < numbers[i]) 
			return 0;
	}
	return 1;
}

int change(char numbers[DIGIT], int size, int change_times)
{
	if (change_times == 0) {
		int rs = 0;
		for (int i = 0; i < size; ++i) {
			rs += (numbers[i] - '0') * tenExps[size-i-1];
		}
		return rs;
	} else if (isRSorted(numbers, size)) {
		if (isExistSameElement(numbers, size)) 
			return change(numbers, size, 0);
		else {
			num_switch(numbers, size-2, size-1);
			int rs = change(numbers, size, 0);
			num_switch(numbers, size-2, size-1);
			return rs;
		}
	}
	int max = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (numbers[i] >= numbers[j] || !isMax(numbers+j+1, size-j-1, numbers[j])) {
				continue;
			} 
			num_switch(numbers, i, j);
			int tmp = change(numbers, size, change_times-1);
			num_switch(numbers, i, j);
			if (max < tmp)
				max = tmp;
		}
	}
	return max;
}

int main()
{
	int N, size, score, change_times;
	char numbers[DIGIT];

	scanf("%d", &N);
	for (int case_num = 1; case_num <= N; ++case_num) {
		scanf("%s", numbers);
		size = 0;
		while (numbers[size] != 0)
			size++;
		scanf("%d", &change_times);
		
		score = change(numbers, size, change_times);
		printf("#%d %d\n", case_num, score);
	}
}

