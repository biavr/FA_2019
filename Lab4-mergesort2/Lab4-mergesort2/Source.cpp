/*
Author: Binaca Avram
Group: 30421
Problem: Merge sort on k arrays of length n

Describing the apprach:
->we create a list of lists which respects the principle of a min-heap;
->we create the output array that has the dimension n*k;
->everytime we select the smallest element and add it to the output list;
->this smallest element is the first element of the first list all the time(list[0]->first->key)
because of the heap properties;
->after extracting that element we remove it from that list and we call heapify to restore the heap;
->if the list is over (the element that was added was the last one in the list) we place infinity instead
and call heapify;
->this loop will be executed n*k times, for each element that needs to be placed in the output array;

Conclusions and efficiency:
->as known the heapify function takes O(logk) in this case
->as we call heapify n*k times in the main loop, we get the time complexity as O(nklogk) for this strategy

Observations:
->another solution was possible, implementing the heap as a separate array, but this method is more efficient,
as it does not use extra memory;
->the strategy that I used is way more convenient when we have arrays of different sizes

*/
#include <iostream>
#include "Header.h"
using namespace std;

Profiler profiler("mergesort");

int k; //nb of lists
int n; //nb of items in each list
int opK;

typedef struct node
{
	int key;
	struct node* next;
}NodeT;

typedef struct
{
	NodeT* first;
	int count;
}ListT;

NodeT* createNode(int key)
{
	NodeT* n = (NodeT*)malloc(sizeof(NodeT));
	n->key = key;
	n->next = NULL;
	return n;
}

ListT* createList()
{
	ListT* l = (ListT*)malloc(sizeof(ListT));
	l->count = 0;
	l->first = NULL;
	return l;
}

void addNode(ListT *l, int key)
{
	NodeT* nod = createNode(key);
	NodeT* p = l->first;
	if (p == NULL)
	{
		l->first = nod;
	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = nod;
	}
	l->count++;
}

void removeFirstNode(ListT* l)
{
	NodeT* nod = l->first;
	l->first = l->first->next;
	l->count--;
}

ListT* generateList(int n)
{
	ListT* l = createList();
	int* a = (int*)malloc(n * sizeof(int));
	FillRandomArray(a, n, 1, 20000, true, 1);
	for (int i = 0; i < n; i++)
	{
		addNode(l, a[i]);
	}
	return l;
}

ListT* generateListDemo(int n)
{
	ListT* l = createList();
	int* a = (int*)malloc(n * sizeof(int));
	FillRandomArray(a, n, 1, 50, true, 1);
	for (int i = 0; i < n; i++)
	{
		addNode(l, a[i]);
	}
	return l;
}

