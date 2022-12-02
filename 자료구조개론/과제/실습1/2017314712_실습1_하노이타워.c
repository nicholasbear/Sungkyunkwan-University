#include <stdio.h>

void Hanoitower(int num, char from, char by, char to) {
	if (num == 1) {
		printf("원반%d을 기둥%c에서 기둥%c옮긴다\n", 1, from, to);
	}
	else {
		Hanoitower(num - 1, from, to, by);
		printf("원반%d을 기둥%c에서 기둥%c옮긴다\n", num, from, to);
		Hanoitower(num - 1, by, from, to);
	}

}


int main() {
	int a = 0;

	printf("타워링 개수를 입력하시오: ");
	scanf_s("%d", &a);
	printf("맨위에 있는 원반은 1 맨밑에 있는 원반을 n이라하자\n");
	Hanoitower(a, 'A', 'B', 'C');


}