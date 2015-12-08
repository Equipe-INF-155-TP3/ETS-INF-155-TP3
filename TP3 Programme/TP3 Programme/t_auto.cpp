#include "t_auto.h"

  //***********************##########################*************************/
 //************************# Fonction: detecter_obs #************************/
//*************************##########################***********************/
static int detecter_obs(const t_auto *navette){
	int couleur;
	double distance, angle;
	t_pt2d point;
	double test = DEMI_PI;
	double max = navette->largeur/2+30;
	for(distance = navette->largeur/2; distance <= max; distance += 15 ){
		for(angle = -DEMI_CHP_VIS_VOIT; angle <= DEMI_CHP_VIS_VOIT ; angle += PAS_CHP_VIS_VOIT ){
			point.X = navette->position.X+distance*cos(angle-navette->dir+DEMI_PI);
			point.Y = navette->position.Y+distance*sin(angle-navette->dir+DEMI_PI);
			couleur = detecter_pixel(point);
			//dessiner_rond(point, AUTO);
			if ( couleur != AUTO && couleur != NOIR ){
				//printf("atention!  Pouet Pouet!\n");
				//dessiner_rond(point, 2);
				return 1;
			}
		}
	}
	return 0;
}


  //*********************###############################**********************/
 //**********************# Fonction: calcule_les_coins #*********************/
//***********************###############################********************/
//Permet de mettre à jours la position des coins de la voiture.
static void calcule_les_coins(t_auto *voiture){
	int demilargeur;
	double sindir, cosdir;

	//On précalcule les valeurs complexes pour sauver de la puissance de calcul.
	demilargeur = voiture->largeur/2;
	sindir = sin(voiture->dir);
	cosdir = cos(voiture->dir);

	//On calcule les coins.
	/* calculer les 2 coins du devant */
	voiture->supG.X = voiture->position.X - (cosdir * demilargeur);
	voiture->supG.Y = voiture->position.Y + (sindir * demilargeur);

	voiture->supD.X = voiture->position.X + (cosdir * demilargeur);
	voiture->supD.Y = voiture->position.Y - (sindir * demilargeur);

	/* calculer les 2 coins du derrière */
	voiture->infG.X = voiture->supG.X - (sindir * voiture->longueur);
	voiture->infG.Y = voiture->supG.Y - (cosdir * voiture->longueur);

	voiture->infD.X = voiture->supD.X - (sindir * voiture->longueur);
	voiture->infD.Y = voiture->supD.Y - (cosdir * voiture->longueur);
}


  //**************************#######################*************************/
 //***************************# Fonction: init_auto #************************/
//****************************#######################***********************/
t_auto init_auto(t_pt2d pos_depart, double dir_depart){
	t_auto voiture; //On crée la nouvelle voiture

	//On la positionne comme indiqué.
	voiture.position = pos_depart;
	voiture.dir = dir_depart;

	//On initialise les valeurs.
	voiture.acc.X = 0; voiture.acc.Y = 0;
	voiture.vel.X = 0; voiture.vel.Y = 0;
	voiture.longueur = LONG; voiture.largeur = LARG;
	voiture.attente = 0;

	//On calcule les positions des coins.
	calcule_les_coins(&voiture);

	return voiture;
}


  //************************##########################************************/
 //*************************# Fonction: obt_pos_auto #***********************/
//**************************##########################**********************/
void obt_pos_auto(const t_auto *navette, t_pt2d *pos_ref, 
	                t_pt2d *supG, t_pt2d *supD, t_pt2d *infG, t_pt2d *infD){

	//On copie les valeurs dans les pointeurs.
	*pos_ref = navette->position;
	*supG = navette->supG;
	*supD = navette->supD;
	*infG = navette->infG;
	*infD = navette->infD;
}


  //**********************##############################**********************/
 //***********************# Fonction: changer_acc_auto #*********************/
//************************##############################********************/
void changer_acc_auto(t_auto *navette, t_pt2d dest){
	double distance;
	t_pt2d delta;
	double gaz;


	//On calcule la distance entre la voiture et sa destination.
	delta.X = dest.X-navette->position.X;
	delta.Y = dest.Y-navette->position.Y;
	distance = dist(dest,navette->position);

	
	//On calcule l'accélération.
	if (detecter_obs(navette)){
		navette->attente = 1;
		navette->acc.X = navette->vel.X*FREIN;
		navette->acc.Y = navette->vel.Y*FREIN;
	} else {
		if (navette->attente)
			gaz = PRUDENCE;
		else gaz = 1;
		
		navette->acc.X = delta.X/distance*gaz;
		navette->acc.Y = delta.Y/distance*gaz;
	}

	//Si la voiture s'approche de sa destination, elle cêsse d'accélérer.
	if(distance*2 < navette->largeur ){
		if (abs(delta.X) < 1)
			navette->acc.X = 0;
		else
			navette->acc.X *= 0.1;
		if (abs(delta.Y) < 1)
			navette->acc.Y = 0;
		else
			navette->acc.Y *= 0.1;
		navette->attente = 0;
	}
}


  //************************###########################***********************/
 //*************************# Fonction: deplacer_auto #**********************/
//**************************###########################*********************/
void deplacer_auto(t_auto *navette){
	double vitesse;//Serviras à stoker la vitesse.

	//On accumule la vitesse avec l'accelereration.
	navette->vel.X += navette->acc.X;
	navette->vel.Y += navette->acc.Y;

	vitesse = sqrt(  navette->vel.X*navette->vel.X
					 +navette->vel.Y*navette->vel.Y );
	if (vitesse > MAXVEL){//On normalise la vitesse.
		navette->vel.X *= MAXVEL/vitesse;
		navette->vel.Y *= MAXVEL/vitesse;
	}

	//On accumule la position avec la vitesse.
	navette->position.X += navette->vel.X;
	navette->position.Y += navette->vel.Y;

	//On recalcule la direction.
	//La fonction atan2() corrige automatiquement les signes
	//On ajoute PI pour compencer la direction décalé de la voiture.
	navette->dir = atan2(-navette->vel.Y,navette->vel.X)+DEMI_PI;

	//On calcule les nouvelles positions des coins.
	calcule_les_coins(navette);
}




