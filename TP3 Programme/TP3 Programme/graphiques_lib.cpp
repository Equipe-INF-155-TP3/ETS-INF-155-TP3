/******************************************************************************
// GRAPHIQUES_LIB.CPP
// ****************************************************************************
// Cette librairie contient les fonctions d'affichage en mode graphique.
/******************************************************************************/

#include "winbgim.h"
#include "graphiques_lib.h"
#include <math.h>

#define BKSPACE  8
#define RETURN  13
#define MAXL    30
#define ARRONDI(x) ((int)floor(x + 0.5))   //permet d'arrondir les coordonnées réelles

/******************************************************************************
// initialiser_graphique
// ****************************************************************************
// Cette fonction permet d'ouvrir le mode graphique.
******************************************************************************/
void  initialiser_graphique()
{	/* demander l'auto détection */
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
// Cette fonction privée permet de dessiner une des lignes de la route.
// ****************************************************************************
// Parametres : ptA, ptB = les 2 extrémités de la ligne à afficher.
******************************************************************************/
static void dessiner_ligne(t_pt2d ptA, t_pt2d ptB)       
{
	setcolor(LIGNE);    
	setlinestyle(SOLID_LINE, 1, 3);

	/****** ARRONDIR LES POINTS ******/
	moveto(ARRONDI(ptA.X), ARRONDI(ptA.Y));  //Positionner le crayon au debut de la ligne
		   
	lineto(ARRONDI(ptB.X), ARRONDI(ptB.Y));  //Faire une ligne jusqu'a l'extremité de fin
}


/******************************************************************************
// dessiner_route
// ****************************************************************************
// Cette fonction permet de dessiner la route à parcourir.
// ****************************************************************************
// Parametres : route = le contenu complet de la route à afficher.
******************************************************************************/
void dessiner_route(const t_route *route)     

{ 
	int i;
	int xmax, ymax;


	xmax = route->dimx;    //on récupère les coordonnées maximales X et Y
	ymax = route->dimy;

	setcolor(WHITE); //On veut des lignes blanches

	for (i = 0; i < route->nb_lignes; i++)
	{
		line(route->liste_lignes[i].ptA.X, /* On fait les lignes en partant d'un point A (X,Y) a un point B	(X,Y)								*/
			 route->liste_lignes[i].ptA.Y,  
			 route->liste_lignes[i].ptB.X,
			 route->liste_lignes[i].ptB.Y);

		printf("\n%i \n%i \n%i \n%i\n", route->liste_lignes[i].ptA.X, route->liste_lignes[i].ptA.Y, route->liste_lignes[i].ptB.X, route->liste_lignes[i].ptB.Y);
		getch();
	}

}


/******************************************************************************
// dessiner_chemin
// ****************************************************************************
// Cette fonction permet de dessiner les points-cibles du chemin à suivre.
// Ces points seront numérotés à l'écran à partir de 1.
// ****************************************************************************
// Parametres : chemin = le contenu complet de chemin à suivre.
******************************************************************************/
void dessiner_chemin(const t_chemin *chemin)     
{ 
	int i;

	setcolor(RED); //On veut des points rouge

	for (i = 0; i <= chemin->nb_pts; i++);
	{
		circle(chemin->liste_pts[i].X, 		//Cercle a partir avec coordonnée (X,Y) avec rayon de 1
			   chemin->liste_pts[i].Y, 1);
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
   circle(ARRONDI(pt.X), ARRONDI(pt.Y), 6);   //cercle avec 6 pixels de rayon
   floodfill(ARRONDI(pt.X), ARRONDI(pt.Y), coul);
}


/******************************************************************************
// dessiner_auto
// ****************************************************************************
// Cette fonction permet de dessiner une auto.
// ****************************************************************************
// Parametres : ptAuto = position de l'auto.
//              supG, supD, infG, infD = les 4 coins de l'auto à afficher.
//              coul= la couleur de l'auto.
******************************************************************************/
void dessiner_auto(t_pt2d ptAuto, t_pt2d supG, t_pt2d supD, t_pt2d infG, t_pt2d infD, int coul)      
{   /* calcul de la distance diagonale du rectangle */
	int dx = (infD.X - supG.X);   
    int dy = (infD.Y - supG.Y);

	setcolor(coul);    
	setlinestyle(SOLID_LINE, 1, 2);
	setfillstyle(SOLID_FILL, coul);

	/* déssiner l'oeil de l'auto */
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
// Fonction pour afficher les coordonnées d'un point-cible du chemin à suivre.
// ****************************************************************************
// Parametres : cible = la position du point.
//              i = son indice dans la liste.
//              dimx = la larguer de la route.
/*****************************************************************************/
void afficher_pos(t_pt2d cible, int i, int dimx)
{  int  texth, py;
   char buff[MAXL];

   setcolor(WHITE);
   /* Si c'est le premier point, on afficher d'abord le titre */
   if (i==0){
     settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
     outtextxy(dimx + 8, 0, "CIBLES :");
   }

   settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
   texth = textheight("XXX") + 1;   //taille de la police en pixels
   py = 20 + (i * texth);           //calcul de la position verticale

   /* On converti les coordonnées en string avant d'afficher */
   sprintf(buff, "%2i:(%4d, %4d )", i+1, (int)cible.X, (int)cible.Y);

   outtextxy(dimx + 10, py, buff);   //à droite de la route
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
   bar(0, dimy + 8, 1202, dimy + 40);   //barre rouge pour la couleur de fond

   setcolor(WHITE);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(px, dimy + 15, "(N)ouveau Fichier");
   px += textwidth("(N)ouveau Fichier") + 20;         //décaler la position horiz.

   outtextxy(px, dimy + 15, "(D)emarrer Auto");
   px += textwidth("(D)emarrer auto") + 20;           //décaler la position horiz.

   outtextxy(px, dimy + 15, "(ESC) Annuler Simulation");
   px += textwidth("(ESC) Annuler Simulation") + 20;  //décaler la position horiz.

   outtextxy(px, dimy + 15, "(Q)uitter");
}


/******************************************************************************
// detecter_pixel
// ****************************************************************************
// Fonction pour détecter la valeur d'un pixel-écran.
// ****************************************************************************
// Parametres : la position-écran a intérroger.
// Sortie  : la valeur du pixel (de 0..15).
/*****************************************************************************/
int detecter_pixel(t_pt2d pos)
{ return  getpixel(pos.X, pos.Y); }


/******************************************************************************
// effacer_route
// ****************************************************************************
// Fonction pour effacer juste la section-route de l'écran.
// ****************************************************************************
// Parametres : dimx, dimy = les dimensions de la route à effacer.
/*****************************************************************************/
void effacer_route(int dimx, int dimy)
{ 	setfillstyle(SOLID_FILL, BLACK);
	  bar(0, 0, dimx+6, dimy+6);
}


/******************************************************************************
// effacer_ecran
// ****************************************************************************
// Fonction pour effacer tout l'écran.
/*****************************************************************************/
void effacer_ecran()
{  cleardevice(); }


/******************************************************************************
// saisie_nomF
// ****************************************************************************
// Fonction pour saisir un nom de fichier en mode graphique.
// ****************************************************************************
// Parametres : aucun
// Sortie  : pointeur vers la chaîne de caractère saisie.
/*****************************************************************************/
char * saisie_nomF()
{  int px=10, l = 0, fini = 0;;
   char ch, buff[2]={0, 0};
   static char nomF[MAXL] = {0};   //chaîne de la saisie

   /* Nettoyage de l'écran et afficher la question */
   effacer_ecran();
   setcolor(WHITE);
   setfillstyle(SOLID_FILL, BLACK);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
   outtextxy(px, 15, "Quel est le fichier texte ? ");
   px += textwidth("Quel est le fichier texte ? ");   //position de départ de la saisie

   /* tant que l'on a pas reçu la touche <ENTER> lire les lettres de la chaîne */
	do {
		ch = _getch();
		switch (ch) {
			case BKSPACE :   //enlever une lettre de la chaîne
					if (l) { 
						--l;  nomF[l] = '\0';
						px-=16;
						bar(px, 15, px+20, 31);   //effacer derniere lettre
					}
					break;

			case RETURN  : fini = 1;   //fin de la saisie
					break;

			default :                  //ajouter une lettre a la chaine
					if (l<MAXL) {
						nomF[l] = ch;  
						l++;  nomF[l] = '\0';
						buff[0] = ch;
						outtextxy(px, 15, buff);   //afficher la lettre
						px+=16;
					}
		}
	} while (!fini);

	return nomF;
}


/******************************************************************************
// saisie_touche
// ****************************************************************************
// Fonction pour détecter et saisir une touche-clavier.
// ****************************************************************************
// Parametre : pointeur vers la touche qui a été pesée (sortie).
// Sortie  : 1 si une touche a été pesée, 0 sinon.
/*****************************************************************************/
int saisie_touche(char *ch)
{ 
  if (_kbhit()) {            //si on a détecté une touche-clavier..
    *ch = toupper(_getch());   //la touche sera retournée en MAJUSCULES
	return 1;
  }

  return 0;   //aucune touche détectée
}


/******************************************************************************
// delai
// ****************************************************************************
// Fonction pour faire un delai d'affichage.
// ****************************************************************************
// Parametre : le nombre de millisecondes de délai (1000 = 1 sec.).
/*****************************************************************************/
void delai(int ms)
{  delay(ms); }


/******************************************************************************
// pause-ecran
// ****************************************************************************
// Fonction pour faire une pause-écran (avec touche-clavier).
// ****************************************************************************
// Parametres : aucun
/*****************************************************************************/
void pause_ecran()
{  _getch();  }


/******************************************************************************
// pixel
// ****************************************************************************
// Fonction pour allumer un pixel JAUNE à une position désirée.
// ****************************************************************************
// Parametres : x, y = position du pixel.
/*****************************************************************************/
void pixel(int x, int y)
{ putpixel(x, y, YELLOW); }