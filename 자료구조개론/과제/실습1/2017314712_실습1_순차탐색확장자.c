#include <stdio.h>


void LinearSearch(int a, int *arr) {

	for (int b = 0; b < 11; b++) {

		if (b = arr[a]) {
			printf("��� :11���� �˻����� arr�� 10���� index���� %d�� �߰ߵ�", a);
		}
		break;

	}
}

int main() {

	int Arr[12] = { 1,4,5,8,12,9,2,0,3,6,10,11 };
	int a;

	printf("1~10���̿��ִ� �ڿ��� �ϳ��� �Է��Ͻÿ�.");
	scanf_s("%d", &a);
	
	while (a <= 0 || a >= 10) {
		printf("���ڸ� �ٽ� �Է��Ͻÿ�");
		scanf_s("%d", a);
	}
	if (a > 0 && a < 10) {
		LinearSearch(a, Arr);
	}

	return 0;
}