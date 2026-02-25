#include "../include/tile.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
//TILE
tile initialisation_tuile(char side_A, char side_B, char side_C, char side_D, char side_E, int id){
	tile T; 
	
	
	T.id = id;


	T.cote[0].type = side_A; 
	T.cote[0].meeple = NONDEFINI; 
	
	T.cote[1].type = side_B; 
	T.cote[1].meeple = NONDEFINI; 
	
	T.cote[2].type = side_C; 
	T.cote[2].meeple = NONDEFINI; 
	
	T.cote[3].type = side_D; 
	T.cote[3].meeple = NONDEFINI; 
	
	T.cote[4].type = side_E; 
	T.cote[4].meeple = NONDEFINI; 

	T.x = NONDEFINI;
	T.y = NONDEFINI;

	return T;
}



void afficherinfotuile(tile T){
	//for debugging
	int montrer_tuiles = 0, couleurarriere = 1;           
	// int montrer_tuiles = 1, couleurarriere = 0;
	printf("Tuile %d :\n", T.id);

	//affichage basique
	// printf("  %c  \n", T.cote[0].type);
	// printf("%c %c %c\n", T.cote[3].type, T.cote[4].type, T.cote[1].type);
	// printf("  %c  \n\n", T.cote[2].type);

	//affichage avec couleurs
	printf("   ");
	affichercote(T.cote[0], montrer_tuiles, couleurarriere,NONDEFINI);
	printf("\n");
	affichercote(T.cote[3], montrer_tuiles, couleurarriere,NONDEFINI);
	affichercote(T.cote[4], montrer_tuiles, couleurarriere,NONDEFINI);
	affichercote(T.cote[1], montrer_tuiles, couleurarriere,NONDEFINI);
	printf("\n");
	printf("   ");
	affichercote(T.cote[2], montrer_tuiles, couleurarriere,NONDEFINI);
	printf("\n");
	

	printf("coords : (%d, %d)\n", T.x, T.y);
}


void affichertuile(tile T, int montrer_tuiles, int couleurarriere){
	// int montrer_tuiles = 1, couleurarriere = 0;
	printf("   ");
	affichercote(T.cote[0], montrer_tuiles, couleurarriere,NONDEFINI);
	printf("\n");
	affichercote(T.cote[3], montrer_tuiles, couleurarriere,NONDEFINI);
	affichercote(T.cote[4], montrer_tuiles, couleurarriere,NONDEFINI);
	affichercote(T.cote[1], montrer_tuiles, couleurarriere,NONDEFINI);
	printf("\n");
	printf("   ");
	affichercote(T.cote[2], montrer_tuiles, couleurarriere,NONDEFINI);
	printf("\n");
	
}


void tournertuile(tile* T, int degrees){
	int tmpi1, tmpi2;
	char tmpc1, tmpc2;
	if (degrees == 90 || degrees == -270){
		tmpi1 = T->cote[1].meeple;
		tmpc1 = T->cote[1].type;
		T->cote[1].meeple = T->cote[0].meeple;
		T->cote[1].type = T->cote[0].type;
		
		tmpi2 = T->cote[2].meeple;
		tmpc2 = T->cote[2].type;
		T->cote[2].meeple = tmpi1;
		T->cote[2].type = tmpc1;
		
		tmpi1 = T->cote[3].meeple;
		tmpc1 = T->cote[3].type;
		T->cote[3].meeple = tmpi2;
		T->cote[3].type = tmpc2;

		T->cote[0].meeple = tmpi1;
		T->cote[0].type = tmpc1;

	}
	else if (degrees == 180 || degrees == -180){
		tournertuile(T, 90);
		tournertuile(T, 90);
	}
	else if (degrees == 270 || degrees == -90){
		tournertuile(T, 90);
		tournertuile(T, 90);
		tournertuile(T, 90);
	}
	else if (degrees == 0){
		return;
	}
	else{
		printf("error tournertuile() : degrees value can't be divided by 90\n");
		exit(1);
	}
}

