#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "winBGIm.h"    
#include "donnees_route.h"
#include "graphiques_lib.h"
#include "t_auto.h"

int main()
{
	char *nomF;
	t_route route;
	t_chemin chemin;
	t_pt2d depart;
	double dir_depart;
	int nb_obs;

	initialiser_graphique();

	nomF = saisie_nomF();

	if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs))
	{
		effacer_ecran();

		dessiner_route(&route);
		//dessiner_chemin();
	int nomF;

	initialiser_graphique();

	saisie_nomF();
	

	effacer_ecran();
	//dessiner_route();
	//dessiner_chemin();

	pause_ecran();

		pause_ecran();
	}

	system("pause");
	return EXIT_SUCCESS;
}