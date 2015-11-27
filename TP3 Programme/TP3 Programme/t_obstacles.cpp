#include "t_obstacles.h"





  //************************###########################***********************/
 //*************************# Fonction: detecter_auto #**********************/
//**************************###########################*********************/
static int detecter_auto(const t_obstacle *obs){
	double vel, dx, dy;
	vel = sqrt(dist(obs->velocite,));


}




  //***********************#############################**********************/
 //************************# Fonction: creer_liste_obs #*********************/
//*************************#############################********************/
t_liste_obs  creer_liste_obs(int nb_obs, int dimx, int dimy){

	t_liste_obs liste;
	int i;
	double vel, dir;
	t_obstacle *obs;
	liste.obstacles	= (t_obstacle *)malloc(sizeof(t_obstacle)*nb_obs);
	if (liste.obstacles == NULL){//si l'alocation s'est bien déroulé.
		liste.nombre = 0;
	} else {
		liste.nombre = nb_obs;
		srand(time(NULL));
	
		for (i=0; i<liste.nombre; i++){
			obs = &liste.obstacles[i];
			//On positionne les obstacles à au moin 5 pixel des bordures.
			obs->position.X = rand()%(dimx-2*DIST_MIN)+DIST_MIN;
			obs->position.Y = rand()%(dimy-2*DIST_MIN)+DIST_MIN;

			////On calcule une vélocité aléatoire.
			obs->velocite.X = (rand()%1000)*0.001*(VEL_MAX-VEL_MIN)+VEL_MIN;
			obs->velocite.Y = (rand()%1000)*0.001*(VEL_MAX-VEL_MIN)+VEL_MIN;

			//On applique la couleur aléatoire
			do obs->couleur = rand()%MAX_COULEUR;
			while (obs->couleur == NOIR
					|| obs->couleur == AUTO
					||obs->couleur == LIGNE);
		}
	}
	return liste;

}


  //************************##########################************************/
 //*************************# Fonction: detruire_obs #***********************/
//**************************##########################**********************/
void detruire_obs(t_liste_obs *obstacles){
	free(obstacles->obstacles);
	obstacles->obstacles = NULL;
	obstacles->nombre = 0;
}


  //************************##########################************************/
 //*************************# Fonction: afficher_obs #***********************/
//**************************##########################**********************/
void afficher_obs(const t_liste_obs *obstacles){
	int i;

	for(i=0; i<obstacles->nombre; i++){
		dessiner_rond(obstacles->obstacles[i].position
					 ,obstacles->obstacles[i].couleur);
	}
}


  //************************##########################************************/
 //*************************# Fonction: deplacer_obs #***********************/
//**************************##########################**********************/
void deplacer_obs(t_liste_obs *obstacles, int dimx, int dimy){
	int i;
	t_obstacle *obs;
	for(i=0; i<obstacles->nombre; i++){
		obs = &obstacles->obstacles[i];

		//On met à jours la position.
		obs->position.X += obs->velocite.X;
		obs->position.Y += obs->velocite.Y;

		//On vérifie les bordures.
		if (obs->position.X < DIST_MIN || obs->position.X > dimx-DIST_MIN)
			obs->velocite.X *= -1;
		if (obs->position.Y < DIST_MIN || obs->position.Y > dimy-DIST_MIN)
			obs->velocite.Y *= -1;
	}
}