void transfert(tile Ancien, tile* Nouveau){
	//copies Ancien's attributes into Nouveau, admitting they've both already been allocated
	Nouveau->id = Ancien.id;

	Nouveau->cote[0].meeple = Ancien.cote[0].meeple;
	Nouveau->cote[0].type = Ancien.cote[0].type;
	Nouveau->cote[1].meeple = Ancien.cote[1].meeple;
	Nouveau->cote[1].type = Ancien.cote[1].type;
	Nouveau->cote[2].meeple = Ancien.cote[2].meeple;
	Nouveau->cote[2].type = Ancien.cote[2].type;
	Nouveau->cote[3].meeple = Ancien.cote[3].meeple;
	Nouveau->cote[3].type = Ancien.cote[3].type;
	Nouveau->cote[4].meeple = Ancien.cote[4].meeple;
	Nouveau->cote[4].type = Ancien.cote[4].type;

	Nouveau->x = Ancien.x;
	Nouveau->y = Ancien.y;
}


int cote_adjacent(int s){
	//returns the adjacent side of s on a grid
	if (s == 0) return 2;
	else if (s == 2) return 0;
	else if (s == 1) return 3;
	else if (s == 3) return 1;
	else return NONDEFINI;
} 

void tuilesadjacentes(int *x, int *y, int *s){
	if (*s == 4) return;

	if (*s == 0) (*y)--;
	if (*s == 1) (*x)++;
	if (*s == 2) (*y)++;
	if (*s == 3) (*x)--;
	*s = cote_adjacent(*s);
}


int comptype(char t1, char t2){
	// compares t1 and t2, returns 1 if the same et 0 if not
	// (because we have to take into account blason and ville which are the same)
	if (t1 == t2)
		return 1;
	if (t1 == 'c' && t2 == 'b')
		return 1;
	if (t1 == 'b' && t2 == 'c')
		return 1;
	return 0;
}



//STACK
stack pile_initialisation() {
  stack S;
  S.nombretuiles = 0;
  return S;
}



tile depiler(stack* S){
	if (S->nombretuiles == 0){
	 tile T= initialisation_tuile(' ', ' ', ' ', ' ', ' ', NONDEFINI);
		return T;
	}
	else{
		tile L = S->tab[S->nombretuiles-1];
		tile Ctrl = initialisation_tuile(L.cote[0].type, L.cote[1].type, L.cote[2].type, L.cote[3].type, L.cote[4].type, L.id);
		
		S->nombretuiles--;
		return Ctrl;
	}
}

void empiler(stack* S, tile T) {
	if(T.id != NONDEFINI){
	
	S->tab[S->nombretuiles] = T;
	S->tab[S->nombretuiles].cote[0] = T.cote[0];
	S->tab[S->nombretuiles].cote[1] = T.cote[1];
	S->tab[S->nombretuiles].cote[2] = T.cote[2];
	S->tab[S->nombretuiles].cote[3] = T.cote[3];
	S->tab[S->nombretuiles].cote[4] = T.cote[4];
	
	S->nombretuiles++;
	}
	
}

tile supprimer(stack* S, int ind){
	//supprimers indth element of S
	//. places the element to supprimer at the top of the stack to depiler it next

	tile T= initialisation_tuile(' ', ' ', ' ', ' ', ' ', NONDEFINI);
	transfert(S->tab[ind], &T);
	tile ctrl2;
	for (int i = ind ; i < S->nombretuiles-1 ; i++){
		ctrl2 = S->tab[i+1];
		transfert(ctrl2, &S->tab[i]);
	}

	transfert(T, &S->tab[S->nombretuiles-1]);                           //1 2 3 4 5

	
	
	return depiler(S);
}


