/*
 * nwe.c - Nordwest-Ecken-Regel
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Enthaelt alle notwendigen Funktionen, um eine
 * Basisloesung nach der Nordwest-Ecken-Regel zu
 * erstellen.
 */

#include "solver.h"

/*
 * Kante (Zeile x Spalte) nach Nordwest-Ecken-Regel
 * bestimmen und in die Basisloesung aufnehmen.
 */
void waehlekante_nwe(problem *p, matrix *x)
{
	int i,j;
	for(j=0; j < p->nachfrage; j++)
	{
		/* Wenn die Zeile gestrichen ist, ueberspringen. */
		if(p->spalten[j] == 0)
			continue;
		else
		{
			for(i=0; i < p->angebot; i++)
			{
				/* Wenn die Spalte gestrichen ist, ueberspringen. */
				if(p->zeilen[i] == 0)
					continue;
				else
				{
					/* Fluss bestimmen und Kapazitaeten anpassen. */
					int fluss = min(p->angebote[i],p->nachfragen[j]);
					p->angebote[i] -= fluss;
					p->nachfragen[j] -= fluss;
					x->matrix[i*x->y+j] = fluss;
					/* Wenn Kapazitaet von Angebot und Nachfrage gleichzeitig 0, dann erst Zeile, danach Spalte streichen. */
					if(p->angebote[i] == 0 && p->nachfragen[j] == 0 && p->num_spalten > 1)
					{
						streichespalte(j,p);
						x->matrix[i*x->y+j+1] = 0;
						streichezeile(i,p);
					}
					/* Angebot = 0 -> Zeile Streichen */
					else if(p->angebote[i] == 0)
						streichezeile(i,p);
					/* Nachfrage = 0 -> Spalte Streichen */
					else if(p->nachfragen[j] == 0)
						streichespalte(j,p);
					if(DEBUG)
						printf("Waehle Kante %3d,%3d\n",i,j);
					break;
				}
			}
			break;
		}
	}
}
