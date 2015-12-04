#include <stdio.h>
#include <stdlib.h>
#include "donnees_route.h"
#include <math.h>


#define LONG_MAX_NOM_F 15
#define MODE_OUVERTURE "rt"
#define RAD_A_DEG (3.14159/180)



int lire_fichier(char *nomF, t_route *route, t_pt2d *depart, double *dir_dep, t_chemin *chemin, int *nb_obs){

	FILE * fichier;
	int i;
	double dir_dep_deg;
	

	fichier = fopen(nomF, MODE_OUVERTURE);
	if (fichier == NULL)
		return 0;

	fscanf(fichier,"%d %d\n", &route->dimx, &route->dimy);
	fscanf(fichier,"%d\n", &route->nb_lignes);
	(route->liste_lignes) = (t_ligne*)malloc((route->nb_lignes)*sizeof(t_ligne));

	for (i = 0; i < (route->nb_lignes); i++){

		/* fscanf(fichier,"%d %d %d %d\n",	&(route->liste_lignes[i].ptA.X),
											&(route->liste_lignes[i].ptA.Y),
											&(route->liste_lignes[i].ptB.X),
											&(route->liste_lignes[i].ptB.Y)); */

		fscanf(fichier, "%lf",	&route->liste_lignes[i].ptA.X);
		fscanf(fichier, "%lf",	&route->liste_lignes[i].ptA.Y);
		fscanf(fichier, "%lf",	&route->liste_lignes[i].ptB.X);
		fscanf(fichier, "%lf\n", &route->liste_lignes[i].ptB.Y);
	}

	fscanf(fichier, "%lf %lf %lf\n", &depart->X, &depart->Y, &dir_dep_deg);
	*dir_dep = dir_dep_deg*RAD_A_DEG; // Conversion des radians en degrés

	fscanf(fichier,"%d\n", &chemin->nb_pts);

	(chemin->liste_pts) = (t_pt2d*)malloc((chemin->nb_pts)*sizeof(t_pt2d)); //erreur ...

	for (i = 0; i < (chemin->nb_pts); i++)
	{
		fscanf(fichier, "%lf",   &chemin->liste_pts[i].X);
		fscanf(fichier, "%lf\n", &chemin->liste_pts[i].Y);
	}
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


t_pt2d obt_pt(const t_chemin *chemin, int pos){
	if (pos >= chemin->nb_pts)
		printf("Erreur dans la fonction obt_pt. le point [%d] n'existe pas.", pos);
	else
		return chemin->liste_pts[pos];
}

void obt_dim_route(const t_route *route, int *dimx, int *dimy){
	*dimx = route->dimx;
	*dimy = route->dimy;
}




