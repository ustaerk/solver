/*
 * problem.c - Initialisierung und Verwaltung des Problems.
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Enthaelt alle notwendigen Funktionen, um ein
 * Optimierungsproblem zu initialisieren und zu
 * verwalten
 */

#include "solver.h"

/*
 * Reserviert Speicher fuer ein neues Problem, initialisiert es
 * und liefert einen Pointer auf dessen Speicherbeginn.
 */

problem *newproblem(int angebot, int nachfrage)
{
	problem *p = (problem*) malloc (sizeof( struct problem_s) );
	p->angebot = angebot;
	p->nachfrage = nachfrage;
	p->num_kanten = edges;
	p->num_spalten = nachfrage;
	p->num_zeilen = angebot;
	p->angebote = (int*) malloc( sizeof(int) * angebot);
	p->nachfragen = (int*) malloc( sizeof(int) * nachfrage);
	p->zeilen = (int*) malloc( sizeof(int) * angebot);
	p->spalten = (int*) malloc( sizeof(int) * nachfrage);
	p->matrix = (int*) malloc( sizeof(int) * angebot * nachfrage );
	p->vogel_spalten = (int*) malloc( sizeof(int) * nachfrage);
	p->vogel_zeilen = (int*) malloc( sizeof(int) * angebot);
	p->alpha = (int*) malloc(sizeof(int) * angebot);
	p->beta = (int*) malloc(sizeof(int) * nachfrage);
	/* Matrix, zeilen und spalten initialisieren */
	int i,j;
	for(i=0; i < angebot; i++) {
		for(j=0; j < nachfrage; j++) {
			p->matrix[i*nachfrage+j] = BIGINT;
		}
	}
	for(i=0; i < angebot; i++)
		p->zeilen[i] = 1;
	for(i=0; i < nachfrage; i++)
		p->spalten[i] = 1;
	return p;
}

/*
 * Streicht eine Zeile aus dem Problem (Kapazitaet des Angebotsknoten = 0).
 */

void streichezeile(int z, problem *p)
{
	p->zeilen[z] = 0;
	p->num_zeilen--;
	p->vogel_zeilen[z] = -1;
	if(DEBUG)
		printf("Streiche Zeile %3d\n",z);
}

/*
 * Streicht eine Spalte aus dem Problem (Kapazitaet des Nachfrageknoten = 0).
 */

void streichespalte(int s, problem *p)
{
	p->spalten[s] = 0;
	p->num_spalten--;
	p->vogel_spalten[s] = -1;
	if(DEBUG)
		printf("Streiche Spalte %3d\n",s);
}
