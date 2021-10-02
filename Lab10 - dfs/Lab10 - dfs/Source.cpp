/*
 Author: Bianca Avram
 Group: 30421
 Problem: Depth-first-search, Tarjan, topological sort

 DFS:
 ->it is an algorithm that traverses the whole graph and has as output a minimum spanning tree or a forest of minimum spanning trees
 ->it starts from a random node and goes "deep" down until it cannot go anymore
 ->this means that when it comes back to visit even more vertices, it kind of backtracks
 ->it adds 2 new fields in the node structure, namely d, the timestamp that indicates when the node has been coloured grey,
 and f, the timestamp that tells us when the node has been coloured black
 ->the running time is O(V + E) as in bfs, because all the components of the graph are processed at most once
 ->even if it doesn't go directly to all the neighbours of a vertex, it finally discovers them all as it "backtracks"

 Tarjan:
 ->runs in linear time
 ->uses a stack as additional memory
 ->obtains all the strongly connected components of a directed graph
 ->I used a similar structure as the one that keeps the adjacency list of the graph to store the output
 ->it uses a stack to "remember" through which nodes the algorithm has passed
 ->the 2 timestamps become index(d) and lowlink(f)
 ->these mark the moment the vertex has been pushed on the stack and respectively the smallest index of any node that
 can be reached from the source node or its DFS tree
 ->this algorithm contains 2 functions: strongconnect and tarjan
 ->strongconnect oes all the job, practically
 ->tarjan only makes sure that the function has been called for all the vertices

 Topological sort:
 ->is based on a DFS call where we add the node to a structure that resembles a stack (nodes are pushed, but never popped) as their colour
 becomes black
 ->the nodes are added at front, as in a stack
 ->the output is the structure which is printed from top to bottom
 ->the complexity of this algorithm is the same as DFS 
 ->the only difference is the memory tat is used to store the result, which is in O(V)
 */

#include <iostream>
#include "Header.h"
using namespace std;

Profiler profiler("BFS");
int op;

typedef struct node
{
	int key;
	char color; //at Tarjan this field is used to determine if a node is on the stack or not; white = not on the stack; black = on the stack
	int d; //used as index for Tarjan
	int f; //used as lowlink for Tarjan
	node* parent;
	node* next;
}NodeT;

typedef struct
{
	int x;
	int y;
}EdgeT;

typedef struct
{
	NodeT* top;
}StackT;


NodeT* createNode(int key)
{
	NodeT* n = (NodeT*)malloc(sizeof(NodeT));
	n->key = key;
	n->color = 'w';
	n->d = 0;
	n->f = 0;
	n->next = NULL;
	n->parent = NULL;
	return n;
}

void insertAtRear(NodeT* n, int key)
{
	NodeT* p = createNode(key);
	NodeT* q = n;
	while (q->next != NULL)
	{
		q = q->next;
	}
	q->next = p;
}

EdgeT createEdge(int x, int y)
{
	EdgeT e;
	e.x = x;
	e.y = y;
	return e;
}

EdgeT* generateSetOfEdges(int a[], int n, int m)
{
	EdgeT* edges = (EdgeT*)malloc(m * sizeof(EdgeT));
	int** matr = (int**)calloc(n + 1, sizeof(int*));
	for (int i = 0; i <= n; i++)
	{
		matr[i] = (int*)calloc(n + 1, sizeof(int));
	}
	int x, y;
	for (int i = 0; i < m; i++)
	{
		do
		{
			x = rand() % n + 1;
			y = rand() % n + 1;
		} while (x == y || matr[x][y] != 0);
		edges[i] = createEdge(x, y);
		matr[x][y] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		free(matr[i]);
	}
	free(matr);
	return edges;
}

int findNodeIndex(NodeT** list, int n, int x)
{
	for (int i = 0; i < n; i++)
	{
		if (list[i]->key == x)
			return i;
	}
	return -1;
}

