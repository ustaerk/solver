/*
 * mkk.c - Methode der kleinsten Kosten
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Enthaelt alle notwendigen Funktionen, um eine
 * Basisloesung nach der Methode der kleinsten Kosten
 * zu erstellen.
 */

#include "solver.h"

/*
 * Kante (Zeile x Spalte) nach der Methode der kleinsten
 * Kosten bestimmen und in die Basisloesung aufnehmen.
 */

void waehlekante_mkk(problem *p, matrix *x)
{
	int i,j,min_c=BIGINT,merker_i=0,merker_j=0;
	for(i=0; i < p->angebot; i++)
	{
		/* Wenn die Zeile gestrichen ist, ueberspringen. */
		if(p->zeilen[i] == 0)
			continue;
		else
		{
			for(j=0; j < p->nachfrage; j++)
			{
				/* Wenn die Spalte gestrichen ist, ueberspringen. */
				if(p->spalten[j] == 0)
					continue;
				else
				{
					/* Minimum gefunden -> Position speichern. */
					if(p->matrix[i*p->nachfrage+j] < min_c)
					{
						min_c = p->matrix[i*p->nachfrage+j];
						merker_i = i;
						merker_j = j;
					}
				}
			}
		}
	}
	i = merker_i;
	j = merker_j;
	if(DEBUG)
		printf("Waehle Kante %3d,%3d\n",i,j);
	/* Fluss bestimmen und Kapazitaeten anpassen. */
	int fluss = min(p->angebote[i],p->nachfragen[j]);
	p->angebote[i] -= fluss;
	p->nachfragen[j] -= fluss;
	x->matrix[i*x->y+j] = fluss;
	/* Wenn Kapazitaet von Angebot und Nachfrage gleichzeitig 0, dann erst Zeile, danach Spalte streichen */
	if(p->angebote[i] == 0 && p->nachfragen[j] == 0 && p->num_spalten > 1)
	{
		streichezeile(i,p);
		x->matrix[i*x->y+j+1] = 0;
		streichespalte(j,p);
	}
	/* Angebot = 0 -> Zeile Streichen */
	else if(p->angebote[i] == 0)
		streichezeile(i,p);
	/* Nachfrage = 0 -> Spalte Streichen */
	else if(p->nachfragen[j] == 0)
		streichespalte(j,p);
}
