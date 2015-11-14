

#if !defined (_T_AUTO_)
#define _T_AUTO_

#include "graphiques_lib.h"


	  //********************###############################***********************/
	 //*********************#  Inclure les bibliothèques  #**********************/
	//**********************###############################*********************/

	#define LONG    70
	#define LARG    40


	  //**********************############################************************/
	 //***********************#  Définir les constantes  #***********************/
	//************************############################**********************/


	typedef struct{                  //Enregistrement des infos sur l'auto
	  t_pt2d  acc;               	   //vecteur accélération
	  t_pt2d  vel;               	   //vecteur vitesse
	  t_pt2d  position;                //position de l'oeil (point de référence)
	  int     longueur, largeur;       //dimensions de l'auto
	  t_pt2d  supG, supD, infG, infD;  //coordonnées des 4 coins de l'auto (pour afficher)
	  double  dir;                     //angle de direction (en radians)
	  int attente;                     //booléen pour indiquer si l'auto attends
									   //le passage d'un piéton
	} t_auto;


	  //*********************#############################************************/
	 //**********************#  Prototypes de fonctions  #************************/
	//***********************#############################**********************/


	/******************************************************************************
	nom: init_auto
	description: Cette fonction va créer et initialiser la navette avec les données 
				de départ.  La longueur et la largeur de la navette seront 
				initialisées avec les constantes (LONG, LARG). La position de départ 
				ainsi que l’angle de départ de la navette sont copiés dans les 
				champs « .position » et « .dir » respectivement.  Les vecteurs 
				d’accélération et de vitesse sont initialement mis à zéro de même 
				que le booléen « .attente ».
	paramètres:
	- t_pt2d: "pos_depart" 
	- double: "dir_depart" 
	retour: 
	- t_auto:
	//****************************************************************************/
	t_auto init_auto(t_pt2d pos_depart, double dir_depart);


	/******************************************************************************
	nom: obt_pos_auto
	description: 
	paramètres: Cette fonction informatrice sert à récupérer la position de référence 
				et les 4 coins de la navette.  Cette fonction sera utile à chaque 
				fois que l’on voudra faire afficher la navette.
	- t_auto *: "navette" 
	- t_pt2d *: "pos_ref" 
	- t_pt2d *: "supG"
	- t_pt2d *: "supD"
	- t_pt2d *: "infG"
	- t_pt2d *: "infD"
	retour: aucun
	//****************************************************************************/
	void obt_pos_auto(const t_auto *navette, t_pt2d *pos_ref, 
	                t_pt2d *supG, t_pt2d *supD, t_pt2d *infG, t_pt2d *infD);


	/******************************************************************************
	nom: changer_acc_auto
	description: Cette fonction va calculer la nouvelle accélération de la navette 
				pour la diriger vers le point-cible « dest » reçu en paramètre.
	paramètres:
	- t_auto *: "navette"
	- t_pt2d *: "dest"
	retour: aucun
	//****************************************************************************/
	void changer_acc_auto(t_auto *navette, t_pt2d dest);


	/******************************************************************************
	nom: deplacer_auto
	description: Cette fonction va faire la mise-à-jour du vecteur de vitesse 
				ainsi que de la position actuelle de la navette. 
	paramètres:
	- t_auto *: "navette"
	retour: aucun
	//****************************************************************************/
	void deplacer_auto(t_auto *navette);


#endif