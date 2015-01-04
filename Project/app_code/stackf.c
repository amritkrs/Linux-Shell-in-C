/*THIS FILE CONTAINS THE Stack_f FUNCTIONS USING LINKED LIST
 WRITTEN BY :- AMRIT KUMAR
 	       IT IS A STACK FOR FLOAT NUMBERS.
*/
#include"stackf.h"
//STACK FUNCTION THAT RETURNS POINTER TO A STACK.
Stack_f CreateStack_f(void)
{
	Stack_f s;
	
	s = malloc(sizeof(struct node_f));
	s->Next = NULL;
	return s;
}
//MAKE STACK EMPTY
void MakeEmpty_f(Stack_f s)
{
	DeleteList_f(s);
}
//PUSH CODE FOR STACK
void Push_f(float x,Stack_f s)
{
	InsertAfter_f(x,s,0);
}
//POP CODE FOR STACK
void Pop_f(Stack_f s)
{
	 if(IsEmpty_f(s))
        {
                puts("Stack_f is empty");
               
        }

	Delete_f(s->Next->Element,s);
}
//RETURN TOP ELEMENT ON STACK
float Top_f(Stack_f s)
{
	if(IsEmpty_f(s))
	{
		puts("Stack_f is empty");
		return 0;
	}
	return s->Next->Element;
}
//RETURN TOP ELEMENT AND POP THAT ONE OUT.
float TopandPop_f(Stack_f s)
{
	 if(IsEmpty_f(s))
        {
                puts("Stack_f is empty");
                return 0;
        }

	float x;
	x = Top_f(s);
	Pop_f(s);
	return x;
}

