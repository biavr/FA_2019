/*
 Author: Bianca-Veronica Avram
 Group: 30421
 Problem: Breadth-First-Search MST generation

 The BFS traversal takes a graph (it can be connected or not) and returns a tree that contains all the vertices of the graph. If the graph
 is unconnected, then the result will be a forest of trees. The result is represented using the field parent of a node structure, such
 as, in the end, we will get a parent vector. This is a representation of a multiway tree which is the output of BFS.

 ->In what concerns the implementation of this algorithm, we start by initializing the queue and the colour of each node to white.
 ->We start with a node and enqueue it, then we process each of it unprocessed neighbours, adding the edges to the output tree. 
 ->After processing a node is done, we colour it black.
 ->At each step a node is dequeued and preocessed.
 ->This means that each node is to be enqueued at most once and dequeued at most once.
 ->Concerning the fact that enqueueing and dequeueing operations run in O(1), and this is done for each node of the graph,
 we obtain a O(V) term for the complexity of BFS.
 ->For each node, we have to process all its neighbours.
 ->That means that we have to heck each edge an process it if it's the case.
 ->From here, we get the other term of the complexity, which is O(E).
 ->So, we can deduce that the running time of BFS is O(V+E).

 For graph generation, I used the EdgeT type that contains the ends of a node. I make sure I don't add the same edge multiple times by keeping 
 an adjacency matrix where I mark the positions (x,y) and (y,x) with 1 when edge (x,y) is created. I free the matrix after use.
*/

#include <iostream>
#include "Header.h"
using namespace std;

Profiler profiler("BFS");
int op;

typedef struct node
{
	int key;
	char color;
	int dist;
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
	NodeT* head;
	NodeT* tail;
}QueueT;

NodeT* createNode(int key)
{
	NodeT* n = (NodeT*)malloc(sizeof(NodeT));
	n->key = key;
	n->color = 'w';
	n->next = NULL;
	n->parent = NULL;
	return n;
}

QueueT* initializeQueue()
{
	QueueT* q = (QueueT*)malloc(sizeof(QueueT));
	q->head = q->tail = NULL;
	return q;
}

bool isEmtyQueue(QueueT* q)
{
	if (q->head == NULL || q->tail == NULL)
		return true;
	return false;
}

void enqueue(QueueT* q, NodeT* nod)
{
	NodeT* n = createNode(nod->key);
	n->color = nod->color;
	n->dist = nod->dist;
	n->parent = nod->parent;
	if (isEmtyQueue(q))
	{
		q->head = q->tail = n;
	}
	else
	{
		q->tail->next = n;
		q->tail = n;
	}
}

