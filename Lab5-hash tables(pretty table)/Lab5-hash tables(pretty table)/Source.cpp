/*
Author: Bianca Avram
Group: 30421
Problem: Hash tables

 The hash table is actually an array where the access to the elements is made using a function called hash function.
 In this exercise, I used quadratic probing, as the hash function is based on a 2nd degree polynomial that has i
 as the x.
 We denoted by alpha the load factor which is the ratio between the number of elements inserted in the hash table
 and the size of the table(which is prefered to be a prime number).
 The 2 operations performed on a hash table are insert and search.
 The insert function finds a convenient position for an element to be inserted using i as the variable of the
 second degree polynomial. This operation is repeated until a free cell is found in the array, otherwise
 we have hash table overflow, which means that there is no room for another element or a position for it cannot be found.
 The search operation is also based on the hash function which is calculated again and again until the desired
 element is found in the table.
 As complexity, both insert and search run the same.
 Inserting an element inthe hash table with load factor alpha requires at most 1/(1-alpha) probes on average.
 Finding an element in a hash table with load factor alpha requires at most (1/alpha)*ln(1/(1-alpha)).
*/

#include <iostream>
#include "Header.h"
#define SIZETEST 31 //size of the array used as a hash table in demo
#define SIZE 10007 //size of hash table in analysis
#define C1 7
#define C2 3 //constants used for the hash function
using namespace std;

int a[SIZE];
int aDemo[SIZETEST];
int trialf;
int trialnf;

void initializeToZero()
{
	for (int i = 0; i < SIZE; i++)
	{
		a[i] = 0;
	}
}

int hash1(int key)
{
	return key % SIZE;
}

int h(int key, int i)
{
	return (hash1(key) + C1 * i + C1 * i * i) % SIZE;
}

int hash1_demo(int key)
{
	return key % SIZETEST;
}

int h_demo(int key, int i)
{
	return (hash1_demo(key) + C1 * i + C1 * i * i) % SIZETEST;
}

int hash_insert(int key)
{
	int i = 0;
	while (i != SIZE)
	{
		int j = h(key, i);
		if (a[j] == 0)
		{
			a[j] = key;
			return j;
		}
		i++;
	}
	if (i >= SIZE)
	{
		cout << "Hash table overflow " << key << endl;
	}
}

int hash_search(int key)
{
	int i = 0;
	trialf = 1;
	trialnf = 1;
	int j = h(key, i);
	while (a[j] != 0 && i != SIZE)
	{
		if (a[j] == key)
			return j;
		trialf++;
		trialnf++;
		j = h(key, i);
		i++;
	}
	return -1;
}

int hash_insert_demo(int key, int* trial)
{
	int i = 0;
	while (i != SIZETEST)
	{
		int j = h_demo(key, i);
		if (aDemo[j] == 0)
		{
			aDemo[j] = key;
			*trial = i + 1;
			return j;
		}
		i++;
	}
	if (i == SIZETEST)
	{
		cout << "*Hash table overflow*" << endl;
		return -1;
	}
}

int hash_search_demo(int key, int* trial)
{
	int i = 0;
	int j = h_demo(key, i);
	while (aDemo[j] != 0 && i != SIZETEST)
	{
		(*trial)++;
		if (aDemo[j] == key)
			return j;
		j = h_demo(key, i);
		i++;
	}
	return -1;
}

void printArray(int* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%2d : %3d\n", i, a[i]);
	}
	cout << endl;
}

