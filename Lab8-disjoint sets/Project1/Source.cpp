/*
Author: Bianca Avram
Group: 30421
Problem: Disjoint sets and Kruskal algorithm

I defined a struct for a node, which contains the key, the rank and a pionter to its representative.
For an edge, I have another struct that contains the 2 vertices and the weight. 

As total complexity, Kruskal algorithm runs in O(mlogn), where m is the number of all the edges of the graph and n is the number of vertices.
The most challenging task for this lab was not implementing the given operations, but generating a connected graph.
->first, I created the first n edges and at each step I added a node which I linked to one of the nodes which were already added
->like this, I created a connected component
->then, all I did was to add edges using srand() function, but I checked every time that the edge was not added before
->I did this by holding an adjacency matrix 

The set of nodes contains all the numbers from 1 to n, sorted, then it is transformed in a proper set of nodes, where each node
has as representative the node itself.

The make_set operation takes O(1)
The find_set operation takes O(logn)
The union operation takes O(logn)

Kruskal algorithm takes O(mlogn)
m comes from the for that goes through the whole set of edges
n comes from the union operations that are executed
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Header.h"
using namespace std;

Profiler profiler("Disjoint sets");
int assign;
int comp;

typedef struct node
{
	int key;
	int rank;
	node* rep;
}SetT;

typedef struct
{
	int x;
	int y;
	int w;
}EdgeT;

SetT* make_set(int x)
{
	SetT* p = (SetT*)malloc(sizeof(SetT));
	p->key = x;
	p->rank = 0;
	p->rep = p;
	assign += 3;
	return p;
}

SetT* find_node(int x, SetT** set, int n)
{
	//sequential search in an array
	for (int i = 0; i < n; i++)
	{
		//comp++;
		if (set[i]->key == x)
			return set[i];
	}
	return NULL;
}

SetT* find_set(SetT* x)
{
	if (x == NULL)
		return NULL;
	comp++;
	if (x->rep != x)
	{
		assign++;
		x->rep = find_set(x->rep);
	}
	return x->rep;
}

SetT* unifyDemo(SetT* x, SetT* y)
{
	SetT* xRep = find_set(x);
	SetT* yRep = find_set(y);
	printf("Representative of %d is %d\n", x->key, xRep->key);
	printf("Representative of %d is %d\n", y->key, yRep->key);
	SetT* ret;
	if (xRep->rank > yRep->rank)
	{
		yRep->rep = xRep;
		ret = xRep;
	}
	else
	{
		xRep->rep = yRep;
		if (xRep->rank == y->rank)
		{
			yRep->rank++;
		}
		ret = yRep;
	}
	return ret;
}

SetT* unify(SetT* x, SetT* y)
{
	SetT* xRep = find_set(x);
	SetT* yRep = find_set(y);
	assign += 2;
	comp++;
	SetT* ret;
	if (xRep->rank > yRep->rank)
	{
		yRep->rep = xRep;
		ret = xRep;
		assign += 2;
	}
	else
	{
		assign += 2;
		comp++;
		xRep->rep = yRep;
		if (xRep->rank == y->rank)
		{
			assign++;
			yRep->rank++;
		}
		ret = yRep;
	}
	return ret;
}

SetT** createSetOfNodes(int *a, int n)
{
	SetT** set = (SetT**)malloc(n * sizeof(SetT*));
	for (int i = 0; i < n; i++)
	{
		set[i] = make_set(a[i]);
	}
	return set;
}

EdgeT createEdge(int x, int y, int w)
{
	EdgeT e;
	e.x = x;
	e.y = y;
	e.w = w;
	return e;
}

EdgeT* createEdgeSetDemo(int x[], int y[], int w[], int m)
{
	EdgeT* e = (EdgeT*)malloc(sizeof(EdgeT) * m);
	for (int i = 0; i < m; i++)
	{
		e[i] = createEdge(x[i], y[i], w[i]);
	}
	return e;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void heapify(EdgeT* e, int m, int i)
{
	int l = left(i);
	int r = right(i);
	int smallest;
	if (l < m && e[l].w < e[i].w)
		smallest = l;
	else smallest = i;
	if (r < m && e[r].w < e[smallest].w)
		smallest = r;
	if (smallest != i)
	{
		swap(e[i], e[smallest]);
		heapify(e, m, smallest);
	}
}

void buildHeap(EdgeT* e, int m)
{
	for (int i = m / 2 - 1; i >= 0; i--)
	{
		heapify(e, m, i);
	}
}

EdgeT extractMin(EdgeT* e, int k)
{
	EdgeT min = e[0];
	e[0].w = INT_MAX;
	//swap(e[0], e[k]);
	heapify(e, k, 0);
	return min;
}

void demoSets()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int n = sizeof(a) / sizeof(int);
	SetT** set = createSetOfNodes(a, n);
	cout << "Node set:\n";
	for (int i = 0; i < n; i++)
	{
		cout << set[i]->key << " ";
	}
	cout << endl << endl;
	int i, j;
	SetT* nod1, * nod2, * u;
	i = 4;
	j = 7;
	cout << "Unify sets tht contain elements " << i << " and " << j << endl;
	nod1 = find_node(i, set, n);
	nod2 = find_node(j, set, n);
	u = unifyDemo(nod1, nod2);
	printf("Sets that contain elements %d and %d were unified with representative %d\n\n", i, j, u->key);
	i = 2;
	j = 6;
	cout << "Unify sets tht contain elements " << i << " and " << j << endl;
	nod1 = find_node(i, set, n);
	nod2 = find_node(j, set, n);
	u = unifyDemo(nod1, nod2);
	printf("Sets that contain elements %d and %d were unified with representative %d\n\n", i, j, u->key);
	i = 1;
	j = 4;
	cout << "Unify sets tht contain elements " << i << " and " << j << endl;
	nod1 = find_node(i, set, n);
	nod2 = find_node(j, set, n);
	u = unifyDemo(nod1, nod2);
	printf("Sets that contain elements %d and %d were unified with representative %d\n\n", i, j, u->key);
	i = 8;
	j = 2;
	cout << "Unify sets tht contain elements " << i << " and " << j << endl;
	nod1 = find_node(i, set, n);
	nod2 = find_node(j, set, n);
	u = unifyDemo(nod1, nod2);
	printf("Sets that contain elements %d and %d were unified with representative %d\n\n", i, j, u->key);
	i = 5;
	j = 9;
	cout << "Unify sets tht contain elements " << i << " and " << j << endl;
	nod1 = find_node(i, set, n);
	nod2 = find_node(j, set, n);
	u = unifyDemo(nod1, nod2);
	printf("Sets that contain elements %d and %d were unified with representative %d\n\n", i, j, u->key);
}

void printEdgeSet(EdgeT* e, int m)
{
	for (int i = 0; i < m; i++)
	{
		cout << e[i].x << " " << e[i].y << " " << e[i].w;
		cout << endl;
	}
}

void printNodesRepresentatives(SetT** s, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Representative of %d is %d\n", s[i]->key, s[i]->rep->key);
	}
	cout << endl;
}

EdgeT* kruskalDemo(int a[], int n, EdgeT* e, int m)
{
	EdgeT* k = (EdgeT*)malloc(n * sizeof(EdgeT));
	int index = 0;
	SetT** s = createSetOfNodes(a, n);
	buildHeap(e, m);
	while (index < n - 1)
	{
		EdgeT f = extractMin(e, m - 1);
		if (find_set(find_node(f.x, s, n)) != find_set(find_node(f.y, s, n)))
		{
			k[index] = f;
			index++;
			unify(find_set(find_node(f.x, s, n)), find_set(find_node(f.y, s, n)));
			cout << "\nStep #" << index << endl;
			printf("Edge (%d, %d, %d) was added\n", f.x, f.y, f.w);
			printNodesRepresentatives(s, n);
		}
		m--;
	}
	return k;
}

EdgeT* kruskal(int a[], int n, EdgeT* e, int m)
{
	EdgeT* k = (EdgeT*)malloc(n * sizeof(EdgeT));
	int index = 0;
	SetT** s = createSetOfNodes(a, n);
	buildHeap(e, m);
	for (int i = 0; i < m; i++)
	{
		EdgeT f = extractMin(e, m - 1);
		SetT* x1 = find_set(find_node(f.x, s, n));
		SetT* x2 = find_set(find_node(f.y, s, n));

		if (x1 != x2)
		{
			k[index] = f;
			index++;
			unify(x1, x2);
		}
		m--;
	}
	/*while (index < n - 1)
	{
		EdgeT f = extractMin(e, m - 1);
		SetT* x1 = find_set(find_node(f.x, s, n));
		SetT* x2 = find_set(find_node(f.y, s, n));

		if (x1 != x2)
		{
			k[index] = f;
			index++;
			unify(x1, x2);
		}
		m--;
	}*/
	return k;
}

