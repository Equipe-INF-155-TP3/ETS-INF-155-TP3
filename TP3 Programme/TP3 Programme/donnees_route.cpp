#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "donnees_route.h"



#define LONG_MAX_NOM_F 15
#define MODE_OUVERTURE "rt"
#define RAD_A_DEG (3.14159/180)

  //********************#############################************************/
 //*********************#  Fonction: lire_fichier  #***********************/
//**********************#############################**********************/


int lire_fichier(char *nomF, t_route *route, t_pt2d *depart, double *dir_dep, t_chemin *chemin, int *nb_obs){

	FILE * fichier;
	int i;
	double dir_dep_deg;
	

	fichier = fopen(nomF, MODE_OUVERTURE);  /* Vérification que le fichier a bien été ouvert */
	if (fichier == NULL)
		return 0;

	/* LECTURE DONNEES POUR LA ROUTE */

	/* Lecture première lignes pour les dimensions de route */
	fscanf(fichier, "%d %d\n", &(route->dimx), &(route->dimy));		

	/* Lecture pour le nombre de lignes*/
	fscanf(fichier, "%d\n", &(route->nb_lignes));							

	/* Allocation dynamique */
	(route->liste_lignes) = (t_ligne*)malloc((route->nb_lignes)*sizeof(t_ligne)); 
	assert(route->liste_lignes);	/* Vérification de l'allocation dynamique */

	for (i = 0; i < (route->nb_lignes); i++){ /* Lecture du fichier et remplissage des tableaux position*/

		fscanf(fichier, "%lf %lf %lf %lf\n", &(route->liste_lignes[i].ptA.X), 
											 &(route->liste_lignes[i].ptA.Y),
											 &(route->liste_lignes[i].ptB.X),
											 &(route->liste_lignes[i].ptB.Y));
	}

	/* Lecture pour la position de départ de la voiture */
	fscanf(fichier, "%lf %lf %lf\n", &depart->X, &depart->Y, &dir_dep_deg);		
	*dir_dep = dir_dep_deg*RAD_A_DEG;		/* Conversion des radians en degrés */


	/* LECTURE DONNEES POUR LE CHEMIN */

	fscanf(fichier,"%d\n", &chemin->nb_pts);

	(chemin->liste_pts) = (t_pt2d*)malloc((chemin->nb_pts)*sizeof(t_pt2d)); /* Allocation dynamique*/
	assert(chemin->liste_pts);	/* Vérification de l'allocation dynamique avec assert */

	for (i = 0; i < (chemin->nb_pts); i++)
	{
		fscanf(fichier, "%lf",   &chemin->liste_pts[i].X);
		fscanf(fichier, "%lf\n", &chemin->liste_pts[i].Y);
	}

	/* LECTURE POUR NOMBRE D'OBSTACLE */

	fscanf(fichier, "%d", nb_obs); 	/* On obtient le nombre d'obstacles */

	return 1;
}


  //********************#############################************************/
 //*********************#  Fonction: dist  #***********************/
//**********************#############################**********************/

double dist(t_pt2d p1, t_pt2d p2){

	double dx, dy;			/* Déclaration des variables */

	dx = (p2.X) - (p1.X);	/* Calcul de la différence en X */
	dy = (p2.Y) - (p1.Y);	/* Calcul de la différence en Y */
	
	return sqrt(dx*dx+dy*dy);  /* Application du théorème de Pythagore */
}

  //********************#############################************************/
 //*********************#  Fonction: detruire_chemin  #***********************/
//**********************#############################**********************/

void detruire_chemin(t_route *route, t_chemin *chemin){
	free(chemin->liste_pts);
	free(route->liste_lignes);
}

  //********************#############################************************/
 //*********************#  Fonction: obt_pt  #***********************/
//**********************#############################**********************/



t_pt2d obt_pt(const t_chemin *chemin, int pos){
	if (pos >= chemin->nb_pts){
		printf("Erreur dans la fonction obt_pt. le point [%d] n'existe pas.", pos);
		return chemin->liste_pts[chemin->nb_pts];
	} else
		return chemin->liste_pts[pos];
}

  //********************#############################************************/
 //*********************#  Fonction: obt_dim_route  #***********************/
//**********************#############################**********************/


void obt_dim_route(const t_route *route, int *dimx, int *dimy){
	*dimx = route->dimx;
	*dimy = route->dimy;
}

  //********************#############################************************/
 //*********************#  Fonction: obt_nb_lignes  #***********************/
//**********************#############################**********************/


int obt_nb_lignes(const t_route *route){
	return route->nb_lignes;
}

  //********************#############################************************/
 //*********************#  Fonction: obt_nb_pts  #***********************/
//**********************#############################**********************/

int obt_nb_pts(const t_chemin *chemin){
	return chemin->nb_pts;
}