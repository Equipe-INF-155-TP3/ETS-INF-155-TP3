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
	int valide;

	initialiser_graphique();
	nomF = saisie_nomF();

	valide = lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs);
	if (valide)
	{
		effacer_ecran();
		dessiner_route(&route);
		dessiner_chemin(&chemin);
		//pause_ecran();
	}

	fermer_graphique();
   	system("pause");
	return EXIT_SUCCESS;
}