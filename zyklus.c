#include "solver.h"

tmatrix *newtmatrix(matrix *m)
{
	tmatrix *tm = (tmatrix*) malloc(sizeof(struct tmatrix_s));
	tm->x = m->x;
	tm->y = m->y;
	tm->matrix = (int*) malloc(sizeof(int) * m->x * m->y);
	int i,j;
	for(i = 0; i < tm->x; i++)
	{
		for( j = 0; j < tm->y; j++)
		{
			if(m->matrix[i*tm->y+j] >= 0)
				tm->matrix[i*tm->y+j] = 1;
			else
				tm->matrix[i*tm->y+j] = 0;
		}
	}
	return tm;

}

node *newnode(int x, int y)
{
	node *n = (node*) malloc(sizeof(struct node_s));
	n->x = x;
	n->y = y;
	n->next = 0;
	return n;
}

int findezyklus(node *n, tmatrix *m)
{
	node *p = n;
	if(!nextzeilennachbar(n,m,p))
	{
		if(!nextspaltennachbar(n,m,p))
		{
			return 0;
		}
	}
	return 1;
}

int nextzeilennachbar(node *n, tmatrix *m, node *p)
{
	int todo[m->x+m->y-1];
	int y=0,zaehler=0;
	for(y=0; y < m->y; y++)
	{
		if(y == n->y)
			continue;
		if(m->matrix[n->x*m->y+y] == 1)
		{
			todo[zaehler] = y;
			zaehler++;
		}
	}
	for(y=0; y < zaehler; y++)
	{
		if(DEBUG)
			printf("%d,%d => Probiere %d,%d\n",n->x,n->y,n->x,todo[y]);
		node *new = newnode(n->x,todo[y]);
		if(todo[y] == p->y)
		{
			n->next = (struct node_t*) new;
			return 1;
		}
		int next = nextspaltennachbar(new, m, p);
		if(next)
		{
			n->next = (struct node_t*) new;
			return 1;
		}
	}
	return 0;
}

int nextspaltennachbar(node *n, tmatrix *m, node *p)
{
	int todo[m->x+m->y-1];
	int x=0,zaehler=0;
	for(x=0; x < m->x; x++)
	{
		if(x == n->x)
			continue;
		if(m->matrix[x*m->y+n->y] == 1)
		{
			todo[zaehler] = x;
			zaehler++;
		}
	}
	for(x=0; x < zaehler; x++)
	{
		if(DEBUG)
			printf("%d,%d => Probiere %d,%d\n",n->x,n->y,n->y,todo[x]);
		node *new = newnode(todo[x],n->y);
		if(todo[x] == p->x)
		{
			n->next = (struct node_t*) new;
			return 1;
		}
		int next = nextzeilennachbar(new, m, p);
		if(next)
		{
			n->next = (struct node_t*) new;
			return 1;
		}
	}
	return 0;
}

void cycleprint(node *n)
{
	if(n != NULL)
	{
		printf("%2d,%2d\n",n->x,n->y);
		cycleprint((node*)n->next);
	}
}

int zykluskosten(node *n, problem *p, int i, int j)
{
	if(n != NULL)
	{
		if(i%2 == 0)
		{
			i++;
			j += p->matrix[n->x*p->nachfrage+n->y];
			return zykluskosten((node*)n->next,p,i,j);
		}
		else
		{
			i++;
			j -= p->matrix[n->x*p->nachfrage+n->y];
			return zykluskosten((node*)n->next,p,i,j);
		}
	}
	return j;
}

int maxfluss(node *n, matrix *x, int i, int j)
{
	if(n != NULL)
	{
		if(i%2 != 0)
		{
			i++;
			if(x->matrix[n->x*x->y+n->y] < j)
				j = x->matrix[n->x*x->y+n->y];
			return maxfluss((node*)n->next,x,i,j);
		}
		else
		{
			i++;
			return maxfluss((node*)n->next,x,i,j);
		}
	}
	return j;
}

void aenderloesung(matrix *x, node *n, int mfluss, int i, int nu)
{
	if(n != NULL)
	{
		if(i%2 == 0)
		{
			i++;
			if(x->matrix[n->x*x->y+n->y] == -1)
				x->matrix[n->x*x->y+n->y] = mfluss;
			else
				x->matrix[n->x*x->y+n->y] += mfluss;
			aenderloesung(x,(node*)n->next,mfluss,i,nu);
		}
		else
		{
			i++;
			if(x->matrix[n->x*x->y+n->y] == mfluss)
			{
				if(!nu)
				{
					x->matrix[n->x*x->y+n->y] = -1;
					nu = 1;
				}
				else if(nu)
				{
					x->matrix[n->x*x->y+n->y] = 0;
				}
			}
			else
			{
				x->matrix[n->x*x->y+n->y] -= mfluss;
			}
			aenderloesung(x,(node*)n->next,mfluss,i,nu);
		}
	}
}

