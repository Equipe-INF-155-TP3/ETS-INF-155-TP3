#include <stdio.h>
#include <stdlib.h>
#include "donnees_route.h"
#include <math.h>  // Utilisation de sqrt
#include <assert.h>


#define LONG_MAX_NOM_F 15
#define MODE_OUVERTURE "rt"
#define RAD_A_DEG (3.14159/180)
#define _CRT_SECURE_NO_WARNINGS


int lire_fichier(char *nomF, t_route *route, t_pt2d *depart, double *dir_dep, t_chemin *chemin, int *nb_obs){

	FILE * fichier;
	int i;
	double dir_dep_deg;

	fichier = fopen(nomF, MODE_OUVERTURE);
	if (fichier == NULL){
		printf("erreur d'ouverture de fichier");
		return 0;
	}
	fscanf(fichier, "%i %i\n", &route->dimx, &route->dimy);
	fscanf(fichier, "%i\n", route->nb_lignes);
	(route->liste_lignes) = (t_ligne*)malloc((route->nb_lignes)*sizeof(t_ligne));
	assert(route->liste_lignes);
	for (i = 0; i < (route->nb_lignes); i++){
		fscanf(fichier, "%lf %lf lf% % lf\n",	route->liste_lignes[i].ptA.X,
												route->liste_lignes[i].ptA.Y,
												route->liste_lignes[i].ptB.X,
												route->liste_lignes[i].ptB.Y);
	}

	fscanf(fichier, "%i %i %lf \n", depart->X, depart->Y, dir_dep_deg);
	*dir_dep = dir_dep_deg*RAD_A_DEG; // Conversion des radians en degrés

	fscanf(fichier, "%i\n", chemin->nb_pts);
	(chemin->liste_pts) = (t_pt2d*)malloc((chemin->nb_pts)*sizeof(t_pt2d)); //erreur ...
	assert(chemin->liste_pts);
	for (i = 0; i < (chemin->nb_pts); i++){
		fscanf(fichier, "%lf %lf\n", chemin->liste_pts[i].X, chemin->liste_pts[i].Y);
	}

	fscanf(fichier, "%i", nb_obs);

	return 1;
}


double dist(t_pt2d p1, t_pt2d p2){

	double dx, dy; // Déclaration des variables

	dx = (p2.X) - (p1.X); // calcul de la différence en X
	dy = (p2.Y) - (p1.Y); // calcul de la différence en Y
	
	return sqrt(dx*dx+dy*dy);  // Application du théorème de Pythagore
}

void detruire_chemin(t_route *route, t_chemin *chemin){
	free(chemin->liste_pts);
	free(route->liste_lignes);
}


void obt_dim_route(const t_route *route, int *dimx, int *dimy){


}

t_ligne obt_ligne(const t_route *route, int pos){


}

int obt_nb_lignes(const t_route *route) {


}

t_pt2d obt_pt(const t_chemin *chemin, int pos){


}

int obt_nb_pts(const t_chemin *chemin){



}