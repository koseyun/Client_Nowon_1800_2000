#include <stdio.h>
#include <stdlib.h>

void Add(int, int), ShowAll();


typedef struct _Node {
	int id;
	int value;
	struct _Node* next;
} Node;

Node* head,* tail,* tmp, * tmp2;

void Add(int in_id, int in_value) {
	tmp = (Node*)malloc(sizeof(Node));
	if (head == NULL)
		head = tmp;
	else
		tail->next = tmp;

	tmp->id = in_id;
	tmp->value = in_value;
	tmp->next = NULL;
	tail = tmp;
}

void AddFirst(int in_id, int in_value) {
	tmp = (Node*)malloc(sizeof(Node));
	if (head == NULL) {
		head = tmp;
		tail = head;
	}
	else
		tmp->next = head;

	tmp->id = in_id;
	tmp->value = in_value;
	head = tmp;
}

void AddAfter(int target_id, int in_id, int in_value) {
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->id == target_id) {
			tmp2 = (Node*)malloc(sizeof(Node));
			
			tmp2->next = tmp->next;
			tmp->next = tmp2;
			tmp2->id = in_id;
			tmp2->value = in_value;
			return;
		}
		tmp = tmp->next;
	}
	return;
}

int GetFirst() {
	if (head == NULL)
		return -1;
	else
		return head->value;
}

int GetLast() {
	if (tail == NULL)
		return -1;
	else
		return tail->value;
}

int Remove(int target_id) {

	int isRemoved = 0;
	tmp = head;

	if (tmp != NULL) {

		if (head->id == target_id)
		{
			tmp = head;
			head = tmp->next;
			free(tmp);
			isRemoved = 1;
		}


		while (tmp->next != NULL)
		{
			if (tmp->next->id = target_id) {
				tmp2 = tmp->next->next;
				free(tmp->next);
				isRemoved = 1;
				tmp->next = tmp2;

				if (tmp->next->next == NULL)
					tail = tmp->next;
				break;
			}
			else
				tmp = tmp->next;
		}
	}

	return isRemoved;
	
}

void ShowAll() {
	tmp = head;
	printf("(id, value) : ");
	while (tmp != NULL)
	{
		printf("(%d, %d)", tmp->id, tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

int main() {
	
	Add(1,3);
	Add(3,25);
	Add(6,35);
	Add(21,4);
	AddAfter(21, 33, 33);
	ShowAll();

	return 0;
}