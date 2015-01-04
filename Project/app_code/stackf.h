
#ifndef _STACKF_H
#define _STACKF_H


#include"listf.h"



typedef List_f Stack_f;

Stack_f CreateStack_f(void);
void MakeEmpty_f(Stack_f s);
void Push_f(float x,Stack_f s);
void Pop_f(Stack_f s);
float Top_f(Stack_f s);
float TopandPop_f(Stack_f s);

//#endif
#endif
