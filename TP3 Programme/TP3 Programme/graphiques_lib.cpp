/******************************************************************************
// GRAPHIQUES_LIB.CPP
// ****************************************************************************
// Cette librairie contient les fonctions d'affichage en mode graphique.
/******************************************************************************/

#include "winBGIm.h"
#include "graphiques_lib.h"
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

#define BKSPACE  8
#define RETURN  13
#define MAXL    30
#define ARRONDI(x) ((int)floor(x + 0.5))   /* Permet d'arrondir les coordonn�es r�elles */

/******************************************************************************
// initialiser_graphique
// ****************************************************************************
// Cette fonction permet d'ouvrir le mode graphique.
******************************************************************************/
void  initialiser_graphique()
{	/* demander l'auto d�tection */
	int gdriver = DETECT, gmode;

	/* initialiser le mode graphique */
	initgraph(&gdriver, &gmode, "");
}

/******************************************************************************
// fermer_graphique
// ****************************************************************************
// Cette fonction permet de fermer le mode graphique.
******************************************************************************/
void  fermer_graphique()
{  closegraph();  }


/******************************************************************************
// dessiner_ligne
// ****************************************************************************
// Cette fonction priv�e permet de dessiner une des lignes de la route.
// ****************************************************************************
// Parametres : ptA, ptB = les 2 extr�mit�s de la ligne � afficher.
******************************************************************************/
static void dessiner_ligne(t_pt2d ptA, t_pt2d ptB)       
{
	setcolor(LIGNE);    
	setlinestyle(SOLID_LINE, 1, 3);

	/****** ARRONDIR LES POINTS ******/
	moveto(ARRONDI(ptA.X), ARRONDI(ptA.Y));  /* Positionner le crayon au debut de la ligne */
		   
	lineto(ARRONDI(ptB.X), ARRONDI(ptB.Y));  /* Faire une ligne jusqu'a l'extremit� de fin */
}


/******************************************************************************
// dessiner_route
// ****************************************************************************
// Cette fonction permet de dessiner la route � parcourir.
// ****************************************************************************
// Parametres : route = le contenu complet de la route � afficher.
******************************************************************************/
void dessiner_route(const t_route *route)     

{ 
	int i;
	int xmax, ymax;

	xmax = route->dimx;   
	ymax = route->dimy;

	setcolor(LIGNE);					/* On veut des lignes blanches */

	/* Dessiner route avec point A et B initial et point A et B final */
	for (i = 0; i < route->nb_lignes; i++)	
	{
		line(route->liste_lignes[i].ptA.X,
			 route->liste_lignes[i].ptA.Y,
			 route->liste_lignes[i].ptB.X,
			 route->liste_lignes[i].ptB.Y);
	}
}


/******************************************************************************
// dessiner_chemin
// ****************************************************************************
// Cette fonction permet de dessiner les points-cibles du chemin � suivre.
// Ces points seront num�rot�s � l'�cran � partir de 1.
// ****************************************************************************
// Parametres : chemin = le contenu complet de chemin � suivre.
******************************************************************************/
void dessiner_chemin(const t_chemin *chemin)     
{ 
	int i;
	char buff[80];

					
	setfillstyle(SOLID_FILL, POINT);	/* Couleur du remplissage */

	for (i = 0; i < chemin->nb_pts; i++)
	{
		setcolor(POINT);					/* On veut des points rouge */
		circle(chemin->liste_pts[i].X, 	/* Cercle avec coordonn�e (X,Y) et rayon POINT */
			   chemin->liste_pts[i].Y, POINT); 

		/* Remplissage du cercle avec couleur de remplissage */
		floodfill(chemin->liste_pts[i].X, chemin->liste_pts[i].Y, POINT); 

		setcolor(LIGNE);		/* �criture des num�ros en blanc*/
		itoa(i + 1, buff, 10);	/* Conversion de i en string; on d�bute � #1 donc +1 */

		/* �criture du num�ro de point � cot� avec d�calage de 15 */
		outtextxy(chemin->liste_pts[i].X + 15, chemin->liste_pts[i].Y, buff);   
	}
}


