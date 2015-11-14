

#if !defined (_T_AUTO_)
#define _T_AUTO_

#include "graphiques_lib.h"


	  //********************###############################***********************/
	 //*********************#  Inclure les biblioth�ques  #**********************/
	//**********************###############################*********************/

	#define LONG    70
	#define LARG    40


	  //**********************############################************************/
	 //***********************#  D�finir les constantes  #***********************/
	//************************############################**********************/


	typedef struct{                  //Enregistrement des infos sur l'auto
	  t_pt2d  acc;               	   //vecteur acc�l�ration
	  t_pt2d  vel;               	   //vecteur vitesse
	  t_pt2d  position;                //position de l'oeil (point de r�f�rence)
	  int     longueur, largeur;       //dimensions de l'auto
	  t_pt2d  supG, supD, infG, infD;  //coordonn�es des 4 coins de l'auto (pour afficher)
	  double  dir;                     //angle de direction (en radians)
	  int attente;                     //bool�en pour indiquer si l'auto attends
									   //le passage d'un pi�ton
	} t_auto;


	  //*********************#############################************************/
	 //**********************#  Prototypes de fonctions  #************************/
	//***********************#############################**********************/


	/******************************************************************************
	nom: init_auto
	description: Cette fonction va cr�er et initialiser la navette avec les donn�es 
				de d�part.  La longueur et la largeur de la navette seront 
				initialis�es avec les constantes (LONG, LARG). La position de d�part 
				ainsi que l�angle de d�part de la navette sont copi�s dans les 
				champs � .position � et � .dir � respectivement.  Les vecteurs 
				d�acc�l�ration et de vitesse sont initialement mis � z�ro de m�me 
				que le bool�en � .attente �.
	param�tres:
	- t_pt2d: "pos_depart" 
	- double: "dir_depart" 
	retour: 
	- t_auto:
	//****************************************************************************/
	t_auto init_auto(t_pt2d pos_depart, double dir_depart);


	/******************************************************************************
	nom: obt_pos_auto
	description: 
	param�tres: Cette fonction informatrice sert � r�cup�rer la position de r�f�rence 
				et les 4 coins de la navette.  Cette fonction sera utile � chaque 
				fois que l�on voudra faire afficher la navette.
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
	description: Cette fonction va calculer la nouvelle acc�l�ration de la navette 
				pour la diriger vers le point-cible � dest � re�u en param�tre.
	param�tres:
	- t_auto *: "navette"
	- t_pt2d *: "dest"
	retour: aucun
	//****************************************************************************/
	void changer_acc_auto(t_auto *navette, t_pt2d dest);


	/******************************************************************************
	nom: deplacer_auto
	description: Cette fonction va faire la mise-�-jour du vecteur de vitesse 
				ainsi que de la position actuelle de la navette. 
	param�tres:
	- t_auto *: "navette"
	retour: aucun
	//****************************************************************************/
	void deplacer_auto(t_auto *navette);


#endif