/*
Author: Bianca Avram
Group: 30421

As expected, quicksort is a more efficient strategy. Both of them run in O(nlogn) in the average case.
The aspect that makes the difference is that quicksort doesn't do swaps, because they are not necessary. 
Heapsort does a lot of swaps, while at quicksort they are almost unecessary. Swaps are time consuming.

-> Heapsort is based on the function heapify which starts from the premise that we have 2 heaps
and we have to add another element by comparing it with the roots of the 2 heaps then deciding where is the
proper place to fix the new item.

-> Quicksort is a divide et impera strategy that partitions the given array into 2 parts following the rule:
on the right all the elements must be greater or equal the the chosen pivot and on the left
all the elements must be smaller than the pivot (the equal part can be in any part of the patition)

->When comparing these 2, we can notice that heapsort does not act differently depending on the case.
No matter the input array, the algorithm will always run in O(nlogn).
When it comes to quicksort, on the worst case, which is when the array is already sorted or sorted 
decreasingly, we can remark that the complexity goes right to O(n^2). That makes it as bad as
bubbleSort on this case

->Regarding the quickSelect (or randomizedSelect, as I named it) strategy that is ment to improve 
partitioning for quicksort, we can be ensured that each time we pick as pivot the element that 
has a median value, such that, when wepartition the array, we get 2 parts of equal lengths. 
The principle is the same, we just modifythe way we choose the pivot in order to avoid the 
occurence of the worst case when the lenghts ofthe parts resulted from the partition are visibly 
different (for example, when one part has 1 element and the other one all the other elements that remain).

->As a conclusion, we are recommended to use quicksort when we are almost convinced that the
array is in total disorder, because here, the best case is just the same as the average case
*/
#include <iostream>
#include <cstdlib> 
#include <time.h>
#include "Header.h"
using namespace std;

Profiler profiler("quickVSheap");

int opHeap;
int opQuick;
int opRQuick;

void printArray(int* a, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

int partition(int* a, int p, int r)
{
	int x = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		opQuick++;
		if (a[j] <= x)
		{
			i++;
			int aux = a[i];
			a[i] = a[j];
			a[j] = aux;
			opQuick += 3;
		}
	}
	int aux = a[i+1];
	a[i+1] = a[r];
	a[r] = aux;
	opQuick += 3;
	return i + 1;
}

