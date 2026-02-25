#include "player.h"
#include "tile.h"


#ifndef GAME_H
#define GAME_H

#define TAILLE 50                //size of *visited_tiles

#define CLEAR "\033[2J\033[H"
#define SLEEPTIME 3.0

typedef struct jeu_t{
    int nombrejoueurs;
    joueurs joueurs[6];
    stack pioche;
    grid arene;
    
}jeu;


void donnertuiles(jeu *G);

int estdedans(int *tab, int value);
void ajoutertuilesvisites(int value);

void affichertuilesvisites();

int recuperermeeplejoueurs(jeu G, int meeple);
void pointsmax(jeu * G, int meeples[6], int points);
void enlever_meeples_de_zone(jeu *G, int meeples[6], int x, int y, int s);
int zoneferme(jeu Jeu, int x, int y, int s, int meeples[6]);
int pcount(jeu Jeu, int x, int y, int s, int start, int meeples[6], int final_evaluation);

//int points_count(jeu Jeu, int x, int y, int s, int start, int meeples[6], int final_evaluation);
int abbayeestferme(jeu G, int x, int y);

int classement(jeu Jeu);

jeu miseajeu(char* filename, int nombrejoueurs);

jeu demarrer_jeu(char* filename);
void gameplay(jeu G);







#endif
