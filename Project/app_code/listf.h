#include<stdio.h>
#include<stdlib.h>
//#include"List_f.h"

#ifndef _LISTF_H
#define _LISTF_H


struct node_f;
typedef struct node_f *ptrtonode_f;
typedef ptrtonode_f List_f;
typedef ptrtonode_f Position_f;
int IsEmpty_f(List_f l);
Position_f Find_f(float x,List_f l);
void Delete_f(float x,List_f l);
Position_f FindPrevious_f(float x,List_f l);
void Insert_f(float x,List_f l,Position_f p);
void DeleteList_f(List_f l);
void InsertAfter_f(float x,List_f l,int n);
int Count_f(List_f l);
void Display_f(List_f l);
Position_f FindPre_f(Position_f p,List_f l);
void Swap_fLink_f(Position_f p,Position_f q,List_f l);
void Swap_f(Position_f p,Position_f q);
void SelectionSort_f(List_f l);
void Reverse_f(List_f l);

struct node_f
{
        float Element;
        Position_f Next;
};

#endif
