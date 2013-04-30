/*
 * solver.c - Hauptprogramm.
 * 
 * (C) 2004 Ulrich Staerk
 * 
 * Startet die Funktionen zum Einlesen des Graphen,
 * zur Berrechnung der Basisloesung und zur Optimierung
 * dieser.
 */
 
#include "solver.h"

int main(void)
{
	int i=0;
	problem *p = readparameters(&nodes,&edges);
	if(!p) {
		printf("readparameters failed.");
		exit(1);
	}
	printf("Knoten:\t\t%4d\n  Angebot:\t%4d\n  Nachfrage:\t%4d\nKanten:\t\t%4d\n\n",nodes,p->angebot,p->nachfrage,edges);
	readgraph(p);
	printf("Kosten auf Kanten nach dem Einlesen:\n\n");
	printgraph(p);
	matrix *x = newmatrix(p->angebot,p->nachfrage);
	/* Solange noch Spalten oder Zeilen vorhanden, Kante waehlen,
	 * in die Basisloesung aufnehmen und Vogel-Werte neu berechnen. */
/*
	for(i=0; i < p->angebot+p->nachfrage-1; i++)
	{
		waehlekante_vogel(p,x);
		vogel(p);
	}
	printf("\n\nBasislösung nach Vogel:\n\n");
	printmatrix(x);

	p = readparameters(&nodes,&edges);
	readgraph(p);
	x = newmatrix(p->angebot,p->nachfrage);
*/


	for(i=0; i < p->angebot+p->nachfrage-1; i++)
	{
		waehlekante_nwe(p,x);
	}
	printf("\n\nBasislösung nach Nordwest-Ecken-Regel:\n\n");
	printmatrix(x);
	
/*
	p = readparameters(&nodes,&edges);
	readgraph(p);
	x = newmatrix(p->angebot,p->nachfrage);
	
	for(i=0; i < p->angebot+p->nachfrage-1; i++)
	{
		waehlekante_mkk(p,x);
	}
	printf("\n\nBasislösung nach Methode der kleinsten Kosten:\n\n");
	printmatrix(x);
	*/
	
	/* Stepping stone */
	/*
	stepstone(x,p);
	printf("\n\nBasislösung nach Stepping Stone:\n\n");
	printmatrix(x);
	*/
	
	/* Modi */
	modi(p,x);
	printf("\n\nBasislösung nach Modi:\n\n");
	printmatrix(x);

	return 0;
}
