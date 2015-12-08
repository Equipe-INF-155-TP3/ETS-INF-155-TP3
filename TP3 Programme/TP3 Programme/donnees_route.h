/******************************************************************************
// DONNEES_ROUTE.H
// ****************************************************************************
// Cette librairie contient les fonctions de gestion des données de la route
// et du chemin à suivre.
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#if !defined (__DONNEES_ROUTE__)

#define __DONNEES_ROUTE__ 1
#define _CRT_SECURE_NO_WARNINGS


/******************************************************************************/
/*                       Déclaration des types                                */
/******************************************************************************/
typedef struct {             /* Enregistrement d'un point */
	double X, Y;
} t_pt2d;

typedef struct {             /* Enregistrement d'une ligne     */
	t_pt2d ptA, ptB;		 /*	  Extrémité A et B d'une ligne */
} t_ligne;

typedef struct {             /* Enregistrement de la route */
  int      dimx, dimy;		 /*		Taille en unités de la route */
  t_ligne *liste_lignes;	 /*		Liste dynamique des lignes   */
  int      nb_lignes;		 /*		Le nombre de lignes dans la liste */
} t_route;

typedef struct{              /* Enregistrement du chemin à suivre */
	t_pt2d *liste_pts;		 /*		Liste dynamique des points    */
	int     nb_pts;			 /*		Le nombre de points dans la liste */
} t_chemin;

/******************************************************************************
                   FONCTIONS de CRÉATION et de DESTRUCTION
******************************************************************************/

/******************************************************************************
// lire_fichier
// ****************************************************************************
// Cette fonction permet d'ouvrir un fichier texte de coordonnées-chemin.
//
// Le nom du fichier a déjà été saisi en mode-graphique. Une fois le fichier 
// ouvert on recupere les informations utiles à la creation de la route et chemin.
//
// Parametres : nomF = le nom du fichier texte à ouvrir.
//              route = référence à la route à remplir.
//              depart = référence à la position de départ de l'auto.
//              dir_dep = référence à la direction de départ de l'auto.
//              chemin = référence au chemin à remplir.
//              nb_obs = référence au nombre de piétons à générer.
// Sortie : 1 si le fichier a été ouvert avec succes, 0 sinon.
//*****************************************************************************/
int lire_fichier(char *nomF, t_route *route, t_pt2d *depart, double *dir_dep, 
	               t_chemin *chemin, int *nb_obs);


/******************************************************************************
// detruire_chemin
// ****************************************************************************
// Cette fonction permet les allocation dynamiques de la route et du chemin.
//
// Parametres : route = référence à la route à détruire.
//              chemin = référence au chemin à détruire.
//*****************************************************************************/
void detruire_chemin(t_route *route, t_chemin *chemin);


/******************************************************************************
// dist
// ****************************************************************************
// Fonction de calcul de la distance entre 2 points.
//
// Parametres : p1, p2 = les 2 points.
// Sortie : la distance scalaire.
//****************************************************************************/
double dist(t_pt2d p1, t_pt2d p2);


/******************************************************************************
                   FONCTIONS INFORMATRICES SUR LES CHAMPS
******************************************************************************/

/******************************************************************************
// obt_dim_route
// ****************************************************************************
// Cette fonction permet de récupérer les dimensions de la route.
//
// Parametres : route = les données de la route.
//              dimx, dimy = références aux 2 dimensions à récupérer.
//****************************************************************************/
void obt_dim_route(const t_route *route, int *dimx, int *dimy);

/******************************************************************************
// obt_ligne
// ****************************************************************************
// Cette fonction permet de récupérer une des lignes de la route.
//
// Parametres : route = les données de la route.
//              pos = la position de la ligne désirée dans la liste.
// Sortie : une copie de la ligne récupérée.
//****************************************************************************/
t_ligne obt_ligne(const t_route *route, int pos);

/******************************************************************************
// obt_nb_lignes
// ****************************************************************************
// Cette fonction permet de récupérer le nombre de lignes dans la route.
//
// Parametres : route = les données de la route.
// Sortie : le nombre de lignes dans la liste.
//****************************************************************************/
int obt_nb_lignes(const t_route *route);

/******************************************************************************
// obt_pt
// ****************************************************************************
// Cette fonction permet de récupérer un des points du chemin à suivre.
//
// Parametres : chemin = les données de du chemin.
//              pos = la position du point désirée dans la liste.
// Sortie : une copie du point récupéré.
//****************************************************************************/
t_pt2d obt_pt(const t_chemin *chemin, int pos);

/******************************************************************************
// obt_nbPts
// ****************************************************************************
// Cette fonction permet de récupérer le nombre de points dans le chemin.
//
// Parametres : chemin = les données de la route.
// Sortie : le nombre de points dans la liste.
//****************************************************************************/
int obt_nb_pts(const t_chemin *chemin);

#endif