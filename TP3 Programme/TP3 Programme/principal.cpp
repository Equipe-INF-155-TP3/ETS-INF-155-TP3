#include <stdlib.h>
#include <stdio.h>
#include <conio.h>  // pour getch
#include <ctype.h>  // pour fonction to upper

#include "donnees_route.h"
#include "graphiques_lib.h"

#define _CRT_SECURE_NO_WARNINGS

char choix_menu(void);						/* Cette fonction renvoi le charact�re
											en majuscule choisi par
											l'utilisateur */



char choix_menu(void)
{

	// D�claration de la variable	
	char choix; // cette variable contient la donn�e � renvoyer

	// Affichage du menu
	choix = getch();
	fflush(stdin);
	choix = toupper(choix); // mise en majuscule
	return choix;
}


int main(void){
	t_route route;
	t_chemin chemin;
	t_pt2d depart;
	double dir_dep;
	int nb_obj;
/*	// D�claration des variables
	char choix;

	//S�qence
	switch (choix) {
		case 'N' : 
		case 'D' :
		case 'Q': detruire_chemin()



	}

	*/
	lire_fichier("aeroport_parking.txt", &route, &depart, &dir_dep, &chemin, &nb_obj);
	initialiser_graphique();
	system("pause");
	effacer_ecran();
	dessiner_route(&route);
	system("pause");
	return EXIT_SUCCESS;
}