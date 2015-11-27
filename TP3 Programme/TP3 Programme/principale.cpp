#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "winBGIm.h"    
#include "donnees_route.h"
#include "graphiques_lib.h"
#include "t_auto.h"

int main()
{
	int nomF;

	initialiser_graphique();

	saisie_nomF();
	

	

	effacer_ecran();
	//dessiner_route();
	//dessiner_chemin();

	pause_ecran();


	system("pause");
	return EXIT_SUCCESS;
}