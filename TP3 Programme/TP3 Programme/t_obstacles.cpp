#include "t_obstacles.h"





  //************************###########################***********************/
 //*************************# Fonction: detecter_auto #**********************/
//**************************###########################*********************/
static int detecter_auto(const t_obstacle *obs){
	double dx, dy, decal, i, vel;
	t_pt2d  p3, p;
	dx = obs->velocite.X;
	dy = obs->velocite.Y;
	vel = sqrt(dx*dx + dy*dy);
	dx *= CHAMP_VISION / vel; /* Normalisation des vecteurs */
	dy *= CHAMP_VISION / vel; 

	p3.X = (obs->position.X + dx);
	p3.Y = (obs->position.Y + dy);

	for (i = -LARG_VISION; i <= LARG_VISION; i++){
		decal = (i / 2);
		p.X = p3.X + dy*decal;
		p.Y = p3.Y - dx*decal;

		if (detecter_pixel(p) == AUTO)
			return 1;
	}
	return 0;
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
	if (liste.obstacles == NULL){	/* Si l'allocation s'est bien déroulé */
		liste.nombre = 0;
	} else {
		liste.nombre = nb_obs;
		srand(time(NULL));
	
		for (i=0; i<liste.nombre; i++){
			obs = &liste.obstacles[i];
			do{
				/* On positionne les obstacles à au moins 5 pixels des bordures */
				obs->position.X = rand() % (dimx - 2 * DIST_MIN) + DIST_MIN;
				obs->position.Y = rand() % (dimy - 2 * DIST_MIN) + DIST_MIN;
			} while (detecter_auto(obs)); // 

			/* On calcule une vélocité aléatoire */
			obs->velocite.X = (rand()%1000)*0.001*(VEL_MAX-VEL_MIN)+VEL_MIN;
			obs->velocite.Y = (rand()%1000)*0.001*(VEL_MAX-VEL_MIN)+VEL_MIN;
			if (rand()%2) obs->velocite.X *= -1;
			if (rand()%2) obs->velocite.Y *= -1;


			/* On applique la couleur aléatoire */
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
		if (detecter_auto(obs)){
			if (abs(obs->velocite.X) < abs(obs->velocite.Y)){
				obs->velocite.X *= SURPRISE_FAIBLE;
				obs->velocite.Y *= SURPRISE_FORT;
			}
			else{
				obs->velocite.X *= SURPRISE_FORT;
				obs->velocite.Y *= SURPRISE_FAIBLE;
			}
			obs->position.X += obs->velocite.X*SURPRISE;
			obs->position.Y += obs->velocite.Y*SURPRISE;

		}
		;

		/* Mise à jour de la position */
		obs->position.X += obs->velocite.X;
		obs->position.Y += obs->velocite.Y;

		/* Vérification des bordures */
		if (obs->position.X < DIST_MIN || obs->position.X > dimx-DIST_MIN)
			obs->velocite.X *= COLLISION_MUR;
		if (obs->position.Y < DIST_MIN || obs->position.Y > dimy-DIST_MIN)
			obs->velocite.Y *= COLLISION_MUR;
	}
}

