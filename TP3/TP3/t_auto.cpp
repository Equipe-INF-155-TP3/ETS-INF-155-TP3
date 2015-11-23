#include "t_auto.h"
#define PI 3.14159
static void calcule_les_coins(t_auto *voiture){
	int demilargeur;
	double sindir, cosdir;

	//On pr�calcule les valeurs complexes pour sauver du proccessus.
	demilargeur = voiture->largeur/2;
	sindir = sin(voiture->dir);
	cosdir = cos(voiture->dir);

	//On calcule les coins.
	/* calculer les 2 coins du devant */
	voiture->supG.X = voiture->position.X - (cosdir * demilargeur);
	voiture->supG.Y = voiture->position.Y + (sindir * demilargeur);

	voiture->supD.X = voiture->position.X + (cosdir * demilargeur);
	voiture->supD.Y = voiture->position.Y - (sindir * demilargeur);

	/* calculer les 2 coins du derri�re */
	voiture->infG.X = voiture->supG.X - (sindir * voiture->longueur);
	voiture->infG.Y = voiture->supG.Y - (cosdir * voiture->longueur);

	voiture->infD.X = voiture->supD.X - (sindir * voiture->longueur);
	voiture->infD.Y = voiture->supD.Y - (cosdir * voiture->longueur);
}

t_auto init_auto(t_pt2d pos_depart, double dir_depart){
	t_auto voiture; //On cr�e la nouvelle voiture

	//On la positionne comme indiqu�.
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

void obt_pos_auto(const t_auto *navette, t_pt2d *pos_ref, 
	                t_pt2d *supG, t_pt2d *supD, t_pt2d *infG, t_pt2d *infD){

	//On copie les valeurs dans les pointeurs.
	*pos_ref = navette->position;
	*supG = navette->supG;
	*supD = navette->supD;
	*infG = navette->infG;
	*infD = navette->infD;
}

void changer_acc_auto(t_auto *navette, t_pt2d dest){
	double distance;
	t_pt2d delta;
	//On calcule la distance entre la voiture et sa destination.
	delta.X = dest.X-navette->position.X;
	delta.Y = dest.Y-navette->position.Y;
	distance = dist(dest,navette->position);

	//On calcule l'acc�l�ration.
	navette->acc.X = delta.X/distance;
	navette->acc.Y = delta.Y/distance;

	//Si la voiture s'approche de sa destination, elle c�sse d'acc�l�rer.
	if(distance < navette->largeur/2 ){
		if (abs(delta.X) < 1)
			navette->acc.X = 0;
		else
			navette->acc.X = 0.1;
		if (abs(delta.Y) < 1)
			navette->acc.Y = 0;
		else
			navette->acc.Y *= 0.1;
	}
}

void deplacer_auto(t_auto *navette){
	int vitesse;//Serviras � stoker la vitesse.

	//On accumule la vitesse avec l'accelereration.
	navette->vel.X += navette->acc.X;
	navette->vel.Y += navette->acc.Y;
	vitesse == sqrtl(navette->vel.X*navette->vel.X+navette->vel.Y*navette->vel.Y);

	if (vitesse > MAXVEL){//On normalise la vitesse.
		navette->vel.X *= MAXVEL/vitesse;
		navette->vel.Y *= MAXVEL/vitesse;
	}

	//On accumule la position avec la vitesse.
	navette->position.X += navette->vel.X;
	navette->position.Y += navette->vel.Y;

	//On recalcule la direction.
	//La fonction atan2() corrige automatiquement les signes
	//On ajoute PI pour compencer la direction d�cal� de la voiture.
	navette->dir = atan2(navette->vel.Y,navette->vel.X)+PI;



	//On calcule les nouvelles positions des coins.
	calcule_les_coins(navette);
}