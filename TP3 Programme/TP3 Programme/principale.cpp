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


/* Taux de rafraichissement en millisecondes (ms) */
#define RAFRAICHISSEMENT 50	

/* Le premier point du chemin où la voiture serat positionné */
#define PREMIER_POINT 0

/* Définir les choix_menu permis selon la situation. */
#define CHOIX_POSSIBLES_NORMAL "DN\033"//'\033' est pour echap.
#define CHOIX_POSSIBLES_ECHAP "DQN"
#define ECHAP '\033'

  //**********************############################************************/
 //***********************#  Fonction: choisir_menu  #***********************/
//************************############################**********************/
/* Permet de détecter et discriminer l'appuis des touches en les comparant
	avec une string recue en paramètre. */
static void choisir_menu( char *choix , const char *possible ){
	char ch, i;
	/* Compare avec la string */
	if ( saisie_touche(&ch) ){
		for(i=0;possible[i];i++){
			if (possible[i] == ch)
				*choix = ch;
		}
	}
}


  //******************###################################*********************/
 //*******************#  Fonction: Entrée du programme  #********************/
//********************###################################*******************/
int main()
{

	/* Déclarer les variables. */
	t_route route;
	t_chemin chemin;
	t_auto voiture;
	t_pt2d pos_ref, supG, supD, infG, infD;
	t_liste_obs  obstacles;
	int nb_obs, dimx, dimy;

	/* Permet de savoir si un chemin à été chargé. */
	int chemin_charge = 0; 

	/* Conditions de départ. */
	t_pt2d depart;
	double dir_depart;

	/* Variables d'objectif */
	t_pt2d cible;
	int prochain_point, nb_points;
	double dist_precedente, distance;

	/* Le choix_menu est initialisé à 'N' pour forcer 
	   à choisir un fichier avant de commecer. */
	char choix_menu = 'N', *nomF;

	initialiser_graphique();

	//Début de la boucle principale.
	do{
		switch (choix_menu) {
			case 'N':

				effacer_ecran();
				/* Si le chemin à été chargé auparavant, on le détruit pour
				   pouvoir en charger un autre. */
				if (chemin_charge){
					detruire_chemin(&route, &chemin);
					chemin_charge = 0;
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
					choix_menu = 'Q';

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
				obstacles = creer_liste_obs( nb_obs, dimx, dimy );

				/* Obtenir et Afficher la première cible */
				prochain_point = PREMIER_POINT;
				cible = obt_pt( &chemin, prochain_point);
				nb_points = obt_nb_pts(&chemin);

				/* Dessiner la voiture et obtenir les conditions initiales */
				obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);
				dist_precedente = dist(pos_ref, cible);

				/* Dessiner le menu */
				afficher_menu(dimy);

				while (choix_menu == 'D'){

					/* Calcul du comportement de la voiture. */
					changer_acc_auto(&voiture, cible);
					deplacer_auto(&voiture);

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
					afficher_obs(&obstacles);

					/* Pause pour limiter la vitesse d'éxécution */
					delai(RAFRAICHISSEMENT);

					/* Vérifier si une touche a été appuyée */
					choisir_menu(&choix_menu, CHOIX_POSSIBLES_NORMAL);

				}/* Fin de la boucle de simulation */
			break;

			case ECHAP:
				// Verifier si on appuis sur la touche 'Q'.
				do{
					choisir_menu( &choix_menu, CHOIX_POSSIBLES_ECHAP );
				}while (choix_menu == ECHAP);
			break;

			case 'Q':
				// Fermer le mode graphique.
				fermer_graphique();

				/* Si le chemin à été chargé auparavant, on le détruit. */
				if (chemin_charge){
					detruire_chemin(&route, &chemin);
					chemin_charge = 0;
				}
			break;



		}

	} while(choix_menu != 'Q');
	//Fin de la boucle principale.



	return EXIT_SUCCESS;
}