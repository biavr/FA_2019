/*
Author: Bianca Avram
Group: 30421
Problem: Compare bottom up strategy for building a heap with the top down strategy

As we can notice in the graph, overall the bottom up strategy is more efficient, even if,
in what concerns the number of ... the top down strategy is better.

Bottom up:
-based on the heapify function which places each new node at its convenient position in the heap
-the complexity of heapify function is O(logn), which comes from the height of the tree
-for the fuction buildHeap, the heapify algorithm is used n/2 times so that the complexity
of this function is O(n), because a mathematical calculus we did at the course

Top down:
- is an iterative strategy which is composed of 3 function:
	-buildTopDown()
	-insertHeap()
	-increaseKey()
-I generated an array to store the initial values, then I use it to buld the new array that keeps the heap property 
at each insesrtion step
-as there are n elements that need to be inserted, we get a complexity of O(n)
-for each element, we have to find its proper place, so that consists in a coplexity of O(logn) which comes 
from the height of the tree.

As a conclusion, we get that the bottomm up strategy is more efficient, comparing O(n) and O(nlogn)
*/

#include <iostream>
#include "Profiler.h"
using namespace std;

Profiler profiler("Heap");

int cmpbu;
int assignbu;
int cmptd;
int assigntd;

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

int parent(int i)
{
	if (i % 2 == 0)
		return i / 2 - 1;
	else
		return i / 2;
}

void printArray(int* a, int size)
{
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
}

void heapify(int* a,int len, int i)
{
	//printArray(a, len);
	cmpbu += 3;
	int l = left(i);
	int r = right(i);
	int largest;
	if (l < len && a[l] > a [i])
		largest = l;
	else largest = i;
	if (r < len && a[r] > a[largest])
		largest = r;
	if (largest != i)
	{
		int aux = a[i];
		a[i] = a[largest];
		a[largest] = aux;
		assignbu += 3;

		heapify(a, len, largest);
	}
}

void buildHeap(int* a, int len)
{
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		heapify(a, len, i);
	}
}

void demoBuildHeap()
{
	int a[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	cout << "Initial array:" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl << "Demo bottom up:";
	buildHeap(a, 10);
	printArray(a, 10);
}

void heapsort(int* a,int len)
{
	buildHeap(a, len);
	int size = len;
	for (int i = len - 1; i >= 1; i--)
	{
		printArray(a, len);
		int aux = a[i];
		a[i] = a[0];
		a[0] = aux;
		size--;
		heapify(a, size, 0);
	}
}

void demoHeapsort()
{
	cout << "Demo heapsort:";
	int a[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	heapsort(a, 10);
	printArray(a, 10);
}

void increaseKey(int* a, int i, int key)
{
	a[i] = key;
	assigntd++;
	while (i >= 1 && a[parent(i)] < a[i])
	{
		cmptd++;
		int p = parent(i);
		int aux = a[p];
		a[p] = a[i];
		a[i] = aux;
		assigntd += 3;
		i = p;
	}
	cmptd++;
}

void heapInsert(int* a, int len, int key)
{
	a[len - 1] = -1;
	assigntd++;
	increaseKey(a, len - 1, key);
}

void buildTopDown(int* a, int* heap, int size)
{
	int n = 0;
	for (int i = 0; i < size; i++)
	{
		n++;
		heapInsert(heap, n, a[i]);
	}
}

void demoTopDown()
{
	cout << "Demo top down:";
	int d[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	int* a = (int *)malloc(10*sizeof(int));
	buildTopDown(d, a, 10);
	printArray(a, 10);
}

int* avgCase(int size)
{
	int* a = (int*)malloc(size * sizeof(int));
	FillRandomArray(a, size, 1, 10000, true, 0);
	return a;
}

int* duplicate(int* a,int size)
{
	int* b = (int *)malloc(size * sizeof(int));
	int i = 0;
	while (i < size)
	{
		b[i] = a[i];
		i++;
	}
	return b;
}

void generateAvgGraph()
{
	for (int size = 100; size <= 10000; size += 100)
	{
		assignbu = 0;
		cmpbu = 0;

		assigntd = 0;
		cmptd = 0;
		for (int j = 0; j < 5; j++)
		{
			int* a = avgCase(size);
			int* b = duplicate(a, size);
			int* heap = (int*)malloc(size*sizeof(int));
			buildHeap(a, size);
			buildTopDown(b, heap, size);
		}
		assignbu /= 5;
		cmpbu /= 5;
		assigntd /= 5;
		cmptd /= 5;

		/*profiler.countOperation("assignments_top_down", size, assigntd);
		profiler.countOperation("comparisons_top_down", size, cmptd);
		profiler.addSeries("operations_top_down", "assignments_top_down", "comparisons_top_down");

		profiler.countOperation("assignments_bottom_up", size, assignbu);
		profiler.countOperation("comparisons_bottom_up", size, cmpbu);
		profiler.addSeries("operations_bottom_up", "assignments_bottom_up", "comparisons_bottom_up");

		profiler.createGroup("assignments", "assignments_top_down", "assignments_bottom_up");
		profiler.createGroup("comparisons", "comparisons_top_down", "comparisons_bottom_up");
		profiler.createGroup("operations", "operations_top_down", "operations_bottom_up");*/
		profiler.countOperation("operations_top_down", size, cmptd + assigntd);
		profiler.countOperation("operations_bottom_up", size, cmpbu + assignbu);
		profiler.createGroup("operations","operations_top_down", "operations_bottom_up");

	}
}

int* worstCase(int size)
{
	int* a = (int*)malloc(size * sizeof(int));
	FillRandomArray(a, size, 1, 10000, true, 1);
	return a;
}

void generateWorstGraph()
{
	assignbu = 0;
	cmpbu = 0;
	assigntd = 0;
	cmptd = 0;

	profiler.reset();
	for (int size = 100; size <= 10000; size += 100)
	{
		int* a = worstCase(size);
		int* b = duplicate(a, size);
		int* heap = (int*)malloc(size * sizeof(int));
		buildHeap(a, size);
		buildTopDown(b, heap, size);

		profiler.countOperation("assignments_top_down", size, assigntd);
		profiler.countOperation("comparisons_top_down", size, cmptd);
		profiler.addSeries("operations_top_down", "assignments_top_down", "comparisons_top_down");

		profiler.countOperation("assignments_bottom_up", size, assignbu);
		profiler.countOperation("comparisons_bottom_up", size, cmpbu);
		profiler.addSeries("operations_bottom_up", "assignments_bottom_up", "comparisons_bottom_up");

		profiler.createGroup("assignments", "assignments_top_down", "assignments_bottom_up");
		profiler.createGroup("comparisons", "comparisons_top_down", "comparisons_bottom_up");
		profiler.createGroup("operations", "operations_top_down", "operations_bottom_up");
	}
}

int main()
{
	demoBuildHeap();
	cout << endl << endl;
	demoHeapsort();
	cout << endl << endl;
	demoTopDown();
	generateAvgGraph();
	generateWorstGraph();
	profiler.showReport();
}