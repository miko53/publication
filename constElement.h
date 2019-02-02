
#ifndef __CONSTELEMENT_H__
#define __CONSTELEMENT_H__

#include "PubElement.h"

typedef union 
{
	unsigned long ulongValue;
	unsigned char ucharValue[sizeof(unsigned long)];
} unionLongChar;


const unsigned char ID_RACINE = 0;
const unsigned char ID_CATEGORIE = 1;
const unsigned char ID_DOCUMENT = 2;

const int ICON_CATEGORIE = 0;
const int ICON_CATEGORIE_SELECT = 1;
const int ICON_ROOT = 2;
const int ICON_DOCUMENT = 3;


const int TAILLE_CHAMP_TEXTE = 255;

// version de la base
const BYTE VERSION_BASE_LOGICIEL = 10;

// version du soft, il peut y avoir plusieurs version logiciel pour une seule base
const BYTE VERSION_LOGICIEL = 10;


// offset des droits utilisateurs
//const unsigned long DROIT_OPTION_DISQUE       =   0x01;
const unsigned long DROIT_AJOUTER_ELEMENT            =   0x01;
const unsigned long DROIT_MODIFIER_ELEMENT           =   0x02;
const unsigned long DROIT_SUPPRIMER_ELEMENT          =   0x04;
const unsigned long DROIT_AJOUTER_UTILISATEUR        =   0x08;
const unsigned long DROIT_MODIFIER_DROIT_UTILISATEUR =   0x10;
const unsigned long DROIT_SUPPRIMER_UTILISATEUR      =   0x20;
const unsigned long DROIT_MODIFIER_PROPRIETE_BASE    =   0x40;
//const unsigned long DROIT_DEPLACER_ELEMENT           =   0x80;


const unsigned char CRYPT_PASSWORD[] = "DeAw{ιθ433η@SioOw5;_Z<pK";


// structure utile pour la recherche d'un auteur
typedef struct
{
	char* pNom;
	char* pPrenom;
	char* pNationalite;
} stRechercheAuteur;


// structure pour la recherche d'une categorie
typedef struct
{
	char* pNomCategorie;
	char* pNomLogin;
} stRechercheCategorie;


// structure de passage pour les publication
typedef struct
{
	long idAuteur;
	long idSujet;
	long idGenre;
	long idType;
	BOOL fichierValide;
	CString nomFichier;
	CString resume;
	CString nomDocument;
	CList<long, long&> listMotClefs;
	CPubElement *elementPere;
} stAjouterPublication;


// boite de dialogue d'ajout ou de modification, le choix se fait par 
// la bd dialogue qui ouvre la fenetre 
#define o_OUVERTURE_NORMAL          0
#define o_OUVERTURE_PAR_RECHERCHE   1


//modification de publication
const unsigned char PAS_MODIFICATION =    0x00;
const unsigned char MODIFICATION_TYPE_1 = 0x01;
const unsigned char MODIFICATION_TYPE_2 = 0x02;
const unsigned char MODIFICATION_TYPE_3 = 0x04;
const unsigned char MODIFICATION_TYPE_4 = 0x08;
const unsigned char MODIFICATION_TYPE_5 = 0x10;



// modification de mot de pas
const int MODIF_OK = 1;
const int ANCIEN_PASSWORD_KO = 2;

#endif //__CONSTELEMENT_H__