void printList(ListT* l)
{
	NodeT* nod = l->first;
	while (nod != NULL && nod->next != NULL)
	{
		cout << nod->key << ", ";
		nod = nod->next;
	}
	if (nod != NULL)
	{
		cout << nod->key;
	}
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void heapify(ListT** list, int k, int i)
{
	int l = left(i);
	int r = right(i);
	int smallest;
	opK += 3;
	if (l < k && list[l]->first->key < list[i]->first->key)
		smallest = l;
	else smallest = i;
	if (r < k && list[r]->first->key < list[smallest]->first->key)
		smallest = r;
	if (smallest != i)
	{
		swap(list[i], list[smallest]);
		opK += 3;
		heapify(list, k, smallest);
	}
}

void buildHeap(ListT** list, int k)
{
	for (int i = k / 2 - 1; i >= 0; i--)
	{
		heapify(list, k, i);
	}
}

ListT** createListOfLists(int k, int n)
{
	ListT** l = (ListT**)malloc(k * sizeof(ListT*));
	for (int i = 0; i < k; i++)
	{
		l[i] = (ListT*)malloc(n/k * sizeof(int));
		l[i] = generateList(n/k);
	}

	buildHeap(l, k);

	return l;
}

ListT** createListOfListsDemo(int k, int n)
{
	ListT** l = (ListT**)malloc(k * sizeof(ListT*));
	for (int i = 0; i < k; i++)
	{
		l[i] = (ListT*)malloc(n * sizeof(int));
		l[i] = generateListDemo(n);
		cout << "List " << i << ": ";
		printList(l[i]);
		cout << endl;
	}

	buildHeap(l, k);

	return l;
}

void printListOfLists(ListT** l, int k, int n)
{
	cout << "Current heap:" << endl;
	for (int i = 0; i < k ; i++)
	{
		cout << "List " << i <<": ";
		printList(l[i]);
		cout << endl;
	}
}

int extractMin(ListT** l, int k, int n)
{
	int min = l[0]->first->key;
	opK += 2;
	if (l[0]->first->next == NULL)
	{
		l[0]->first->key = INT_MAX;
		opK++;
	}
	else
	{
		removeFirstNode(l[0]);
		opK++;
	}
	heapify(l, k, 0);
	return min;
}

ListT* outputList(ListT** l, int k, int n)
{
	ListT* out = createList();
	for (int i = 0; i < n / k * k ; i++)
	{
		int val = extractMin(l, k, n/k);
		opK += 2;
		addNode(out, val);
	}
	return out;
}

ListT* outputListDemo(ListT** l, int k, int n)
{
	ListT* out = createList();
	cout << endl << endl;

	for (int i = 0; i < n * k; i++)
	{
		int val = extractMin(l, k, n);
		opK++;
		addNode(out, val);
		printListOfLists(l,k,n);
		cout << endl;
		cout << "Output list: ";
		printList(out);
		cout << endl << "***" <<endl;
	}
	return out;
}

int *mergesort2(ListT* l1, ListT* l2, int n)
{
	int* merge = (int*)malloc(n * sizeof(int));
	NodeT* p = l1->first;
	NodeT* q = l2->first;
	for (int i = 0; i < n * 2; i++)
	{
		if (p == NULL)
		{
			merge[i] = q->key;
			q = q->next;
		}
		else if(q == NULL)
		{
			merge[i] = p->key;
			p = p->next;
		}
		else
		{
			if (p->key < q->key)
			{
				merge[i] = p->key;
				p = p->next;
			}
			else
			{
				merge[i] = q->key;
				q = q->next;
			}
		}
	}
	return merge;
}

void test()
{
	cout << "******************************Demo mergesort******************************" << endl;
	ListT** l = createListOfListsDemo(4, 5);
	ListT* out = outputListDemo(l, 4, 5);
	//printList(out);
	cout << endl << "**************************************************************************" << endl;
}

void demoMerge2()
{
	cout << endl << "************************Demo mergesort for 2 lists************************" << endl;
	ListT* l1 = generateListDemo(4);
	printList(l1);
	cout << endl;
	ListT* l2 = generateListDemo(4);
	printList(l2);
	int* a = mergesort2(l1, l2, 4);
	cout << endl << "Sorted list: " ;
	for (int i = 0; i < 8; i++)
	{
		cout << a[i] << " ";
	}
	cout<< endl << "**************************************************************************";
	return;
}

void generateGraphKFixed()
{
	k = 5;
	for (int n = 100; n <= 5000; n+=100)
	{
		opK = 0;
		for (int j = 0; j < 5; j++)
		{
			ListT** list = createListOfLists(k, n);
			ListT* out = outputList(list, k, n);
		}
		opK /= 5;
		profiler.countOperation("k_fixed_operations_k_5", n, opK);
	}


	k = 10;
	for (int n = 100; n <= 5000; n+=100)
	{
		opK = 0;
		for (int j = 0; j < 5; j++)
		{
			ListT** list = createListOfLists(k, n);
			ListT* out = outputList(list, k, n);
		}
		opK /= 5;
		profiler.countOperation("k_fixed_operations_k_10", n, opK);
	}

	k = 100;
	for (int n = 100; n <= 5000; n+=100)
	{
		opK = 0;
		for (int j = 0; j < 5; j++)
		{
			ListT** list = createListOfLists(k, n);
			ListT* out = outputList(list, k, n);
		}
		opK /= 5;
		profiler.countOperation("k_fixed_operations_k_100", n, opK);
	}
	profiler.createGroup("k_fixed_operations", "k_fixed_operations_k_5", "k_fixed_operations_k_10", "k_fixed_operations_k_100");
	
}

void generateGraphNFixed()
{
	n = 10000;
	for (k = 10; k <= 500; k += 10)
	{
		opK = 0;
		for (int j = 0; j < 5; j++)
		{
			ListT** list = createListOfLists(k, n);
			ListT* out = outputList(list, k, n);
		}
		opK /= 5;
		profiler.countOperation("n_5000_fixed_opreations", k, opK);
	}
	profiler.createGroup("n_fixed_operations", "n_5000_fixed_operations_k=5");
}

int main()
{
	int testVariable;
	cout << "Enter the test variable(0 for demos, 1 for graphs): ";
	cin >> testVariable;
	if (testVariable == 0)
	{
		test();
		demoMerge2();
	}
	else
	{
		profiler.reset();
		generateGraphKFixed();
		generateGraphNFixed();
		profiler.showReport();
	}
	return 0;
}