NodeT** createAdjencyList(int v[], int n, EdgeT* e, int m)
{
	NodeT** list = (NodeT**)malloc(n * sizeof(NodeT*));
	for (int i = 0; i < n; i++)
	{
		list[i] = createNode(v[i]);
	}
	for (int i = 0; i < m; i++)
	{
		int posx = findNodeIndex(list, n, e[i].x);
		insertAtRear(list[posx], e[i].y);
	}
	return list;
}

void printList(NodeT** list, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << list[i]->key << " : ";
		if (list[i]->next == NULL)
		{
			cout << "-\n";
		}
		else
		{
			NodeT* p = list[i]->next;
			while (p->next != NULL)
			{
				cout << p->key << ", ";
				p = p->next;
			}
			cout << p->key << endl;
		}
	}
}

void initializeNodes(NodeT** list, int n)
{
	return;
	//for this problem I do not need this function, as I create nodes already initialized
	//parent to NULL and colour to white
}

void dfs_visit(NodeT** list, int n, int i, int* time)
{
	(*time)++;
	list[i]->d = (*time);
	list[i]->color = 'g';
	NodeT* v = list[i];
	op += 3;
	while (v != NULL)
	{
		int index = findNodeIndex(list, n, v->key);
		if (list[index]->color == 'w')
		{
			list[index]->parent = list[i];
			dfs_visit(list, n, index, time);
		}
		v = v->next;
		op += 3;
	}
	list[i]->color = 'b';
	(*time)++;
	list[i]->f = (*time);
	op += 3;
}

void dfs(NodeT** list, int n)
{
	initializeNodes(list, n);
	int time = 0;
	for (int i = 0; i < n; i++)
	{
		op++;
		if (list[i]->color == 'w')
		{
			dfs_visit(list, n, i, &time);
		}
	}
}

void dfs_visitDemo(NodeT** list, int n, int i, int* time)
{
	(*time)++;
	list[i]->d = (*time);
	list[i]->color = 'g';
	printf("\nNode with key %d turned GREY with timestamp d = %d", list[i]->key, list[i]->d);
	NodeT* v = list[i]->next;
	while (v != NULL)
	{
		int index = findNodeIndex(list, n, v->key);
		if (list[index]->color == 'w')
		{
			list[index]->parent = list[i];
			dfs_visitDemo(list, n, index, time);
		}
		v = v->next;
	}
	list[i]->color = 'b';
	(*time)++;
	list[i]->f = (*time);
	printf("\nNode with key %d turned BLACK with timestamp f = %d", list[i]->key, list[i]->f);
}

void dfsDemo(NodeT** list, int n)
{
	initializeNodes(list, n);
	int time = 0;
	for (int i = 0; i < n; i++)
	{
		if (list[i]->color == 'w')
		{
			dfs_visitDemo(list, n, i, &time);
		}
	}
}

int* generateArrayOfKeys(int size)
{
	int* a = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		a[i] = i + 1;
	}
	return a;
}

void DFSdemo()
{
	int n = 6;
	int* a = generateArrayOfKeys(n);
	cout << "\n*******************************************DEMO DFS*******************************************\n\n";
	cout << "The graph contains the nodes with keys:\n";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	int m = 8;
	EdgeT* e = (EdgeT*)malloc(m * sizeof(EdgeT));
	e[0].x = 1; e[0].y = 2;
	e[1].x = 1; e[1].y = 4;
	e[2].x = 4; e[2].y = 2;
	e[3].x = 2; e[3].y = 5;
	e[4].x = 5; e[4].y = 4;
	e[5].x = 3; e[5].y = 5;
	e[6].x = 3; e[6].y = 6;
	e[7].x = 6; e[7].y = 6;
	cout << "The graph contains the edges:\n";
	for (int i = 0; i < m; i++)
	{
		cout << "(" << e[i].x << " - " << e[i].y << ")" << endl;
	}
	cout << endl;
	cout << "Adjacency list:\n";
	NodeT** list = createAdjencyList(a, n, e, m);
	printList(list, n);
	cout << endl;
	cout << "Start DFS:";
	dfsDemo(list, n);
	cout << endl;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		if(list[i]->parent == NULL)
			cout << "In the MST forest the node with key " << list[i]->key << " is the root of one of the trees" << endl;
		else
			cout << "In the MST the parent of node with key " << list[i]->key << " is the node with key " << list[i]->parent->key << endl;
	}
	cout << "\n*******************************************END DEMO*******************************************\n";
}

