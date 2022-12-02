#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
}Node;

typedef struct Queue {
	Node* front;
	Node* rear;
	Node* cur;
	int numofdata;
}Queue;

void Frontinsert(Queue* que,int data) {
	Node* Newnode = (Node*)malloc(sizeof(Node));
	Newnode->data = data;

	if (que->front== NULL) {
		Newnode->next = NULL;
		Newnode->prev = NULL;
		que->front= Newnode;
		que->rear = Newnode;
	}

	else {
		que->front->prev = Newnode;
		Newnode->next = que->front;
		que->front= Newnode;
		que->front->prev = NULL;
	}
	que->cur = que->front;
	(que->numofdata)++;
}

void Rearinsert(Queue*que, int data) {
	Node* Newnode = (Node*)malloc(sizeof(Node));
	Newnode->data = data;

	if (que->front== NULL) {
		Newnode->next = NULL;
		Newnode->prev = NULL;
		que->front = Newnode;
		que->rear = Newnode;
	}
	else {
		que->rear->next = Newnode;
		Newnode->prev = que->rear;
		que->rear = Newnode;
		que->rear->next = NULL;
	}
	que->cur = que->front;
	(que->numofdata)++;
}

int Frontremove(Queue* que) {
	if (que->numofdata == 0) {
		return 1;
	}

	else {
		if (que->numofdata==1) {
			que->front = NULL;
			que->rear = NULL;
			que->cur = NULL;
			(que->numofdata)--;
		}
		else {
			que->front = que->front->next;
			que->front->prev = NULL;
			que->cur = que->front;
			(que->numofdata)--;
		}
		return 0;
	}
}

int Rearremove(Queue* que) {
	if (que->numofdata == 0) {
		return 1;
	}

	else {
		if (que->numofdata==1) {
			que->front = NULL;
			que->rear = NULL;
			que->cur = NULL;
			(que->numofdata)--;
		}
		else {
			que->rear = que->rear->prev;
			que->rear->next = NULL;
			(que->numofdata)--;
			que->cur = que->front;
		}
		return 0;
	}
}

int main(void) {
	srand((unsigned)time(NULL));
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->front = NULL;
	que->rear = NULL;
	que->cur = NULL;
	que->numofdata = 0;

	for (int i = 1; i <= 10; i++) {
		int random = (rand() % 4) + 1;
		printf("%d 번째  %d\n", i,random);

		if (random == 1) {
			Frontinsert(que, i);
			printf("%d->       ", i);
			while (que->cur != NULL) {
				printf("%d  ",que->cur->data);
				que->cur = que->cur->next;
			}
			printf("\n");

		}

		if (random == 2) {
			Rearinsert(que, i);
			printf("<-%d      ", i);
			while (que->cur != NULL) {
				printf("%d  ", que->cur->data);
				que->cur = que->cur->next;
			}
			printf("\n");
		}
		
		if (random == 3) {
			if (Frontremove(que) == 1) {
				printf("ERROR");
				printf("\n");
			}
			else {
				if (que->cur== NULL) {
					printf("숫자가 없음");
				}
				else {
					while (que->cur != NULL) {
						printf("%d  ", que->cur->data);
						que->cur = que->cur->next;
					}
				}
				printf("\n");
			}
		}

		if (random == 4) {
			if (Rearremove(que) == 1) {
				printf("ERROR");
				printf("\n");
			}
			else {
				if (que->cur== NULL) {
					printf("숫자가 없음");
				}
				else {
					while (que->cur != NULL) {
						printf("%d  ", que->cur->data);
						que->cur = que->cur->next;
					}
				}
				printf("\n");
			}
		}
	}

	return 0;
}