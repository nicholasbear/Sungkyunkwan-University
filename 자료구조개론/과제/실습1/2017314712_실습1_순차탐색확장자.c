#include <stdio.h>


void LinearSearch(int a, int *arr) {

	for (int b = 0; b < 11; b++) {

		if (b = arr[a]) {
			printf("출력 :11번쨰 검색끝에 arr의 10번쨰 index에서 %d이 발견됨", a);
		}
		break;

	}
}

int main() {

	int Arr[12] = { 1,4,5,8,12,9,2,0,3,6,10,11 };
	int a;

	printf("1~10사이에있는 자연수 하나를 입력하시오.");
	scanf_s("%d", &a);
	
	while (a <= 0 || a >= 10) {
		printf("숫자를 다시 입력하시오");
		scanf_s("%d", a);
	}
	if (a > 0 && a < 10) {
		LinearSearch(a, Arr);
	}

	return 0;
}