void placeralabasedelapile(stack* S, tile T){
	//places T at the base of S, useful if a player needs to draw another tile

	tile tmp= initialisation_tuile(' ', ' ', ' ', ' ', ' ', NONDEFINI);
	empiler(S, tmp);

	for (int i = S->nombretuiles-1 ; i > 0 ; i--){
		transfert(S->tab[i-1], &S->tab[i]);
	}
	transfert(T, &S->tab[0]);
	

}




void melange(stack* E){
	stack S = pile_initialisation();
	int rng;
	srand((unsigned) time(NULL));
	// algo de melange
	while (E->nombretuiles > 0){
		rng = rand() % E->nombretuiles;
		empiler(&S, supprimer(E, rng));
	}
	
	//copy S back into E
	while(S.nombretuiles > 0){
		empiler(E, depiler(&S));
	}

	

}







void afficherpile(stack S){
	if (S.nombretuiles == 0){
		printf("Stack empty.\n");
	}
	else{
		for (int i = 0 ; i < S.nombretuiles ; i++){
			afficherinfotuile(S.tab[i]);
			printf("\n");
		}
	}
}



stack recupererfichier(char * filename){
	int n = NB_DE_TUILES;
	FILE *fh = fopen(filename, "r");

	if (fh == NULL){
		printf("recupererfichier : erreur d'ouverture de %s\n", filename);
		exit(1);
	}
	stack S;
	S.nombretuiles = n;

	size_t size;
	char* buf = NULL;


	for (int j = 0 ; j < n ; j++){
		for (int i = 0 ; i < 5 ; i++){
			if (i==4){
				getdelim(&buf, &size, '\n', fh);
			}
			else{
				getdelim(&buf, &size, ',', fh);
			}
			
			if (buf[0] == 'p') S.tab[j].cote[i].type = 'p';
			else if (buf[0] == 'r') S.tab[j].cote[i].type = 'r';
			else if (buf[0] == 'v' && buf[4] == 'e') S.tab[j].cote[i].type = 'c';              //pour cité
			else if (buf[0] == 'v' && buf[4] == 'a') S.tab[j].cote[i].type = 'v';
			else if (buf[0] == 'a') S.tab[j].cote[i].type = 'a';
			else if (buf[0] == 'b') {
				S.tab[j].cote[i].type = 'b';
			}			
			else {
				printf("erreur recupererfichier : erreur de lecture\n");
				printf("'%s'\n", buf);
				exit(1);
			}
		}
		S.tab[j].id = j+1;
		S.tab[j].x = NONDEFINI;
		S.tab[j].y = NONDEFINI;
	}
	
	fclose(fh);

	return S;
}



//GRID
grid grille_initialisation(){
	grid G;

	for (int i = 0 ; i < NB_DE_TUILES*2-1 ; i++){
		for (int j = 0 ; j < NB_DE_TUILES*2-1 ; j++){
			G.tab[i][j].id = NONDEFINI;
			G.tab[i][j].x = NONDEFINI;
			G.tab[i][j].y = NONDEFINI;

			
			for (int a = 0 ; a < 5 ; a++){
				G.tab[i][j].cote[a].meeple = NONDEFINI;
				G.tab[i][j].cote[a].type = ' ';
			}
		}
	}

	G.nombretuiles = 0;
	return G;
}





