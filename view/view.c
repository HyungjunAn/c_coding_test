#include <stdio.h>

#define TEST_CASE 10

int min4(int n1, int n2, int n3, int n4)
{
	int rs1 = (n1 > n2)? n2: n1;
    int rs2 = (n3 > n4)? n4: n3;
    return (rs1 > rs2)? rs2: rs1;
}

int main()
{
	int map[1000];	
	int case_num = 1;
    int size;	
	int ttl_view = 0;
    int tmp_view;
	for (int case_num = 1; case_num <= TEST_CASE; ++case_num) {
        ttl_view = 0;		
		scanf("%d", &size);		
		for (int i = 0; i < size; ++i) {
			scanf("%d", &map[i]);			
		}
		for (int i = 2; i < size - 2; ++i) {
            tmp_view = min4(map[i] - map[i-2], map[i] - map[i-1], map[i] - map[i+1], map[i] - map[i+2]);
            if (tmp_view > 0)
                ttl_view += tmp_view;                       
        }
		printf("#%d %d\n", case_num, ttl_view);        
	}
}