void generateGraphV()
{
	int V = 100; // number of nodes in the graph
	int* nodes = generateArrayOfKeys(V);
	for (int E = 1000; E <= 4500; E += 100)
	{
		op = 0;
		EdgeT* edges = generateSetOfEdges(nodes, V, E);
		NodeT** list = createAdjencyList(nodes, V, edges, E);
		dfs(list, V);
		profiler.countOperation("dfs_V_fixed", E, op);
	}
}

void generateGraphE()
{
	int E = 4500;
	for (int V = 100; V <= 200; V += 10)
	{
		op = 0;
		int* nodes = generateArrayOfKeys(V);
		EdgeT* edges = generateSetOfEdges(nodes, V, E);
		NodeT** list = createAdjencyList(nodes, V, edges, E);
		dfs(list, V);
		profiler.countOperation("dfs_E_fixed", V, op);
	}
}

StackT* createStack()
{
	StackT* s = (StackT*)malloc(sizeof(StackT));
	s->top = NULL;
	return s;
}

bool isEmptyStack(StackT* s)
{
	if (s->top == NULL)
		return true;
	return false;
}

void push(StackT* s, int key)
{
	NodeT* p = createNode(key);
	if (isEmptyStack(s) == true)
	{
		s->top = p;
	}
	else
	{
		p->next = s->top;
		s->top = p;
	}
}

int pop(StackT* s)
{
	int p = s->top->key;
	NodeT* q = s->top;
	s->top = s->top->next;
	free(q);
	return p;
}

void dfs_visitTopological(NodeT** list, int n, int i, int* time, StackT* s)
{
	(*time)++;
	//printf("Node %d reached at timestamp %d\n", list[i]->key, (*time));
	list[i]->d = (*time);
	list[i]->color = 'g';
	NodeT* v = list[i];
	while (v != NULL)
	{
		int index = findNodeIndex(list, n, v->key);
		//int index = v->key - 1;
		if (list[index]->color == 'w')
		{
			list[index]->parent = list[i];
			dfs_visitTopological(list, n, index, time, s);
		}
		v = v->next;
	}
	list[i]->color = 'b';
	push(s, list[i]->key); 
	(*time)++;
	list[i]->f = (*time);
	printf("\nVertex with key %d was finished at timestamp %d", list[i]->key, list[i]->f);
}

void dfsTopological(NodeT** list, int n, StackT* s)
{
	initializeNodes(list, n);
	int time = 0;
	for (int i = 0; i < n; i++)
	{
		op++;
		if (list[i]->color == 'w')
		{
			dfs_visitTopological(list, n, i, &time, s);
		}
	}
}

StackT* topologicalSort(NodeT** list, int n)
{
	StackT* t = createStack();
	dfsTopological(list, n, t);
	return t;
}

void topologicalSortDemo()
{
	int n = 6;
	int* a = generateArrayOfKeys(n);
	cout << "*************************************DEMO TOPOLOGICAL SORT************************************\n\n";
	cout << "The graph contains the nodes with keys:\n";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	int m = 8;
	EdgeT* e = (EdgeT*)malloc(m * sizeof(EdgeT));
	e[0].x = 1; e[0].y = 2;
	e[1].x = 1; e[1].y = 4;
	e[2].x = 4; e[2].y = 2;
	e[3].x = 2; e[3].y = 5;
	e[4].x = 5; e[4].y = 4;
	e[5].x = 3; e[5].y = 5;
	e[6].x = 3; e[6].y = 6;
	e[7].x = 6; e[7].y = 6;
	cout << "The graph contains the edges:\n";
	for (int i = 0; i < m; i++)
	{
		cout << "(" << e[i].x << " - " << e[i].y << ")" << endl;
	}
	cout << endl;
	cout << "Adjacency list:\n";
	NodeT** list = createAdjencyList(a, n, e, m);
	printList(list, n);
	cout << endl;
	cout << "Topological sort START:";
	StackT* t = topologicalSort(list, n);
	cout << endl << endl;
	cout << "Sorted set of nodes (after topological sort):\n";
	NodeT* p = t->top;
	while (p)
	{
		cout << p->key << " ";
		p = p->next;
	}
	cout << "\n\n*******************************************END DEMO*******************************************\n";
}

