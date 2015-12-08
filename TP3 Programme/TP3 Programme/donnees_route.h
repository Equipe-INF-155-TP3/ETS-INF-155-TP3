/******************************************************************************
// DONNEES_ROUTE.H
// ****************************************************************************
// Cette librairie contient les fonctions de gestion des donn�es de la route
// et du chemin � suivre.
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#if !defined (__DONNEES_ROUTE__)

#define __DONNEES_ROUTE__ 1
#define _CRT_SECURE_NO_WARNINGS


/******************************************************************************/
/*                       D�claration des types                                */
/******************************************************************************/
typedef struct {             /* Enregistrement d'un point */
	double X, Y;
} t_pt2d;

typedef struct {             /* Enregistrement d'une ligne     */
	t_pt2d ptA, ptB;		 /*	  Extr�mit� A et B d'une ligne */
} t_ligne;

typedef struct {             /* Enregistrement de la route */
  int      dimx, dimy;		 /*		Taille en unit�s de la route */
  t_ligne *liste_lignes;	 /*		Liste dynamique des lignes   */
  int      nb_lignes;		 /*		Le nombre de lignes dans la liste */
} t_route;

typedef struct{              /* Enregistrement du chemin � suivre */
	t_pt2d *liste_pts;		 /*		Liste dynamique des points    */
	int     nb_pts;			 /*		Le nombre de points dans la liste */
} t_chemin;

/******************************************************************************
                   FONCTIONS de CR�ATION et de DESTRUCTION
******************************************************************************/

/******************************************************************************
// lire_fichier
// ****************************************************************************
// Cette fonction permet d'ouvrir un fichier texte de coordonn�es-chemin.
//
// Le nom du fichier a d�j� �t� saisi en mode-graphique. Une fois le fichier 
// ouvert on recupere les informations utiles � la creation de la route et chemin.
//
// Parametres : nomF = le nom du fichier texte � ouvrir.
//              route = r�f�rence � la route � remplir.
//              depart = r�f�rence � la position de d�part de l'auto.
//              dir_dep = r�f�rence � la direction de d�part de l'auto.
//              chemin = r�f�rence au chemin � remplir.
//              nb_obs = r�f�rence au nombre de pi�tons � g�n�rer.
// Sortie : 1 si le fichier a �t� ouvert avec succes, 0 sinon.
//*****************************************************************************/
int lire_fichier(char *nomF, t_route *route, t_pt2d *depart, double *dir_dep, 
	               t_chemin *chemin, int *nb_obs);


/******************************************************************************
// detruire_chemin
// ****************************************************************************
// Cette fonction permet les allocation dynamiques de la route et du chemin.
//
// Parametres : route = r�f�rence � la route � d�truire.
//              chemin = r�f�rence au chemin � d�truire.
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
// Cette fonction permet de r�cup�rer les dimensions de la route.
//
// Parametres : route = les donn�es de la route.
//              dimx, dimy = r�f�rences aux 2 dimensions � r�cup�rer.
//****************************************************************************/
void obt_dim_route(const t_route *route, int *dimx, int *dimy);

/******************************************************************************
// obt_ligne
// ****************************************************************************
// Cette fonction permet de r�cup�rer une des lignes de la route.
//
// Parametres : route = les donn�es de la route.
//              pos = la position de la ligne d�sir�e dans la liste.
// Sortie : une copie de la ligne r�cup�r�e.
//****************************************************************************/
t_ligne obt_ligne(const t_route *route, int pos);

/******************************************************************************
// obt_nb_lignes
// ****************************************************************************
// Cette fonction permet de r�cup�rer le nombre de lignes dans la route.
//
// Parametres : route = les donn�es de la route.
// Sortie : le nombre de lignes dans la liste.
//****************************************************************************/
int obt_nb_lignes(const t_route *route);

/******************************************************************************
// obt_pt
// ****************************************************************************
// Cette fonction permet de r�cup�rer un des points du chemin � suivre.
//
// Parametres : chemin = les donn�es de du chemin.
//              pos = la position du point d�sir�e dans la liste.
// Sortie : une copie du point r�cup�r�.
//****************************************************************************/
t_pt2d obt_pt(const t_chemin *chemin, int pos);

/******************************************************************************
// obt_nbPts
// ****************************************************************************
// Cette fonction permet de r�cup�rer le nombre de points dans le chemin.
//
// Parametres : chemin = les donn�es de la route.
// Sortie : le nombre de points dans la liste.
//****************************************************************************/
int obt_nb_pts(const t_chemin *chemin);

#endif