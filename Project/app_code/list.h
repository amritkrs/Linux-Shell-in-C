#define MAXSIZE 30
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _LIST_H
#define _LIST_H

typedef char ElementType;
struct node;
typedef struct node *ptrtonode;
typedef ptrtonode List;
typedef ptrtonode Position;
int IsEmpty(List l);
Position Find(ElementType x[],List l);
void Delete(ElementType x[],List l);
Position FindPrevious(ElementType x[],List l);
void Insert(ElementType x[],List l,Position p);
void DeleteList(List l);
void InsertAfter(ElementType x[],List l,int n);
int Count(List l);
void Display(List l);
Position FindPre(Position p,List l);
void SwapLink(Position p,Position q,List l);
void Swap(Position p,Position q);
void SelectionSort(List l);
void Reverse(List l);


struct node
{
        ElementType Element[MAXSIZE];
        Position Next;
};

#endif
