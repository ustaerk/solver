/*
 * vogel.c - Vogel'sche Approximationsmethode
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Enthaelt alle notwendigen Funktionen, um eine
 * Basisloesung nach der Methode der Vogel'schen
 * Approximationsmethode zu erstellen.
 */

#include "solver.h"

/*
 * Differenz zwischen besten und zweitbesten Kosten bestimmen
 * und in vogel_spalten bzw. vogel_zeilen speichern.
 */

void vogel(problem *p)
{
	int i,j,min_one,min_two;
	for(i = 0; i < p->angebot; i++)
	{
		min_one=999999;
		min_two=999999;
		/* Wenn die Zeile gestrichen ist, ueberspringen. */
		if(p->zeilen[i] == 0)
			continue;
		for(j=0; j < p->nachfrage; j++)
		{
			/* Wenn die Spalte gestrichen ist, ueberspringen. */
			if(p->spalten[j] == 0)
				continue;
			/* Beste und zweitbeste Kosten finden und zwischenspeichern */
			if(p->matrix[i*p->nachfrage+j] < min_one)
			{
				min_two = min_one;
				min_one = p->matrix[i*p->nachfrage+j];
			}
			else if(p->matrix[i*p->nachfrage+j] < min_two)
				min_two = p->matrix[i*p->nachfrage+j];
		}
		/* Differenz zwischen besten und zweitbesten Kosten berechnen und speichern */
		if(p->num_spalten > 1)
			p->vogel_zeilen[i] = min_two - min_one;
	}
	for(j = 0; j < p->nachfrage; j++)
	{
		min_one=BIGINT,min_two=BIGINT;
		/* Wenn die Spalte gestrichen ist, ueberspringen. */
		if(p->spalten[j] == 0)
			continue;
		for(i = 0; i < p->angebot; i++)
		{
			/* Wenn die Zeile gestrichen ist, ueberspringen. */
			if(p->zeilen[i] == 0)
				continue;
			/* Beste und zweitbeste Kosten finden und zwischenspeichern */
			if(p->matrix[i*p->nachfrage+j] <= min_one)
			{
				min_two = min_one;
				min_one = p->matrix[i*p->nachfrage+j];
			}
			else if(p->matrix[i*p->nachfrage+j] <= min_two)
				min_two = p->matrix[i*p->nachfrage+j];
		}
		/* Differenz zwischen besten und zweitbesten Kosten berechnen und speichern */
		if(p->num_zeilen > 1)
			p->vogel_spalten[j] = min_two - min_one;
	}
}

/*
 * Das Maximum und seine Koordinate aus vogel_spalten suchen
 */

vogel_t *vogel_max_spalten(problem *p)
{
	vogel_t *v = (vogel_t*) malloc (sizeof(struct vogel_s));
	int i=0,s=0,max=0;
	for(i = 0; i < p->nachfrage; i++)
	{
		/* Wenn die Spalte gestrichen ist, ueberspringen. */
		if(p->spalten[i] == 0)
			continue;
		if(p->vogel_spalten[i] > max)
		{
			max = p->vogel_spalten[i];
			s = i;
		}
	}
	v->coord = s;
	v->max = max;
	return v;
}

/*
 * Das Maximum und seine Koordinate aus vogel_zeilen suchen
 */

vogel_t *vogel_max_zeilen(problem *p)
{
	vogel_t *v = (vogel_t*) malloc (sizeof(struct vogel_s));
	int i=0,z=0,max=0;
	for(i = 0; i < p->angebot; i++)
	{
		/* Wenn die Zeile gestrichen ist, ueberspringen. */
		if(p->zeilen[i] == 0)
			continue;
		if(p->vogel_zeilen[i] > max)
		{
			max = p->vogel_zeilen[i];
			z = i;
		}
	}
	v->coord = z;
	v->max = max;
	return v;
}

/*
 * Kante (Zeile x Spalte) nach der Vogel'schen Approximationsmethode
 * bestimmen und in die Basisloesung aufnehmen.
 */

void waehlekante_vogel(problem *p, matrix *x)
{
	vogel_t *max_spalten,*max_zeilen;
	max_spalten = vogel_max_spalten(p);
	max_zeilen = vogel_max_zeilen(p);
	int merker_i=0,merker_j=0;
	/* Groesste Differenz liegt in einer Zeile, Zeile steht fest. */
	if(max_zeilen->max >= max_spalten->max)
	{
		merker_i = max_zeilen->coord;
		int j,min=BIGINT;
		for(j = 0; j < p->nachfrage; j++)
		{
			/* Wenn die Spalte gestrichen ist, ueberspringen. */
			if(p->spalten[j] == 0)
				continue;
			/* Noch Spalte finden (minimale Kosten innerhalb der Zeile) */
			if(p->matrix[merker_i*p->nachfrage+j] <= min)
			{
				merker_j = j;
				min = p->matrix[merker_i*p->nachfrage+j];
			}
		}
	}
	/* Groesste Differenz liegt in einer Spalte, Spalte steht fest. */
	else if(max_spalten->max > max_zeilen->max)
	{
		merker_j = max_spalten->coord;
		int i,min=BIGINT;
		for(i = 0; i < p->angebot; i++)
		{
			/* Wenn die Zeile gestrichen ist, ueberspringen. */
			if(p->zeilen[i] == 0)
				continue;
			/* Noch Zeile finden (minimale Kosten innerhalb der Spalte) */
			if(p->matrix[i*p->nachfrage+merker_j] <= min)
			{
				merker_i = i;
				min = p->matrix[i*p->nachfrage+merker_j];
			}
		}
	}
	int i = merker_i;
	int j = merker_j;
	/* Fluss bestimmen und Kapazitaeten anpassen. */
	int fluss = min(p->angebote[i],p->nachfragen[j]);
	p->angebote[i] -= fluss;
	p->nachfragen[j] -= fluss;
	x->matrix[i*x->y+j] = fluss;
	/* Wenn Kapazitaet von Angebot und Nachfrage gleichzeitig 0, dann erst Zeile, danach Spalte streichen. */
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
