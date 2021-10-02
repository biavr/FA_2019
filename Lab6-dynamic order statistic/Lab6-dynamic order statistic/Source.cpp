/*
Author: Bianca Avram
Group: 30421
Problem: Dynamic Order Statistic

This problem is based on 3 main functions: buildTree, OS_select and OS_delete

BuildTree 
->is the function that takes a sorted array, which is equivalent to inorder traversal for a tree,
and obtains the ADS reptesentation of a perfect balanced binary tree;
->it is a divide et impera strategy which chooses a "root" every time, than creates the subtrees from left and right;
->its time complexity is O(n), as resulted from master theorem, which is completely expected, because we need to process
each and every element in the array;

Select
->it obtains te node that contains the ith smallest key in the sorted initial array;
->it is implemented recursively and we get to choose at each step if we go to left or right to search for the key;
->when we get to a leaf, that means that we found the mode we wanted
->this function uses the field "size" from the structure of a node, which contains the number of nodes in the 
subtree that has that node as root (including this node)
->when the node is found, a poiner to it is returned
->the time complexity for this function is O(logn)
->logn represents the height of the tree, which is kept balanced in what concerns the number of nodes in each subtree
->this complexity i given by the fact that we never have to go through the whole tree to find a node, because we
now exactly at each step that there is a branch we can eliminate

Delete
->to delete a node, first we have to look for it in the tree using OS_select
->this already gives the complexity of O(logn)
->the following steps are to effectively delete the node, which implies looking for its successor
->there are 3 cases: leaves, nodes with only one descendant and nodes with 2 descendants
->each gives a different complexity
->the first 2 run in O(1), but the thirs case runs in O(logn), because the problem of finding the successor 
might take longer
->after finding and deleting a node, we have to update the "size" field
->to notice that only the nodes on the branch until the deleted node are affected
->for this, we use the "parent" field in order to go upwards, from the parent of the deleted node or the parent of the
successor (for case 3), until the root
->we decrement the size at every step until the root
->this process also takes O(logn), the height of the tree
->in the end, we have O(logn) the complexity for the OS_delete function, as a sum of O(logn)s

*/
#include <iostream>
#include <ctime>
#include "Profiler.h"
#define COUNT 10 
using namespace std;

Profiler profiler("trees");

int opBuild;
int opDelete;
int opSelect;

typedef struct node
{
	int key;
	int size;
	node* left;
	node* right;
	node* parent;
}NodeT;

NodeT* createNode(int key)
{
	NodeT* n = (NodeT*)malloc(sizeof(NodeT));
	n->key = key;
	n->parent = NULL;
	n->left = NULL;
	n->right = NULL;
	n->size = 1;
	return n;
}

int* generateArray(int size)
{
	int* a = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		a[i] = i + 1;
	}
	return a;
}

NodeT* buildTree(int a[], int l, int r, NodeT* parent, int size)
{
	opBuild++;
	if (l <= r)
	{
		int m = (r + l) / 2;
		NodeT* root = createNode(a[m]);
		root->parent = parent;
		opBuild += 3;
		if (size % 2 == 0)
		{
			root->size = size;
			root->left = buildTree(a, l, m - 1, root, size / 2 - 1);
			opBuild += 3;
			if (root->left)
			{
				root->left->parent = root;
				opBuild++;
			}
			opBuild += 2;
			root->right = buildTree(a, m + 1, r, root, size / 2);
			if (root->right)
			{
				opBuild++;
				root->right->parent = root;
			}
			return root;
		}
		root->size = size;
		root->left = buildTree(a, l, m - 1, root, size / 2);
		opBuild += 3;
		if (root->left)
		{
			root->left->parent = root;
			opBuild++;
		}
		opBuild += 2;
		root->right = buildTree(a, m + 1, r, root, size / 2);
		if (root->right)
		{
			root->right->parent = root;
			opBuild++;
		}
		return root;
	}
	return NULL;
}

void inorder(NodeT* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		
		for (int i = 0; i < root->size; i++)
		{
			cout << "     ";
		}
		cout << root->size << ", " << root->key << endl;
		inorder(root->right);
	}
}

void prettyPrint(NodeT* root, int space)
{
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	prettyPrint(root->right, space);

	// Print current node after space 
	// count 
	printf("\n");
	for (int i = COUNT ; i < space ; i++)
		printf(" ");
	cout << root->key << ", " << root->size;

	// Process left child 
	prettyPrint(root->left, space);
}

void buildTreeDemo()
{
	cout << "BuildTree demo****************************************" << endl << endl;
	int size = 11;
	//int* a = generateArray(size);
	int a[] = { 14, 17, 18, 22, 25, 48, 52, 55, 83, 94, 99 };
	cout << "Initial array:\n";
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	NodeT* root = buildTree(a, 0, size - 1, NULL, size);
	//inorder(root);
	prettyPrint(root, 0);
}

