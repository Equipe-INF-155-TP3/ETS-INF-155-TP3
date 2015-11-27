#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "winBGIm.h"    
#include "donnees_route.h"
#include "graphiques_lib.h"
#include "t_auto.h"

int main()
{
	char nomF;
	t_route route;
	t_chemin chemin;
	t_pt2d depart;
	double dir_depart;
	int nb_obs;

	initialiser_graphique();

	/******************************************************************************/
	// Fonction pour saisir un nom de fichier en mode graphique.
	// Entr�es : aucun
	// Sortie  : pointeur vers la cha�ne de caract�re saisie.
	/******************************************************************************/
	nomF = *saisie_nomF();

	lire_fichier("haunted_house.txt",&route,&depart,&dir_depart, &chemin,&nb_obs);

	
	effacer_ecran();

	dessiner_route(&route);
	//dessiner_chemin();

	pause_ecran();


	system("pause");
	return EXIT_SUCCESS;
}