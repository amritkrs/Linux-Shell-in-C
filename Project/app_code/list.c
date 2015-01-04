/*THIS FILE CONTAINS THE DIFFERENT ADT FUNCTIONS FOR LINKED LISTS
  WRITTEN BY:- AMRIT KUMAR
  DATE :- 28/11/12
*/

#include"list.h"
//TO CHECK IF LIST IS EMPTY
/*HEADER IMPLEMENTATION ASSUMED*/
int IsEmpty(List l)
{
	return l->Next == NULL;
}
/*HEADER IMPLEMENTATION ASSUMED*/
int Islast(Position p,List l)
{
	return p->Next == NULL;
}
/*HEADER IMPLEMENTATION ASSUMED*/
//RETURN THE POSITION AT WHICH X IS FIND
Position Find(ElementType x[],List l)
{
	Position p;
	
	p = l->Next;
	while(p!=NULL && strcmp(p->Element,x)!=0)
		p = p->Next;
	
	return p;
}
/* RETURNS THE NUMBER OF POSITION AT WHICH X IS FOUND */
/*HEADER IMPLEMENTATION ASSUMED*/
int FindWhere(ElementType x[],List l)
{
 	Position p;
	int i = 0;
        p = l->Next;
        while(p!=NULL && strcmp(p->Element,x)!=0)
                {
			p = p->Next;
			i++;
		}
	if(p == NULL)
		i = -1;
	return i;
}
/*DELETE THE FIRST OCCURENCE*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Delete(ElementType x[],List l)
{
	Position p , tmpcell ;
	
	p = FindPrevious(x,l);
	
	if(!Islast(p,l))
	{
		tmpcell = p->Next;
		p->Next = tmpcell->Next;
		free(tmpcell);
	}
}
/*RETURN THE POSITION PREVIOUS TO FIRST OCCURENCE OF X*/
/*HEADER IMPLEMENTATION ASSUMED*/
Position FindPrevious(ElementType x[],List l)
{
	Position p;
	
	p = l;
	
	while(p->Next != NULL && strcmp(p->Next->Element,x)!=0)
		p = p->Next;

	return p;
}
/*INSERT AFTER LEGAL POSITION P*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Insert(ElementType x[],List l, Position p)
{
	Position tmpcell ;
	
	tmpcell = malloc(sizeof(struct node ));
	
	if(tmpcell == NULL)
		puts("OUT OF SPACE");
	
	strcpy(tmpcell->Element,x);
	tmpcell->Next = p->Next;
	p->Next = tmpcell;
}
/*INSERT THE ELEMENT AFTER WHICHEVER TRAVERSING LIST FOR N SUCCESIVE POSITION FROM START*/
/*HEADER IMPLEMENTATION ASSUMED*/
void InsertAfter(ElementType x[],List l,int n)
{
	Position p;
	p = l;
	
	if(n > Count(l))
	{
		printf("\nTHERE IS ONLY %d NUMBER OF ELEMENTS IN LIST\n",Count(l));
		return;
	}
	if(n<0)
	{
		printf("\nINVALID POSITION\n");
	}

	while( n > 0)
	{
		p = p->Next;
		n--;
	}
	Insert(x,l,p);

}
/*RETURN THE SIZE OF LIST*/
/*HEADER IMPLEMENTATION ASSUMED*/
int Count(List l)
{
	int count=0;
	
	while((l = l->Next) != NULL)
		count++;

	return count;
}
//PRINT THE ELEMENT OF ENTIRE LIST
/*HEADER IMPLEMENTATION ASSUMED*/
void Display(List l)
{
	while((l = l->Next) != NULL)
		printf("%s  ",l->Element);
	
	printf("\n");
}
/*DELETE THE ENTIRE LIST EXCEPT HEADER*/
/*HEADER IMPLEMENTATION ASSUMED*/
void DeleteList(List l)
{
	Position p,tmp;
	
	p = l->Next;
	l->Next = NULL;
	while(p != NULL)
	{
		tmp = p->Next;
		free(p);
		p = tmp;
	}
}
/*REVERSE THE LIST BY REORDERING THE LINK IN OPPOSITE DIRECTION*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Reverse(List l)
{
	Position p,q,r;
	p = l->Next;
	
	r = NULL;
	
	while(p!=NULL)
	{
		q = r;
		r = p;
		p = p->Next;
		r ->Next=q;
	}

	l->Next = r;
}
/*SORT THE LIST USING SELECTION SORT*/
void SelectionSort(List l)
{
	Position p,Max,q,r;
	
	p = l->Next;
	if(!IsEmpty(l))
	{
		while(p->Next !=NULL)
		{
			Max = p;
			for(q = p; q!=NULL; q = q->Next)
			{
				if(Max->Element < q->Element)
					Max = q;
			}
		//	Swap(Max,p);
			r = p;
		 	p = p->Next;
			SwapLink(Max,r,l);
//			p = p->Next;
		}
	}
}
/*SWAP THE ELEMENTS AT SPECIFIED POSITIONS*/
/*HEADER IMPLEMENTATION ASSUMED*/
/*
void Swap(Position p,Position q)
{
	ElementType temp[30];
	
	temp = p->Element;
	
	p->Element = q->Element;
	
	q->Element = temp;
}*/
/*SWAP THE LINKS OF SPECIFIED POSITION*/
/*HEADER IMPLEMENTATION ASSUMED*/
void SwapLink(Position p,Position q,List l)
{
	Position r,s,tmp;
	r = FindPre(p,l);
	s = FindPre(q,l);
	r->Next = q;
	s->Next = p;
	tmp = p->Next;
	p->Next = q->Next;
	q->Next = tmp;
}
/*RETURN THE PREVIOUS POSITION TO GIVEN POSITION*/
/*HEADER IMPLEMENTATION ASSUMED*/
Position FindPre(Position p,List l)
{
	Position r,q;
	
	q = l->Next;
	r = l;
	while(q!=NULL && q!=p)
	{
		r = q;
		q = q->Next;
	}

	return r;
}

