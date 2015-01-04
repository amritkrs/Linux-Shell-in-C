
#ifndef _STACK_H
#define _STACK_H

#include"list.h"
typedef List Stack;

Stack CreateStack(void);

void MakeEmpty(Stack s);
void Push(ElementType x[],Stack s);
void Pop(Stack s);
ElementType* Top(Stack s);
void TopandPop(Stack s,char t[]);

#endif