void hashDemo()
{
	cout << "========================================Demo========================================" << endl << endl;
	int x;
	cout << "Elements to be inserted:" << endl;
	int arr[] = { 15, 6, 21, 34, 85, 64, 12, 14, 8, 5, 7, 10, 17, 22, 49, 46, 55, 38, 40, 74, 1, 22, 16, 94, 108, 72, 86, 20, 30 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << endl;
	for (int i = 0; i < 29; i++)
	{
		int t;
		int p = hash_insert_demo(arr[i], &t);
		if (p != -1)
		{
			printf("Element %3d was inserted at position %3d in %3d", arr[i], p, t);
		}
		else
		{
			cout << "Could not insert element " << arr[i] << endl;
		}
		if (t == 1)
		{
			cout << " trial" << endl;
		}
		else
		{
			cout << " trials" << endl;
		}
	}

	cout << endl << "Hash table:" << endl;
	printArray(aDemo, SIZETEST);

	int el[] = { 30, 5, 17, 1, 31, 14, 25 };
	int i = 0;
	cout << endl << "===================================Given elements search===============================";
	while (i < sizeof(el) / sizeof(int))
	{
		int t = 0;
		cout << endl << "Search for emelent: " << el[i] << endl;
		int pos = hash_search_demo(el[i], &t);
		if (pos == -1)
		{
			printf("Element %3d not found\n", el[i]);
		}
		else
		{
			printf("Element %3d found at position %3d in %3d trial", el[i], pos, t);
			if (t != 1) cout << "s";
			cout << endl;
		}
		i++;
	}

	cout << endl << "===================================Non-uniform search===============================";
	for (int j = 0; j < 12; j++)
	{
		int t = 0;
		cout << endl << "Search for emelent: " << arr[j] << endl;
		int pos = hash_search_demo(arr[j], &t);
		if (pos == -1)
		{
			printf("Element %3d not found\n", arr[j]);
		}
		else
		{
			printf("Element %3d found at position %3d in %3d trial", arr[j], pos, t);
			if (t != 1) cout << "s";
			cout << endl;
		}
	}

	cout << endl << "=====================================Uniform search=================================";
	for (int j = 0; j < SIZETEST; j += 5)
	{
		int t = 0;
		cout << endl << "Search for emelent: " << arr[j] << endl;
		int pos = hash_search_demo(arr[j], &t);
		if (pos == -1)
		{
			printf("Element %3d not found\n", arr[j]);
		}
		else
		{
			printf("Element %3d found at position %3d in %3d trial", arr[j], pos, t);
			if (t != 1) cout << "s";
			cout << endl;
		}
	}

	cout << endl << "====================================================================================" << endl;
}

int* generateArrayToInsert(int size)
{
	int* a = (int*)malloc(sizeof(int) * size);
	FillRandomArray(a, size, 1, 20000, true, 0);
	return a;
}

int* generateElementsToBeFound(int m, int a[], int size)
{
	int* array = (int*)malloc(m * sizeof(int));
	int* index = (int*)malloc(m / 2 * sizeof(int));
	FillRandomArray(index, m / 2, 0, size - 1, true, 0);
	for (int i = 0; i < m / 2; i++)
	{
		array[i] = a[index[i]];
	}
	FillRandomArray(index, m / 2, 20001, 50000, true, 0);
	for (int i = m / 2; i < m; i++)
	{
		array[i] = index[m - i];
	}
	return array;
}

void generateTable()
{
	float alpha[5] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
	int m = 3000;

	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "|             |                  |                  |                      |                      |" << endl;
	cout << "| Load factor | Avg found effort | Max found effort | Avg not found effort | Max not found effort |" << endl;
	cout << "|             |                  |                  |                      |                      |" << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 5; i++)
	{
		int size = int(alpha[i] * float(SIZE));
		int* arr = generateArrayToInsert(size);
		for (int j = 0; j < size; j++)
		{
			hash_insert(arr[j]);
		}
		int* find = generateElementsToBeFound(m, arr, size);
		float maxf = 0; //max effort for found
		float maxnf = 0; //max effort not found
		float avgf = 0; //average effort found
		float avgnf = 0; //average effort not found

		for (int j = 0; j < m; j++)
		{
			trialf = 0; //effort for found
			trialnf = 0; //effort not found
			int f = hash_search(find[j]);
			if (f == -1)
			{
				avgnf += trialnf;
				if (trialnf > maxnf)
				{
					maxnf = trialnf;
				}
			}
			else
			{
				avgf += trialf;
				if (trialf > maxf)
				{
					maxf = trialf;
				}
			}
		}
		avgf /= m / 2;
		avgnf /= m / 2;

		cout << "|             |                  |                  |                      |                      |" << endl;
		printf("| %11g | %16g | %16g | %20g | %20g |\n", alpha[i], avgf, maxf, avgnf, maxnf);
		cout << "|             |                  |                  |                      |                      |" << endl;
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		initializeToZero();
	}
}

int main()
{
	int test;
	cout << "Input the test variable(0 for demo, 1 for table): ";
	cin >> test;
	if (test == 0)
	{
		hashDemo();
	}
	else
	{
		generateTable();
	}

	return 0;
}