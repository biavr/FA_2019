#include <iostream>
#include "profiler.h"
#define AVG_BUBBLE_COMP "average_bubble_comp"
#define AVG_BUBBLE_ASSIGN "average_bubble_assignments"
#define AVG_BUBBLE_OP "average_bubble_operations"

#define BEST_BUBBLE_COMP "best_bubble_comp"
#define BEST_BUBBLE_ASSIGN "best_bubble_assignments"
#define BEST_BUBBLE_OP "best_bubble_operations"

#define WORST_BUBBLE_COMP "worst_bubble_comp"
#define WORST_BUBBLE_ASSIGN "worst_bubble_assignments"
#define WORST_BUBBLE_OP "worst_bubble_operations"

#define AVG_INSERTION_COMP "average_insertion_comp"
#define AVG_INSERTION_ASSIGN "average_insertion_assignments"
#define AVG_INSERTION_OP "average_insertion_operations"

#define BEST_INSERTION_COMP "best_insertion_comp"
#define BEST_INSERTION_ASSIGN "best_insertion_assignments"
#define BEST_INSERTION_OP "best_insertion_operations"

#define WORST_INSERTION_COMP "worst_insertion_comp"
#define WORST_INSERTION_ASSIGN "worst_insertion_assignments"
#define WORST_INSERTION_OP "worst_insertion_operations"

#define AVG_SELECTION_COMP "average_selection_comp"
#define AVG_SELECTION_ASSIGN "average_selection_assignments"
#define AVG_SELECTION_OP "average_selection_operations"

#define BEST_SELECTION_COMP "best_selection_comp"
#define BEST_SELECTION_ASSIGN "best_selection_assignments"
#define BEST_SELECTION_OP "best_selection_operations"

#define WORST_SELECTION_COMP "worst_selection_comp"
#define WORST_SELECTION_ASSIGN "worst_selection_assignments"
#define WORST_SELECTION_OP "worst_selection_operations"

using namespace std;

Profiler profiler("Sort");
int assign;
int comp;

void swap(int* a, int* b)
{
	//this function interchanges the values for a and b
	int aux = *a;
	*a = *b;
	*b = aux;
}

void print_array(int size, int v[])
{
	for (int i = 0; i < size; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void bubbleSort(int* a, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			comp++;
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
				assign += 3;
			}
		}
		//print_array(n, a);
	}
}

void insertionSort(int* a, int n)
{
	int i, j;
	int piv;
	for (i = 1; i < n; i++)
	{
		piv = a[i];
		assign++;
		j = i - 1;
		comp++;
		while ((j >= 0) && (piv < a[j]))
		{
			assign++;
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = piv;
		assign++;
		
		//print_array(n, a);
	}
}

void selectionSort(int* a, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		int index = i + 1;
		for (j = i + 2; j < n; j++)
		{
			comp++;
			if (a[index] < a[j])
			{
				index = j;
			}
		}
		comp++;
		if (a[i] < a[index])
		{
			swap(&a[i + 1], &a[index]);
			assign += 3;
		}
		else
		{
			swap(&a[i], &a[index]);
			assign += 3;
		}
	}
}

void demoInsertion()
{
	cout << endl << "Demo insertion" << endl;
	int a[10] = { 3, 15, 11, 2 ,12, 5, 0, 4, 8, 10};
	insertionSort(a, 10);
}

int* generateAverageCase(int n)
{
	int* a = (int*)malloc(n * sizeof(int));
	FillRandomArray(a, n);//, 1, n, true, 0);
	return a;
}

int* generateBestCase(int n)
{
	int* a = (int*)malloc(n * sizeof(int));
	FillRandomArray(a, n, 1, 10000, true, 1);
	return a;
}

int* generateWorstCase(int n)
{
	int* a = (int*)malloc(n * sizeof(int));
	FillRandomArray(a, n, 1, 10000, true, 2);
	return a;
}

void generateBubbleGraph()
{
	for (int size = 0; size < 10001; size += 100)
	{
		assign = 0;
		comp = 0;
		int* a = generateAverageCase(size);
		bubbleSort(a, size);
		profiler.countOperation(AVG_BUBBLE_COMP, size, comp);
		profiler.countOperation(AVG_BUBBLE_ASSIGN, size, assign);
		profiler.addSeries(AVG_BUBBLE_OP, AVG_BUBBLE_ASSIGN, AVG_BUBBLE_COMP);

		assign = 0;
		comp = 0;
		a = generateBestCase(size);
		bubbleSort(a, size);
		profiler.countOperation(BEST_BUBBLE_COMP, size, comp);
		profiler.countOperation(BEST_BUBBLE_ASSIGN, size, assign);
		profiler.addSeries(BEST_BUBBLE_OP, AVG_BUBBLE_ASSIGN, AVG_BUBBLE_COMP);

		assign = 0;
		comp = 0;
		a = generateWorstCase(size);
		bubbleSort(a, size);
		profiler.countOperation(WORST_BUBBLE_COMP, size, comp);
		profiler.countOperation(WORST_BUBBLE_ASSIGN, size, assign);
		profiler.addSeries(WORST_BUBBLE_OP, WORST_BUBBLE_ASSIGN, WORST_BUBBLE_COMP);
		free(a);

	}
}

