/*
Author: Bianca Avram
Group: 30421
Problem: Multiway trees

First of all, I started with a regular int vector that for each index i, at position i it holds the parent of i.
For the first transformation, I created the type NodeT which contains a key, the number of children of that key and an array that contains 
all the children of that node. I hold the whole tree in an array of this NodeT type and the print is very similar to an aadjacency list 
from graphs: I have the key and the children of that node.
I have to mention that I used the premise that the root has 0 as parent.
I built this tree in O(n), because I only used a for to traverse the parent vector once and to place each child at its parent.

For the second transformation, I have the TreeT type which holds a key, a left and a right pointer.
I have 2 functions that are used to build the binary tree: siblings and createTree.
CreateTree is used for making the recursive calls of siblings easier to manage, as it only creates the root and calls the 
siblings function for left of root.
Siblings is a recursive function that first goes on the left of the node, linking practically the first child of each node on the
left side. For the right side, we use a for loop, until the end of the array to link all the children of a node. For each
node added this way we need to call again siblings for the left side to complete the links. At the end, a pointer to the root is returned.

In what oncers the space efficiency, the program could have been enhanced by allocating each children array dynamically, but that
would have ment another traversal of the parent vector to establish the number of children for each node.
No other additional memory has been used.

*/

#include <iostream>
using namespace std;

typedef struct node
{
	int key;
	int children[100];
	int noOfChildren;
}NodeT;

typedef struct tree
{
	int key;
	tree* left;
	tree* right;
}TreeT;

void initializeR2(NodeT* r, int n)
{
	for (int i = 0; i <= n; i++)
	{
		r[i].key = i;
		r[i].noOfChildren = 0;
	}
}

void printTree(NodeT* r, int n)
{
	for (int i = 0; i <= n; i++)
	{
		cout << i << ": ";
		if (r[i].noOfChildren == 0)
		{
			cout << "-";
		}
		else
		{
			for (int j = 0; j < r[i].noOfChildren - 1; j++)
			{ 
				cout << r[i].children[j] << ", ";
			}
			cout << r[i].children[r[i].noOfChildren - 1];
		}		
		cout << endl;
	}
	cout << endl;
}


NodeT* r1Tor2(int* a, int n)
{
	NodeT* r = (NodeT*)malloc((n - 1) * sizeof(NodeT));
	initializeR2(r, n);
	for (int i = 0; i <= n; i++)
	{
		//cout << i << " " << a[i] << endl;
		if (i != 0)
		{
			r[a[i]].children[r[a[i]].noOfChildren] = i;
			r[a[i]].noOfChildren++;
		}
		
	}
	return r;
}

TreeT* createNode(int key)
{
	TreeT* p = (TreeT*)malloc(sizeof(TreeT));
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	return p;
}

TreeT* siblings(NodeT * r2, int* a, int i)
{
	if (r2[i].noOfChildren == 0)
		return NULL;
	int j = 0;
	TreeT* p = createNode(a[j]);
	p->left = siblings(r2, r2[p->key].children, p->key);
	TreeT* q = p;
	for (int k = 1; k < r2[i].noOfChildren; k++)
	{
		q->right = createNode(a[k]);
		q = q->right;
		q->left = siblings(r2, r2[q->key].children, q->key);
	}
	return p;
}


TreeT* createTree(NodeT *r2)
{
	TreeT* r3 = createNode(r2[0].children[0]);
	r3->left = siblings(r2, r2[r3->key].children, r3->key);
	return r3;
}


void prettyPrint(TreeT* root, int level)
{
	if (root != NULL)
	{
		for (int i = 0; i < level; i++)
		{
			cout << "     ";
		}
		cout << root->key << endl;
		prettyPrint(root->left, level + 1);
		prettyPrint(root->right, level);
	}
	
}

void r1Tor2Tor3Demo()
{
	int size = 9;
	int a[] = { 0 , 2 , 7 , 5 , 2 , 7 , 7 , 0 , 5 , 2 };
	cout << "R1(parent vector):\n";
	for (int i = 1; i <= size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	cout << "R2(multiway tree):\n";
	NodeT* r2 = r1Tor2(a, size);
	printTree(r2, size);
	TreeT* r3 = createTree(r2);
	cout << endl << "R3(binary tree):\n";
	prettyPrint(r3, 0);
}

int main()
{
	r1Tor2Tor3Demo();
}