int calculateCost(EdgeT* e, int m)
{
	int sum = 0;
	for (int i = 0; i < m; i++)
	{
		sum += e[i].w;
	}
	return sum;
}

void demoKruskal()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int n = sizeof(a) / sizeof(int);
	int x[] = { 1,1,2,2,3,3,4,4,4,5,6,7,7,8 };
	int y[] = { 2,3,3,4,5,6,5,7,8,6,8,8,9,9 };
	int w[] = { 10,12,9,8,3,1,7,8,5,3,6,9,2,11 };
	int m = sizeof(x) / sizeof(int);
	EdgeT* e = createEdgeSetDemo(x, y, w, m);
	cout << "Node set:\n";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	cout << "Edge set:\n";
	printEdgeSet(e, m);
	buildHeap(e, m);
	cout << endl << endl;
	cout << "Edge set as heap:\n";
	printEdgeSet(e, m);
	cout << endl;
	EdgeT* k = kruskalDemo(a, n, e, m);
	cout << endl << "\nEdges in the minimum spanning tree after aplying Kruskal algorithm:\n";
	printEdgeSet(k, n - 1);
	cout << endl << "TOTAL cost = " << calculateCost(k, n - 1);
}

int* genrateSetOfNodes(int size)
{
	int* a = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		a[i] = i + 1;
	}
	return a;
}

