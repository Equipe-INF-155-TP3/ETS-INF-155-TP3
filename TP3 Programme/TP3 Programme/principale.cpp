  //********************##############################************************/
 //*********************#  Pr�sentation du programe  #***********************/
//**********************##############################**********************/
/*
    Titre: La voiture intelligente autoguid�e

	Auteurs:
		- Philippe La Madeleine -LAMP21099204
		- //////////////  �criver votre nom et votre code permanent ici  //////////////
		- //////////////  �criver votre nom et votre code permanent ici  //////////////

	Cours: INF-155

	Groupe: 2

	Objectif:	Programer une voiture qui suivras un parcour pr�d�fini a 
				travest un environement simul� en �vitant les colision avec
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
#include <string.h>
#include <conio.h>
#include <windows.h>


#include "t_auto.h"
#include "t_obstacles.h"

#define RAFRAICHISSEMENT 50	//ms
#define PREMIER_POINT 0


  //***************########################################*******************/
 //****************#  D�finition des fonctions statiques  #******************/
//*****************########################################*****************/


  //********************#############################************************/
 //*********************#  Fonction: choix du menu  #***********************/
//**********************#############################**********************/
static char choisir_menu( const char *choix_possible){
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

		//Cr�er la voiture.
		voiture = init_auto(depart, dir_depart);
		dessiner_route(&route);

		//obtenir et Afficher la premi�re cible.
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
  
    Si on a pes� sur ESC on quitte la boucle imm�diatement 
    distance = distance entre l�auto et la cible
    Si (on est � moins d'une demi-largeur de la cible ET 
        qu'on s'�loigne de la cible), 
	cible = R�cup�rer le prochain point s�il en reste, sinon termin� = VRAI 
distance = calculer la nouvelle distance entre l�auto et la cible
      Afficher ce point � la droite de la route avec � afficher_pos() �
    Fin Si
    Transf�rer la distance dans dist_precedente
  Fin boucle
Fin Si
Fermer le mode graphique

*/

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