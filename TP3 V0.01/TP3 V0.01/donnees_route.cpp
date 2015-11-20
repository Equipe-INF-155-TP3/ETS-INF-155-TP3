#include <stdio.h>
#include <stdlib.h>
#include "donnees_route.h"


#define LONG_MAX_NOM_F 15
#define MODE_OUVERTURE "rt"
#define RAD_A_DEG (3.14159/180)


int lire_fichier(char *nomF, t_route *route, t_pt2d *depart, double *dir_dep, t_chemin *chemin, int *nb_obs){

	FILE * fichier;
	int i;
	double dir_dep_deg;

	fichier = fopen(nomF, MODE_OUVERTURE);
	fscanf(fichier, "%i %i\n", route->dimx, route->dimy);
	fscanf(fichier, "%i\n", route->nb_lignes);
	(route->liste_lignes) = (t_ligne*)malloc((route->nb_lignes)*sizeof(t_ligne));
	for (i = 0; i < (route->nb_lignes); i++){
		fscanf(fichier, "%lf %lf lf% %lf\n", route->liste_lignes[i].ptA.X);
	}

	fscanf(fichier, "%i %i %lf \n", depart->X, depart->Y, dir_dep_deg);
	*dir_dep = dir_dep_deg*RAD_A_DEG; // Conversion des radians en degrés

	fscanf(fichier, "%i\n", chemin->nb_pts);
	(chemin->liste_pts) = (t_chemin*)malloc((chemin->nb_pts)*sizeof(t_chemin)); //erreur ...
	for (i = 0; i < (chemin->nb_pts); i++){
		fscanf(fichier, "%lf %lf\n", chemin->liste_pts[i].X, chemin->liste_pts[i].Y);
	}

}
