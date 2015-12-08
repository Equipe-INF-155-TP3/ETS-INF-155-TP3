  //********************##############################************************/
 //*********************#  Pr�sentation du programme  #***********************/
//**********************##############################**********************/
/*
    Titre: La voiture intelligente autoguid�e

	Auteurs:
		- Philippe La Madeleine -LAMP21099204
		- Clarence Dupuis		-DUPC24069502
		- R�gis Villeneuve		-VILR12039501

	Cours: INF-155

	Groupe: 2

	Objectif:	Programmer une voiture qui suivra un parcours pr�d�fini a 
				travers un environnement simul� en �vitant les collisions avec
				des obstacles dynamiques.
				

	Liste des fonctions r�dig�es:

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

#define RAFRAICHISSEMENT 50	/* Taux de rafraichissement en millisecondes (ms) */
#define PREMIER_POINT 0
#define CHOIX_POSSIBLES "DN"
#define ECHAP 27

static void choisir_menu( char *choix ){
	char ch, i;
	if ( saisie_touche(&ch) ){
		if (ch == ECHAP)
			*choix = ECHAP;
		else
			for(i=0;CHOIX_POSSIBLES[i];i++){
				if (CHOIX_POSSIBLES[i] == ch)
					*choix = toupper(ch);
			}
		}
}


  //******************##################################**********************/
 //*******************#  Fonction: Entr�e du programme  #*********************/
//********************##################################********************/
int main()
{


	t_route route;
	t_chemin chemin;
	t_auto voiture;
	t_pt2d pos_ref, supG, supD, infG, infD;
	t_liste_obs  obstacles;
	int nb_obs, dimx, dimy, i;
	int chemin_charge = 0;

	t_pt2d depart;
	double dir_depart;

	t_pt2d cible;
	int prochain_point, nb_points;
	double dist_precedente, distance;

	char choix_menu = 'N', ch, *nomF;


	initialiser_graphique();


	do{

		/* V�rifier si une touche a �t� appuy�e */
		choisir_menu(&choix_menu);

		switch (choix_menu) {
			case 'N':

				effacer_ecran();
				if (chemin_charge){
					detruire_chemin(&route, &chemin);
					chemin_charge = 0; /* Drapeau indiquant qu'un chemin est charg�.*/
				}

				/* Saisir le nom de fichier */
				nomF = saisie_nomF();


				effacer_ecran();
				
				

				if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs))
				{
					/* Obtenir les donn�es de la route et du chemin */
					obt_dim_route(&route, &dimx, &dimy);
					nb_points = obt_nb_pts(&chemin);

					/* Cr�er la voiture et les obstacles */
					dessiner_route(&route);
					dessiner_chemin(&chemin);
					afficher_menu(dimy);

					chemin_charge = 1;

					/* On r�active la boucle */
					choix_menu = ECHAP;
				}

			break;
			case 'D':

				/* Cr�er la voiture et les obstacles */
				voiture = init_auto(depart, dir_depart);
				dessiner_route(&route);
				obstacles = creer_liste_obs( nb_obs, dimx, dimy );

				/* Obtenir et Afficher la premi�re cible */
				prochain_point = PREMIER_POINT;
				cible = obt_pt( &chemin, prochain_point);
				nb_points = obt_nb_pts(&chemin);

				/* Dessiner la voiture et obtenir les conditions initiales */
				obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);
				dist_precedente = dist(pos_ref, cible);


				while (choix_menu == 'D'){

					/* Calcul du comportement de la voiture */
					changer_acc_auto(&voiture, cible);
					deplacer_auto(&voiture);
					obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);

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

					/* Pause pour limiter la vitesse d'�x�cution */
					delai(RAFRAICHISSEMENT);

					/* V�rifier si une touche a �t� appuy�e */
					choisir_menu(&choix_menu);

				}/* Fin de la boucle de simulation */

			break;

			case ECHAP:

				saisie_touche(&ch);
				if (ch == 'Q')
					choix_menu = 'Q';

			break;
		}

	} while(choix_menu!='Q');

	if (chemin_charge){
		detruire_chemin(&route, &chemin);
		chemin_charge = 0;
	}

	fermer_graphique();


   	system("pause");
	return EXIT_SUCCESS;
}