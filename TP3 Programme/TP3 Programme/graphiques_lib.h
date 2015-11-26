/******************************************************************************
// GRAPHIQUES_LIB.H
// ****************************************************************************
// Cette librairie contient les fonctions d'affichage en mode graphique.
// **** CE FICHIER SERA FOURNI AUX ÉLEVES ****
/******************************************************************************/
#include "donnees_route.h"
#include <math.h>

#if !defined (_GRLIB_)

#define _GRLIB_ 1

/**************************
  LES CONSTANTES-COULEURS
**************************/

#define  MAX_COULEUR	15		//indice de couleur le plus élevé.
#define  NOIR			0       //un espace libre (noir)
#define  LIGNE			15      //une ligne (blanc)
#define  POINT			4       //un point-cible (rouge)
#define  AUTO			1       //une auto (bleu)

#define DEMI_PI atan(1.0)
#define PI asin(1.0)

/******************************************************************************/
// Fonction pour démarrer le mode graphique.
// Entrées : aucun
// Sortie  : aucun
/******************************************************************************/
void initialiser_graphique();

/******************************************************************************/
// Fonction pour fermer le mode graphique.
// Entrées : aucun
// Sortie  : aucun
/******************************************************************************/
void fermer_graphique();

/******************************************************************************/
// Fonction pour déssiner la route à parcourir.
// Entrées : les données de la route.
// Sortie  : aucun
/******************************************************************************/
void dessiner_route(const t_route *route);

/******************************************************************************/
// Fonction pour déssiner les points-cibles du chemin à suivre.
// Ces points seront numérotés à l'écran à partir de 1.
// Entrées : les données du chemin.
// Sortie  : aucun
/******************************************************************************/
void dessiner_chemin(const t_chemin *chemin);

/******************************************************************************/
// Fonction pour déssiner un des obstacles.
// Entrées : la position centrale de l'obstacle, la couleur de l'obstacle.
// Sortie  : aucun
/******************************************************************************/
void dessiner_rond(t_pt2d pt, int coul);


/******************************************************************************/
// Fonction pour déssiner la voiture.
// Entrées : ptAuto = position de l'oeil de l'auto.
//           supG, supD, infG, infD = les 4 coins de l'auto.
//           coul = couleur de l'auto.
// Sortie  : aucun
/******************************************************************************/
void dessiner_auto(t_pt2d ptAuto, t_pt2d supG, t_pt2d supD, t_pt2d infG, t_pt2d infD, int coul);

/******************************************************************************/
// Fonction pour afficher les coordonnées d'un point-cible du chemin à suivre.
// Entrées : cible = la position du point.
//           i = son indice dans la liste.
//           dimx = la larguer de la route.
// Sortie  : aucun
/******************************************************************************/
void afficher_pos(t_pt2d cible, int i, int dimx);

/******************************************************************************/
// Fonction pour afficher le menu principal.
// Entrées : la hauteur de la route.
// Sortie  : aucun
/******************************************************************************/
void afficher_menu(int dimy);

/******************************************************************************/
// Fonction pour saisir un nom de fichier en mode graphique.
// Entrées : aucun
// Sortie  : pointeur vers la chaîne de caractère saisie.
/******************************************************************************/
char *saisie_nomF();

/******************************************************************************/
// Fonction pour détecter et saisir une touche-clavier.
// Entrées : pointeur vers la touche qui a été pesée (sortie).
// Sortie  : 1 si une touche a été pesée, 0 sinon.
/******************************************************************************/
int  saisie_touche(char *ch);

/******************************************************************************/
// Fonction pour détecter la valeur d'un pixel-écran.
// Entrées : la position-écran a intérroger.
// Sortie  : la valeur du pixel (de 0..15).
/******************************************************************************/
int  detecter_pixel(t_pt2d pos);

/******************************************************************************/
// Fonction pour effacer tout l'écran.
// Entrées : aucun
// Sortie  : aucun
/******************************************************************************/
void effacer_ecran();

/******************************************************************************/
// Fonction pour effacer juste la section-route de l'écran.
// Entrées : dimx, dimy = les dimensions de la route à effacer.
// Sortie  : aucun
/******************************************************************************/
void effacer_route(int dimx, int dimy);

/******************************************************************************/
// Fonction pour faire un delai d'affichage.
// Entrées : le nombre de millisecondes de délai (1000 = 1 sec.).
// Sortie  : aucun
/******************************************************************************/
void delai(int ms);


/******************************************************************************/
// Fonction pour faire une pause-écran (avec touche-clavier).
// Entrées : aucun
// Sortie  : aucun
/******************************************************************************/
void pause_ecran();

/******************************************************************************/
// Fonction pour allumer un pixel JAUNE à une position désirée.
// Sera utile uniquement pour faire du débuggage.
// Entrées : x, y = position du pixel.
// Sortie  : aucun
/******************************************************************************/
void pixel(int x, int y);

#endif