void printMatrix(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

EdgeT* generateSetOfEdges(int a[], int n, int m)
{
	EdgeT* edges = (EdgeT*)malloc(m * sizeof(EdgeT));
	int** matr = (int**)calloc(n + 1, sizeof(int*));
	for (int i = 0; i <= n; i++)
	{
		matr[i] = (int*)calloc(n + 1, sizeof(int));
	}
	int w = rand() % (n * 4) + 1;
	int x, y;
	int index = 1;
	edges[0] = createEdge(a[0], a[1], w);
	matr[a[0]][a[1]] = w;
	matr[a[1]][a[0]] = w;
	for (int i = 2; i < n; i++)
	{
		w = rand() % (n * 4) + 1;
		x = a[i];
		y = rand() % a[i - 1] + 1;
		edges[index] = createEdge(x, y, w);
		index++;
		matr[x][y] = w;
		matr[y][x] = w;
	}
	for (int i = n; i < m; i++)
	{
		do
		{
			x = rand() % n + 1;
			y = rand() % n + 1;
		} while (x == y || matr[x][y] != 0);
		w = rand() % (n * 4) + 1;
		edges[index] = createEdge(x, y, w);
		index++;
		matr[x][y] = w;
		matr[y][x] = w;
	}
	for (int i = 0; i < n; i++)
	{
		free(matr[i]);
	}
	free(matr);
	return edges;
}

void generateGraph()
{
	for (int n = 100; n <= 10000; n += 100)
	{
		comp = 0;
		assign = 0;
		int* nodes = genrateSetOfNodes(n);
		int m = n * 4;
		EdgeT* edges = generateSetOfEdges(nodes, n, m);
		EdgeT* k = kruskal(nodes, n, edges, m);
		//cout << assign + comp << endl;
		profiler.countOperation("assignments", n, assign);
		profiler.countOperation("comparisons", n, comp);
		profiler.countOperation("operations", n, assign + comp);
		free(nodes);
		free(edges);
	}
	profiler.showReport();
}

int main()
{
	int test;
	cout << "Introduce the test variable (0 for demos, 1 fo graphs): ";
	cin >> test;
	if (test == 0)
	{
		demoSets();
		demoKruskal();
	}
	else
	{
		generateGraph();
	}
	
}