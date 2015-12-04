  //********************##############################************************/
 //*********************#  Présentation du programe  #***********************/
//**********************##############################**********************/
/*
    Titre: La voiture intelligente autoguidée

	Auteurs:
		- Philippe La Madeleine -LAMP21099204
		- //////////////  écriver votre nom et votre code permanent ici  //////////////
		- //////////////  écriver votre nom et votre code permanent ici  //////////////

	Cours: INF-155

	Groupe: 2

	Objectif:	Programer une voiture qui suivras un parcour prédéfini a 
				travest un environement simulé en évitant les colision avec
				des obstacles dynamiques.
				

	Liste des fonctions rédigées:

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

		
	Date de création: 6 novembre 2015

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


#include "t_auto.h"
#include "t_obstacles.h"

#define RAFRAICHISSEMENT 50	//ms
#define PREMIER_POINT 0


  //***************########################################*******************/
 //****************#  Définition des fonctions statiques  #******************/
//*****************########################################*****************/


  //********************#############################************************/
 //*********************#  Fonction: choix du menu  #***********************/
//**********************#############################**********************/
static char choisir_menu( const char *choix_possible){
	char choix = 0, i;
	do {
		choix=toupper(getch()); // Percoit la première touche appuillé en majuscule.
		// Compare la touche appuillé avec tout les élément de la chaine de
		// caractère "choix_possible".
		for(i=0;choix_possible[i];i++){
			if (choix_possible[i] == choix)
				return choix; // Renvoit la touche appuillé si celle ci est dans la liste.
		}
	} while (choix);//Recommence tant que la touche ne correspond pas.
	return choix;
}
//Permet de tester le mode graphique
static void mode_N(){//////////////////////////////////////////////////////////////

	char *nomF;
	t_route route;
	t_chemin chemin;
	t_pt2d depart;
	double dir_depart;
	int nb_obs;

	nomF = saisie_nomF();
	
	if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs))
	{
		effacer_ecran();
		dessiner_route(&route);
		dessiner_chemin(&chemin);
		pause_ecran();
	}
}/////////////////////////////////////////////////////////////////////////////////////


static void mode_D(){

	char *nomF = saisie_nomF();
	t_pt2d cible;
	t_auto voiture;

	t_route route;
	t_chemin chemin;
	t_pt2d depart;
	double dir_depart;
	int nb_obs, dimx, dimy;
	t_pt2d pos_ref, supG, supD, infG, infD;
	double dist_precedente;


	if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs)){
		effacer_ecran();

		//Créer la voiture.
		voiture = init_auto(depart, dir_depart);
		dessiner_route(&route);

		//obtenir et Afficher la première cible.
		cible = obt_pt( &chemin, PREMIER_POINT);

		afficher_pos(cible,PREMIER_POINT,1);
		
		//Dessiner la voiture.
		obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);
		dessiner_auto( pos_ref, supG, supD, infG, infD, AUTO );

		dist_precedente = dist(pos_ref, cible);

		obt_dim_route(&route, &dimx, &dimy);


		do {//////////////////////////////////////////////////////////////////
			changer_acc_auto(&voiture, cible);
			effacer_route(dimx, dimy);
			deplacer_auto(&voiture);
			obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);
			dessiner_auto( pos_ref, supG, supD, infG, infD, AUTO );
			if (toupper(getch() == 'Q')
				return 0;

			delai(RAFRAICHISSEMENT);
			

		}while (1);//////////////////////////////////////////////////////////////////////////
	
		pause_ecran();
		
	}

/*
  
    Si on a pesé sur ESC on quitte la boucle immédiatement 
    distance = distance entre l’auto et la cible
    Si (on est à moins d'une demi-largeur de la cible ET 
        qu'on s'éloigne de la cible), 
	cible = Récupérer le prochain point s’il en reste, sinon terminé = VRAI 
distance = calculer la nouvelle distance entre l’auto et la cible
      Afficher ce point à la droite de la route avec « afficher_pos() »
    Fin Si
    Transférer la distance dans dist_precedente
  Fin boucle
Fin Si
Fermer le mode graphique

*/

}


  //******************##################################**********************/
 //*******************#  Fonction: Entrée du programe  #*********************/
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
	char choix_menu = 'N';

	initialiser_graphique();
	
	//choix_menu = choisir_menu("NDQ")
	switch (choix_menu){
		case 'N':
			mode_N();
			break;
		case 'D':
			mode_D();
			break;
		case 'Q':
			//detruire_route();
			//////////////////////////
			break;
	}


	fermer_graphique();


   	system("pause");
	return EXIT_SUCCESS;
}