void strongconnect(NodeT** list, int n, int i, int *index, StackT* s, NodeT** out, int *ncc)
{
	list[i]->d = (*index);
	list[i]->f = (*index);
	(*index)++;
	push(s, i); // I only push the index in the list of the node so that I don't have to search te key when I pop it
	list[i]->color = 'b';
	NodeT* v = list[i]->next;
	while (v != NULL)
	{
		int newi = findNodeIndex(list, n, v->key);
		if (list[newi]->d == 0)
		{
			strongconnect(list, n, newi, index, s, out, ncc);
			list[i]->f = (list[i]->f < list[newi]->f) ? list[i]->f : list[newi]->f;
		}
		else
		{
			if (list[newi]->color == 'b')
			{
				list[i]->f = (list[i]->f < list[newi]->d) ? list[i]->f : list[newi]->d;
			}
		}
		v = v->next;
	}
	int j;
	if (list[i]->d == list[i]->f)
	{
		cout << "Vertex " << list[i]->key << " is the start of a new connected component\n";
		(*ncc)++;
		out[(*ncc)] = createNode(list[i]->key);
		do
		{		
			j = pop(s);
			list[j]->color = 'w';
			if (list[j]->key != out[(*ncc)]->key)
			{
				insertAtRear(out[(*ncc)], list[j]->key);
			}
		}while (j != i);	
	} 	
}

NodeT** tarjan(NodeT** list, int n, int *ncc)
{
	NodeT** out = (NodeT**)malloc(n * sizeof(NodeT*)); //the output of the Tarjan algorithm
	//built as an array of lists which are actually the sets of vertices in the same connected component
	StackT* s = createStack();
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		if (list[i]->d == 0)
			strongconnect(list, n, i, &index, s, out, ncc);
	}
	return out;
}

void tarjanDemo()
{
	int n = 6;
	int* a = generateArrayOfKeys(n);
	cout << "\n*****************************************DEMO TARJAN******************************************\n\n";
	cout << "The graph contains the nodes with keys:\n";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	int m = 8;
	EdgeT* e = (EdgeT*)malloc(m * sizeof(EdgeT));
	e[0].x = 1; e[0].y = 2;
	e[1].x = 1; e[1].y = 4;
	e[2].x = 4; e[2].y = 2;
	e[3].x = 2; e[3].y = 5;
	e[4].x = 5; e[4].y = 4;
	e[5].x = 3; e[5].y = 5;
	e[6].x = 3; e[6].y = 6;
	e[7].x = 6; e[7].y = 6;
	cout << "The graph contains the edges:\n";
	for (int i = 0; i < m; i++)
	{
		cout << "(" << e[i].x << " - " << e[i].y << ")" << endl;
	}
	cout << endl;
	cout << "Adjacency list:\n";
	NodeT** list = createAdjencyList(a, n, e, m);
	printList(list, n);
	cout << endl;
	cout << "Tarjan START:\n";
	int ncc = -1;
	NodeT** conn = tarjan(list, n, &ncc);
	cout << endl << "The connected components are:\n";
	for (int i = 0; i <= ncc; i++)
	{
		cout << "Component no. " << i + 1 << " contains the vertices: ";
		NodeT* p = conn[i];
		while (p != NULL)
		{
			cout << p->key << " ";
			p = p->next;
		}
		cout << endl;
	}
	cout << "\n\n*******************************************END DEMO******************************************\n";
}

int main()
{
	int test;
	cout << "Enter the test variable (0 for demos, 1 for graphs): ";
	cin >> test;
	if (test == 0)
	{
		cout << endl;
		DFSdemo();
		cout << endl;
		topologicalSortDemo();
		cout << endl;
		tarjanDemo();
	}
	else
	{
		generateGraphE();
		generateGraphV();
		profiler.showReport();
	}
}