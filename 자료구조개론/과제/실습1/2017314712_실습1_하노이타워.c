#include <stdio.h>

void Hanoitower(int num, char from, char by, char to) {
	if (num == 1) {
		printf("����%d�� ���%c���� ���%c�ű��\n", 1, from, to);
	}
	else {
		Hanoitower(num - 1, from, to, by);
		printf("����%d�� ���%c���� ���%c�ű��\n", num, from, to);
		Hanoitower(num - 1, by, from, to);
	}

}


int main() {
	int a = 0;

	printf("Ÿ���� ������ �Է��Ͻÿ�: ");
	scanf_s("%d", &a);
	printf("������ �ִ� ������ 1 �ǹؿ� �ִ� ������ n�̶�����\n");
	Hanoitower(a, 'A', 'B', 'C');


}