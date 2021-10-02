#include <iostream>
#include "list_op.h"
#include "profiler.h"
using namespace std;

ListT* createList()
{
	ListT* L = (ListT*)malloc(sizeof(ListT));
	L->first = L->last = NULL;
	L->count = 0;
	return L;
}

NodeT* createNode(int key)
{
	NodeT* n = (NodeT*)malloc(sizeof(NodeT));
	n->key = key;
	n->next = NULL;
	return n;
}

void insertAtRear(ListT* l, int key)
{
	NodeT* node = createNode(key);
	if (l->first == NULL)
	{
		l->first = node;
		l->last = node;
	}
	else
	{
		l->last->next = node;
		l->last = node;
	}
	l->count++;
}

ListT* generateList(int size)
{
	ListT* l = createList();
	int* a = (int*)malloc(size * sizeof(int));
	FillRandomArray(a, size, 1, 20, true, 1);
	for (int i = 0; i < size; i++)
	{
		insertAtRear(l, a[i]);
	}
	return l;
}

void deletFromFront(ListT* l)
{
	NodeT* n = l->first;
	l->first = l->first->next;
	free(n);
}