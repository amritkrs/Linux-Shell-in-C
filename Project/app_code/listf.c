/*THIS FILE CONTAINS THE DIFFERENT ADT FUNCTIONS FOR LINKED List_fS
  WRITTEN BY:- AMRIT KUMAR
  DATE :- 28/11/12
*/

#include"listf.h"

//TO CHECK IF List_f IS EMPTY
/*HEADER IMPLEMENTATION ASSUMED*/
int IsEmpty_f(List_f l)
{
	return l->Next == NULL;
}
/*HEADER IMPLEMENTATION ASSUMED*/
int IsLast_f(Position_f p,List_f l)
{
	return p->Next == NULL;
}
/*HEADER IMPLEMENTATION ASSUMED*/
//RETURN THE Position_f AT WHICH X IS Find_f
Position_f Find_f(float x,List_f l)
{
	Position_f p;
	
	p = l->Next;
	while(p!=NULL && p->Element != x)
		p = p->Next;
	
	return p;
}
/* RETURNS THE NUMBER OF Position_f AT WHICH X IS FOUND */
/*HEADER IMPLEMENTATION ASSUMED*/
int Find_fWhere(float x,List_f l)
{
 	Position_f p;
	int i = 0;
        p = l->Next;
        while(p!=NULL && p->Element != x)
                {
			p = p->Next;
			i++;
		}
	if(p == NULL)
		i = -1;
	return i;
}
/*Delete_f THE FIRST OCCURENCE*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Delete_f(float x,List_f l)
{
	Position_f p , tmpcell ;
	
	p = FindPrevious_f(x,l);
	
	if(!IsLast_f(p,l))
	{
		tmpcell = p->Next;
		p->Next = tmpcell->Next;
		free(tmpcell);
	}
}
/*RETURN THE Position_f PREVIOUS TO FIRST OCCURENCE OF X*/
/*HEADER IMPLEMENTATION ASSUMED*/
Position_f FindPrevious_f(float x,List_f l)
{
	Position_f p;
	
	p = l;
	
	while(p->Next != NULL && p->Next->Element != x)
		p = p->Next;

	return p;
}
/*Insert_f AFTER LEGAL Position_f P*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Insert_f(float x,List_f l, Position_f p)
{
	Position_f tmpcell ;
	
	tmpcell = malloc(sizeof(struct node_f ));
	
	if(tmpcell == NULL)
		puts("OUT OF SPACE");
	
	tmpcell->Element = x;
	tmpcell->Next = p->Next;
	p->Next = tmpcell;
}
/*Insert_f THE ELEMENT AFTER WHICHEVER TRAVERSING List_f FOR N SUCCESIVE Position_f FROM START*/
/*HEADER IMPLEMENTATION ASSUMED*/
void InsertAfter_f(float x,List_f l,int n)
{
	Position_f p;
	p = l;
	
	if(n > Count_f(l))
	{
		printf("\nTHERE IS ONLY %d NUMBER OF ELEMENTS IN List_f\n",Count_f(l));
		return;
	}
	if(n<0)
	{
		printf("\nINVALID Position_f\n");
	}

	while( n > 0)
	{
		p = p->Next;
		n--;
	}
	Insert_f(x,l,p);

}
/*RETURN THE SIZE OF List_f*/
/*HEADER IMPLEMENTATION ASSUMED*/
int Count_f(List_f l)
{
	int Count_f=0;
	
	while((l = l->Next) != NULL)
		Count_f++;

	return Count_f;
}
//PRINT THE ELEMENT OF ENTIRE List_f
/*HEADER IMPLEMENTATION ASSUMED*/
void Display_f(List_f l)
{
	while((l = l->Next) != NULL)
		printf("%f ",l->Element);
	
	printf("\n");
}
/*Delete_f THE ENTIRE List_f EXCEPT HEADER*/
/*HEADER IMPLEMENTATION ASSUMED*/
void DeleteList_f(List_f l)
{
	Position_f p,tmp;
	
	p = l->Next;
	l->Next = NULL;
	while(p != NULL)
	{
		tmp = p->Next;
		free(p);
		p = tmp;
	}
}
/*Reverse_f THE List_f BY REORDERING THE LINK IN OPPOSITE DIRECTION*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Reverse_f(List_f l)
{
	Position_f p,q,r;
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
/*SORT THE List_f USING SELECTION SORT*/
void SelectionSort_f(List_f l)
{
	Position_f p,Max,q,r;
	
	p = l->Next;
	if(!IsEmpty_f(l))
	{
		while(p->Next !=NULL)
		{
			Max = p;
			for(q = p; q!=NULL; q = q->Next)
			{
				if(Max->Element < q->Element)
					Max = q;
			}
		//	Swap_f(Max,p);
			r = p;
		 	p = p->Next;
			Swap_fLink_f(Max,r,l);
//			p = p->Next;
		}
	}
}
/*Swap_f THE ELEMENTS AT SPECIFIED Position_fS*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Swap_f(Position_f p,Position_f q)
{
	float temp;
	
	temp = p->Element;
	
	p->Element = q->Element;
	
	q->Element = temp;
}
/*Swap_f THE LINKS OF SPECIFIED Position_f*/
/*HEADER IMPLEMENTATION ASSUMED*/
void Swap_fLink_f(Position_f p,Position_f q,List_f l)
{
	Position_f r,s,tmp;
	r = FindPre_f(p,l);
	s = FindPre_f(q,l);
	r->Next = q;
	s->Next = p;
	tmp = p->Next;
	p->Next = q->Next;
	q->Next = tmp;
}
/*RETURN THE PREVIOUS Position_f TO GIVEN Position_f*/
/*HEADER IMPLEMENTATION ASSUMED*/
Position_f FindPre_f(Position_f p,List_f l)
{
	Position_f r,q;
	
	q = l->Next;
	r = l;
	while(q!=NULL && q!=p)
	{
		r = q;
		q = q->Next;
	}

	return r;
}

