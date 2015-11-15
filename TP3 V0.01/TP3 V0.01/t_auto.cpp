#include "t_auto.h"

static void calcule_les_coins(t_auto *voiture){
	int demilargeur;
	double sindir, cosdir;

	//On précalcule les valeurs complexes pour sauver du proccessus.
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

//Calcule une puissance en utilisant la méthode russe.
static int puissance(int x,int n){
	int mem = 1; // Permetra de gèrer les imparitées

	/*Divise successivement chaque multiplication en groupes de 2 pour 
	  finalement obtenir le même résultat q'une longue série de
	  multiplication en moin d'opérations.*/
	while(n>=2){
		if (n%2) // si n devien impair, mem compence en se multipliant par X.
			mem *= x;
		x *= x;
		n /= 2;
	}
	x *= mem;//applique la correction des valeurs impaires de n.
	return x-1;// retourne le nombre moin 1.
}



t_auto init_auto(t_pt2d pos_depart, double dir_depart){
	t_auto voiture; //On crée la nouvelle voiture


	//On la positionne comme indiqué.
	voiture.position = pos_depart;
	voiture.dir = dir_depart;

	//On initialise les valeurs.
	voiture.acc.X = 0;
	voiture.acc.Y = 0;
	voiture.vel.X = 0;
	voiture.vel.Y = 0;
	voiture.longueur = LONG;
	voiture.largeur = LARG;
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
	int dX, dY, distance;
	//On calcule la distance entre la voiture et sa destination.
	dX = dest.X-navette->position.X;
	dY = dest.Y-navette->position.Y;
	distance = sqrtf(puissance(dX,2)+puissance(dY,2));

	//On calcule l'accélération.
	navette->acc.X = dX/distance;
	navette->acc.Y = dY/distance;

	//Si la voiture s'approche de sa destination, elle cêsse d'accélérer.
	if(distance < navette->largeur/2 ){
		if (abs(dX) < 1)
			navette->acc.X = 0;
		else
			navette->acc.X = 0.1;

		if (abs(dY) < 1)
			navette->acc.Y = 0;
		else
			navette->acc.Y *= 0.1;
	}

}

