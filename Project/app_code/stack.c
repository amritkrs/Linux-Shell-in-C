/*THIS FILE CONTAINS THE STACK FUNCTIONS USING LINKED LIST
 WRITTEN BY :- AMRIT KUMAR
	       IT IS A STACK FOR STRINGS.
*/
#include"stack.h"
//FUNCTION THAT RETURNS A STACK POINTER FOR WHICH IT ASSIGNS MEMORY.
Stack CreateStack(void)
{
	Stack s;	//TO BE USED AS HEADER AND PASSED AFTER MEMORY ALLOCATION.
	
	s = malloc(sizeof(struct node));
	s->Next = NULL;
	return s;
}
//TO MAKE STACK EMPTY
void MakeEmpty(Stack s)
{
	DeleteList(s);
}
//PUSH OPERATION IN STACK
void Push(ElementType x[],Stack s)
{
	InsertAfter(x,s,0);
}
//POP OPERATION IN STACK.
void Pop(Stack s)
{
	 if(IsEmpty(s))
        {
                puts("stack is empty");
               
        }

	Delete(s->Next->Element,s);
}
//TOP OPERATION THAT RETURNS POINTER TO A STRING.
ElementType* Top(Stack s)
{
	if(IsEmpty(s))
	{
		puts("stack is empty");
		return 0;
	}
	return s->Next->Element;
}
//TOP AND POP WHICH DOES TOP 1ST AND POP NEXT.
void TopandPop(Stack s,char t[])
{
	 if(IsEmpty(s))
        {
                puts("stack is empty");
              //  return 0;
        }
	char *p;
	p = Top(s);
	strcpy(t,p);
	Pop(s);

}

