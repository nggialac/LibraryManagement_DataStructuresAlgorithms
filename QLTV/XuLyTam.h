#pragma once
#include <iostream>
#include "Marcro.h"
using std::string;

struct TenHo
{
	string hoten;
	int MADG;
};
typedef struct TenHo TEN_HO;

struct Temp_List
{
	int index;
	int MADG;
};
typedef struct Temp_List TEMP_LIST;

struct NodeTempList
{
	TEMP_LIST tl;
	struct NodeTempList * pNext;
};
typedef struct NodeTempList NODE_TEMPLIST;

struct ListTempList
{
	//so phan tu
	// int n;
	NODE_TEMPLIST *pHead;
	NODE_TEMPLIST *pTail;

};
typedef struct ListTempList LIST_TEMPLIST;

// ..... khoi tao........
void initList_TEMPLIST(LIST_TEMPLIST &l);

//.......get node.........
NODE_TEMPLIST* GetNode_TEMPLIST(int index, int MADG);

//...... add tail link list........
void AddTailList_TEMPLIST(LIST_TEMPLIST &l, int index, int MADG);

// function to find out middle element
NODE_TEMPLIST * Middle(NODE_TEMPLIST * start, NODE_TEMPLIST * last);

// Function for implementing the Binary Search on linked list
NODE_TEMPLIST * BinarySearch_TEMPLIST(LIST_TEMPLIST l, int index);

//............xoa list..................
void ClearAll_TEMPLIST(LIST_TEMPLIST &l);