int tuileposable(grid G, tile T, int x, int y){
	//returns 1 si can be placed, 0 otherwise


	if (x <= 0 || y <= 0 || x >= NB_DE_TUILES*2-1 || y>= NB_DE_TUILES*2-1) return 0;
	else if (G.tab[x][y].id != NONDEFINI){
		//there's already a tile at this place
		return 0;
	}
	if (G.tab[x-1][y].id == NONDEFINI && G.tab[x][y-1].id == NONDEFINI && G.tab[x+1][y].id == NONDEFINI && G.tab[x][y+1].id == NONDEFINI && G.nombretuiles > 0) return 0;
	if (G.tab[x][y-1].id != NONDEFINI && y-1 >=0){
		if (!comptype(G.tab[x][y-1].cote[2].type, T.cote[0].type)) return 0;
	}
	if (G.tab[x+1][y].id != NONDEFINI && x+1 <=NB_DE_TUILES*2-1){
		if (!comptype(G.tab[x+1][y].cote[3].type, T.cote[1].type)) return 0;
	} 
	if (G.tab[x][y+1].id != NONDEFINI && y+1 <= NB_DE_TUILES*2-1){
		if (!comptype(G.tab[x][y+1].cote[0].type, T.cote[2].type)) return 0;
	}
	if (G.tab[x-1][y].id != NONDEFINI && x-1 >=0){
		if (!comptype(G.tab[x-1][y].cote[1].type, T.cote[3].type)) return 0;
	} 


	return 1;
}



int placertuilesurgrille(grid* G, tile T, int x, int y){

	//assert tile can be placed
	if (!tuileposable(*G, T, x, y)) return 0;

	
	//tile can be placed
	G->tab[x][y].id = T.id;
	G->tab[x][y].cote[0] = T.cote[0];
	G->tab[x][y].cote[1] = T.cote[1];
	G->tab[x][y].cote[2] = T.cote[2];
	G->tab[x][y].cote[3] = T.cote[3];
	G->tab[x][y].cote[4] = T.cote[4];

	G->tab[x][y].x = x;
	G->tab[x][y].y = y;

	G->nombretuiles++;
	

	return 1;
}


int meeplesurlazone(grid G, int x, int y, int s, int start){
	//checks if there's a meeple on the area of the side s of the tile at (x, y)
	//fonction récursive

	if (s < 0 || s > 4)
		return 0;

	char type = G.tab[x][y].cote[s].type;

	// conditions d'arrêt
	if ((G.tab[x][y].cote[4].type == 'a' || G.tab[x][y].cote[4].type == 'v') && G.tab[x][y].cote[4].meeple == NONDEFINI && s == 4) return 0;
	int new_x = x, new_y = y, adj_side = s;
	tuilesadjacentes(&new_x, &new_y, &adj_side);

	if (s!= 4 && G.tab[new_x][new_y].cote[adj_side].meeple != NONDEFINI) return 1;


	// on check la tuile actuelle
	if (G.tab[x][y].cote[s].meeple != NONDEFINI) return 1;
	if (comptype(G.tab[x][y].cote[4].type, type)){
		if (G.tab[x][y].cote[4].meeple != NONDEFINI) return 1;
		for (int i = 0 ; i < 4 ; i++){
			if (i != s){
				if (comptype(G.tab[x][y].cote[i].type, type)){
					if (G.tab[x][y].cote[4].meeple != NONDEFINI) return 1;
				}
			}
		}
	}
	
	if (s == 4){
		// on parcourt de tous les côtes qui correspondent
		// note : ce sera toujours la première récursion car on appelle ensuite que des côtés inférieurs à 4
		for (int i = 0 ; i < 4 ; i++){
			if (comptype(G.tab[x][y].cote[i].type, type)){
				if (G.tab[x][y].cote[i].meeple != NONDEFINI) return 1;
				adj_side = i;
				new_x = x;
				new_y = y;
				tuilesadjacentes(&new_x, &new_y, &adj_side);
				if (G.tab[new_x][new_y].id != NONDEFINI){
					return meeplesurlazone(G, new_x, new_y, adj_side, 0);
				}
			}

		}
	}
				  
	else{
		for (int i = 0 ; i < 4 ; i++){
			if (comptype(G.tab[x][y].cote[i].type, type) && comptype(G.tab[x][y].cote[4].type, type)){
				if (i == s && start == 0) 
					continue;
				if (G.tab[x][y].cote[i].meeple != NONDEFINI) return 1;
				adj_side = i;
				new_x = x;
				new_y = y;
				tuilesadjacentes(&new_x, &new_y, &adj_side);
				if (G.tab[new_x][new_y].id != NONDEFINI){
					return meeplesurlazone(G, new_x, new_y, adj_side, 0);
				}
			}

		}
		if (!comptype(G.tab[x][y].cote[4].type, type) && start){
			adj_side = s;
			new_x = x;
			new_y = y;
			tuilesadjacentes(&new_x, &new_y, &adj_side);
			if (G.tab[new_x][new_y].id != NONDEFINI){
				return meeplesurlazone(G, new_x, new_y, adj_side, 0);
			}
		}
		
	}
	
	return 0;
}





