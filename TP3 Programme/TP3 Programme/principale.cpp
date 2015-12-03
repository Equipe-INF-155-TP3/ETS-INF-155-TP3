  //********************##############################************************/
 //*********************#  Pr�sentation du programe  #***********************/
//**********************##############################**********************/
/*
    Titre: La voiture intelligente autoguid�e

	Auteurs:
		- Philippe La Madeleine -LAMP21099204
		- Clarence Dupuis		-DUPC24069502
		- //////////////  �criver votre nom et votre code permanent ici  //////////////

	Cours: INF-155

	Groupe: 2

	Objectif:	Programer une voiture qui suivras un parcour pr�d�fini a 
				travers un environement simul� en �vitant les collision avec
				des obstacles dynamiques.
				

	Liste des fonctions r�dig�es:

		* Module principale
			- main

		* Module donnees_route
			- detruire_chemin
			- dist
			- lire_fichier

		* Module graphique
			- afficher_menu
			- afficher_pos
			- delai
			- dessiner_auto
			- dessiner_chemin
			- dessiner_ligne
			- dessiner_rond
			- dessiner_route
			- detecter_pixel
			- effacer_ecran
			- effacer_route
			- fermer_graphique
			- initialiser_graphique
			- pause_ecran
			- pixel
			- saisie_nom
			- saisie_touche

		* Module t_auto
			- changer_acc_auto
			- deplacer_auto
			- init_auto
			- obt_pos_auto
		
		* Module t_obstacle
			- afficher_obs
			- cree_obs
			- deplacer_obs
			- detecter_auto
			- detruire_obs

		* Module WINBGIM

		
	Date de cr�ation: 6 novembre 2015

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "winBGIm.h"    
#include "donnees_route.h"
#include "graphiques_lib.h"
#include "t_auto.h"

#define _CRT_SECURE_NO_WARNINGS

  //***************########################################*******************/
 //****************#  D�finition des fonctions statiques  #******************/
//*****************########################################*****************/


  //********************#############################************************/
 //*********************#  Fonction: choix du menu  #***********************/
//**********************#############################**********************/
static char choix_menu( const char *choix_possible){
	char choix = 0, i;
	do {
		choix=toupper(getch()); // Percoit la premi�re touche appuill� en majuscule.
		// Compare la touche appuill� avec tout les �l�ment de la chaine de
		// caract�re "choix_possible".
		for(i=0;choix_possible[i];i++){
			if (choix_possible[i] == choix)
				return choix; // Renvoit la touche appuill� si celle ci est dans la liste.
		}
	} while (choix);//Recommence tant que la touche ne correspond pas.
	return choix;
}



  //******************##################################**********************/
 //*******************#  Fonction: Entr�e du programe  #*********************/
//********************##################################********************/
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

	
	if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs))
	{
		effacer_ecran();
		dessiner_route(&route);
		dessiner_chemin(&chemin);
		pause_ecran();
	}

	fermer_graphique();


   	system("pause");
	return EXIT_SUCCESS;
}