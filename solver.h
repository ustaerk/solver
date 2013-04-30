/*
 * solver.h - Headerdatei fuer 'solver'
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Stellt Datenstrukturen zur Speicherung der Daten bereit
 * und enthaelt Funktionsdeklarationen.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0
#define BIGINT 2147483647

/*
 * Datentyp zum Halten des kompletten Problems
 */

typedef struct problem_s
{
	int angebot;		/* # Angebotsknoten */
	int nachfrage;		/* # Nachfrageknoten */
	int num_spalten;	/* # Spalten */
	int num_zeilen;		/* # Zeilen */
	int num_kanten;
	int *zeilen;		/* Zeile gestrichen = 0 */
	int *spalten;		/* Spalte gestrichen = 0 */
	int *angebote;		/* Kapazitaet der Angebotsknoten */
	int *nachfragen;	/* Kapazitaet der Nachfrageknoten */
	int *matrix;		/* Kosten auf den Kanten */
	int *vogel_spalten;	/* Differenz zwischen besten und zweitbesten Kosten fuer die Spalten */
	int *vogel_zeilen;  /* Differenz zwischen besten und zweitbesten Kosten fuer die Zeilen */
	int *alpha;			/* alpha fuer modi */
	int *beta;			/* beta fuer modi */
} problem;

/*
 * eine Matrix (z.B. die Ergebnismatrix)
 */
 
typedef struct matrix_s
{
	int x;				/* x-Dimension */
	int y;				/* y-Dimension */
	int *matrix;		/* Zeiger auf Speicherbereich mit den Werten */
} matrix;

/*
 * Speichert das Maximum von vogel_spalten oder
 * vogel_zeilen und speichert dessen Position im 
 * array.
 */

typedef struct vogel_s
{
	int coord;			/* int Wert mit Position in vogel_spalte bzw. vogel_zeile */
	int max;			/* Maximum-Wert */
} vogel_t;

typedef struct tmatrix_s
{
	int x;				/* x-Dimension */
	int y;				/* y-Dimension */
	int *matrix;		/* Zeiger auf Speicherbereich mit den Werten */
} tmatrix;

typedef struct node_s { int x; int y; struct node_t *next;} node;

/*
 * Funktionen aus problem.c
 */

problem *newproblem(int angebot, int nachfrage);
void streichezeile(int z, problem *p);
void streichespalte(int s, problem *p);
void updatezeile(int i, problem *p);
void updatespalte(int j, problem *p);

/*
 * Funktionen aus vogel.c
 */
 
void vogel(problem*);
vogel_t *vogel_max_spalten(problem *p);
vogel_t *vogel_max_zeilen(problem *p);
void waehlekante_vogel(problem*, matrix*);

/*
 * Funktionen aus common.c
 */
 
matrix *newmatrix(int x, int y);
void printtmatrix(tmatrix *x);
void printgraph(problem *p);
void printmatrix(matrix *x);
int min(int a, int b);

/*
 * Variablen zum Speichern der Anzahl der Knoten und Kanten
 */

int nodes,edges;

/*
 * Funktionen aus graphreader.c
 */

problem *readparameters(int *nodes, int *edges);
void readgraph(problem *p);

/*
 * Funktionen aus nwe.c
 */

void waehlekante_nwe(problem *p, matrix *x);

/*
 * Funktionen aus mkk.c
 */

void waehlekante_mkk(problem *p, matrix *x);


/*
 * Funktionen aus zyklus.c
 */

node *newnode(int x, int y);
int findezyklus(node *n, tmatrix *m);
int nextzeilennachbar(node *n, tmatrix *m, node *p);
int nextspaltennachbar(node *n, tmatrix *m, node *p);
tmatrix *newtmatrix(matrix *m);
void cycleprint(node *n);
int zykluskosten(node *n, problem *p, int i, int j);
int maxfluss(node *n, matrix *x, int i, int j);
void aenderloesung(matrix *x, node *n, int mfluss, int i, int nu);

/*
 * Funktionen aus stepstone.c
 */

void stepstone(matrix *x, problem *p);

void update_alphabeta(problem *p, tmatrix *m);
void print_alphabeta(problem *p);
void modi(problem *p, matrix *x);
