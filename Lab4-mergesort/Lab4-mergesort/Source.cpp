#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "list_op.h"
#include "profiler.h"
using namespace std;

int n; //number of elements of a list
int k; //number of lists

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void printlist(ListT* l[])
{
	for (int i = 0; i < k; i++)
	{
		NodeT* n = l[i]->first;
		while (n->next != NULL)
		{
			cout << n->key << " ";
			n = n->next;
		}
		cout << n->key;
		cout << endl;
	}

}

void interchange(ListT *l[],int i, int j)
{
	NodeT* aux;
	aux = l[i]->first;
	l[i]->first = l[j]->first;
	l[j]->first = aux;
}


void heapify(ListT* list[], int i)
{
	int r = right(i);
	int l = left(i);
	int smallest;
	if (l < k && list[l]->first->key < list[i]->first->key)
	{
		smallest = l;
	}
	if (r < k && list[smallest]->first->key > list[r]->first->key)
	{
		smallest = r;
	}
	if (smallest != i)
	{
		//swap(list[i], list[smallest]);
		//cout << "fac "<<list[smallest]->first->key<<" "<<list[i]->first->key << endl;
		interchange(list, i, smallest);
		printlist(list);
		cout << endl;
		heapify(list, smallest);
	}
}



void buildHeap(ListT *l[])
{
	for (int i = k / 2 - 1; i >= 0; i--)
	{
		heapify(l, i);
	}
	printlist(l);
	cout << endl;
}


int extractMin(ListT* l[])
{
	//size is number of lists
	int min = l[0]->first->key;
	NodeT* n = l[0]->first;
	if (n->next == NULL)
	{
		l[0]->first->key = INT_MAX;
	}
	else
	{
		l[0]->first = l[0]->first->next;
		free(n);
	}
	heapify(l, 0);

	return min;

}

ListT* mergesort(ListT* l[])
{
	ListT* out = createList();
	while ((l[0]->first->key != INT_MAX))
	{
		int m = extractMin(l);
		insertAtRear(out, m);
	}
	return out;
}

void showList(ListT* l)
{
	NodeT* nod = l->first;
	while (nod != NULL)
	{
		cout << nod->key << " ";
		nod = nod->next;
	}
}

void demoMergesort2Arrays()
{
	n = 5;
	k = 2;
	ListT* list[2];
	ListT* l1 = generateList(5);
	list[0] = l1;
	//showList(list[0]);
	//cout << endl;
	ListT* l2 = generateList(5);
	
	list[1] = l2;
	//showList(list[1]);
	//cout << endl;
	printlist(list);
	cout << endl;
	ListT* out = mergesort(list);
	cout << "Sorted list:" << endl;
	showList(out);
}

int main()
{
	demoMergesort2Arrays();
}