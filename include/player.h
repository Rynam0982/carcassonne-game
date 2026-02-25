
#ifndef PLAYER_H
#define PLAYER_H
#include "tile.h"

typedef struct joueurs_t{
	int id;
	int meeple_color;
	int meeple_numero;
	int score;
	stack main;
}joueurs;


joueurs demarrerjoueur(int numero, int meeple);


void afficher_joueurs(joueurs P);
void affichermainjoueurs(joueurs P);

int placermeeplesurtuile(tile* T, int side, joueurs* P);



#endif
