#pragma once
typedef struct node
{
	int key;
	struct node* next;
}NodeT;

typedef struct
{
	NodeT* first;
	NodeT* last;
	int count;
}ListT;

extern ListT* createList();
extern NodeT* createNode(int key);
extern void insertAtRear(ListT* l, int key);
extern ListT* generateList(int size);
extern void deletFromFront(ListT* l);