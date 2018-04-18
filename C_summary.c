#include <stdio.h>
#include <stdlib.h>

// Conditional Compile
#ifdef IS_DEBUG 
char* msg = "debug";
#else
char* msg = "release";
#endif

int sum(int n1, int n2)
{
	return n1 + n2;
}

// Inline
inline int minus(int n1, int n2)
{
	return n1 - n2;
}

struct student {
	char name[10];
	int score;
};

union Data {
	int i;
	double d;
	char* str;
};

// Enum
enum day1 {
	mon1, tue1, wed1, thu1, fri1, sat1, sun1
};	// 0, 1, 2, 3, 4, 5, 6
enum day2 {
	mon2=5, tue2, wed2, thu2=10, fri2, sat2, sun2
};	// 5, 6, 7, 10, 11, 12, 13

int main(int argc, char **argv)
{
	printf("-----------------------------------------\n");
	
// 2D Array
	int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7}, {8, 9}};
	printf("%d\n", arr[1][3]);
	
// Pointer Array
	int *p_arr[3] = {arr, (arr+1), (arr+2)};
	printf("%d\n", *(*(p_arr + 1) + 2));

// Array Pointer
	int (*arr_p)[4] = arr;
	printf("%d\n", *(*(arr_p + 1) + 2));

// Function Pointer
	int (*fp)(int, int) = sum;
	printf("%d\n", fp(1, 2));
	printf("%d\n", (*sum)(1, 2));

// Const
	int *p1 = (int*)malloc(sizeof(int)*1);
	int *p2 = (int*)malloc(sizeof(int)*1);
	*p1 = 1;
	*p2 = 2;

	int* const pc_v = p1;
	*pc_v = 3; 	// OK
	// pc_v = p2; 	// ERROR
	
	int const *cp_v = p1;
	// *cp_v = 3; 	// ERROR
	cp_v = p2;	// OK

	int const * const cpc_v = p1;
	// *cpc_v = 3; 	// ERROR
	// cpc_v = p2; 	// ERROR
	
	
// Variable Argument Macro
#define debug(s, ...) printf(s, __VA_ARGS__)
	debug("good%s\n", "test");

// Structure
	struct student s1;
	struct student s2 = {"abc", 30};
	struct student s3 = {.score = 30, .name = "abc"};
	struct student* sp = &s3;
	struct student sl1[2] = {{"a", 20}, {"b", 30}};
	struct student sl2[2] = {s2, s3};

	printf("%d\n", s3.score);
	printf("%d\n", (*sp).score);
	printf("%d\n", sp->score);

// Union
	union Data data1 = {10};
	// union Data data2 = {"abc"};	// ERROR: only first member can be initialized
	data1.str = "abc";

// Enum
	enum day1 day = wed1;
	printf("%d\n", day);
	day = thu1;
	printf("%d\n", day);

// Bit Operator
	int b1;
	b1 = 1 & 2; 		//  0: 1, 1 -> 1
	b1 = 1 ^ (2 + 1); 	//  2: 1, 0 -> 1
	b1 = 1 | 2; 		//  3: 1, 1 -> 1 or 1, 0 -> 1
	b1 = ~1;	 	// -2: 1 -> 0 or 0 -> 1
	b1 = 4;
	// n bit shift
	b1 <<= 1; 		//  * 2^n
	b1 >>= 1; 		//  / 2^n
}
