// HEADER FILE Aufgabe 4
#include "stdint.h"

typedef struct node{
	uint32_t data;		//Daten an der Stelle der Liste
	struct node *next;	//Rekursive definition des Structs
} node_t;
