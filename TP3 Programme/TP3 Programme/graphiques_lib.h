/******************************************************************************
// GRAPHIQUES_LIB.H
// ****************************************************************************
// Cette librairie contient les fonctions d'affichage en mode graphique.
// **** CE FICHIER SERA FOURNI AUX �LEVES ****
/******************************************************************************/
#include "donnees_route.h"
#include <math.h>

#if !defined (_GRLIB_)

#define _GRLIB_ 1

/**************************
  LES CONSTANTES-COULEURS
**************************/

#define  MAX_COULEUR	15		//indice de couleur le plus �lev�.
#define  NOIR			0       //un espace libre (noir)
#define  LIGNE			15      //une ligne (blanc)
#define  POINT			4       //un point-cible (rouge)
#define  AUTO			1       //une auto (bleu)

#define DEMI_PI atan(1.0)
#define PI asin(1.0)

/******************************************************************************/
// Fonction pour d�marrer le mode graphique.
// Entr�es : aucun
// Sortie  : aucun
/******************************************************************************/
void initialiser_graphique();

/******************************************************************************/
// Fonction pour fermer le mode graphique.
// Entr�es : aucun
// Sortie  : aucun
/******************************************************************************/
void fermer_graphique();

/******************************************************************************/
// Fonction pour d�ssiner la route � parcourir.
// Entr�es : les donn�es de la route.
// Sortie  : aucun
/******************************************************************************/
void dessiner_route(const t_route *route);

/******************************************************************************/
// Fonction pour d�ssiner les points-cibles du chemin � suivre.
// Ces points seront num�rot�s � l'�cran � partir de 1.
// Entr�es : les donn�es du chemin.
// Sortie  : aucun
/******************************************************************************/
void dessiner_chemin(const t_chemin *chemin);

/******************************************************************************/
// Fonction pour d�ssiner un des obstacles.
// Entr�es : la position centrale de l'obstacle, la couleur de l'obstacle.
// Sortie  : aucun
/******************************************************************************/
void dessiner_rond(t_pt2d pt, int coul);


/******************************************************************************/
// Fonction pour d�ssiner la voiture.
// Entr�es : ptAuto = position de l'oeil de l'auto.
//           supG, supD, infG, infD = les 4 coins de l'auto.
//           coul = couleur de l'auto.
// Sortie  : aucun
/******************************************************************************/
void dessiner_auto(t_pt2d ptAuto, t_pt2d supG, t_pt2d supD, t_pt2d infG, t_pt2d infD, int coul);

/******************************************************************************/
// Fonction pour afficher les coordonn�es d'un point-cible du chemin � suivre.
// Entr�es : cible = la position du point.
//           i = son indice dans la liste.
//           dimx = la larguer de la route.
// Sortie  : aucun
/******************************************************************************/
void afficher_pos(t_pt2d cible, int i, int dimx);

/******************************************************************************/
// Fonction pour afficher le menu principal.
// Entr�es : la hauteur de la route.
// Sortie  : aucun
/******************************************************************************/
void afficher_menu(int dimy);

/******************************************************************************/
// Fonction pour saisir un nom de fichier en mode graphique.
// Entr�es : aucun
// Sortie  : pointeur vers la cha�ne de caract�re saisie.
/******************************************************************************/
char *saisie_nomF();

/******************************************************************************/
// Fonction pour d�tecter et saisir une touche-clavier.
// Entr�es : pointeur vers la touche qui a �t� pes�e (sortie).
// Sortie  : 1 si une touche a �t� pes�e, 0 sinon.
/******************************************************************************/
int  saisie_touche(char *ch);

/******************************************************************************/
// Fonction pour d�tecter la valeur d'un pixel-�cran.
// Entr�es : la position-�cran a int�rroger.
// Sortie  : la valeur du pixel (de 0..15).
/******************************************************************************/
int  detecter_pixel(t_pt2d pos);

/******************************************************************************/
// Fonction pour effacer tout l'�cran.
// Entr�es : aucun
// Sortie  : aucun
/******************************************************************************/
void effacer_ecran();

/******************************************************************************/
// Fonction pour effacer juste la section-route de l'�cran.
// Entr�es : dimx, dimy = les dimensions de la route � effacer.
// Sortie  : aucun
/******************************************************************************/
void effacer_route(int dimx, int dimy);

/******************************************************************************/
// Fonction pour faire un delai d'affichage.
// Entr�es : le nombre de millisecondes de d�lai (1000 = 1 sec.).
// Sortie  : aucun
/******************************************************************************/
void delai(int ms);


/******************************************************************************/
// Fonction pour faire une pause-�cran (avec touche-clavier).
// Entr�es : aucun
// Sortie  : aucun
/******************************************************************************/
void pause_ecran();

/******************************************************************************/
// Fonction pour allumer un pixel JAUNE � une position d�sir�e.
// Sera utile uniquement pour faire du d�buggage.
// Entr�es : x, y = position du pixel.
// Sortie  : aucun
/******************************************************************************/
void pixel(int x, int y);

#endif