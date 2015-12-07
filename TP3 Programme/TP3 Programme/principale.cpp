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
	int dimx;
	int dimy;

	nomF = saisie_nomF();
	
	if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs))
	{
		effacer_ecran();
		afficher_menu(route.dimy);
		dessiner_route(&route);
		dessiner_chemin(&chemin);
		pause_ecran();
	}
}/////////////////////////////////////////////////////////////////////////////////////


static void mode_D(){


	t_pt2d cible;
	t_auto voiture;

	t_route route;
	t_chemin chemin;
	t_liste_obs  obstacles;
	t_pt2d depart;
	double dir_depart;
	int nb_obs, dimx, dimy;
	t_pt2d pos_ref, supG, supD, infG, infD;
	double dist_precedente, distance;
	int prochain_point, nb_points;
	char ch, *nomF;


	//nomF = saisie_nomF();
	nomF = "haunted_house.txt";
	if (lire_fichier(nomF, &route, &depart, &dir_depart, &chemin, &nb_obs)){

		effacer_ecran();

		//Obtenir les données de la route et du chemin.
		obt_dim_route(&route, &dimx, &dimy);
		nb_points = obt_nb_pts(&chemin);

		//Créer la voiture et les obstacles.
		voiture = init_auto(depart, dir_depart);
		dessiner_route(&route);
		obstacles = creer_liste_obs( nb_obs, dimx, dimy );

		//Obtenir et Afficher la première cible.
		prochain_point = PREMIER_POINT;
		cible = obt_pt( &chemin, prochain_point);
		nb_points = obt_nb_pts(&chemin);

		//Dessiner la voiture et obtenir des conditions initiales.
		obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);
		dessiner_auto( pos_ref, supG, supD, infG, infD, AUTO );
		dist_precedente = dist(pos_ref, cible);
		afficher_pos(cible,prochain_point,dimx);


		//Boucle d'éxécution de la simulation.
		while (prochain_point < nb_points) {


			//Calcul du comportement de la voiture.
			changer_acc_auto(&voiture, cible);
			deplacer_auto(&voiture);
			obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);

			distance = dist(pos_ref, cible);
			if (2*distance < LARG && distance > dist_precedente){
				cible = obt_pt( &chemin, ++prochain_point);
				distance = dist(pos_ref, cible);
				afficher_pos(cible,prochain_point,dimx);
			}
			dist_precedente = distance;
			obt_pos_auto(&voiture, &pos_ref, &supG, &supD, &infG, &infD);

			//Calcul du comportement des obstacles.
			deplacer_obs( &obstacles, dimx, dimy );


			//effacer et redessiner le monde.
			effacer_route(dimx, dimy);
			dessiner_auto( pos_ref, supG, supD, infG, infD, AUTO );
			dessiner_route(&route);
			//dessiner_chemin(&chemin);
			afficher_obs(&obstacles);



			//vérifier si une touche a été appuillé.
			if ( saisie_touche(&ch) ){
				printf("Une touche à été appuillé.\n");
				if ( toupper(ch) == 'Q' )
					return;
			}

			//Pause pour limiter la vitesse d'éxécution.
			delai(RAFRAICHISSEMENT);


		}//Fin de la boucle de simulation.




		pause_ecran();
		
	}

/*
  


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
	char choix_menu = 'D';

	initialiser_graphique();

		//choix_menu = choisir_menu("NDQ");
		switch (choix_menu)
		{
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