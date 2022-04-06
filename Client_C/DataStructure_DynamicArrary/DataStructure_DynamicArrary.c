#include <stdio.h>
#include <stdlib.h>

void Add(int item);
int Remove(int item), RemoveAt(int index);
void Clear();

const int DEFAULT_SIZE = 1;
int* data;
int count;
int capacity;
int* tmp;

int main() {

	Add(1);
	Add(3);
	Add(5);
	Add(5);
	Add(5);
	printf("%d\n", count);

	return 0;
}

void Add(int item)
{
	if (count == 0) {
		data = (int*)malloc(DEFAULT_SIZE * sizeof(int));
	}
	else if (count >= capacity) {
		tmp = (int*)malloc(count * 2 * sizeof(int));
		for (int i = 0; i < count; i++)
			tmp[i] = data[i];
		free(data);
		data = (int*)malloc(count * 2 * sizeof(int));
		for (int i = 0; i < count; i++)
			data[i] = tmp[i];
		free(tmp);
	}

	data[count] = item;
	capacity = sizeof(data) / sizeof(int);
	count++;
}