/******************************************************************************
// dessiner_rond
// ****************************************************************************
// Cette fonction permet de dessiner un des obstacles.
// ****************************************************************************
// Parametres : pt = la position de l'obstacle, coul = couleur de l'obstacle.
******************************************************************************/
void dessiner_rond(t_pt2d pt, int coul)  
{
   setcolor(coul);
   setlinestyle(SOLID_LINE, 1, 3);
   setfillstyle(SOLID_FILL, coul);

   /******** ARRONDIR *******/
   circle(ARRONDI(pt.X), ARRONDI(pt.Y), 6);   /* Cercle avec 6 pixels de rayon */
   floodfill(ARRONDI(pt.X), ARRONDI(pt.Y), coul);
}


/******************************************************************************
// dessiner_auto
// ****************************************************************************
// Cette fonction permet de dessiner une auto.
// ****************************************************************************
// Parametres : ptAuto = position de l'auto.
//              supG, supD, infG, infD = les 4 coins de l'auto � afficher.
//              coul= la couleur de l'auto.
******************************************************************************/
void dessiner_auto(t_pt2d ptAuto, t_pt2d supG, t_pt2d supD, t_pt2d infG, t_pt2d infD, int coul)      
{   /* calcul de la distance diagonale du rectangle */
	int dx = (infD.X - supG.X);   
    int dy = (infD.Y - supG.Y);

	setcolor(coul);    
	setlinestyle(SOLID_LINE, 1, 2);
	setfillstyle(SOLID_FILL, coul);

	/* d�ssiner l'oeil de l'auto */
	circle(ARRONDI(ptAuto.X), ARRONDI(ptAuto.Y), 6);  

	/* faire les 4 lignes du rectangle de l'auto */
	line(ARRONDI(infG.X), ARRONDI(infG.Y), ARRONDI(infD.X), ARRONDI(infD.Y));
	line(ARRONDI(infD.X), ARRONDI(infD.Y), ARRONDI(supD.X), ARRONDI(supD.Y));
	line(ARRONDI(supD.X), ARRONDI(supD.Y), ARRONDI(supG.X), ARRONDI(supG.Y));
	line(ARRONDI(supG.X), ARRONDI(supG.Y), ARRONDI(infG.X), ARRONDI(infG.Y));

	floodfill(supG.X + dx/2, supG.Y + dy/2, coul);   //remplir le rectangle
}


/******************************************************************************
// afficher_pos
// ****************************************************************************
// Fonction pour afficher les coordonn�es d'un point-cible du chemin � suivre.
// ****************************************************************************
// Parametres : cible = la position du point.
//              i = son indice dans la liste.
//              dimx = la larguer de la route.
/*****************************************************************************/
void afficher_pos(t_pt2d cible, int i, int dimx)
{  int  texth, py;
   char buff[MAXL];

   setcolor(WHITE);
   /* Si c'est le premier point, on affiche d'abord le titre */
   if (i==0){
     settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
     outtextxy(dimx + 8, 0, "CIBLES :");
   }

   settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
   texth = textheight("XXX") + 1;				/* Taille de la police en pixels */
   py = 20 + (i * texth);						/* Calcul de la position verticale */

   /* On converti les coordonn�es en string avant d'afficher */
   sprintf_s(buff, "%2i:(%4d, %4d )", i+1, (int)cible.X, (int)cible.Y);

   outtextxy(dimx + 10, py, buff);				/* � droite de la route */
}


/******************************************************************************
// afficher_menu
// ****************************************************************************
// Fonction pour afficher le menu principal.
// ****************************************************************************
// Parametres : la hauteur de la route.
/*****************************************************************************/
void afficher_menu(int dimy)
{  int px = 20;

   setfillstyle(SOLID_FILL, RED);
   bar(0, dimy + 8, 1202, dimy + 40);   /* Barre rouge pour la couleur de fond */

   setcolor(WHITE);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(px, dimy + 15, "(N)ouveau Fichier");
   px += textwidth("(N)ouveau Fichier") + 20;         /* D�caler la position horiz */

   outtextxy(px, dimy + 15, "(D)emarrer Auto");
   px += textwidth("(D)emarrer auto") + 20;           /* D�caler la position horiz */

   outtextxy(px, dimy + 15, "(ESC) Annuler Simulation");
   px += textwidth("(ESC) Annuler Simulation") + 20;  /* D�caler la position horiz */

   outtextxy(px, dimy + 15, "(Q)uitter");
}


