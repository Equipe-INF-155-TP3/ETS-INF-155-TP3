

#if !defined (_T_AUTO_)
#define _T_AUTO_


	  //********************###############################*******************/
	 //*********************#  Inclure les bibliothèques  #******************/
	//**********************###############################*****************/

#include "graphiques_lib.h"
#include <math.h>


	  //**********************############################********************/
	 //***********************#  Définir les constantes  #*******************/
	//************************############################******************/

	#define LONG    70
	#define LARG    40
	#define MAXVEL	10 



	typedef struct{						//Enregistrement des infos sur l'auto
	  t_pt2d	acc;					//vecteur accélération
	  t_pt2d	vel;					//vecteur vitesse
	  t_pt2d	position;				//position de l'oeil (point de référence)
	  int		longueur, largeur;		//dimensions de l'auto
	  t_pt2d	supG, supD, infG, infD;	//coordonnées des 4 coins de l'auto (pour afficher)
	  double	dir;					//angle de direction (en radians)
	  int		attente;				//booléen pour indiquer si l'auto attends
										//le passage d'un piéton
	} t_auto;


	  //*********************#############################********************/
	 //**********************#  Prototypes de fonctions  #*******************/
	//***********************#############################******************/


	/******************************************************************************
	nom: init_auto
	description: Crée et initialise la navette avec les données de départ.
	paramètres:
	- t_pt2d: "pos_depart" 
	- double: "dir_depart" 
	retour: 
	- t_auto:
	//****************************************************************************/
	t_auto init_auto(t_pt2d, double);


	/******************************************************************************
	nom: obt_pos_auto
	description: Sert à récupérer la position de référence 
				et les 4 coins de la navette.
	paramètres: 
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
	description: Permet de calculer l'accélération de la navette en fonction de 
				sa destination.
	paramètres:
	- t_auto *: "navette"
	- t_pt2d *: "dest"
	retour: aucun
	//****************************************************************************/
	void changer_acc_auto(t_auto *, t_pt2d );


	/******************************************************************************
	nom: deplacer_auto
	description: Sert à mettre-à-jour la vecteur de vitesse et la position de la navette. 
	paramètres:
	- t_auto *: "navette"
	retour: aucun
	//****************************************************************************/
	void deplacer_auto(t_auto *);


#endif