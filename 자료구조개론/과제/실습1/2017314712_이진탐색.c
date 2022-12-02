#include <stdio.h>

int BinarySearch(int a,int *arr) {
	int first = 0;
	int last = 11;
	int mid = 0;

	while (first <= last) {
		mid = (first + last) / 2;
		if (arr[mid] == a) {
			return mid+1;
		}
		else {
			if (arr[mid] > a) {
				last = mid - 1;
			}
			else
				first = mid + 1;
		}
	}
	return -1;
}

int findnum(int a,int *arr) {
	int first = 0;
	int last = 11;
	int mid = 0;
	int num = 0;

	while (first <= last) {
		mid = (first + last) / 2;
		num++;
		if (arr[mid] == a) {
			return num;
		}
		else {
			if (arr[mid] > a) {
				last = mid - 1;
			}
			else
				first = mid + 1;
		}
	}
	return -1;
}



int main() {

	int Arr[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int a = 0;

	printf("1부터 12사이의 찾는 숫자를 입력하시오: ");
	scanf_s("%d", &a);
	while (a < 1 || a>12) {
		printf("숫자를 다시 입력하시오: ");
		scanf_s("%d", &a);
	}
	printf("%d번째의 검색끝에 arr의 %d번째 index에서 %d이 발견됨", findnum(a,Arr),BinarySearch(a, Arr), BinarySearch(a,Arr));

	return 0;
}