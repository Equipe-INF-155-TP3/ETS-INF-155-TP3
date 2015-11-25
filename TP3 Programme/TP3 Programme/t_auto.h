

#if !defined (_T_AUTO_)
#define _T_AUTO_


	  //********************###############################*******************/
	 //*********************#  Inclure les biblioth�ques  #******************/
	//**********************###############################*****************/

#include "graphiques_lib.h"
#include <math.h>


	  //**********************############################********************/
	 //***********************#  D�finir les constantes  #*******************/
	//************************############################******************/

	#define LONG    70
	#define LARG    40
	#define MAXVEL	10 



	typedef struct{						//Enregistrement des infos sur l'auto
	  t_pt2d	acc;					//vecteur acc�l�ration
	  t_pt2d	vel;					//vecteur vitesse
	  t_pt2d	position;				//position de l'oeil (point de r�f�rence)
	  int		longueur, largeur;		//dimensions de l'auto
	  t_pt2d	supG, supD, infG, infD;	//coordonn�es des 4 coins de l'auto (pour afficher)
	  double	dir;					//angle de direction (en radians)
	  int		attente;				//bool�en pour indiquer si l'auto attends
										//le passage d'un pi�ton
	} t_auto;


	  //*********************#############################********************/
	 //**********************#  Prototypes de fonctions  #*******************/
	//***********************#############################******************/


	/******************************************************************************
	nom: init_auto
	description: Cr�e et initialise la navette avec les donn�es de d�part.
	param�tres:
	- t_pt2d: "pos_depart" 
	- double: "dir_depart" 
	retour: 
	- t_auto:
	//****************************************************************************/
	t_auto init_auto(t_pt2d, double);


	/******************************************************************************
	nom: obt_pos_auto
	description: Sert � r�cup�rer la position de r�f�rence 
				et les 4 coins de la navette.
	param�tres: 
	- t_auto *: "navette" 
	- t_pt2d *: "pos_ref" 
	- t_pt2d *: "supG"
	- t_pt2d *: "supD"
	- t_pt2d *: "infG"
	- t_pt2d *: "infD"
	retour: aucun
	//****************************************************************************/
	void obt_pos_auto(const t_auto *, t_pt2d *, t_pt2d *, t_pt2d *, t_pt2d *, t_pt2d *);


	/******************************************************************************
	nom: changer_acc_auto
	description: Permet de calculer l'acc�l�ration de la navette en fonction de 
				sa destination.
	param�tres:
	- t_auto *: "navette"
	- t_pt2d *: "dest"
	retour: aucun
	//****************************************************************************/
	void changer_acc_auto(t_auto *, t_pt2d );


	/******************************************************************************
	nom: deplacer_auto
	description: Sert � mettre-�-jour la vecteur de vitesse et la position de la navette. 
	param�tres:
	- t_auto *: "navette"
	retour: aucun
	//****************************************************************************/
	void deplacer_auto(t_auto *);


#endif