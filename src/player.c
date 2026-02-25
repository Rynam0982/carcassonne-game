#include "../include/player.h"

joueurs demarrerjoueur(int numero, int meeple){
	joueurs P;

	P.id = numero;
	P.meeple_color = meeple;
	P.meeple_numero = 7;
	P.score = 0;

	P.main = pile_initialisation();

	return P;
}





void afficher_joueurs(joueurs P){
	printf("joueurs %s%d%s\nmeeples : ", BOLD, P.id, END_FORMAT);
	
	switch (P.meeple_color)
		{
		case 0:
			printf(YELLOW);
			break;
		
		case 1:
			printf(RED);
			break;
		
		case 2:
			printf(GREEN);
			break;
		
		case 3:
			printf(BLUE);
			break;
		
		case 4:
			printf(CYAN);
			break;
		
		case 5:
			printf(MAGENTA);
			break;
		
		default:
			printf("\033[37m");          //white
			break;
		}

	printf(" %d%s\n", P.meeple_numero, END_FORMAT);

	printf("score : %d\n", P.score);
	printf("%d tiles in hand\n", P.main.nombretuiles);

}

void affichermainjoueurs(joueurs P){
	printf("Player %d\n", P.id);
	printf("%d tiles in main\n", P.main.nombretuiles);
	afficherpile(P.main);
}


int placermeeplesurtuile(tile* T, int side, joueurs * P){
	//returns 0 if was unable to place a meeple
	if (T->cote[side].meeple != NONDEFINI || P->meeple_numero <= 0){
		return 0;
	} 
	
	T->cote[side].meeple = P->meeple_color;
	P->meeple_numero--;


	return 1;
}