int dequeue(QueueT* q)
{
	if (isEmtyQueue(q) == true)
		return -1;
	int f = q->head->key;
	NodeT* first = q->head;
	q->head = q->head->next;
	free(first);
	return f;
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

int findNodeIndex(NodeT** list, int n, int x)
{
	return x - 1;
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
	//this commented part is for when we want the graph to be connected
	/*edges[0] = createEdge(a[0], a[1]);
	matr[a[0]][a[1]] = 1;
	matr[a[1]][a[0]] = 1;
	for (int i = 2; i < n; i++)
	{
		x = a[i];
		y = rand() % a[i - 1] + 1;
		edges[index] = createEdge(x, y);
		index++;
		matr[x][y] = 1;
		matr[y][x] = 1;
	}*/
	for (int i = 0; i < m; i++)
	{
		do
		{
			x = rand() % n + 1;
			y = rand() % n + 1;
		} while (x == y || matr[x][y] != 0);
		edges[i] = createEdge(x, y);
		matr[x][y] = 1;
		matr[y][x] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		free(matr[i]);
	}
	free(matr);
	return edges;
}

NodeT** createAdjencyList(int v[], int n, EdgeT* e, int m)
{
	NodeT** list = (NodeT**)(malloc(n * sizeof(NodeT*)));
	for (int i = 0; i < n; i++)
	{
		list[i] = createNode(v[i]);
	}
	for (int i = 0; i < m; i++)
	{
		int posx = findNodeIndex(list, n, e[i].x);
		int posy = findNodeIndex(list, n, e[i].y);
		insertAtRear(list[posx], e[i].y);
		insertAtRear(list[posy], e[i].x);
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

void bfs(int source, NodeT** list, int n)
{
	for (int i = 0; i < n && list[i]->key != source; i++)
	{
		list[i]->color = 'w';
		list[i]->dist = INT_MAX;
		list[i]->parent = NULL;
		op++;
	}
	QueueT* q = initializeQueue();
	int s = findNodeIndex(list, n, source); //gets the index grom the list where element with key souce is found
	enqueue(q, list[s]);
	op++;
	list[s]->dist = 0;
	list[s]->color = 'g';
	list[s]->parent = createNode(0);
	//list[s]->parent = NULL;
	while (isEmtyQueue(q) == false)
	{
		op++;
		int d = dequeue(q);
		int inu = findNodeIndex(list, n, d);
		NodeT* u = list[inu];
		NodeT* v = u;
		while (v != NULL)
		{
			int inv = findNodeIndex(list, n, v->key);
			op++;
			if (list[inv]->color == 'w')
			{
				op += 3;
				list[inv]->color = 'g';
				list[inv]->dist = list[inu]->dist + 1;
				list[inv]->parent = list[inu];
				enqueue(q, list[inv]);
			}
			v = v->next;
			list[inu]->color = 'b';
			op += 2;
		}
	}
}

void bfsDemo(int source, NodeT** list, int n)
{
	for (int i = 0; i < n && list[i]->key != source; i++)
	{
		list[i]->color = 'w';
		list[i]->dist = INT_MAX;
		list[i]->parent = NULL;
	}
	QueueT* q = initializeQueue();
	int s = findNodeIndex(list, n, source); //gets the index grom the list where element with key souce is found
	enqueue(q, list[s]);
	list[s]->dist = 0;
	list[s]->color = 'g';
	list[s]->parent = createNode(0);
	//list[s]->parent = NULL;
	while (isEmtyQueue(q) == false)
	{
		int d = dequeue(q);
		int inu = findNodeIndex(list, n, d);
		NodeT* u = list[inu];
		NodeT* v = u;
		while (v != NULL)
		{
			int inv = findNodeIndex(list, n, v->key);
			if (list[inv]->color == 'w')
			{
				list[inv]->color = 'g';
				list[inv]->dist = list[inu]->dist + 1;
				list[inv]->parent = list[inu];
				printf("Edge (%d - %d) added\n", u->key, v->key);
				enqueue(q, list[inv]);
			}
			v = v->next;
			list[inu]->color = 'b';
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

void BFSdemo()
{
	int n = 8;
	int* a = generateArrayOfKeys(n);
	cout << "*******************************************DEMO BFS*******************************************\n\n";
	cout << "The graph contains the nodes with keys:\n";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	int m = 10;
	EdgeT* e = (EdgeT*)malloc(m * sizeof(EdgeT));
	e[0].x = 1; e[0].y = 2;
	e[1].x = 1; e[1].y = 5;
	e[2].x = 2; e[2].y = 6;
	e[3].x = 3; e[3].y = 4;
	e[4].x = 3; e[4].y = 6;
	e[5].x = 3; e[5].y = 7;
	e[6].x = 4; e[6].y = 7;
	e[7].x = 4; e[7].y = 8;
	e[8].x = 6; e[8].y = 7;
	e[9].x = 7; e[9].y = 8;
	cout << "The graph contains the edges:\n";
	for (int i = 0; i < m; i++)
	{
		cout << e[i].x << " - " << e[i].y << endl;
	}
	cout << endl << endl;
	cout << "Adjacency list:\n";
	NodeT** list = createAdjencyList(a, n, e, m);
	printList(list, n);
	cout << endl;
	cout << "Start BFS:\n";
	bfsDemo(7, list, n);
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		if (list[i]->parent->key == 0)
			cout << "In the MST the node with key " << list[i]->key << " is the root of the tree" << endl;
		else
			cout << "In the MST the parent of node with key " << list[i]->key << " is the node with key " << list[i]->parent->key << endl;
	}
	cout << "\n*******************************************END DEMO*******************************************\n";
}

int findWhite(NodeT** list, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (list[i]->color == 'w')
			return i;
	}
	return -1;
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
		int source;
		int pos = findWhite(list, V);
		while (pos != -1)
		{
			source = list[pos]->key;
			bfs(source, list, V);
			pos = findWhite(list, V);
		}
		profiler.countOperation("bfs_V_fixed", E, op);
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
		int source;
		int pos = findWhite(list, V);
		while (pos != -1)
		{
			source = list[pos]->key;
			bfs(source, list, V);
			pos = findWhite(list, V);
		}
		profiler.countOperation("bfs_E_fixed", V, op);
	}
}

int main()
{
	int test;
	cout << "Introduce the test variable(0 for demo, 1 for graphs): ";
	cin >> test;
	if (test == 0)
	{
		BFSdemo();
	}
	else
	{
		generateGraphE();
		generateGraphV();
		profiler.showReport();
	}
	
}