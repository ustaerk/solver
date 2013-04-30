#include "solver.h"

void update_alphabeta(problem *p, tmatrix *m)
{
	int i=0,j=0;
	p->alpha[0] = 0;
	for(i=0; i < p->angebot; i++)
	{
		for(j=0; j < p->nachfrage; j++)
		{
			if(m->matrix[i*m->y+j] == 1)
			{
				if(i==0)
					p->beta[j] = p->matrix[i*p->nachfrage+j] - p->alpha[i];
				if(p->alpha[i])
				{
					p->beta[j] = p->matrix[i*p->nachfrage+j] - p->alpha[i];
					int x=0;
					for(x=0; x < p->nachfrage; x++)
					{
						if(m->matrix[i*m->y+x] == 1)
						{
							p->beta[x] = p->matrix[i*p->nachfrage+x] - p->alpha[i];
						}
					}
				}
				if(p->beta[j])
				{
					p->alpha[i] = p->matrix[i*p->nachfrage+j] - p->beta[j];
					int x=0;
					for(x=0; x < p->angebot; x++)
					{
						if(m->matrix[x*m->y+j] == 1)
						{
							p->alpha[x] = p->matrix[x*p->nachfrage+j] - p->beta[j];
						}
					}
				}
			}
		}
	}
}

void relcost(problem *p, matrix *x)
{
	int i=0,j=0;
	for(i=0; i < p->angebot; i++)
	{
		for(j=0; j < p->nachfrage; j++)
		{
			x->matrix[i*x->y+j] = p->matrix[i*p->nachfrage+j] - p->alpha[i] - p->beta[j];
		}
	}
}

void print_alphabeta(problem *p)
{
	int i=0;
	printf("Alpha: ");
	for(i=0; i < p->angebot; i++)
	{
		printf("%4d",p->alpha[i]);
	}
	printf("\n");
	printf("Beta:  ");
	for(i=0; i < p->nachfrage; i++)
	{
		printf("%4d",p->beta[i]);
	}
	printf("\n");
}

void modi(problem *p, matrix *x)
{
	matrix *rcost = newmatrix(p->angebot,p->nachfrage);
	nochmal:
	{
		tmatrix *m = newtmatrix(x);
		update_alphabeta(p,m);
		relcost(p,rcost);
		if(DEBUG)
		{
			printf("\nLoesung:\n");
			printmatrix(x);
			printf("\n\n");
			printf("Wahrheitsmatrix zu Loesung:\n");
			printtmatrix(m);
			printf("\n\n");
			printf("\nAlpha/Beta dazu:\n");
			print_alphabeta(p);
			printf("\n\n");
			printf("\nRelative Kosten dazu:\n");
			printmatrix(rcost);
			printf("\n\n");
		}
		int i=0,j=0,min=0,merker_i=0,merker_j=0;
		for(i=0; i < rcost->x; i++)
		{
			for(j=0; j < rcost->y; j++)
			{
				if(rcost->matrix[i*rcost->y+j] < min)
				{
					min = rcost->matrix[i*rcost->y+j];
					merker_i = i;
					merker_j = j;
				}
			}
		}
		if(min < 0)
		{
			node *n = newnode(merker_i,merker_j);
			if(findezyklus(n,m))
			{
				int mfluss = maxfluss(n,x,0,BIGINT);
				/* Basisloesung anpassen */
				aenderloesung(x,n,mfluss,0,0);
				goto nochmal;
			}
		}
	}
}
