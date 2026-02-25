#include "include/game.h"

int main(int argc, char **argv){
	
	if (argc == 2 && !strcmp(argv[1], "clear"))
		printf(CLEAR);

	jeu G = demarrer_jeu("data/tuiles_base_simplifiees.csv");
	gameplay(G);
	

	return 0;
}