void affichercote(side S, int montrer_meeples, int couleurfond,int joueur){
	if (couleurfond != 0){
		if(S.type == 'b'){
        		    printf("\033[41");       // rouge
		} else if (S.type == 'p'){
			printf("\033[42");       // vert
		} else if (S.type == 'r'){
			printf("\033[47");       // gris clair       
		} else if (S.type == 'c'){
			printf("\033[43");       // marron
		} else if (S.type == 'v'){
			printf("\033[43");       // beige
		} else if (S.type == 'a'){
			printf("\033[33");       // jaune
		} else {
			printf("\033[40");       // noir
		}
		
		if (montrer_meeples == 0) {
			printf("m");
		} else {
			printf(";");
		}
		if(S.meeple == NONDEFINI){
		printf("   \033[0m");
		}else{
		printf(" %d \033[0m", joueur);
	
		}
	}
	/*
	if (montrer_meeples != 0){
		if (couleurfond == 0) {
			printf("\033[");
		}
		if(S.meeple == 0){
			printf("33m"); // yellow
		} else if (S.meeple == 1){
			printf("31m"); // red
		} else if (S.meeple == 2){
			printf("32m"); // green
		} else if (S.meeple == 3){
			printf("34m"); // blue
		} else if (S.meeple == 4){
			printf("36m"); // cyan
		} else if (S.meeple == 5){
			printf("35m"); // magenta
		} else {
			printf("37m"); // white
		}
		printf(" %c ", S.type);
	}
	*/
	
	
}


//Affichage de la grille :
// 
//     0     1     2
//     b
// 0 b b b 
//     b
//     c     p
// 1 c c c p p p
//     c     p
// 
// 2
// 
// 
int largeur_console() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

