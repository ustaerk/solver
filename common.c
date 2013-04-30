/*
 * common.c - gemeinsam genutzte Funktionen
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Enthaelt generische Funktionen zur Ausgabe und zur
 * gemeinsamen Benutzung der einzelnen Programmteile.
 */

#include "solver.h"

/*
 * Reserviert Speicher fuer eine Matrix (z.B. Basisloesung) und
 * initialisiert diese.
 */

matrix *newmatrix(int x, int y)
{
	matrix *m = (matrix*) malloc(sizeof(struct matrix_s));
	m->x = x;
	m->y = y;
	m->matrix = (int*) malloc(sizeof(int) * x * y);
	/* Matrix mit -1 fuellen */
	int i,j;
	for(i = 0; i < x; i++)
	{
		for( j = 0; j < y; j++)
		{
			m->matrix[i*y+j] = -1;
		}
	}
	return m;
}

/*
 * Gibt einen eingelesenen Graphen auf der Konsole aus.
 */

void printgraph(problem *p)
{
	printf("Kap.     |");
	int i,j;
	for(i=0; i < p->nachfrage; i++)
		printf("%4d",p->nachfragen[i]);
	printf("\n");
	printf("  Knoten |");
	for(i=p->angebot; i < p->nachfrage+p->angebot; i++)
		printf("%4d",i+1);
	printf("\n");
	printf("----------");
	for(i=p->angebot; i < p->nachfrage+p->angebot; i++)
		printf("----");
	printf("\n");
	for(i=0; i < p->angebot; i++) {
		printf("%4d%4d |",p->angebote[i],i+1);
		for(j=0; j < p->nachfrage; j++) {
			if(p->matrix[i*p->nachfrage+j] != BIGINT)
				printf("%4d", p->matrix[i*p->nachfrage+j]);
			else
				printf("    ");
		}
		printf("\n");
	}
}

/*
 * Gibt eine Matrix auf der Konsole aus.
 */

void printmatrix(matrix *x)
{
	int i,j;
	printf("Knoten |");
	for(i=x->x; i < x->x+x->y; i++)
		printf("%4d",i+1);
	printf("\n");
	printf("--------");
	for(i=x->x; i < x->x+x->y; i++)
		printf("----");
	printf("\n");
	for(i=0; i < x->x; i++) {
		printf("%6d |",i+1);
		for(j=0; j < x->y; j++) {
			if(x->matrix[i*x->y+j] != -1)
				printf("%4d", x->matrix[i*x->y+j]);
			else
				printf("    ");
		}
		printf("\n");
	}
}

void printtmatrix(tmatrix *x)
{
	int i,j;
	printf("Knoten |");
	for(i=x->x; i < x->x+x->y; i++)
		printf("%4d",i+1);
	printf("\n");
	printf("--------");
	for(i=x->x; i < x->x+x->y; i++)
		printf("----");
	printf("\n");
	for(i=0; i < x->x; i++) {
		printf("%6d |",i+1);
		for(j=0; j < x->y; j++) {
			if(x->matrix[i*x->y+j] != -1)
				printf("%4d", x->matrix[i*x->y+j]);
			else
				printf("    ");
		}
		printf("\n");
	}
}

/*
 * Bestimmt das Minimum zweier Zahlen.
 */

int min(int a, int b)
{
	return a <= b ? a : b;
}
