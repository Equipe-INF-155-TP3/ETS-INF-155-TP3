  //********************##############################************************/
 //*********************#  Présentation du programme  #***********************/
//**********************##############################**********************/
/*
    Titre: La voiture intelligente autoguidée

	Auteurs:
		- Philippe La Madeleine -LAMP21099204
		- Clarence Dupuis		-DUPC24069502
		- Régis Villeneuve		-VILR12039501

	Cours: INF-155

	Groupe: 2

	Objectif:	Programmer une voiture qui suivra un parcours prédéfini a 
				travers un environnement simulé en évitant les collisions avec
				des obstacles dynamiques.
				

	Liste des fonctions rédigées:

		* Module principale
			- main

		* Module donnees_route
			- detruire_chemin
			- dist
			- lire_fichier
			- obt_dim_route
			- obt_ligne
			- obt_nb_lignes
			- obt_pt
			- obt_nb_pts
	
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

  //********************###############################***********************/
 //*********************#  Inclure les bibliothèques  #**********************/
//**********************###############################*********************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "t_auto.h"
#include "t_obstacles.h"




#define RAFRAICHISSEMENT 50	/* Taux de rafraichissement en millisecondes (ms) */
#define PREMIER_POINT 0

#define CHOIX_POSSIBLES_NORMAL "DN\033"//'\033' est pour echap.
#define CHOIX_POSSIBLES_ECHAP "Q"
#define ECHAP '\033'


  //**********************############################************************/
 //***********************#  Fonction: choisir_menu  #***********************/
//************************############################**********************/
static void choisir_menu( char *choix , const char *possible ){
	char ch, i;
	if ( saisie_touche(&ch) ){
		for(i=0;possible[i];i++){
			if (possible[i] == ch)
				*choix = ch;
		}
		printf("touche : %c\n",ch);
	}
}


  //******************###################################*********************/
 //*******************#  Fonction: Entrée du programme  #********************/
//********************###################################*******************/
int main()
{


	t_route route;
	t_chemin chemin;
	t_auto voiture;
	t_pt2d pos_ref, supG, supD, infG, infD;
	t_liste_obs  obstacles;
	int nb_obs, dimx, dimy;
	int chemin_charge = 0;

	t_pt2d depart;
	double dir_depart;

	t_pt2d cible;
	int prochain_point, nb_points;
	double dist_precedente, distance;

	char choix_menu = 'N', ch, *nomF;


	initialiser_graphique();




	do{

		/* Vérifier si une touche a été appuyée */
		choisir_menu(&choix_menu, CHOIX_POSSIBLES_NORMAL);

		switch (choix_menu) {
			case 'N':

				effacer_ecran();
				if (chemin_charge){
					detruire_chemin(&route, &chemin);
					chemin_charge = 0; /* Drapeau indiquant qu'un chemin est chargé.*/
				}

				/* Saisir le nom de fichier */
				nomF = saisie_nomF();

				/*On nétoye l'écrans.*/
				effacer_ecran();
				
				

				if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs))
				{
					/* Obtenir les données de la route et du chemin */
					obt_dim_route(&route, &dimx, &dimy);
					nb_points = obt_nb_pts(&chemin);

					/* Dessiner la voiture et les obstacles */
					dessiner_route(&route);
					dessiner_chemin(&chemin);
					afficher_menu(dimy);

					/*On indique qu'un chemin à été chargé.
					chemin_charge = 1;

					/* On réactive la boucle */
					choix_menu = ECHAP;
				} else {

					/*On indique à la boucle de s'arrêter.*/
					choix_menu = 0;

					/*fermer l'écrans graphique.*/
					fermer_graphique();

					/*On indique à l'opérateur que le fichier est introuvable.*/
					printf("Impossible d'ouvrir le fichier \"%s\"\n", nomF);

					/*Permetre à l'opérateur de lire le message en l'invitant
					  à appuiller sur une touche.*/
					system("pause");
				}

			break;
			case 'D':

				/* Créer la voiture et les obstacles */
				voiture = init_auto(depart, dir_depart);
				dessiner_route(&route);
				obstacles = creer_liste_obs( nb_obs, dimx, dimy );

				/* Obtenir et Afficher la première cible */
				prochain_point = PREMIER_POINT;
				cible = obt_pt( &chemin, prochain_point);
				nb_points = obt_nb_pts(&chemin);

				/* Dessiner la voiture et obtenir les conditions initiales */
				obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);
				dist_precedente = dist(pos_ref, cible);
				

				while (choix_menu == 'D'){

					/* Calcul du comportement de la voiture. */
					changer_acc_auto(&voiture, cible);
					deplacer_auto(&voiture);
					obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);

					/* Détection de la proximité de la cible. */
					distance = dist(pos_ref, cible);
					if (2*distance < LARG && distance > dist_precedente )
						if (prochain_point < nb_points-1){
							cible = obt_pt( &chemin, ++prochain_point);
							distance = dist(pos_ref, cible);
							afficher_pos(cible,prochain_point,dimx);
						}else
							choix_menu = ECHAP;
					
					dist_precedente = distance;
					obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);

					/* Calcul du comportement des obstacles */
					deplacer_obs( &obstacles, dimx, dimy );


					/* Effacer et redessiner le trajet */
					effacer_route(dimx, dimy);
					dessiner_auto( pos_ref, supG, supD, infG, infD, AUTO );
					dessiner_route(&route);

					/* dessiner_chemin(&chemin) */
					afficher_obs(&obstacles);

					afficher_menu(dimy);

					/* Pause pour limiter la vitesse d'éxécution */
					delai(RAFRAICHISSEMENT);

					/* Vérifier si une touche a été appuyée */
					choisir_menu(&choix_menu, CHOIX_POSSIBLES_NORMAL);

				}/* Fin de la boucle de simulation */

			break;

			case ECHAP:
				// Verifier si on appuis sur la touche 'Q'.
				choisir_menu( &choix_menu, CHOIX_POSSIBLES_ECHAP );

			break;

			case 'Q':
				// Fermer le graphique.
				fermer_graphique();
				//Indique à la boucle de s'arrêter.
				choix_menu = 0;
			break;



		}

	} while(choix_menu);

	if (chemin_charge){// Si le chemin à 
		detruire_chemin(&route, &chemin);
		chemin_charge = 0;
	}


	return EXIT_SUCCESS;
}