void afficher_grille(grid G, int montrer_meeples, int couleurfond, int X_highlight, int Y_highlight,int joueur){
	//on parcourt une première fois pour établir la fenêtre d'où sont les tuiles placées 
	if (G.nombretuiles == 0){
		printf("Empty grid.\n");
		return;
	}


	
	
	char* highlight_TR = "-"; 
	char* highlight_TL = "-"; 
	char* highlight_BR = "-"; 
	char* highlight_BL = "-"; 


	int maxX = -1, maxY = -1;
	int minX = NB_DE_TUILES*2, minY = NB_DE_TUILES*2;

	for (int i = 0 ; i < NB_DE_TUILES*2-1 ; i++){
		for (int j = 0 ; j < NB_DE_TUILES*2-1 ; j++){
			if (G.tab[i][j].id != NONDEFINI){
				if (minX > i) minX = i;
				if (minY > j) minY = j;

				if (maxX < i) maxX = i;
				if (maxY < j) maxY = j;
			}
		}
	}
	
	
    	
	
	//Affichage :
	//Centrer l'affichage
	int width_console = largeur_console();
	
	int taille=3;
	printf(BOLD);
	if (minX > 0) minX--;
	if (minY > 0) minY--;
	if (maxX < NB_DE_TUILES*2-1) maxX++;
	if (maxY < NB_DE_TUILES*2-1) maxY++;
	if (minX > 1) minX = minX -2;
	if (minY > 1) minY = minY -2;
	if (maxX < NB_DE_TUILES*2-2) maxX = maxX + 2;
	if (maxY < NB_DE_TUILES*2-2) maxY = maxY + 2;
	for (int i = minX; i <= maxX+1; i++) {
		taille = taille +7;
    	}
    	taille++;
    	int padding = (width_console - taille) / 2;
    	for (int i = 0; i < padding; i++) {
        printf(" ");
    }
	printf("  +");
	
	for (int i = minX; i <= maxX+1; i++) {
        	if (i >= 100) printf("--------");
		if (i < 100 && i >= 10) printf("--------");
		if (i < 10) printf("--------");
		
    	}
    	
    	
    	printf("+\n");
    	
    	
    	
    	
    	
    	for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    	
    	
	printf("       ");
	for (int i = minX ; i < maxX+1 ; i++){
		if (i >= 100) printf("%d      ", i);
		if (i < 100 && i >= 10) printf(" %d      ", i);
		if (i < 10) printf(" %d       ", i);
	}
	
	printf(END_FORMAT);
	printf("\n");
    
    	
    	
	
	for (int j = minY ; j < maxY+1 ; j++){
		for (int i = 0; i < padding; i++) {
        printf(" ");
    
    }
		printf("       ");
		for (int i = minX ; i < maxX+1 ; i++){
			
			if (G.tab[i][j].id != NONDEFINI){
				affichercote(G.tab[i][j].cote[0], montrer_meeples, couleurfond,joueur);
				if (j == Y_highlight && i == X_highlight)
					printf(" %s ", highlight_TR);
				else
					printf("   ");
			}
			else{
				printf("      ");
				
			}

			//case suivante
			if (j == Y_highlight && i == X_highlight-1)
				printf(" %s ", highlight_TL);
			else
				printf("   ");
			
				
		}
		
		
		printf("\n");
		for (int i = 0; i < padding; i++) {
        printf(" ");
    
    }
		printf(BOLD);
		if (j >= 100) printf("%d ", j);
		else if (j < 100 && j >= 10) printf(" %d ", j);
		else if (j < 10) printf("  %d ", j);
		printf(END_FORMAT);
		for (int i = minX ; i < maxX+2 ; i++){
			if (G.tab[i][j].id != NONDEFINI){
				affichercote(G.tab[i][j].cote[3], montrer_meeples, couleurfond,joueur);
				affichercote(G.tab[i][j].cote[4], montrer_meeples, couleurfond,joueur);
				affichercote(G.tab[i][j].cote[1], montrer_meeples, couleurfond,joueur);
			}
			else{
				
				printf("         ");
				
			}
			
		}
		printf("\n");
		for (int i = 0; i < padding; i++) {
        printf(" ");
    
    }
		
		printf("       ");
		for (int i = minX ; i < maxX+1 ; i++){
			if (G.tab[i][j].id != NONDEFINI){
				affichercote(G.tab[i][j].cote[2], montrer_meeples, couleurfond,joueur);
				if (j == Y_highlight && i == X_highlight)
					printf(" %s ", highlight_BR);
				else
					printf("   ");
			}
			else{
				printf("      ");
				
			}

			//case suivante
			if (j == Y_highlight && i == X_highlight-1)
				printf(" %s ", highlight_BL);
			else
				printf("   ");
			

		}
		printf("\n");

	}
	for (int i = 0; i < padding; i++) {
        printf(" ");
    }
	printf("       ");
	for (int i = minX ; i < maxX+1 ; i++){
		if (i >= 100) printf("%d      ", i);
		if (i < 100 && i >= 10) printf(" %d      ", i);
		if (i < 10) printf(" %d       ", i);
	}
	printf("\n");
	for (int i = 0; i < padding; i++) {
        printf(" ");
    }
	printf("  +");
	for (int i = minX; i <= maxX+1; i++) {
        	if (i >= 100) printf("--------");
		if (i < 100 && i >= 10) printf("--------");
		if (i < 10) printf("--------");
    	}
    	printf("+\n");
	

}