NodeT* OS_select(NodeT* x, int i)
{
	int r;
	opSelect += 5;
	if (x == NULL)
		return x;
	if (x->left == NULL && x->right == NULL)
		return x;
	if (x->left != NULL)
	{
		r = x->left->size + 1;
	}
	else
	{
		r = x->size - 1;
	}
	opSelect++;
	if (i == r)
		return x;
	else
	{
		opSelect++;
		if (i < r)
			return OS_select(x->left, i);
		else
			return OS_select(x->right, i - r);
	}
		
}

void OS_selectDemo()
{
	cout << endl;
	cout << "OS_select Demo****************************************" << endl << endl;
	int size = 11;
	//int* a = generateArray(size);
	int a[] = { 14, 17, 18, 22, 25, 48, 52, 55, 83, 94, 99 };
	cout << "Initial array:\n";
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	NodeT* root = buildTree(a, 0, size - 1, NULL, size);
	NodeT* q = OS_select(root, 3);
	cout << "The 3rd smallest key is " << q->key << endl;
	q = OS_select(root, 7);
	cout << "The 7th smallest key is " << q->key << endl;
	q = OS_select(root, 5);
	cout << "The 5th smallest key is " << q->key << endl;
	cout << endl;
}

NodeT* findMin(NodeT* root)
{
	if (root == NULL)
		return root;
	while (root->left != NULL)
	{
		root = root->left;
		opDelete++;
	}
	return root;
}

NodeT* findSucc(NodeT* root)
{
	opDelete += 2;
	if (root->right != NULL)
		return findMin(root->right);
	NodeT* y = root->parent;
	opDelete += 2;
	while (y != NULL && root == y->right)
	{
		opDelete += 3;
		root = y;
		y = y->parent;
	}
	return y;
}

void OS_delete(NodeT* root, int i)
{
	NodeT* p;
	NodeT* z = OS_select(root, i);
	opDelete += 7;
	if (z == NULL)
		return;
	NodeT* y;
	NodeT* x;
	if (z->left == NULL || z->right == NULL)
		y = z;
	else
		y = findSucc(z);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
	{
		x->parent = y->parent;
		opDelete++;
	}	
	opDelete++;
	if (y->parent == NULL)
	{
		root = x;
		opDelete++;
	}		
	else
	{
		opDelete += 2;
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	z->key = y->key;
	p = y->parent;
	free(y);

	//updating the size
	while (p != NULL)
	{
		p->size--;
		p = p->parent;
		opDelete += 3;
	}
}

void OS_deleteDemo()
{
	cout << endl;
	cout << "OS_delete Demo****************************************" << endl << endl;
	int size = 11;
	//int* a = generateArray(size);
	int a[] = { 14, 17, 18, 22, 25, 48, 52, 55, 83, 94, 99 };
	cout << "Initial array:\n";
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << endl;
	NodeT* root = buildTree(a, 0, size - 1, NULL, size);
	cout << endl << "Initial tree" << endl << endl;
	prettyPrint(root, 0);
	cout << endl << endl << "Delete 5th node" << endl << endl;
	OS_delete(root, 5);
	prettyPrint(root, 0);
	cout << endl << endl << "Delete 6th node" << endl << endl;
	OS_delete(root, 6);
	prettyPrint(root, 0);
	cout << endl << endl << "Delete 3rd node" << endl << endl;
	OS_delete(root, 3);
	prettyPrint(root, 0);
}

void generateGraph()
{
	for (int size = 100; size <= 10000; size += 100)
	{
		opBuild = 0;
		opSelect = 0;
		opDelete = 0;
		for (int m = 0; m < 5; m++)
		{
			int* a = generateArray(size);
			NodeT* root = buildTree(a, 0, size - 1, NULL, size);
			for (int i = 0; i < size; i++)
			{
				int random = rand() % (size - i);
				OS_delete(root, random);
			}
			
		}
		opBuild /= 5;
		opSelect /= 5;
		opDelete /= 5;
		profiler.countOperation("operations_build", size, opBuild);
		profiler.countOperation("operations_select", size, opSelect);
		profiler.countOperation("operations_delete", size, opSelect + opDelete);
	}
	profiler.showReport();
}

int main()
{
	srand(time(NULL));
	int test;
	cout << "Input the test variable (0 for demo and 1 for graph):";
	cin >> test;
	if (test == 0)
	{
		buildTreeDemo();
		OS_selectDemo();
		OS_deleteDemo();
	}
	else
	{
		generateGraph();
	}
}