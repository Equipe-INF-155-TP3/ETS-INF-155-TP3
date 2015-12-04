

#if !defined (_T_OBSTACLES_)
#define _T_OBSTACLES_
#define _CRT_SECURE_NO_WARNINGS

	  //********************###############################***********************/
	 //*********************#  Inclure les bibliothèques  #**********************/
	//**********************###############################*********************/

	#include "graphiques_lib.h"
	#include <time.h>


	  //**********************############################************************/
	 //***********************#  Définir les constantes  #***********************/
	//************************############################**********************/

	#define DIST_MIN 5
	#define VEL_MIN 0.1
	#define VEL_MAX 3


	  //*************************#######################**************************/
	 //**************************#  Définir les types  #*************************/
	//***************************#######################************************/

	typedef struct {             //Enregistrement d'un obstacle
		int couleur;
		t_pt2d position, velocite;
	} t_obstacle;

	typedef struct {             //Enregistrement d'une liste d'obdtacle
		t_obstacle *obstacles;
		int nombre;
	} t_liste_obs;


	  //*********************#############################************************/
	 //**********************#  Prototypes de fonctions  #************************/
	//***********************#############################**********************/


	/******************************************************************************
	nom: init_auto
	description: 
	paramètres:
	- t_pt2d: "pos_depart" 
	- double: "dir_depart" 
	retour: 
	- t_auto:
	//****************************************************************************/
	t_liste_obs  creer_liste_obs(int nb_obs, int dimx, int dimy);


	/******************************************************************************
	nom: detruire_obs
	description: 
	paramètres:
	- t_liste_obs *: "obstacles"
	retour: aucun
	//****************************************************************************/
	void detruire_obs(t_liste_obs *obstacles);


	/******************************************************************************
	nom: afficher_obs
	description: 
	paramètres:
	- const t_liste_obs *: "obstacles"
	retour: aucun
	//****************************************************************************/
	void afficher_obs(const t_liste_obs *obstacles);


	/******************************************************************************
	nom: deplacer_obs
	description: 
	paramètres:
	- t_liste_obs *: "obstacles"
	- int: "dimx"
	- int: "dimy"
	retour: aucun
	//****************************************************************************/
	void deplacer_obs(t_liste_obs *obstacles, int dimx, int dimy);


#endif