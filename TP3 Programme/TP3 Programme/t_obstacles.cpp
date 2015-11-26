#include "t_obstacles.h"


  //***********************#############################**********************/
 //************************# Fonction: creer_liste_obs #*********************/
//*************************#############################********************/
t_liste_obs  creer_liste_obs(int nb_obs, int dimx, int dimy){
	/*
Pour ce qui est de la couleur
d’affichage, veuillez exclure les valeurs 0 (noir), 1 (bleu) et 15 (blanc)
car ce sont des couleurs « réservées ».  La fonction retourne la nouvelle 
structure ainsi créée, ou bien une structure vide si l’allocation dynamique a échouée.
	*/
	t_liste_obs liste;
	int i;
	double vel, dir;
	t_obstacle obs;
	liste.obstacles	= (t_obstacle *)malloc(sizeof(t_obstacle)*nb_obs);
	liste.nombre = nb_obs;
	srand(time(NULL));
	
	for (i=0; i<liste.nombre; i++){
		obs = liste.obstacles[i];
		//On positionne les obstacles à au moin 5 pixel des bordures.
		obs.position.X = rand()%(dimx-2*DIST_MIN)+DIST_MIN;
		obs.position.Y = rand()%(dimy-2*DIST_MIN)+DIST_MIN;

		//On calcule une vélocité et une direction aléatoire.
		vel = (rand()%1000)*0.001*(VEL_MAX-VEL_MIN)+VEL_MIN;
		dir = (rand()%1000)*0.002*PI;

		//On décompose la vélocité en X et Y.
		obs.velocite.X = vel*cos(dir);
		obs.velocite.Y = vel*sin(dir);

		do obs.couleur = rand()%MAX_COULEUR;
		while (obs.couleur == NOIR
				|| obs.couleur == AUTO
				||obs.couleur == LIGNE);
	}

	return liste;

}


  //************************##########################************************/
 //*************************# Fonction: detruire_obs #***********************/
//**************************##########################**********************/
void detruire_obs(t_liste_obs *obstacles){}


  //************************##########################************************/
 //*************************# Fonction: afficher_obs #***********************/
//**************************##########################**********************/
void afficher_obs(const t_liste_obs *obstacles){}


  //************************##########################************************/
 //*************************# Fonction: deplacer_obs #***********************/
//**************************##########################**********************/
void deplacer_obs(t_liste_obs *obstacles, int dimx, int dimy){}
