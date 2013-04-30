#include "solver.h"

void stepstone(matrix *x, problem *p)
{
	tmatrix *m = newtmatrix(x);
	printf("\nWahrheitsmatrix zur Basisloesung:\n\n");
	printtmatrix(m);
	printf("\n");
	nochmal:
	{
		m = newtmatrix(x);
		int i=0,j=0;
		for(i=0; i < m->x; i++)
		{
			for(j=0; j < m->y; j++)
			{
				if(m->matrix[i*m->y+j] == 0)
				{
					node *n = newnode(i,j);
					if(findezyklus(n,m))
					{
						int kosten = zykluskosten(n,p,0,0);
						if(kosten < 0)
						{
							int mfluss = maxfluss(n,x,0,BIGINT);
							/* Basisloesung anpassen */
							aenderloesung(x,n,mfluss,0,0);
							goto nochmal;
						}
					}
				}
			}
		}
	}
}
