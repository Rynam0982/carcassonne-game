#ifndef TUILE_H
#define TUILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>



#define NONDEFINI -1              //pour toutes les valeurs non definies, notamment à l'initialisation
#define NB_DE_TUILES 72


#define BOLD "\033[1;37m"

#define CYAN "\033[36m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

#define END_FORMAT "\033[0m"

typedef struct side_t{
	char type;
	int meeple;
}side;


typedef struct tile_t{
	int id;                 //if == NONDEFINI (-1) -> vide
	int x, y;               //coordonnees sur la grille, initialisees a -1           
	side cote[5];            //5 cotes
}tile;


typedef struct stack_t{
	tile tab[72];
	int nombretuiles;
}stack;


typedef struct grid_t{
	tile tab[144][144];
	int nombretuiles;
}grid;



//TILE
tile initialisation_tuile(char side_A, char side_B, char side_C, char side_D, char side_E, int id);

void afficherinfotuile(tile T);
void affichertuile(tile T, int montrer_tuiles, int couleurarriere);
void tournertuile(tile* T, int degrees);
int cote_adjacent(int s);
void tuilesadjacentes(int *x, int *y, int *s);
int comptype(char t1, char t2);


//STACK
stack pile_initialisation();


tile depiler(stack *S);
void empiler(stack *S, tile T);
tile supprimer(stack *S, int ind);
void placeralabasedelapile(stack* S, tile T);
void transfert(tile Ancien, tile* Nouveau);
void afficherpile(stack S);
stack recupererfichier(char* filename);
void melange(stack* S);



//GRID
grid grille_initialisation();

int tuileposable(grid G, tile T, int x, int y);
int placertuilesurgrille(grid* G, tile T, int x, int y);
int meeplesurlazone(grid G, int x, int y, int s, int start);
void affichercote(side S, int montrer_meeples, int couleurarriere,int joueur);
void afficher_grille(grid G, int montrer_tuiles, int couleurarriere, int X_highlight, int Y_highlight,int joueur);



#endif