/******************************************************************************
// detecter_pixel
// ****************************************************************************
// Fonction pour d�tecter la valeur d'un pixel-�cran.
// ****************************************************************************
// Parametres : la position-�cran a int�rroger.
// Sortie  : la valeur du pixel (de 0..15).
/*****************************************************************************/
int detecter_pixel(t_pt2d pos)
{ return  getpixel(pos.X, pos.Y); }


/******************************************************************************
// effacer_route
// ****************************************************************************
// Fonction pour effacer juste la section-route de l'�cran.
// ****************************************************************************
// Parametres : dimx, dimy = les dimensions de la route � effacer.
/*****************************************************************************/
void effacer_route(int dimx, int dimy)
{ 	setfillstyle(SOLID_FILL, BLACK);
	  bar(0, 0, dimx+6, dimy+6);
}


/******************************************************************************
// effacer_ecran
// ****************************************************************************
// Fonction pour effacer tout l'�cran.
/*****************************************************************************/
void effacer_ecran()
{  cleardevice(); }


/******************************************************************************
// saisie_nomF
// ****************************************************************************
// Fonction pour saisir un nom de fichier en mode graphique.
// ****************************************************************************
// Parametres : aucun
// Sortie  : pointeur vers la cha�ne de caract�re saisie.
/*****************************************************************************/
char * saisie_nomF()
{  int px=10, l = 0, fini = 0;;
   char ch, buff[2]={0, 0};
   static char nomF[MAXL] = {0};   /* Cha�ne de la saisie */

   /* Nettoyage de l'�cran et afficher la question */
   effacer_ecran();
   setcolor(WHITE);
   setfillstyle(SOLID_FILL, BLACK);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(px, 15, "Quel est le fichier texte ? ");
   px += textwidth("Quel est le fichier texte ? ");   /* Position de d�part de la saisie */

   /* Tant que l'on a pas re�u la touche <ENTER> lire les lettres de la cha�ne */
	do {
		ch = getch();
		switch (ch) {
			case BKSPACE :   /* Enlever une lettre de la cha�ne */
					if (l) { 
						--l;  nomF[l] = '\0';
						px-=16;
						bar(px, 15, px+20, 31);   /* Effacer derniere lettre */
					}
					break;

			case RETURN  : fini = 1;   /* Fin de la saisie */
					break;

			default :                  /* Ajouter une lettre a la chaine */
					if (l<MAXL) {
						nomF[l] = ch;  
						l++;  nomF[l] = '\0';
						buff[0] = ch;
						outtextxy(px, 15, buff);   /* Afficher la lettre */
						px+=16;
					}
		}
	} while (!fini);

	return nomF;
}


/******************************************************************************
// saisie_touche
// ****************************************************************************
// Fonction pour d�tecter et saisir une touche-clavier.
// ****************************************************************************
// Parametre : pointeur vers la touche qui a �t� pes�e (sortie).
// Sortie  : 1 si une touche a �t� pes�e, 0 sinon.
/*****************************************************************************/
int saisie_touche(char *ch)
{ 
  if (kbhit()) {            /* Si on a d�tect� une touche-clavier... */
    *ch = toupper(getch());/* La touche sera retourn�e en MAJUSCULES */
	return 1;
  }

  return 0;   /* Aucune touche d�tect�e */
}


/******************************************************************************
// delai
// ****************************************************************************
// Fonction pour faire un delai d'affichage.
// ****************************************************************************
// Parametre : le nombre de millisecondes de d�lai (1000 = 1 sec.).
/*****************************************************************************/
void delai(int ms)
{  delay(ms); }


/******************************************************************************
// pause-ecran
// ****************************************************************************
// Fonction pour faire une pause-�cran (avec touche-clavier).
// ****************************************************************************
// Parametres : aucun
/*****************************************************************************/
void pause_ecran()
{  getch();  }


/******************************************************************************
// pixel
// ****************************************************************************
// Fonction pour allumer un pixel JAUNE � une position d�sir�e.
// ****************************************************************************
// Parametres : x, y = position du pixel.
/*****************************************************************************/
void pixel(int x, int y)
{ putpixel(x, y, YELLOW); }