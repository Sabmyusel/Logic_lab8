#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <queue>

struct node
{
	int inf;  // полезная информация
	struct node* next; // ссылка на следующий элемент 
};

struct node* Qhead = NULL, * Qlast = NULL;
int** G;
/* Последовательное добавление в очередь элемента (в конец)*/
void queue_push(int inf)
{
	struct node* p = NULL;
	p = (node*)malloc(sizeof(struct node));

	p->next = NULL;
	p->inf = inf;

	if (Qhead == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		Qhead = p;
		Qlast = p;
	}
	else if (Qhead != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		p->next = Qhead;
		Qhead = p;
	}
	return;
}

/* Последовательное удаление из очереди (из начала)*/
int queue_pop() {
	struct node* sch = Qhead;
	int r = 0;

	if (sch != Qlast) {
		while (sch->next != Qlast) {
			sch = sch->next;
		}
		r = Qlast->inf;
		free(Qlast);
		Qlast = sch;
		sch->next = NULL;
	}
	else {
		r = Qlast->inf;
		free(Qhead);
		Qhead = NULL;
		Qlast = NULL;
	}

	return r;
}

bool queue_len() {
	struct node* sch = Qhead;
	if (sch == NULL)
		return false;
	else
		return true;
}

int** gen(int size) {
	int temp = 0;
	int** arr;
	arr = new int* [size];
	for (int i = 0; i < size; i++)
		arr[i] = new int[size] {0};

	srand(time(NULL));

	for (int i = 0; i < size; i++)
		for (int k = i + 1; k < size; k++) {
			temp = rand() % 2;
			//if(temp == 1)
			//	temp = rand() % 2;
			arr[i][k] = temp;
			arr[k][i] = temp;
		}
	return arr;
}

void print(int** graph, int size) {

	printf("   ");
	for (int i = 0; i < size; i++)
		printf(" %d ", i + 1);

	printf("\n    ");
	for (int i = 0; i < size; i++)
		printf("-- ");

	for (int i = 0; i < size; i++) {
		printf("\n %d | ", i + 1);
		for (int k = 0; k < size; k++) {
			printf("%d  ", graph[i][k]);
		}
	}
}

void BFS(int v, bool* num, int size) {
	
	clock_t t1, t2;
	t1 = clock();

	queue_push(v);

	while (queue_len()) {
		v = queue_pop();
		if (num[v] == false) {
			num[v] = true;
			printf("%d  ", v + 1);
			for (int i = 0; i < size; i++)
				if (G[v][i] == 1 && num[i] == false)
					queue_push(i);
		}
	}
	t2 = clock();
	double seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("\nВремя: %0.3f\n", seconds);
}

void BFS2(int v, bool* num, int size, std::queue<int> Q) {

	clock_t t1, t2;
	t1 = clock();

	Q.push(v);

	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		if (num[v] == false) {
			num[v] = true;
			printf("%d  ", v + 1);
			for (int i = 0; i < size; i++)
				if (G[v][i] == 1 && num[i] == false)
					Q.push(i);
		}
	}
	t2 = clock();
	double seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("\nВремя(класс queue): %0.3f\n", seconds);
}

void InDep(int size, int type, std::queue<int> Q, int v) {

	bool* num = new bool[size] {false};

	if(type == 1)
		BFS(v, num, size);
	if(type == 2)
		BFS2(v, num, size, Q);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size = 0;
	int num = 0;
	std::queue<int> Q;
	while (1) {
		printf("Введите кол-во вершин графа: ");
		scanf("%d", &size);
		G = gen(size);
		print(G, size);

		printf("\n\n");
		printf("Обход: \n");
		InDep(size, 1, Q, num);

		printf("\n\n");
		printf("Обход (класс queue): \n");
		InDep(size, 2, Q, num);
		printf("\n\n");

		system("pause");
		system("cls");
	}
	return 0;
}