void quicksort(int* a, int p, int r)
{
	if (p < r)
	{
		int q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}

void quicksortdemo(int* a, int p, int r)
{
	if (p < r)
	{
		int q = partition(a, p, r);
		printf("In the ordered array the pivot %d is on position %d\n", a[q], q);
		quicksortdemo(a, p, q - 1);
		quicksortdemo(a, q + 1, r);
	}
}

void demoQuicksort(int *a,int size)
{
	cout << "+++++++++++++++++++++Demo quicksort++++++++++++++++++++++" << endl << endl;
	cout << "Initial array:" << endl;
	printArray(a, size);
	cout << endl;
	quicksortdemo(a, 0, size-1);
	cout << endl;
	cout << endl << "Sorted array :" << endl;
	printArray(a, size);
	cout << endl;
}

int random(int p, int r)
{
	srand(time(NULL));
	int random = p + rand() % (r - p);
	return random;
}

int randomizedPartition(int* a, int p, int r)
{
	int i = random(p, r);
	int aux = a[r];
	a[r] = a[i];
	a[i] = aux;
	opRQuick += 3;
	return partition(a, p, r);
}

int quickSelect(int* a, int p, int r, int i)
{
	if (p == r)
		return a[p];
	int q = randomizedPartition(a, p, r);
	int k = q - p + 1;
	if (i == k)
		return a[q];
	else
	{
		if (i < k)
		{
			return quickSelect(a, p, q - 1, i);
		} 
		else
		{
			return quickSelect(a, q + 1, r, i - k);
		}
	}
}

void demoQuickSelect()
{	
	cout << "*****************Demo quickSelect*****************";
	int size = 10;
	int i = 5;
	int a[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	cout << endl << "Initial array: ";
	printArray(a, 10);
	int q = quickSelect(a, 0, size - 1, i);
	printf("\nIn the ordered array, the %dth smallest element is: %d\n", i, q);
	cout << "**************************************************" << endl;
}

void randomizedQuicksort(int* a, int p, int r)
{
	//opRQuick++;
	if (p < r)
	{
		int q = randomizedPartition(a, p, r);
		printf("In the ordered array the pivot %d is on position %d\n", a[q], q);
		randomizedQuicksort(a, p, q - 1);
		randomizedQuicksort(a, q + 1, r);
	}
}

void demoRandomizedQuicksort(int *a, int size)
{
	cout << "++++++++++++++++++++Demo randomizedQuicksort+++++++++++++++++++++" << endl << endl;
	cout << "Initial array:" << endl;
	printArray(a, size);
	cout << endl;
	randomizedQuicksort(a, 0, size-1);
	cout << endl << "Sorted array:" << endl;
	printArray(a, size);
	cout << endl;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void heapify(int* a, int len, int i)
{
	//printArray(a, len);
	int l = left(i);
	int r = right(i);
	int largest;
	opHeap += 2;
	if (l < len && a[l] > a[i])
		largest = l;
	else largest = i;
	if (r < len && a[r] > a[largest])
		largest = r;
	if (largest != i)
	{
		int aux = a[i];
		a[i] = a[largest];
		a[largest] = aux;
		opHeap += 3;
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

void heapsort(int* a, int len)
{
	buildHeap(a, len);
	int size = len;
	for (int i = len - 1; i >= 1; i--)
	{
		//printArray(a, len);
		int aux = a[i];
		a[i] = a[0];
		a[0] = aux;
		size--;
		opHeap += 3;
		heapify(a, size, 0);
	}
}

void heapsortdemo(int* a, int len)
{
	buildHeap(a, len);
	int size = len;
	for (int i = len - 1; i >= 1; i--)
	{
		cout << "Step " << len - i << ": ";
		printArray(a, len);
		int aux = a[i];
		a[i] = a[0];
		a[0] = aux;
		size--;
		heapify(a, size, 0);
	}
}

void demoHeapsort(int *a,int size)
{	
	cout << "++++++++++++++Demo heapsort++++++++++++++++" << endl << endl;
	cout << "Initial array: ";
	printArray(a, size);
	cout << endl;
	heapsortdemo(a, size);
	cout << "Sorted array: ";
	printArray(a, size);
}

int* generateAvgArray(int size)
{
	int* a = (int *)malloc(size * sizeof(int));
	FillRandomArray(a, size, 1, 10000, true, 0);
	return a;
}

void duplicate(int* src, int* dest, int size)
{
	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

void generateAvgGraph()
{
	for (int size = 100; size < 10001; size += 100)
	{
		opHeap = 0;
		opQuick = 0;
		//opRQuick = 0;
		for (int i = 0; i < 5; i++)
		{
			int* a = generateAvgArray(size);
			int* b = (int*)malloc(size * sizeof(int));
			//int* c = (int*)malloc(size * sizeof(int));
			duplicate(a, b, size);
			//duplicate(a, c, size);
			heapsort(a, size);
			quicksort(b, 0, size - 1);
			//randomizedQuicksort(c, 0, size - 1);
		}
		opHeap /= 5;
		opQuick /= 5;
		//opRQuick /= 5;
		
		profiler.countOperation("avg_heapsort", size, opHeap);
		profiler.countOperation("avg_quicksort", size, opQuick);
		//profiler.countOperation("avg_randomizedQuicksort", size, opRQuick);
		profiler.createGroup("avg_operations", "avg_heapsort", "avg_quicksort");
	}
}

int* generateBestArray(int size)
{
	int* a = (int*)malloc(size * sizeof(int));
	FillRandomArray(a, size, 1, 10000, true, 0);
	return a;
}

void generateBestGraph()
{
	for (int size = 100; size < 10001; size += 100)
	{
		opQuick = 0;

		int* a = generateBestArray(size);
		quicksort(a, 0, size - 1);

		profiler.countOperation("best_quicksort", size, opQuick);
		profiler.createGroup("best_operations", "best_quicksort");

	}
}

int* generateWorstArray(int size)
{
	int* a = (int*)malloc(size * sizeof(int));
	FillRandomArray(a, size, 1, 10000, true, 2);
	return a;
}

void generateWorstGraph()
{
	for (int size = 100; size < 10001; size +=100)
	{
		opQuick = 0;

		int* a = generateWorstArray(size);
		quicksort(a, 0, size - 1);

		profiler.countOperation("worst_quicksort", size, opQuick);
		profiler.createGroup("worst_operations", "worst_quicksort");

	}
}

int main()
{
	int test;
	cout << "test(0 for demo, 1 for graphs) = ";
	cin >> test;
	if (test == 0)
	{
		int a[14] = { 27, 17, 3, 16, 13, 10, 1, 5, 4, 12, 4, 8, 9, 0 };
		cout << endl;
		demoQuicksort(a,14);
		cout << endl;
		demoRandomizedQuicksort(a,14);
		cout << endl;
		demoQuickSelect();
		cout << endl;
		demoHeapsort(a,14);
	}
	else if (test == 1)
	{
		generateAvgGraph();
		generateBestGraph();
		generateWorstGraph();
		profiler.showReport();
	}
	else
		cout << "Invalid test input";
}