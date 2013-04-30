/*
 * graphreader.c - Einlesen des Graphen
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Enthaelt Funktionen zum Einlesen eines von Netgen
 * generierten Graphen und dessen Speicherung in den
 * dafuer vorgesehenen Datenstrukturen.
 */
 
#include "solver.h"

/*
 * Einlesen der Graph-Parameter Anzahl Knoten, Anzahl Kanten
 * und Kapazitaeten der Knoten.
 */
 
problem *readparameters(int *nodes, int *edges)
{
	FILE *fp;
	if(!(fp = fopen("instance","r")))
		return NULL;
	int angebot=0,nachfrage=0;
	char zeile[100];
	/* Parameter einlesen */
	while( fgets(zeile, 100, fp) != NULL ) {
		if(zeile[0] == 'p') {
			char *pzeile = strtok(zeile," ");
			int i=0;
			while(pzeile != NULL) {
				if(i==2)
					*nodes = atoi(pzeile);
				if(i==3)
					*edges = atoi(pzeile);
				pzeile = strtok(NULL, " ");
				i++;
			}
			break;
		}
	}
	/* Knoten einlesen */
	int nodearray[*nodes];
	while( fgets(zeile, 100, fp) != NULL ) {
		if(zeile[0] == 'n') {
			int n = 0,v = 0;
			char *pzeile = strtok(zeile," ");
			int i=0;
			while(pzeile != NULL) {
				if(i==1)
					n = atoi(pzeile);
				if(i==2)
					v = atoi(pzeile);
				pzeile = strtok(NULL, " ");
				i++;
			}
			nodearray[n-1] = v;
		}
	}
	int i=0;
	while(i < *nodes) {
		if(nodearray[i] > 0)
			(angebot)++;
		else
			(nachfrage)++;
		i++;
	}
	fclose(fp);
	/* Kapazitaeten der Knoten im Problem speichern */
	problem *p = newproblem(angebot,nachfrage);
	i=0;
	while(i < *nodes) {
		if(nodearray[i] > 0)
			p->angebote[i] = nodearray[i];
		else
			p->nachfragen[i-angebot] = -nodearray[i];
		i++;
	}
	return p;
}

/*
 * Einlesen der Kosten auf den Kanten.
 */

void readgraph(problem *p)
{
	FILE *fp;
	if(!(fp = fopen("instance","r")))
		exit(1);
	char zeile[100];
	/* Kanten und Kosten einlesen */
	while( fgets(zeile, 100, fp) != NULL ) {
		if(zeile[0] == 'a') {
			int a=0,n=0,c=0,i=0;
			char *pzeile = strtok(zeile," ");
			while(pzeile != NULL) {
				if(i==1)
					a = atoi(pzeile);
				if(i==2)
					n = atoi(pzeile);
				if(i==5)
					c = atoi(pzeile);
				pzeile = strtok(NULL, " ");
				i++;
			}
			n = n - p->angebot - 1;
			a = a - 1;
			p->matrix[a*p->nachfrage+n] = c;
		}
	}
	fclose(fp);
	vogel(p);
}