void generateInsertionGraph()
{
	for (int size = 0; size < 10001; size += 100)
	{
		assign = 0;
		comp = 0;
		int* a = generateAverageCase(size);
		insertionSort(a, size);
		profiler.countOperation(AVG_INSERTION_COMP, size, comp);
		profiler.countOperation(AVG_INSERTION_ASSIGN, size, assign);
		profiler.addSeries(AVG_INSERTION_OP, AVG_INSERTION_ASSIGN, AVG_INSERTION_COMP);

		assign = 0;
		comp = 0;
		a = generateBestCase(size);
		insertionSort(a, size);
		profiler.countOperation(BEST_INSERTION_COMP, size, comp);
		profiler.countOperation(BEST_INSERTION_ASSIGN, size, assign);
		profiler.addSeries(BEST_INSERTION_OP, AVG_INSERTION_ASSIGN, AVG_INSERTION_COMP);

		assign = 0;
		comp = 0;
		a = generateWorstCase(size);
		insertionSort(a, size);
		profiler.countOperation(WORST_INSERTION_COMP, size, comp);
		profiler.countOperation(WORST_INSERTION_ASSIGN, size, assign);
		profiler.addSeries(WORST_INSERTION_OP, WORST_INSERTION_ASSIGN, WORST_INSERTION_COMP);
		free(a);
	}
}

void generateSelectionGraph()
{
	for (int size = 0; size < 10001; size += 100)
	{
		assign = 0;
		comp = 0;
		int* a = generateAverageCase(size);
		selectionSort(a, size);
		profiler.countOperation(AVG_SELECTION_COMP, size, comp);
		profiler.countOperation(AVG_SELECTION_ASSIGN, size, assign);
		profiler.addSeries(AVG_SELECTION_OP, AVG_SELECTION_ASSIGN, AVG_SELECTION_COMP);

		assign = 0;
		comp = 0;
		a = generateBestCase(size);
		selectionSort(a, size);
		profiler.countOperation(BEST_SELECTION_COMP, size, comp);
		profiler.countOperation(BEST_SELECTION_ASSIGN, size, assign);
		profiler.addSeries(BEST_SELECTION_OP, AVG_SELECTION_ASSIGN, AVG_SELECTION_COMP);

		assign = 0;
		comp = 0;
		a = generateWorstCase(size);
		selectionSort(a, size);
		profiler.countOperation(WORST_SELECTION_COMP, size, comp);
		profiler.countOperation(WORST_SELECTION_ASSIGN, size, assign);
		profiler.addSeries(WORST_SELECTION_OP, WORST_SELECTION_ASSIGN, WORST_SELECTION_COMP);
		free(a);
	}
}

int main()
{
	//demoInsertion();
	generateBubbleGraph();
	generateInsertionGraph();
	generateSelectionGraph();
	//average case
	profiler.createGroup("average_assignments", AVG_BUBBLE_ASSIGN, AVG_INSERTION_ASSIGN, AVG_SELECTION_ASSIGN);
	profiler.createGroup("average_comparisons", AVG_BUBBLE_COMP, AVG_INSERTION_COMP, AVG_SELECTION_COMP);
	profiler.createGroup("average_operations", AVG_BUBBLE_OP, AVG_INSERTION_OP, AVG_SELECTION_OP);
	//best case
	profiler.createGroup("best_assignments", BEST_BUBBLE_ASSIGN, BEST_INSERTION_ASSIGN, BEST_SELECTION_ASSIGN);
	profiler.createGroup("best_comparisons", BEST_BUBBLE_COMP, BEST_INSERTION_COMP, BEST_SELECTION_COMP);
	profiler.createGroup("best_operations", BEST_BUBBLE_OP, BEST_INSERTION_OP, BEST_SELECTION_OP);
	//worst case
	profiler.createGroup("worst_assignments", WORST_BUBBLE_ASSIGN, WORST_INSERTION_ASSIGN, WORST_SELECTION_ASSIGN);
	profiler.createGroup("worst_comparisons", WORST_BUBBLE_COMP, WORST_INSERTION_COMP, WORST_SELECTION_COMP);
	profiler.createGroup("worst_operations", WORST_BUBBLE_OP, WORST_INSERTION_OP, WORST_SELECTION_OP);
	profiler.showReport();
}