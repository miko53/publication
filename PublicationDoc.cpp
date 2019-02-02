// PublicationDoc.cpp : implementation of the CPublicationDoc class
//

#include "stdafx.h"
#include "Publication.h"
#include "direct.h"
#include "ProgressDialog.h"
#include "EnterLogin.h"
#include "InfoGalSet.h"
#include "LoginSet.h"
#include "CategorieSet.h"
#include "DocumentSet.h"
#include "NationaliteSet.h"
#include "AuteurSet.h"
#include "PubDocument.h"
#include "DES.h"
#include "AjouterAuteurDialog.h"
#include "RechercheAuteur.h"
#include "AjouterSujetDialog.h"
#include "RechercheSujet.h"
#include "AjouterTypeDialog.h"
#include "TypeSet.h"
#include "RechercheType.h"
#include "AjouterMotClefDialog.h"
#include "MotClefSet.h"
#include "RelationDocumentMotClefSet.h"
#include "RechercheMotClef.h"
#include "AjouterGenreDialog.h"
#include "RechercheGenre.h"
#include "RechercheCategorieDialog.h"
#include "PublicationView.h"
#include "RechercheDocument.h"
#include "RechercheAvdDocument.h"
#include "DialogNouvelUtilisateur.h"
#include "RechercheUtilisateurDialog.h"
#include "modifierPassWordDialog.h"
#include "ListUtilisateurDialog.h"
#include "OptionBaseDialog.h"
#include <stdio.h>

#include "PublicationDoc.h"
#include "NouvellePublication.h"
#include "constElement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef struct
{
	unsigned long identificateurRacine;
	CPubContainer* pElement;
} stSauveElement;

/////////////////////////////////////////////////////////////////////////////
// CPublicationDoc

IMPLEMENT_DYNCREATE(CPublicationDoc, CDocument)

BEGIN_MESSAGE_MAP(CPublicationDoc, CDocument)
	//{{AFX_MSG_MAP(CPublicationDoc)
	ON_COMMAND(ID_AUTEUR_AJOUTER, OnAuteurAjouter)
	ON_COMMAND(ID_AUTEUR_RECHERCHER, OnAuteurRechercher)
	ON_UPDATE_COMMAND_UI(ID_AUTEUR_AJOUTER, OnUpdateAuteurAjouter)
	ON_UPDATE_COMMAND_UI(ID_SUJET_AJOUTER, OnUpdateSujetAjouter)
	ON_COMMAND(ID_SUJET_AJOUTER, OnSujetAjouter)
	ON_COMMAND(ID_SUJET_RECHERCHER, OnSujetRechercher)
	ON_UPDATE_COMMAND_UI(ID_TYPE_AJOUTER, OnUpdateTypeAjouter)
	ON_COMMAND(ID_TYPE_AJOUTER, OnTypeAjouter)
	ON_COMMAND(ID_TYPE_RECHERCHER, OnTypeRechercher)
	ON_UPDATE_COMMAND_UI(ID_MOT_CLEFS_AJOUTER, OnUpdateMotClefsAjouter)
	ON_COMMAND(ID_MOT_CLEFS_AJOUTER, OnMotClefsAjouter)
	ON_COMMAND(ID_MOT_CLEFS_RECHERCHER, OnMotClefsRechercher)
	ON_UPDATE_COMMAND_UI(ID_GENRE_AJOUTER, OnUpdateGenreAjouter)
	ON_COMMAND(ID_GENRE_AJOUTER, OnGenreAjouter)
	ON_COMMAND(ID_GENRE_RECHERCHER, OnGenreRechercher)
	ON_COMMAND(ID_CATEGORIE_RECHERCHER, OnCategorieRechercher)
	ON_COMMAND(ID_PUBLICATION_RECHERCHER, OnPublicationRechercher)
	ON_COMMAND(ID_PUBLICATION_RECHERCHEAVD, OnPublicationRechercheavd)
	ON_UPDATE_COMMAND_UI(ID_UTILISATEUR_AJOUTER, OnUpdateUtilisateurAjouter)
	ON_COMMAND(ID_UTILISATEUR_AJOUTER, OnUtilisateurAjouter)
	ON_COMMAND(ID_UTILISATEUR_RECHERCHER, OnUtilisateurRechercher)
	ON_COMMAND(ID_UTILISATEUR_MOTDEPASSE, OnUtilisateurModifierMotdepasse)
	ON_COMMAND(ID_UTILISATEUR_LISTEDESUTILISATEURS, OnUtilisateurListedesutilisateurs)
	ON_COMMAND(ID_OPTIONS_BASE, OnOptionsBase)
	ON_COMMAND(ID_OPTION_UPDATE_BASE, OnOptionUpdateBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPublicationDoc construction/destruction

CPublicationDoc::CPublicationDoc()
{
	m_elementRoot = NULL;
	m_documentTitle = _T("");
//	SetPathName(pubInfo.databaseDirectory);
}

CPublicationDoc::~CPublicationDoc()
{
	if (m_elementRoot != NULL)
		delete m_elementRoot;
}

BOOL CPublicationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (pubInfo.flagFirstDocument == true)
	{
		pubInfo.flagFirstDocument = false;
		return FALSE;
	}
	else
	{
		CNouvellePublication fenPublication;

		if (fenPublication.DoModal() == IDOK)
		{
			m_InfoBase.m_nomBase = fenPublication.m_nomBase;
			m_InfoBase.m_nomSauvegardeBase = fenPublication.m_nomSauvegarde;
			m_InfoBase.m_utilisateurActuel = fenPublication.m_nomRoot;
			m_InfoBase.m_droitUtilisateur = -1;
			m_InfoBase.m_repertoireRacine = fenPublication.m_repertoireSauvegarde;
			SetTitle(m_documentTitle);

			return creerNouvelleBase(&fenPublication.m_passWord1);
		}
		else
			return FALSE;
	}

	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CPublicationDoc serialization

void CPublicationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPublicationDoc diagnostics

#ifdef _DEBUG
void CPublicationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPublicationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPublicationDoc commands
// returns TRUE vhen creation is OK 

BOOL CPublicationDoc::creerNouvelleBase(CString * password)
{
	CProgressDialog  barreProgres;

	barreProgres.CenterWindow();
	barreProgres.ShowWindow(SW_SHOW);
	barreProgres.m_actionActuel.SetWindowText(_T("Création des objets BDD"));

	/* creation workspace */
	m_InfoBase.m_pWorkSpace = new CDaoWorkspace();

	barreProgres.m_progressCtrl.StepIt();


	/* creation database */
	m_InfoBase.m_pDatabase = new CDaoDatabase(m_InfoBase.m_pWorkSpace);


	/* creation de l'objet table pour creer les tables     */
	/* creation de l'objet index pour creer l'index        */
	/* creation de l'objet portant sur les infos du champs */
	CDaoTableDef tableDocument(m_InfoBase.m_pDatabase);
	CDaoIndexInfo indexInfo;
	CDaoIndexFieldInfo  indexInfoField;

	indexInfo.m_strName=_T("Index");
	indexInfo.m_pFieldInfos = &indexInfoField;
	indexInfo.m_nFields = 1;
	indexInfo.m_bPrimary = TRUE;
	indexInfo.m_bUnique = TRUE;


	barreProgres.m_progressCtrl.StepIt();


	m_InfoBase.m_pWorkSpace->Create(_T("DefaultPubWorkspace"), _T("admin"), _T(""));  /* workspace de defaut */
	m_InfoBase.m_pDatabase->Create(m_InfoBase.m_nomSauvegardeBase);       /* creation de la base */

	barreProgres.m_actionActuel.SetWindowText(_T("Création des tables BDD"));
	barreProgres.m_progressCtrl.StepIt();

    // creation de la table document
	tableDocument.Create(_T("Document")); 
	tableDocument.CreateField(_T("Titre"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("IdCategorieRacine"), dbLong, 0);
	tableDocument.CreateField(_T("Resume"), dbMemo, 0);
	tableDocument.CreateField(_T("DateEntree"), dbDate, 0);
	tableDocument.CreateField(_T("Login"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);   //dbFixedField
	tableDocument.CreateField(_T("IdAuteur"), dbLong, 0);
	tableDocument.CreateField(_T("IdSujet"), dbLong, 0);
	tableDocument.CreateField(_T("IdGenre"), dbLong, 0);
	tableDocument.CreateField(_T("IdType"), dbLong, 0);
	tableDocument.CreateField(_T("Extension"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("FichierExiste"), dbBoolean, 0);
	tableDocument.CreateField(_T("IdDocument"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdDocument");
	indexInfoField.m_bDescending = TRUE;

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();

	// creation de la table categorie
	tableDocument.Create(_T("Categorie")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("DateEntree"), dbDate, 0);
	tableDocument.CreateField(_T("Login"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("IdCategorieRacine"), dbLong, 0);
	tableDocument.CreateField(_T("IdCategorie"), dbLong, 0, dbAutoIncrField);
	indexInfoField.m_strName = _T("IdCategorie");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table auteur
	tableDocument.Create(_T("Auteur")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("Prenom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("DateNaissance"), dbDate, 0);
	tableDocument.CreateField(_T("DateMort"), dbDate, 0);
	tableDocument.CreateField(_T("DateEntree"), dbDate, 0);
	tableDocument.CreateField(_T("Login"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("Nationalite"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("RensCompl"), dbMemo, 0);
	tableDocument.CreateField(_T("IdAuteur"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdAuteur");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table Sujet
	tableDocument.Create(_T("Sujet")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("IdSujet"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdSujet");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table Genre
	tableDocument.Create(_T("Genre")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("IdGenre"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdGenre");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table Type
	tableDocument.Create(_T("Type")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("IdType"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdType");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table MotCles
	tableDocument.Create(_T("MotCles")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("IdMotCles"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdMotCles");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table RelationDocMotCles
	tableDocument.Create(_T("RelationDocMotCles")); 
	tableDocument.CreateField(_T("IdDoc"), dbLong, 0);
	tableDocument.CreateField(_T("IdMotCles"), dbLong, 0);

//	indexInfoField.m_strName = _T("IdRelationDocMotCles");

//	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table loginList
	tableDocument.Create(_T("Login")); 
	tableDocument.CreateField(_T("Nom"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("MotDePasse_0"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_1"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_2"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_3"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_4"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_5"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_6"), dbByte, 0);
	tableDocument.CreateField(_T("MotDePasse_7"), dbByte, 0);

	tableDocument.CreateField(_T("Autorisation_0"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_1"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_2"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_3"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_4"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_5"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_6"), dbByte, 0);
	tableDocument.CreateField(_T("Autorisation_7"), dbByte, 0);

	tableDocument.CreateField(_T("IdLogin"), dbLong, 0, dbAutoIncrField);

	indexInfoField.m_strName = _T("IdLogin");

	tableDocument.CreateIndex(indexInfo);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// creation de la table infoGal
	tableDocument.Create(_T("InfoGal")); 
	tableDocument.CreateField(_T("RepertoireRacine"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.CreateField(_T("VersionLogiciel"), dbByte, 0);

	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();



	// creation de la table nationalite
	tableDocument.Create(_T("Nationalite")); 
	tableDocument.CreateField(_T("Pays"), dbText, TAILLE_CHAMP_TEXTE, dbVariableField);
	tableDocument.Append();
	tableDocument.Close();
	barreProgres.m_progressCtrl.StepIt();


	// entrer dans la table des premieres info, la racine, info gal et login root
	// info gal
	barreProgres.m_actionActuel.SetWindowText(_T("Mise à jour de la BDD"));

	CInfoGalSet infoGalSet(m_InfoBase.m_pDatabase);
	CLoginSet loginSet(m_InfoBase.m_pDatabase);
	CCategorieSet categorieSet(m_InfoBase.m_pDatabase);
	SYSTEMTIME dateActuel;

	unsigned char pPasswordCrypter[9] = {0};
	unsigned char pPasswordACrypter[9] = {0};
	int i = 0;

	// copie du password pour finir avec des 0 CString
	for(i=0;i<password->GetLength();i++)
		pPasswordACrypter[i] = (*password)[i];


	try
	{
		infoGalSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [InfoGal]"));
		loginSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));
		categorieSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));

		if ( (infoGalSet.CanAppend() == TRUE) &&
			 (loginSet.CanAppend() == TRUE) && 
			 (categorieSet.CanAppend() == TRUE)) 
		{
			infoGalSet.AddNew();
			infoGalSet.m_RepertoireRacine = m_InfoBase.m_repertoireRacine;
			infoGalSet.m_VersionLogiciel = VERSION_BASE_LOGICIEL;
			infoGalSet.Update();
			infoGalSet.Close();

			barreProgres.m_progressCtrl.StepIt();

			loginSet.AddNew();
			loginSet.m_Nom = m_InfoBase.m_utilisateurActuel;
			cryptageTripleDES(pPasswordACrypter, pPasswordCrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_CRYPTAGE);
			loginSet.m_MotDePasse_0 = pPasswordCrypter[0];
			loginSet.m_MotDePasse_1 = pPasswordCrypter[1];
			loginSet.m_MotDePasse_2 = pPasswordCrypter[2];
			loginSet.m_MotDePasse_3 = pPasswordCrypter[3];
			loginSet.m_MotDePasse_4 = pPasswordCrypter[4];
			loginSet.m_MotDePasse_5 = pPasswordCrypter[5];
			loginSet.m_MotDePasse_6 = pPasswordCrypter[6];
			loginSet.m_MotDePasse_7 = pPasswordCrypter[7];

			for(i=0;i<8;i++)
				pPasswordACrypter[i] = 0xFF;
			cryptageTripleDES(pPasswordACrypter, pPasswordCrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_CRYPTAGE);

			loginSet.m_Autorisation_0 = pPasswordCrypter[0];
			loginSet.m_Autorisation_1 = pPasswordCrypter[1];
			loginSet.m_Autorisation_2 = pPasswordCrypter[2];
			loginSet.m_Autorisation_3 = pPasswordCrypter[3];
			loginSet.m_Autorisation_4 = pPasswordCrypter[4];
			loginSet.m_Autorisation_5 = pPasswordCrypter[5];
			loginSet.m_Autorisation_6 = pPasswordCrypter[6];
			loginSet.m_Autorisation_7 = pPasswordCrypter[7];
			loginSet.m_IdLogin = 0;
			loginSet.Update();
			loginSet.Close();

			barreProgres.m_progressCtrl.StepIt();

			categorieSet.AddNew();
			categorieSet.m_Nom = m_InfoBase.m_nomBase;
			GetLocalTime(&dateActuel);
			categorieSet.m_DateEntree = dateActuel;
			categorieSet.m_Login = m_InfoBase.m_utilisateurActuel;
			categorieSet.m_IdCategorieRacine = 0;
			categorieSet.m_IdCategorie = 0;
			categorieSet.Update();
			categorieSet.Close();

			barreProgres.m_progressCtrl.StepIt();

		}
		else
		{
			CFile::Remove(m_InfoBase.m_nomSauvegardeBase);
			AfxMessageBox(_T("Impossible de mettre à jour la BDD"));
			infoGalSet.Close();
			loginSet.Close();
			categorieSet.Close();
			return FALSE;
		}
	}
	catch (CException* pEx)
	{
		CFile::Remove(m_InfoBase.m_nomSauvegardeBase);
		pEx->ReportError();
		infoGalSet.Close();
		loginSet.Close();
		categorieSet.Close();
		return FALSE;
	}

	AfxMessageBox(_T("La base d'essai est crée\n"), MB_OK, 0);

	m_elementRoot = new CPubRacine(m_InfoBase.m_nomBase, 0, m_InfoBase.m_repertoireRacine);
	UpdateAllViews(NULL, 0L, (CObject*) m_elementRoot);
	return TRUE;
}


BOOL CPublicationDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
// pour acces multi utilisateur
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;

	if (pubInfo.flagFirstDocument != false)
		pubInfo.flagFirstDocument = false;

	CEnterLogin boiteNomUtilisateur;

	// ouvrir base 
	m_InfoBase.m_pWorkSpace = new CDaoWorkspace();
	m_InfoBase.m_pDatabase = new CDaoDatabase(m_InfoBase.m_pWorkSpace);


	m_InfoBase.m_pWorkSpace->Create(_T("DefaultPubWorkspace"), _T("admin"), _T(""));  /* workspace de defaut */
	m_InfoBase.m_nomSauvegardeBase = CString(lpszPathName);
	m_InfoBase.m_pDatabase->Open(m_InfoBase.m_nomSauvegardeBase);


	if (boiteNomUtilisateur.DoModal() == IDOK)
	{
		CString filtreName;
		CLoginSet loginSet(m_InfoBase.m_pDatabase);
		CInfoGalSet infoSet(m_InfoBase.m_pDatabase);
		long nbEnregistrement = 0;

		// lire version 
		BeginWaitCursor();

		infoSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [InfoGal]"));
		infoSet.MoveFirst();
		while (!infoSet.IsEOF())
		{
			nbEnregistrement++;
			infoSet.MoveNext();
		}
		infoSet.MoveFirst();

		if (nbEnregistrement != 1)
		{
			AfxMessageBox(_T("La base est corrompu, impossible de l'ouvrir !"));
			return FALSE;
		}

		if (infoSet.m_VersionLogiciel != VERSION_BASE_LOGICIEL)
		{
			AfxMessageBox(_T("Désolé cette version logiciel ne peut ouvrir cette base"));
			return FALSE;
		}

		m_InfoBase.m_repertoireRacine = infoSet.m_RepertoireRacine;

		// rechercher utilisateur dans la bdd
		m_InfoBase.m_utilisateurActuel = boiteNomUtilisateur.m_login;
		filtreName.Format(_T("[Nom] = '%s'"), m_InfoBase.m_utilisateurActuel);

		loginSet.m_strFilter = filtreName;
		loginSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));
		EndWaitCursor();

		if (loginSet.IsEOF() == TRUE)
		{
			AfxMessageBox(_T("Vous n'etes pas inscrit comme utilisateur de la base !"), MB_OK);
			return FALSE;
		}


		/* Verification du mot de passe */
		char MotdePasse[9];
		char MotdePasseDecrypter[9];

		MotdePasseDecrypter[8] = '\0';
		MotdePasse[8] = '\0';
		unionLongChar uAutorisation;
		int i;

		MotdePasse[0] = loginSet.m_MotDePasse_0;
		MotdePasse[1] = loginSet.m_MotDePasse_1;
		MotdePasse[2] = loginSet.m_MotDePasse_2;
		MotdePasse[3] = loginSet.m_MotDePasse_3;
		MotdePasse[4] = loginSet.m_MotDePasse_4;
		MotdePasse[5] = loginSet.m_MotDePasse_5;
		MotdePasse[6] = loginSet.m_MotDePasse_6;
		MotdePasse[7] = loginSet.m_MotDePasse_7;
		
		cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseDecrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_DECRYPTAGE);

		if (boiteNomUtilisateur.m_password != MotdePasseDecrypter)
			return FALSE;

		/* Mettre a jour autorisation field */
		MotdePasse[0] = loginSet.m_Autorisation_0;
		MotdePasse[1] = loginSet.m_Autorisation_1;
		MotdePasse[2] = loginSet.m_Autorisation_2;
		MotdePasse[3] = loginSet.m_Autorisation_3;
		MotdePasse[4] = loginSet.m_Autorisation_4;
		MotdePasse[5] = loginSet.m_Autorisation_5;
		MotdePasse[6] = loginSet.m_Autorisation_6;
		MotdePasse[7] = loginSet.m_Autorisation_7;

		cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseDecrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_DECRYPTAGE);

		for(i=0; i<sizeof(unsigned long); i++)
			uAutorisation.ucharValue[i] = (unsigned char) MotdePasseDecrypter[i];
		
		m_InfoBase.m_droitUtilisateur = uAutorisation.ulongValue;
	}
	else
		return FALSE;

	// creer dans le tas toutes les categorie et document
	return ouvrirBase(TRUE);
	}


BOOL CPublicationDoc::ouvrirBase(BOOL isOpen)
{
	CProgressDialog  barreProgres;

	CList<stSauveElement, stSauveElement&> listElement;
	CCategorieSet cCategorie(m_InfoBase.m_pDatabase);
	CDocumentSet cDocument(m_InfoBase.m_pDatabase);
	CPubContainer * pContainer;
	stSauveElement structElement;
	POSITION aPosition;
	CString filter;
	CString filterBase = CString(_T("[IdCategorieRacine] = "));

	barreProgres.CenterWindow();
	barreProgres.ShowWindow(SW_SHOW);
	barreProgres.m_actionActuel.SetWindowText(_T("Lecture des categories "));


	cCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));
	while (!cCategorie.IsEOF())
	{
		if ((cCategorie.m_IdCategorie == 0) && (cCategorie.m_IdCategorieRacine == 0))
		{
			/* On a trouve la categorie racine, l'ajouter au doc */
			m_InfoBase.m_nomBase = cCategorie.m_Nom;
			m_elementRoot = new CPubRacine(m_InfoBase.m_nomBase, 0, m_InfoBase.m_repertoireRacine);
		}
		else
		{
			structElement.identificateurRacine = cCategorie.m_IdCategorieRacine;
			pContainer = new CPubContainer(cCategorie.m_Nom, cCategorie.m_IdCategorie);
			structElement.pElement = pContainer;
			listElement.AddHead(structElement);
		}
		cCategorie.MoveNext();		
	}

	if (m_elementRoot == NULL)
	{
		AfxMessageBox(_T("Votre base est invalide ! (Root KO)"), MB_OK);
		return FALSE;
	}
	else
	{
		// ajouter les documents de la racine
		filter = "[IdCategorieRacine] = 0";
		cDocument.m_strFilter = filter;
		cDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));

		while(!cDocument.IsEOF())
		{
			CPubDocument * pDocument;
			pDocument = new CPubDocument(cDocument.m_Titre, cDocument.m_IdDocument, cDocument.m_FichierExiste, cDocument.m_Extension);
			m_elementRoot->ajouterElement(pDocument);
			cDocument.MoveNext();
		}
		cDocument.Close();
	}


	int nbElement = listElement.GetCount();
	barreProgres.m_progressCtrl.SetRange(0, nbElement);
	barreProgres.m_progressCtrl.SetStep(1);
	barreProgres.m_actionActuel.SetWindowText(_T("Creation de l'arborescence "));


	/* avec la liste de categorie, faire l'arbre */
	aPosition = listElement.GetHeadPosition();
	while (aPosition)
	{
		structElement = listElement.GetAt(aPosition);//GetNext(aPosition);
		pContainer = (CPubContainer*) rechercherCategorieRacine(structElement.identificateurRacine, (CPubElement*) m_elementRoot);
		if (pContainer != NULL)
		{
			listElement.RemoveAt(aPosition);

			pContainer->ajouterElement(structElement.pElement);/**/

			/* recherche des documents a ajouter dans ce container */
			filter.Format(_T("%s %i"), filterBase, (structElement.pElement)->donnerIdentificateur());
			cDocument.m_strFilter = filter;
			cDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));

			barreProgres.m_actionActuel.SetWindowText(_T("Recherche documents associes "));

			while(!cDocument.IsEOF())
			{
				CPubDocument * pDocument;
				pDocument = new CPubDocument(cDocument.m_Titre, cDocument.m_IdDocument, cDocument.m_FichierExiste, cDocument.m_Extension);
				structElement.pElement->ajouterElement(pDocument);
				cDocument.MoveNext();
			}
			cDocument.Close();
			aPosition = listElement.GetHeadPosition();
			barreProgres.m_progressCtrl.StepIt();
			barreProgres.m_actionActuel.SetWindowText(_T("Creation de l'arborescence "));
		}
		else
		{
			listElement.GetNext(aPosition);
			if (!aPosition)
			{
				AfxMessageBox(_T("Votre base est invalide ! (element sans attache)"));
				return FALSE;
			}
		}
	}

  if (isOpen == TRUE)
	  AfxMessageBox(_T("La base a été correctement lu "));
	
	SetTitle(m_documentTitle);

	return TRUE;
}

CPubElement* CPublicationDoc::rechercherCategorieRacine(long identificateur, CPubElement * pElement)
{
	if ((pElement->donnerIdentificateur() == identificateur) && 
		((pElement->donnerTypeElement() == ID_CATEGORIE) ||
		 (pElement->donnerTypeElement() == ID_RACINE)))
		return pElement;
	else
	{
		if ((pElement->donnerTypeElement() == ID_CATEGORIE) ||
			(pElement->donnerTypeElement() == ID_RACINE))
		{
			CPubContainer* pContainer = (CPubContainer*) pElement;
			CPubElement* pResult;
			POSITION aPos;


			aPos = pContainer->donnerPositionTete();
			while(aPos)
			{
				pResult = rechercherCategorieRacine(identificateur, pContainer->donnerProchainElement(aPos));
				if (pResult != NULL)
					return pResult;
			}
		}

	}

	return NULL;
}

bool CPublicationDoc::ajouterCategorie(CString categorieName, CPubElement * categoriePere)
{
	/* verifier si avec les droits il peut creer la categorie*/
	/* verifier si avec autres droits, on peut la creer sur le disque */
	/* ajouter dans la base */
	/* mise a jour des vues */
	/* en cas d'erreur effacer le repertoire sur le disque */
	/* et renvoyer false */

	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) != DROIT_AJOUTER_ELEMENT)
	{
		AfxMessageBox(_T("Desolé, vous n'avez pas les droits pour ajouter une categorie"), MB_OK);
		return false;
	}

	/* est ce fait sur un container */
	if (categoriePere->donnerTypeElement() == ID_DOCUMENT)
	{
		/* cas normalement impossible, cf vue */
		AfxMessageBox(_T("Vous ne pouvez ajouter une categorie sur un document !"), MB_OK);
		return false;
	}


//	if ((m_InfoBase.m_droitUtilisateur & DROIT_OPTION_DISQUE) == DROIT_OPTION_DISQUE)
//	{
		CString nomCompletCategorie = categorieName;
		CString nomCategorie;
		CString tempString;
		CPubContainer* pContainer = (CPubContainer*) categoriePere;

		while (pContainer->donnerTypeElement() != ID_RACINE)
		{
			tempString = nomCompletCategorie;
			nomCategorie = pContainer->donnerNom();
			nomCompletCategorie.Format(_T("%s\\%s"), nomCategorie, tempString);
			pContainer = (CPubContainer*) pContainer->donnerParent();
		}
		/* ici parent = racine */
		tempString = nomCompletCategorie;
		nomCompletCategorie.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);

		if (_mkdir(nomCompletCategorie) != 0)
		{
			AfxMessageBox(_T("Impossible de creer la categorie sur le disque specifie "), MB_OK);
			return false;
		}

		/* ajouter dans la base */
		CCategorieSet jeuCategorie(m_InfoBase.m_pDatabase);
		SYSTEMTIME dateActuel;
		long newIdCategorie;

		try
		{
			jeuCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));

			newIdCategorie = createCategorieID(jeuCategorie);

			if (jeuCategorie.CanAppend() == TRUE)
			{
				jeuCategorie.AddNew();
				jeuCategorie.m_Nom = categorieName;
				GetLocalTime(&dateActuel);
				jeuCategorie.m_DateEntree = dateActuel;
				jeuCategorie.m_Login = m_InfoBase.m_utilisateurActuel;
				jeuCategorie.m_IdCategorieRacine = categoriePere->donnerIdentificateur();
				jeuCategorie.m_IdCategorie = newIdCategorie;
				jeuCategorie.Update();
				jeuCategorie.Close();
			}
			else
			{
				_rmdir(nomCompletCategorie);
				AfxMessageBox(_T("Impossible d'ecrire sur la base !"), MB_OK);
				jeuCategorie.Close();
				return false;
			}

		}
		catch (CException* pEx)
		{
			_rmdir(nomCompletCategorie);
			pEx->ReportError();
			jeuCategorie.Close();
			return false;
		}

		CPubContainer* pNewCategorie = new CPubContainer(categorieName, newIdCategorie);

		pContainer = (CPubContainer*) categoriePere;
		pContainer->ajouterElement(pNewCategorie);
		UpdateAllViews(0, 0, (CObject*) pNewCategorie);
//	}

	return true;
}

long CPublicationDoc::createCategorieID(CCategorieSet & categorie)
{
	long newID = 0;

	if (!(categorie.IsBOF() && categorie.IsEOF()))
	{
		categorie.MoveFirst();
		while(!categorie.IsEOF())
		{
			if (newID < categorie.m_IdCategorie)
				newID = categorie.m_IdCategorie;
			categorie.MoveNext();
		}
	}

	return ++newID;
}


bool CPublicationDoc::peutModifierBase()
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_MODIFIER_ELEMENT) == DROIT_MODIFIER_ELEMENT)
		return true;
	else
		return false;
}

bool CPublicationDoc::peutAjouterElemBase()
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
		return true;
	else
		return false;
}


bool CPublicationDoc::peutModifierDroitUtilisateur()
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_MODIFIER_DROIT_UTILISATEUR) == DROIT_MODIFIER_DROIT_UTILISATEUR)
		return true;
	else
		return false;
}


bool CPublicationDoc::peutSupprimerUtilisateur()
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_SUPPRIMER_UTILISATEUR) == DROIT_SUPPRIMER_UTILISATEUR)
		return true;
	else
		return false;
}


bool CPublicationDoc::donnerInfoCategorie(long categorieID, CString & nom, CString & login, COleDateTime& date)
{
	CCategorieSet jeuCategorie(m_InfoBase.m_pDatabase);
	CString filterBase = _T("[IdCategorie] = ");
	CString filter;

	filter.Format(_T("%s %i"), filterBase, categorieID);
	jeuCategorie.m_strFilter = filter;

	try
	{
		jeuCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));

		if (!jeuCategorie.IsEOF())
		{
			nom = jeuCategorie.m_Nom;
			login = jeuCategorie.m_Login;
			date = jeuCategorie.m_DateEntree;
		}
		else
		{
			AfxMessageBox(_T("La categorie n'est pas inscrite dans la base"), MB_OK);
			jeuCategorie.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuCategorie.Close();
		return false;
	}

	jeuCategorie.Close();
	return true;
}

bool CPublicationDoc::modifierCategorie(CPubContainer * pCategorie, CString nouveauNom)
{
	// [ verifier si le repertoire peut etre renommer ]
	// [ mettre a jour la base avec les nouvelles valeurs ]
	// [ informer les vues des modifications ]

	CPubContainer * pContainer = pCategorie;
	CString ancienNom;
	CString nomCategorie;
	CString tempString;
	int result;
	bool estRacine;

	if (pContainer->donnerTypeElement() == ID_RACINE)
		estRacine = true;
	else
		estRacine = false;


	if (estRacine == false)
	{
		pContainer = (CPubContainer*) pContainer->donnerParent();

		while (pContainer->donnerTypeElement() != ID_RACINE)
		{
			tempString = ancienNom;
			nomCategorie = pContainer->donnerNom();
			ancienNom.Format(_T("%s\\%s"), nomCategorie, tempString);
			pContainer = (CPubContainer*) pContainer->donnerParent();
		}

		/* ici parent = racine */
		tempString = ancienNom;
		ancienNom.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);
		tempString = ancienNom;

		ancienNom = tempString + pCategorie->donnerNom();


		nomCategorie = nouveauNom;
		nouveauNom = tempString + nomCategorie;


		result = rename(ancienNom, nouveauNom);

		if (result != 0)
		{
			AfxMessageBox(_T("Impossible de modifier le repertoire !"));
			return false;
		}
	}
	else 
		nomCategorie = nouveauNom;


	// [ recherche la categorie dans la bdd ]
	CCategorieSet jeuCategorie(m_InfoBase.m_pDatabase);
	CString filterBase = _T("[IdCategorie] = ");
	CString filter;
	SYSTEMTIME dateActuel;

	filter.Format(_T("%s %i"), filterBase, pCategorie->donnerIdentificateur());
	jeuCategorie.m_strFilter = filter;

	try
	{
		jeuCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));

		if (!jeuCategorie.IsEOF())
		{
			jeuCategorie.Edit();
			jeuCategorie.m_Nom = nomCategorie;
			GetLocalTime(&dateActuel);
			jeuCategorie.m_DateEntree = dateActuel;
			jeuCategorie.m_Login = m_InfoBase.m_utilisateurActuel;
			jeuCategorie.Update();
			jeuCategorie.Close();
		}
		else
		{
			AfxMessageBox(_T("Votre base ne possede pas cette categorie !!"), MB_OK);
			if (pCategorie->donnerTypeElement() != ID_RACINE)
				rename(nouveauNom, ancienNom);

			jeuCategorie.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		if (estRacine == false)
			rename(nouveauNom, ancienNom);
		pEx->ReportError();
		jeuCategorie.Close();
		return false;
	}


	// mettre a jour dans l'element et informer la vue
	pCategorie->modifierNomElement(nomCategorie);

	if (estRacine == true)
	{
		m_InfoBase.m_nomBase = nomCategorie;
		SetTitle(m_documentTitle);
	}

	UpdateAllViews(0, 1, (CObject*) pCategorie);

	return true;
}


void CPublicationDoc::SetTitle(LPCTSTR lpszTitle) 
{
	m_documentTitle.Format(_T("%s -- %s"), m_InfoBase.m_nomBase, m_InfoBase.m_utilisateurActuel);
	
	CDocument::SetTitle(m_documentTitle);
}


bool CPublicationDoc::peutSupprimerElement()
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_SUPPRIMER_ELEMENT) == DROIT_SUPPRIMER_ELEMENT)
		return true;
	else
		return false;
}

bool CPublicationDoc::supprimerCategorie(CPubContainer * pContainer)
{
	POSITION aPosition;

	aPosition = pContainer->donnerPositionTete();

	// supprimer d'abord les fils

	while (aPosition)
	{
		CPubElement* pFils;
		pFils = pContainer->donnerProchainElement(aPosition);

		switch (pFils->donnerTypeElement())
		{
		case ID_DOCUMENT:
			if (supprimerDocument((CPubDocument*) pFils) == false)
				return false;

			break;

		case ID_CATEGORIE:
		case ID_RACINE:
			if (supprimerCategorie((CPubContainer*) pFils) == false)
				return false;

			break;

		default:
			AfxMessageBox(" Passage interdit ! ");
			return false;
			break;
		}
	}

	// s'occuper maintenant de la categorie en gestion
	// [ effacer la categorie de la base ]
	// [ effacer la categorie et les docs sur le disque ]
	// [ effacer la categorie de la memoire ]

	CCategorieSet jeuCategorie(m_InfoBase.m_pDatabase);
	CString filterBase;
	CString filter;
	
	filterBase = _T("[IdCategorie] = ");

	filter.Format(_T("%s %i"), filterBase, pContainer->donnerIdentificateur());
	jeuCategorie.m_strFilter = filter;

	try
	{
		jeuCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));

		if (jeuCategorie.CanUpdate( ) == TRUE)
		{
			while(jeuCategorie.IsEOF() != TRUE)
			{
				jeuCategorie.Delete();
				jeuCategorie.MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("Impossible d'effectuer un effacement dans la base"));
			jeuCategorie.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuCategorie.Close();
		return false;
	}

	jeuCategorie.Close();

	// recherche d'abord le repertoire
	CPubContainer* pTemp = pContainer;
	CString nomCategorie;
	CString nomCompletCategorie;
	CString tempString;

	while (pTemp->donnerTypeElement() != ID_RACINE)
	{
		tempString = nomCompletCategorie;
		nomCategorie = pTemp->donnerNom();
		nomCompletCategorie.Format(_T("%s\\%s"), nomCategorie, tempString);
		pTemp = (CPubContainer*) pTemp->donnerParent();
	}
	/* ici parent = racine */
	tempString = nomCompletCategorie;
	nomCompletCategorie.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);

	if (_rmdir(nomCompletCategorie) != 0)
	{
		AfxMessageBox(_T("Impossible d'effacer la categorie sur le disque"));
	}

	pTemp = (CPubContainer*) pContainer->donnerParent();
	
	if (pTemp->retirerElement(pContainer) == false)
	{
		AfxMessageBox("Erreur interne, fonction retireElement");
	}

	delete pContainer;

	return true;
}


void CPublicationDoc::mettreAJourNationalite(CComboBox * pBoxCtrl)
{
	// lire la liste des nationalites 
	// et l'ajouter dans le comboBox
	CNationaliteSet jeuNationalite(m_InfoBase.m_pDatabase);

	try
	{
		jeuNationalite.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Nationalite]"));

		if (jeuNationalite.IsEOF() != TRUE)
		{
			jeuNationalite.MoveFirst();

			while (jeuNationalite.IsEOF() != TRUE)
			{
				pBoxCtrl->AddString(jeuNationalite.m_Pays);
				jeuNationalite.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuNationalite.Close();
		return;
	}

	jeuNationalite.Close();
}


bool CPublicationDoc::ajouterAuteur(CString & nomAuteur, CString & prenomAuteur, COleDateTime & dateNaissance, COleDateTime & dateMort, CString& nationalite, CString & renseignement, CComboBox& ctrlNationality, long& IDAuteur)
{
	// verifier si nationalite existe, sinon ajouter dans base
	// verfier si auteur existe, sinon ajouter dans base
	CString filterBase = _T("[Pays] = ");
	CString filter;
	CNationaliteSet jeuNationalite(m_InfoBase.m_pDatabase);

	if (nationalite != _T(""))
	{
		filter.Format(_T("%s \"%s\" "), filterBase, nationalite);
		jeuNationalite.m_strFilter = filter;
	}

	try
	{
		jeuNationalite.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Nationalite]"));

		if (jeuNationalite.IsEOF() == TRUE)
		{
#ifdef _DEBUG
			AfxMessageBox("AjoutNationalite");
#endif /* _DEBUG */

			if (jeuNationalite.CanAppend())
			{
				jeuNationalite.AddNew();
				jeuNationalite.m_Pays = nationalite;
				jeuNationalite.Update();
				jeuNationalite.Close();

				ctrlNationality.AddString(nationalite);
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre a jour la base"));
				jeuNationalite.Close();
				return false;
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuNationalite.Close();
		return false;
	}

	jeuNationalite.Close();

	// ici la nationalite est ok, on peut ajouter l'auteur dans la base
	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);

	if ((nomAuteur == _T("")) || (prenomAuteur == _T("")))
	{
		AfxMessageBox(_T("Il faut remplir les champs Nom et/ou Prenom !"));
		return false;
	}


	filter.Format(_T("[Nom] = \"%s\" AND [Prenom] = \"%s\""), nomAuteur, prenomAuteur);
	jeuAuteur.m_strFilter = filter;
	SYSTEMTIME dateActuel;

	long auteurID;

	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.IsEOF() == TRUE)
		{
#ifdef _DEBUG
			AfxMessageBox("AjoutAuteur");
#endif /* _DEBUG */ 
			jeuAuteur.Close();
			jeuAuteur.m_strFilter = (char*) NULL;
			jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));
			
			auteurID = createAuteurID(jeuAuteur);

			if (jeuAuteur.CanAppend())
			{
				jeuAuteur.AddNew();
				jeuAuteur.m_IdAuteur = auteurID;
				if (dateNaissance.GetStatus() == COleDateTime::valid)
					jeuAuteur.m_DateNaissance = dateNaissance;

				if (dateMort.GetStatus() == COleDateTime::valid)
					jeuAuteur.m_DateMort = dateMort;

				jeuAuteur.m_Nom = nomAuteur;
				jeuAuteur.m_Prenom = prenomAuteur;
				jeuAuteur.m_Nationalite = nationalite;
				jeuAuteur.m_RensCompl = renseignement;
				jeuAuteur.m_Login = m_InfoBase.m_utilisateurActuel;

				GetLocalTime(&dateActuel);
				jeuAuteur.m_DateEntree = dateActuel;
				jeuAuteur.Update();
				jeuAuteur.Close();
				IDAuteur = auteurID;
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre a jour la base"));
				jeuAuteur.Close();
				return false;
			}
		}
		else
		{
			AfxMessageBox(_T("Il existe deja un auteur portant ce nom ! "));
			jeuAuteur.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuAuteur.Close();
		return false;
	}

	AfxMessageBox(_T("L'auteur a été correctement entré "));
	jeuAuteur.Close();
	return true;
}


bool CPublicationDoc::modifierAuteur(CString & nomAuteur, CString & prenomAuteur, COleDateTime & dateNaissance, COleDateTime & dateMort, CString& nationalite, CString & renseignement, CComboBox& ctrlNationality, long IDAuteur)
{
	// voir si la nationalite existe si n'existe pas alors ajouter
	// aller chercher l'enrgistrement qu'il faut (s'il existe)
	// effectuer les modifications
	CString filterBase = _T("[Pays] = ");
	CString filter;
	CNationaliteSet jeuNationalite(m_InfoBase.m_pDatabase);

	if (nationalite != _T(""))
	{
		filter.Format(_T("%s \"%s\" "), filterBase, nationalite);
		jeuNationalite.m_strFilter = filter;
	}

	try
	{
		jeuNationalite.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Nationalite]"));

		if (jeuNationalite.IsEOF() == TRUE)
		{
#ifdef _DEBUG
			AfxMessageBox("AjoutNationalite");
#endif /* _DEBUG */

			if (jeuNationalite.CanAppend())
			{
				jeuNationalite.AddNew();
				jeuNationalite.m_Pays = nationalite;
				jeuNationalite.Update();
				jeuNationalite.Close();

				ctrlNationality.AddString(nationalite);
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre à jour la base"));
				jeuNationalite.Close();
				return false;
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuNationalite.Close();
		return false;
	}

	// ici la nouvelle nationalite si elle n'existait pas a ete ajoute

	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);

	if ((nomAuteur == _T("")) || (prenomAuteur == _T("")))
	{
		AfxMessageBox(_T("Il faut remplir les champs Nom et/ou Prenom !"));
		return false;
	}

	
	// rechercher l'auteur donne par idauteur

	filter.Format(_T("[IdAuteur] = %i"), IDAuteur);
	jeuAuteur.m_strFilter = filter;
	SYSTEMTIME dateActuel;

	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.IsEOF() != TRUE)
		{
			if (jeuAuteur.CanAppend())
			{
				jeuAuteur.Edit();
				if (dateNaissance.GetStatus() == COleDateTime::valid)
					jeuAuteur.m_DateNaissance = dateNaissance;

				if (dateMort.GetStatus() == COleDateTime::valid)
					jeuAuteur.m_DateMort = dateMort;

				jeuAuteur.m_Nom = nomAuteur;
				jeuAuteur.m_Prenom = prenomAuteur;
				jeuAuteur.m_Nationalite = nationalite;
				jeuAuteur.m_RensCompl = renseignement;
				jeuAuteur.m_Login = m_InfoBase.m_utilisateurActuel;

				GetLocalTime(&dateActuel);
				jeuAuteur.m_DateEntree = dateActuel;
				jeuAuteur.Update();
				jeuAuteur.Close();
			}
			else
			{
				jeuAuteur.Close();
				AfxMessageBox(_T("Impossible de mettre a jour la base"));
				return false;
			}
		}
		else
		{
			jeuAuteur.Close();
			AfxMessageBox(_T("Cet auteur n'est pas repértorié dans la base"));
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuAuteur.Close();
		return false;
	}

	AfxMessageBox(_T("La modification a été effectué"));

	return true;
}


long CPublicationDoc::createAuteurID(CAuteurSet & auteurSet)
{
	long newID = 0;

	if (!(auteurSet.IsBOF() && auteurSet.IsEOF()))
	{
		auteurSet.MoveFirst();
		while(!auteurSet.IsEOF())
		{
			if (newID < auteurSet.m_IdAuteur)
				newID = auteurSet.m_IdAuteur;
			auteurSet.MoveNext();
		}
	}

	return ++newID;

}



bool CPublicationDoc::rechercherAuteur(CString & nomAuteur, CString & prenomAuteur, COleDateTime & dateNaissance, COleDateTime & dateMort, CString& nationalite, CString & renseignement, long IDAuteur)
{
	// rechercher a partir de l'indentificateur de l'auteur et mettre a jour les champs
	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdAuteur] = %i", IDAuteur);

	jeuAuteur.m_strFilter = requeteSQL;

	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.IsEOF() != TRUE)
		{
			nomAuteur = jeuAuteur.m_Nom;
			prenomAuteur = jeuAuteur.m_Prenom;
			dateNaissance = jeuAuteur.m_DateNaissance;
			dateMort = jeuAuteur.m_DateMort;
			nationalite = jeuAuteur.m_Nationalite;
			renseignement = jeuAuteur.m_RensCompl;
		}		
		else
		{
			jeuAuteur.Close();
			return false;	
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuAuteur.Close();
		return false;
	}

	jeuAuteur.Close();
	return true;
}


void CPublicationDoc::rechercherAuteur(CListCtrl & listAuteur, stRechercheAuteur & stRechercheAuteur)
{

	CString requeteSQL;
	unsigned char typeRequete = 0;
	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);

	listAuteur.DeleteAllItems();
	listAuteur.EnableWindow(FALSE);

	// préparation de la requete SQL
	if (stRechercheAuteur.pNom != NULL)
		typeRequete += 1;

	if (stRechercheAuteur.pPrenom != NULL)
		typeRequete += 2;

	if (stRechercheAuteur.pNationalite != NULL)
		typeRequete += 4;

	switch (typeRequete)
	{
	case 1: // uniquement le nom
		requeteSQL.Format("[Nom] Like \"%s\"", stRechercheAuteur.pNom);
		break;

	case 2: // uniquement le prenom
		requeteSQL.Format("[Prenom] Like \"%s\"", stRechercheAuteur.pPrenom);
		break;
	case 3:  // nom + prenom 
		requeteSQL.Format("([Nom] Like \"%s\") AND ([Prenom] Like \"%s\")", stRechercheAuteur.pNom, stRechercheAuteur.pPrenom);
		break;

	case 4: // uniquement la nationalite 
		requeteSQL.Format("[Nationalite] Like \"%s\"", stRechercheAuteur.pNationalite);
		break;

	case 5: // nationalite + nom
		requeteSQL.Format("([Nom] Like \"%s\") AND ([Nationalite] Like \"%s\")", stRechercheAuteur.pNom, stRechercheAuteur.pNationalite);
		break;

	case 6: // nationalite + prenom
		requeteSQL.Format("([Nationalite] Like \"%s\") AND ([Prenom] Like \"%s\")", stRechercheAuteur.pNationalite, stRechercheAuteur.pPrenom);
		break;

	case 7: // nom + prenom + nationalite 
		requeteSQL.Format("([Nom] Like \"%s\") AND ([Prenom] Like \"%s\") AND ([Nationalite] Like \"%s\")", stRechercheAuteur.pNom, stRechercheAuteur.pPrenom, stRechercheAuteur.pNationalite);
		break;

	default:
		AfxMessageBox(_T("Type de requete impossible, Erreur interne !"));
		return;
		break;
	}

	jeuAuteur.m_strFilter = requeteSQL;


	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.IsEOF() != TRUE)
		{
			// ajouter dans la liste control 
			long indiceListCtrl = 0;
			CString dateEnCours;
			//DEBUG
			int resultItem;
			BOOL resultBool;

			//listAuteur.SetItemCount(12);
			jeuAuteur.MoveFirst();

			while(!jeuAuteur.IsEOF())
			{
				// ajouter l'auteur courant bug pe remplacer resultItem par indiceListCtrl
				resultItem = listAuteur.InsertItem(indiceListCtrl, jeuAuteur.m_Nom);
				resultBool = listAuteur.SetItemData(indiceListCtrl, (DWORD) jeuAuteur.m_IdAuteur);
				resultBool = listAuteur.SetItemText(indiceListCtrl, 1, jeuAuteur.m_Prenom);
				resultBool = listAuteur.SetItemText(indiceListCtrl, 2, jeuAuteur.m_Nationalite);
				dateEnCours = (jeuAuteur.m_DateNaissance).Format(VAR_DATEVALUEONLY);   
				resultBool = listAuteur.SetItemText(indiceListCtrl, 3, dateEnCours);
				indiceListCtrl++;
				jeuAuteur.MoveNext();
			}
			listAuteur.EnableWindow();
		}		
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre requete"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuAuteur.Close();
}


bool CPublicationDoc::effacerAuteur(long IdAuteur)
{
	// verifier si une publication ne possede pas cette auteur
	// si c'est le cas l'indiquer puis quitter
	// sinon effacer l'auteur en question


	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdAuteur] = %i", IdAuteur);

	jeuDocument.m_strFilter = requeteSQL;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (!jeuDocument.IsEOF())
		{
			AfxMessageBox("Impossible d'effacer cet auteur, un document s'y refere !");
			jeuDocument.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}

	jeuDocument.Close();

	// ici aucun document n'est de l'auteur a effacer
	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);
	jeuAuteur.m_strFilter = requeteSQL;

	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.CanAppend() && (!jeuAuteur.IsEOF()))
		{
			jeuAuteur.MoveFirst();
			jeuAuteur.Delete();
			AfxMessageBox("L'auteur a été correctement effacé");
		}
		else
		{
			AfxMessageBox("Impossible de réaliser l'effacement, auteur inconnu ou inexistant");
			jeuAuteur.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuAuteur.Close();
		return false;
	}

	jeuAuteur.Close();

	return true;
}


long CPublicationDoc::ajouterSujet(bool * resultatFonction, CString sujet)
{
	long SujetID = -1;
	CSujetSet jeuSujet(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", sujet);

	jeuSujet.m_strFilter = requeteSQL;

	try
	{
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

		if (!jeuSujet.IsEOF())
		{
			AfxMessageBox(_T("Il existe déjà un sujet à ce nom !"));
			*resultatFonction = false;
			jeuSujet.Close();
			return SujetID;
		}

		jeuSujet.Close();
		jeuSujet.m_strFilter = (char*) NULL;
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));


		if (jeuSujet.CanAppend())
		{
			SujetID = createSujetID(jeuSujet);

			jeuSujet.AddNew();
			jeuSujet.m_IdSujet = SujetID;
			jeuSujet.m_Nom = sujet;
			jeuSujet.Update();
			AfxMessageBox(_T("Le sujet a été convenablement entré dans la base"));
		}
		else
		{
			AfxMessageBox(_T("Impossible de mettre à jour la base"));
			*resultatFonction = false;
			jeuSujet.Close();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuSujet.Close();
		*resultatFonction = false;
		return SujetID;
	}

	jeuSujet.Close();

	*resultatFonction = true;
	return SujetID;
}


long CPublicationDoc::createSujetID(CSujetSet & jeuSujet)
{
	long newID = 0;

	if (!(jeuSujet.IsBOF() && jeuSujet.IsEOF()))
	{
		jeuSujet.MoveFirst();
		while(!jeuSujet.IsEOF())
		{
			if (newID < jeuSujet.m_IdSujet)
				newID = jeuSujet.m_IdSujet;
			jeuSujet.MoveNext();
		}
	}

	return ++newID;
}


bool CPublicationDoc::modifierSujet(long idSujet, CString newValue)
{
	CSujetSet jeuSujet(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdSujet] = %i", idSujet);

	if (jeuSujet.ExisteDeja(newValue) == true)
	{
		AfxMessageBox("Ce sujet existe déjà dans la base !");
		jeuSujet.Close();
		return false;
	}

	jeuSujet.m_strFilter = requeteSQL;

	try
	{
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

		if (!jeuSujet.IsEOF())
		{
			if (jeuSujet.CanAppend())
			{
				jeuSujet.Edit();
				jeuSujet.m_Nom = newValue;
				jeuSujet.Update();
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre à jour la base"));
				jeuSujet.Close();
				return false;
			}
		}
		else
		{
			AfxMessageBox(_T("Sujet inexistant, erreur interne !"));
			jeuSujet.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuSujet.Close();
		return false;
	}

	jeuSujet.Close();
	return true;
}


void CPublicationDoc::rechercheSujet(CListBox & liste, CString sujet)
{
	CSujetSet jeuSujet(m_InfoBase.m_pDatabase);
	CString requeteSQL;
	long indexListe = 0;

	requeteSQL.Format("[Nom] Like \"%s\"", sujet);

	jeuSujet.m_strFilter = requeteSQL;

	liste.ResetContent();
	liste.EnableWindow(TRUE);

	try
	{
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

		if (!jeuSujet.IsEOF())
		{
			// ajouter les elements trouvés dans la liste
			jeuSujet.MoveFirst();
			while (!jeuSujet.IsEOF())
			{
				// ajouter dans la liste l'auteur courant
				indexListe = liste.AddString(jeuSujet.m_Nom);
				liste.SetItemData(indexListe, (DWORD) jeuSujet.m_IdSujet);
				jeuSujet.MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre demande"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuSujet.Close();
	return;

}


bool CPublicationDoc::effacerSujet(long IDSujet)
{
	// verifier si une publication ne possede pas ce sujet
	// si c'est le cas l'indiquer puis quitter
	// sinon effacer le sujet en question

	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdSujet] = %i", IDSujet);

	jeuDocument.m_strFilter = requeteSQL;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (!jeuDocument.IsEOF())
		{
			AfxMessageBox("Impossible d'effacer ce sujet, un document s'y refere !");
			jeuDocument.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}

	jeuDocument.Close();

	// ici aucun document ne possede le sujet a efface
	CSujetSet jeuSujet(m_InfoBase.m_pDatabase);
	jeuSujet.m_strFilter = requeteSQL;

	try
	{
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

		if (jeuSujet.CanAppend() && (!jeuSujet.IsEOF()))
		{
			jeuSujet.MoveFirst();
			jeuSujet.Delete();
			AfxMessageBox("Le sujet a été correctement effacé");
		}
		else
		{
			AfxMessageBox("Impossible de réaliser l'effacement, sujet inconnu ou inexistant");
			jeuSujet.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuSujet.Close();
		return false;
	}

	jeuSujet.Close();

	return true;
}


bool CPublicationDoc::rechercheSujet(CString & valeurSujet, long IDSujet)
{
	// rechercher a partir de l'indentificateur du sujet et mettre a jour les champs
	CSujetSet jeuSujet(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdSujet] = %i", IDSujet);

	jeuSujet.m_strFilter = requeteSQL;

	try
	{
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

		if (jeuSujet.IsEOF() != TRUE)
		{
			valeurSujet = jeuSujet.m_Nom;
		}		
		else
		{
			jeuSujet.Close();
			return false;	
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuSujet.Close();
		return false;
	}

	jeuSujet.Close();
	return true;
}


long CPublicationDoc::ajouterType(bool * resultatFonction, CString type)
{
	long TypeID = -1;
	CTypeSet jeuType(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", type);

	jeuType.m_strFilter = requeteSQL;

	try
	{
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

		if (!jeuType.IsEOF())
		{
			AfxMessageBox(_T("Il existe déjà un type à ce nom !"));
			*resultatFonction = false;
			jeuType.Close();
			return TypeID;
		}

		jeuType.Close();
		jeuType.m_strFilter = (char*) NULL;
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));


		if (jeuType.CanAppend())
		{
			TypeID = createTypeID(jeuType);

			jeuType.AddNew();
			jeuType.m_IdType = TypeID;
			jeuType.m_Nom = type;
			jeuType.Update();
			AfxMessageBox(_T("Le type a été convenablement entré dans la base"));
		}
		else
		{
			AfxMessageBox(_T("Impossible de mettre à jour la base"));
			*resultatFonction = false;
			jeuType.Close();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuType.Close();
		*resultatFonction = false;
		return TypeID;
	}

	jeuType.Close();

	*resultatFonction = true;
	return TypeID;
}


long CPublicationDoc::createTypeID(CTypeSet & jeuType)
{
	long newID = 0;

	if (!(jeuType.IsBOF() && jeuType.IsEOF()))
	{
		jeuType.MoveFirst();
		while(!jeuType.IsEOF())
		{
			if (newID < jeuType.m_IdType)
				newID = jeuType.m_IdType;
			jeuType.MoveNext();
		}
	}

	return ++newID;
}


bool CPublicationDoc::modifierType(long idType, CString newValue)
{
	CTypeSet jeuType(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdType] = %i", idType);

	if (jeuType.ExisteDeja(newValue) == true)
	{
		AfxMessageBox("Ce type existe déjà dans la base !");
		jeuType.Close();
		return false;
	}

	jeuType.m_strFilter = requeteSQL;

	try
	{
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

		if (!jeuType.IsEOF())
		{
			if (jeuType.CanAppend())
			{
				jeuType.Edit();
				jeuType.m_Nom = newValue;
				jeuType.Update();
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre à jour la base"));
				jeuType.Close();
				return false;
			}
		}
		else
		{
			AfxMessageBox(_T("Type inexistant, erreur interne !"));
			jeuType.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuType.Close();
		return false;
	}

	jeuType.Close();
	return true;
}


bool CPublicationDoc::effacerType(long IDType)
{
	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdType] = %i", IDType);

	jeuDocument.m_strFilter = requeteSQL;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (!jeuDocument.IsEOF())
		{
			AfxMessageBox("Impossible d'effacer ce type, un document s'y refere !");
			jeuDocument.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}

	jeuDocument.Close();

	// ici aucun document ne possede le type a efface
	CTypeSet jeuType(m_InfoBase.m_pDatabase);
	jeuType.m_strFilter = requeteSQL;

	try
	{
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

		if (jeuType.CanAppend() && (!jeuType.IsEOF()))
		{
			jeuType.MoveFirst();
			jeuType.Delete();
			AfxMessageBox("Le type a été correctement effacé");
		}
		else
		{
			AfxMessageBox("Impossible de réaliser l'effacement, Type inconnu ou inexistant");
			jeuType.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuType.Close();
		return false;
	}

	jeuType.Close();

	return true;
}


void CPublicationDoc::rechercheType(CListBox & liste, CString type)
{
	CTypeSet jeuType(m_InfoBase.m_pDatabase);
	CString requeteSQL;
	long indexListe = 0;

	requeteSQL.Format("[Nom] Like \"%s\"", type);

	jeuType.m_strFilter = requeteSQL;

	liste.ResetContent();
	liste.EnableWindow(TRUE);

	try
	{
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

		if (!jeuType.IsEOF())
		{
			// ajouter les elements trouvés dans la liste
			jeuType.MoveFirst();
			while (!jeuType.IsEOF())
			{
				// ajouter dans la liste l'auteur courant
				indexListe = liste.AddString(jeuType.m_Nom);
				liste.SetItemData(indexListe, (DWORD) jeuType.m_IdType);
				jeuType.MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre demande"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuType.Close();
	return;
}


bool CPublicationDoc::rechercheType(CString & valeurType, long IDType)
{
	// rechercher a partir de l'indentificateur du type et mettre a jour les champs
	CTypeSet jeuType(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdType] = %i", IDType);

	jeuType.m_strFilter = requeteSQL;

	try
	{
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

		if (jeuType.IsEOF() != TRUE)
		{
			valeurType = jeuType.m_Nom;
		}		
		else
		{
			jeuType.Close();
			return false;	
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuType.Close();
		return false;
	}

	jeuType.Close();
	return true;
}


bool CPublicationDoc::rechercheMotClef(CString & valeurMotClef, long IDMotClef)
{
	// rechercher a partir de l'indentificateur du motC et mettre a jour les champs
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdMotCles] = %i", IDMotClef);

	jeuMotClef.m_strFilter = requeteSQL;

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (jeuMotClef.IsEOF() != TRUE)
		{
			valeurMotClef = jeuMotClef.m_Nom;
		}		
		else
		{
			jeuMotClef.Close();
			return false;	
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuMotClef.Close();
		return false;
	}

	jeuMotClef.Close();
	return true;
}

long CPublicationDoc::ajouterMotClef(bool * resultatFonction, CString motClef)
{
	long KeyNameID = -1;
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", motClef);

	jeuMotClef.m_strFilter = requeteSQL;

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (!jeuMotClef.IsEOF())
		{
			AfxMessageBox(_T("Ce mot clef existe déjà !"));
			*resultatFonction = false;
			jeuMotClef.Close();
			return KeyNameID;
		}

		jeuMotClef.Close();
		jeuMotClef.m_strFilter = (char*) NULL;
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));


		if (jeuMotClef.CanAppend())
		{
			KeyNameID = createKeyNameID(jeuMotClef);

			jeuMotClef.AddNew();
			jeuMotClef.m_IdMotCles = KeyNameID;
			jeuMotClef.m_Nom = motClef;
			jeuMotClef.Update();
			AfxMessageBox(_T("Le mot clef a été convenablement entré dans la base"));
		}
		else
		{
			AfxMessageBox(_T("Impossible de mettre à jour la base"));
			*resultatFonction = false;
			jeuMotClef.Close();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		*resultatFonction = false;
		jeuMotClef.Close();
		return KeyNameID;
	}


	jeuMotClef.Close();
	*resultatFonction = true;
	return KeyNameID;
}


long CPublicationDoc::createKeyNameID(CMotClefSet & jeuMotClef)
{
	long newID = 0;

	if (!(jeuMotClef.IsBOF() && jeuMotClef.IsEOF()))
	{
		jeuMotClef.MoveFirst();
		while(!jeuMotClef.IsEOF())
		{
			if (newID < jeuMotClef.m_IdMotCles)
				newID = jeuMotClef.m_IdMotCles;
			jeuMotClef.MoveNext();
		}
	}

	return ++newID;
}


bool CPublicationDoc::modifierMotClef(long idMotClef, CString newValue)
{
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdMotCles] = %i", idMotClef);

	if (jeuMotClef.ExisteDeja(newValue) == true)
	{
		AfxMessageBox("Ce mot existe déjà dans la base !");
		jeuMotClef.Close();
		return false;
	}

	jeuMotClef.m_strFilter = requeteSQL;

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (!jeuMotClef.IsEOF())
		{
			if (jeuMotClef.CanAppend())
			{
				jeuMotClef.Edit();
				jeuMotClef.m_Nom = newValue;
				jeuMotClef.Update();
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre à jour la base"));
				jeuMotClef.Close();
				return false;
			}
		}
		else
		{
			AfxMessageBox(_T("Mot clef inexistant, erreur interne !"));
			jeuMotClef.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuMotClef.Close();
		return false;
	}

	jeuMotClef.Close();
	return true;
}


void CPublicationDoc::rechercheMotClef(CListBox & liste, CString motClef)
{
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	CString requeteSQL;
	long indexListe = 0;

	requeteSQL.Format("[Nom] Like \"%s\"", motClef);

	jeuMotClef.m_strFilter = requeteSQL;

	liste.ResetContent();
	liste.EnableWindow(TRUE);

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (!jeuMotClef.IsEOF())
		{
			// ajouter les elements trouvés dans la liste
			jeuMotClef.MoveFirst();
			while (!jeuMotClef.IsEOF())
			{
				// ajouter dans la liste l'auteur courant
				indexListe = liste.AddString(jeuMotClef.m_Nom);
				liste.SetItemData(indexListe, (DWORD) jeuMotClef.m_IdMotCles);
				jeuMotClef.MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre demande"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuMotClef.Close();
	return;

}

bool CPublicationDoc::effacerMotClef(long IDMotClef)
{
	// verifier si une publication ne possede pas ce mot clef
	// si c'est le cas l'indiquer puis quitter
	// sinon effacer le mot clef en question

	CRelationDocumentMotClefSet jeuRelation(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdMotCles] = %i", IDMotClef);

	jeuRelation.m_strFilter = requeteSQL;

	try
	{
		jeuRelation.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [RelationDocMotCles]"));
		if (!jeuRelation.IsEOF())
		{
			AfxMessageBox("Impossible d'effacer ce mot clef, un document s'y refere !");
			jeuRelation.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuRelation.Close();
		return false;
	}

	jeuRelation.Close();

	// ici aucun document ne possede le mot clef a efface
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	jeuMotClef.m_strFilter = requeteSQL;

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (jeuMotClef.CanAppend() && (!jeuMotClef.IsEOF()))
		{
			jeuMotClef.MoveFirst();
			jeuMotClef.Delete();
			AfxMessageBox("Le mot clef a été correctement effacé");
		}
		else
		{
			AfxMessageBox("Impossible de réaliser l'effacement, mot clef inconnu ou inexistant");
			jeuMotClef.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuMotClef.Close();
		return false;
	}

	jeuMotClef.Close();

	return true;
}

bool CPublicationDoc::rechercheGenre(CString & valeurGenre, long IDGenre)
{
	// rechercher a partir de l'indentificateur du genre et mettre a jour les champs
	CGenreSet jeuGenre(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdGenre] = %i", IDGenre);

	jeuGenre.m_strFilter = requeteSQL;

	try
	{
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

		if (jeuGenre.IsEOF() != TRUE)
		{
			valeurGenre = jeuGenre.m_Nom;
		}		
		else
		{
			jeuGenre.Close();
			return false;	
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuGenre.Close();
		return false;
	}

	jeuGenre.Close();
	return true;
}

long CPublicationDoc::ajouterGenre(bool * resultatFonction, CString genre)
{
	long GenreID = -1;
	CGenreSet jeuGenre(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", genre);

	jeuGenre.m_strFilter = requeteSQL;

	try
	{
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

		if (!jeuGenre.IsEOF())
		{
			AfxMessageBox(_T("Il existe déjà un genre à ce nom !"));
			*resultatFonction = false;
			jeuGenre.Close();
			return GenreID;
		}

		jeuGenre.Close();
		jeuGenre.m_strFilter = (char*) NULL;
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));


		if (jeuGenre.CanAppend())
		{
			GenreID = createGenreID(jeuGenre);

			jeuGenre.AddNew();
			jeuGenre.m_IdGenre = GenreID;
			jeuGenre.m_Nom = genre;
			jeuGenre.Update();
			AfxMessageBox(_T("Le genre a été convenablement entré dans la base"));
		}
		else
		{
			AfxMessageBox(_T("Impossible de mettre à jour la base"));
			*resultatFonction = false;
			jeuGenre.Close();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuGenre.Close();
		*resultatFonction = false;
		return GenreID;
	}

	jeuGenre.Close();

	*resultatFonction = true;
	return GenreID;
}


long CPublicationDoc::createGenreID(CGenreSet & jeuGenre)
{
	long newID = 0;

	if (!(jeuGenre.IsBOF() && jeuGenre.IsEOF()))
	{
		jeuGenre.MoveFirst();
		while(!jeuGenre.IsEOF())
		{
			if (newID < jeuGenre.m_IdGenre)
				newID = jeuGenre.m_IdGenre;
			jeuGenre.MoveNext();
		}
	}

	return ++newID;
}



bool CPublicationDoc::modifierGenre(long idGenre, CString newValue)
{
	CGenreSet jeuGenre(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdGenre] = %i", idGenre);

	if (jeuGenre.ExisteDeja(newValue) == true)
	{
		AfxMessageBox("Ce genre existe déjà dans la base !");
		jeuGenre.Close();
		return false;
	}

	jeuGenre.m_strFilter = requeteSQL;

	try
	{
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

		if (!jeuGenre.IsEOF())
		{
			if (jeuGenre.CanAppend())
			{
				jeuGenre.Edit();
				jeuGenre.m_Nom = newValue;
				jeuGenre.Update();
			}
			else
			{
				AfxMessageBox(_T("Impossible de mettre à jour la base"));
				jeuGenre.Close();
				return false;
			}
		}
		else
		{
			AfxMessageBox(_T("Genre inexistant, erreur interne !"));
			jeuGenre.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuGenre.Close();
		return false;
	}

	jeuGenre.Close();
	return true;
}

bool CPublicationDoc::effacerGenre(long IDGenre)
{
	// verifier si une publication ne possede pas ce genre
	// si c'est le cas l'indiquer puis quitter
	// sinon effacer le genre en question

	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdGenre] = %i", IDGenre);

	jeuDocument.m_strFilter = requeteSQL;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (!jeuDocument.IsEOF())
		{
			AfxMessageBox("Impossible d'effacer ce genre, un document s'y refere !");
			jeuDocument.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}

	jeuDocument.Close();

	// ici aucun document ne possede le sujet a efface
	CGenreSet jeuGenre(m_InfoBase.m_pDatabase);
	jeuGenre.m_strFilter = requeteSQL;

	try
	{
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

		if (jeuGenre.CanAppend() && (!jeuGenre.IsEOF()))
		{
			jeuGenre.MoveFirst();
			jeuGenre.Delete();
			AfxMessageBox("Le genre a été correctement effacé");
		}
		else
		{
			AfxMessageBox("Impossible de réaliser l'effacement, genre inconnu ou inexistant");
			jeuGenre.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuGenre.Close();
		return false;
	}

	jeuGenre.Close();

	return true;
}

void CPublicationDoc::rechercheGenre(CListBox & liste, CString genre)
{
	CGenreSet jeuGenre(m_InfoBase.m_pDatabase);
	CString requeteSQL;
	long indexListe = 0;

	requeteSQL.Format("[Nom] Like \"%s\"", genre);

	jeuGenre.m_strFilter = requeteSQL;

	liste.ResetContent();
	liste.EnableWindow(TRUE);

	try
	{
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

		if (!jeuGenre.IsEOF())
		{
			// ajouter les elements trouvés dans la liste
			jeuGenre.MoveFirst();
			while (!jeuGenre.IsEOF())
			{
				// ajouter dans la liste l'auteur courant
				indexListe = liste.AddString(jeuGenre.m_Nom);
				liste.SetItemData(indexListe, (DWORD) jeuGenre.m_IdGenre);
				jeuGenre.MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre demande"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuGenre.Close();
	return;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                          Evenements                                       //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void CPublicationDoc::OnUpdateAuteurAjouter(CCmdUI* pCmdUI) 
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}


void CPublicationDoc::OnUpdateSujetAjouter(CCmdUI* pCmdUI) 
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}


void CPublicationDoc::OnUpdateTypeAjouter(CCmdUI* pCmdUI) 
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}


void CPublicationDoc::OnUpdateMotClefsAjouter(CCmdUI* pCmdUI) 
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}


void CPublicationDoc::OnUpdateGenreAjouter(CCmdUI* pCmdUI) 
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}


void CPublicationDoc::OnAuteurAjouter() 
{
	CAjouterAuteurDialog ajouterAuteur(o_OUVERTURE_NORMAL, -1, this);


	ajouterAuteur.DoModal();
	
}


void CPublicationDoc::OnSujetAjouter() 
{
	CAjouterSujetDialog addSujet(o_OUVERTURE_NORMAL, -1, this);

	addSujet.DoModal();
	
}


void CPublicationDoc::OnTypeAjouter() 
{
	CAjouterTypeDialog ajouterType(o_OUVERTURE_NORMAL, -1, this);

	ajouterType.DoModal();
}


void CPublicationDoc::OnMotClefsAjouter() 
{
	CAjouterMotClefDialog ajouterKey(o_OUVERTURE_NORMAL, -1, this);

	ajouterKey.DoModal();
}


void CPublicationDoc::OnGenreAjouter() 
{
	CAjouterGenreDialog ajouterGenre(o_OUVERTURE_NORMAL, -1, this);

	ajouterGenre.DoModal();
	
}


void CPublicationDoc::OnAuteurRechercher() 
{
	CRechercheAuteur rechercherAuteur(this);

	rechercherAuteur.DoModal();

}


void CPublicationDoc::OnSujetRechercher() 
{
	CRechercheSujet rechercheSujet(this);

	rechercheSujet.DoModal();
}


void CPublicationDoc::OnTypeRechercher() 
{
	CRechercheType rechercheType(this);

	rechercheType.DoModal();
}


void CPublicationDoc::OnMotClefsRechercher() 
{
	CRechercheMotClef rechercheMotClef(this);

	rechercheMotClef.DoModal();
}


void CPublicationDoc::OnGenreRechercher() 
{
	CRechercheGenre rechercheGenre(this);

	rechercheGenre.DoModal();
}



void CPublicationDoc::OnCategorieRechercher() 
{
	CRechercheCategorieDialog aDialog(this);

	aDialog.DoModal();
	
}

void CPublicationDoc::rechercherEtMiseAJourCategorie(CListCtrl & listCategorie, stRechercheCategorie & rechercheCategorie)
{
	// determiner la requete SQL correspondant a la recherche en decodant la structure de recherche
	// lancer la requete sur la bdd
	// pour chaque element trouver,
	//	mettre a jour la liste de controle

	CString requeteSQL;
	unsigned char typeRequete = 0;
	CCategorieSet jeuCategorie(m_InfoBase.m_pDatabase);

	listCategorie.DeleteAllItems();
	listCategorie.EnableWindow(FALSE);

	if (rechercheCategorie.pNomCategorie != NULL)
		typeRequete += 1;

	if (rechercheCategorie.pNomLogin != NULL)
		typeRequete += 2;


	switch(typeRequete)
	{
	case 1: // uniquement le nom de la categorie
		requeteSQL.Format("[Nom] Like \"%s\"", rechercheCategorie.pNomCategorie);
		break;

	case 2: // uniquement le nom du login
		requeteSQL.Format("[Login] Like \"%s\"", rechercheCategorie.pNomLogin);
		break;

	case 3: // categorie et login
		requeteSQL.Format("([Nom] Like \"%s\") AND ([Login] Like \"%s\")", rechercheCategorie.pNomCategorie, rechercheCategorie.pNomLogin);
		break;

	default:
		AfxMessageBox(_T("Type de requete impossible, Erreur interne !"));
		return;
		break;
	}

	jeuCategorie.m_strFilter = requeteSQL;

	try
	{
		jeuCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));
		if (jeuCategorie.IsEOF() != TRUE)
		{
			// ajouter dans la liste control 
			long indiceListCtrl = 0;
			CPubElement* categorieCourante;
			CString date;

			jeuCategorie.MoveFirst();
			while(!jeuCategorie.IsEOF())
			{
				listCategorie.InsertItem(indiceListCtrl, jeuCategorie.m_Nom);
				listCategorie.SetItemData(indiceListCtrl, (DWORD) jeuCategorie.m_IdCategorie);

				if ((jeuCategorie.m_IdCategorieRacine == 0) && (jeuCategorie.m_IdCategorie == 0))
				{
					listCategorie.SetItemText(indiceListCtrl, 1, "[aucune]");
				}
				else
				{
					categorieCourante = rechercherCategorieRacine(jeuCategorie.m_IdCategorieRacine, (CPubElement*) m_elementRoot);
				
					if (categorieCourante != NULL)
						listCategorie.SetItemText(indiceListCtrl, 1, categorieCourante->donnerNom());
					else
					{
						AfxMessageBox("Base corrompu, identificateur racine inconnu");
						jeuCategorie.Close();
						return;
					}
				}

				listCategorie.SetItemText(indiceListCtrl, 2, jeuCategorie.m_Login);

				date = (jeuCategorie.m_DateEntree).Format(/*VAR_DATEVALUEONLY*/);
				listCategorie.SetItemText(indiceListCtrl, 3, date);

				indiceListCtrl++;
				jeuCategorie.MoveNext();
			}

			listCategorie.EnableWindow();
		}		
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre requete"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuCategorie.Close();
}

void CPublicationDoc::afficherCategorieRechercheDansVueCourante(long identificateur)
{
	// rechercher la vue active
	// rechercher l'item tree view correspondant a identificateur
	// selectionner l'element dans le tree view

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*) AfxGetApp()->m_pMainWnd;

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPublicationView *pView = (CPublicationView *) pChild->GetActiveView();


	pView->selectionnerCategorie(identificateur);
}

void CPublicationDoc::mettreAJourListeAuteur(CComboBox & listeAuteur)
{
	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);
	CString formatAuteur;
	int nIndex;

	listeAuteur.ResetContent();

	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.IsEOF() != TRUE)
		{
			jeuAuteur.MoveFirst();
			while (jeuAuteur.IsEOF() != TRUE)
			{
				formatAuteur.Format("%s %s", jeuAuteur.m_Nom, jeuAuteur.m_Prenom);
				nIndex = listeAuteur.AddString(formatAuteur);
				listeAuteur.SetItemData(nIndex, (DWORD) jeuAuteur.m_IdAuteur);
				jeuAuteur.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		listeAuteur.ResetContent();
	}

	jeuAuteur.Close();
}

void CPublicationDoc::mettreAJourListeSujet(CComboBox & listeSujet)
{
	CSujetSet jeuSujet(m_InfoBase.m_pDatabase);
	int nIndex;

	listeSujet.ResetContent();

	try
	{
		jeuSujet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

		if (jeuSujet.IsEOF() != TRUE)
		{
			jeuSujet.MoveFirst();
			while (jeuSujet.IsEOF() != TRUE)
			{
				nIndex = listeSujet.AddString(jeuSujet.m_Nom);
				listeSujet.SetItemData(nIndex, (DWORD) jeuSujet.m_IdSujet);
				jeuSujet.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		listeSujet.ResetContent();
	}

	jeuSujet.Close();
}


void CPublicationDoc::mettreAJourListeGenre(CComboBox & listeGenre)
{
	CGenreSet jeuGenre(m_InfoBase.m_pDatabase);
	int nIndex;

	listeGenre.ResetContent();

	try
	{
		jeuGenre.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

		if (jeuGenre.IsEOF() != TRUE)
		{
			jeuGenre.MoveFirst();
			while (jeuGenre.IsEOF() != TRUE)
			{
				nIndex = listeGenre.AddString(jeuGenre.m_Nom);
				listeGenre.SetItemData(nIndex, (DWORD) jeuGenre.m_IdGenre);
				jeuGenre.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		listeGenre.ResetContent();
	}

	jeuGenre.Close();
}


void CPublicationDoc::mettreAJourListeType(CComboBox & listeType)
{
	CTypeSet jeuType(m_InfoBase.m_pDatabase);
	int nIndex;

	listeType.ResetContent();

	try
	{
		jeuType.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

		if (jeuType.IsEOF() != TRUE)
		{
			jeuType.MoveFirst();
			while (jeuType.IsEOF() != TRUE)
			{
				nIndex = listeType.AddString(jeuType.m_Nom);
				listeType.SetItemData(nIndex, (DWORD) jeuType.m_IdType);
				jeuType.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		listeType.ResetContent();
	}

	jeuType.Close();
}

void CPublicationDoc::mettreAJourMotClef(CListBox & listeMotClef)
{
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	int nIndex;

	listeMotClef.ResetContent();

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (jeuMotClef.IsEOF() != TRUE)
		{
			jeuMotClef.MoveFirst();
			while (jeuMotClef.IsEOF() != TRUE)
			{
				nIndex = listeMotClef.AddString(jeuMotClef.m_Nom);
				listeMotClef.SetItemData(nIndex, (DWORD) jeuMotClef.m_IdMotCles);
				jeuMotClef.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		listeMotClef.ResetContent();
	}

	jeuMotClef.Close();
}


void CPublicationDoc::mettreAJourMotClef(CComboBox & listeMotClef)
{
	CMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);
	int nIndex;

	listeMotClef.ResetContent();

	try
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (jeuMotClef.IsEOF() != TRUE)
		{
			jeuMotClef.MoveFirst();
			while (jeuMotClef.IsEOF() != TRUE)
			{
				nIndex = listeMotClef.AddString(jeuMotClef.m_Nom);
				listeMotClef.SetItemData(nIndex, (DWORD) jeuMotClef.m_IdMotCles);
				jeuMotClef.MoveNext();
			}
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		listeMotClef.ResetContent();
	}

	jeuMotClef.Close();
}


bool CPublicationDoc::ajouterPublication(stAjouterPublication * argPublication)
{
	// si fichier document ok alors le copie a l'emplacement approprié
	// si operation impossible renvoyer KO
	// creer l'id publication
	// mettre a jour les informations sur la publication
	// ouvrir table relation mots clefs
	// pour i de 0 a nombre de mots cles
	// ajouter un element dans la table relation
	// si tout est ok fermer les tables et renvoyer OK
	int indexPoint;
	long idDocument;
	long currentMotClefs;

	CString extension;
	CString nouveauNomFichier;
	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CRelationDocumentMotClefSet jeuMotClef(m_InfoBase.m_pDatabase);

	BOOL resultCopy;
	POSITION aPosition;
	SYSTEMTIME dateActuel;

	// verification -> document existe déjà
	if (publicationExisteDeja(argPublication->nomDocument, argPublication->elementPere) == true)
	{
		AfxMessageBox(_T("Ce document existe déjà, donner un autre nom !"), MB_OK);
		return false;
	}

	if (argPublication->fichierValide == TRUE)
	{
		indexPoint = (argPublication->nomFichier).ReverseFind(_T('.'));
		if (indexPoint == -1)
			extension = _T("");
		else
		{
			extension = (argPublication->nomFichier).Right(((argPublication->nomFichier).GetLength() - 1) - indexPoint);
		}

		nouveauNomFichier.Format("%s.%s", argPublication->nomDocument, extension);

		// recherche du directory, reconstitution du nom complet
		CString nomDocument;
		CString tempString;
		CPubContainer* pContainer = (CPubContainer*) argPublication->elementPere;

		while (pContainer->donnerTypeElement() != ID_RACINE)
		{
			tempString = nouveauNomFichier;
			nomDocument = pContainer->donnerNom();
			nouveauNomFichier.Format(_T("%s\\%s"), nomDocument, tempString);
			pContainer = (CPubContainer*) pContainer->donnerParent();
		}
		/* ici parent = racine */

		tempString = nouveauNomFichier;
		nouveauNomFichier.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);


		resultCopy = CopyFile(argPublication->nomFichier, nouveauNomFichier, TRUE);


		if (resultCopy == FALSE)
		{
			AfxMessageBox(_T("Copie du fichier impossible !"), MB_OK);
			return false;
		}
	}
	

	try 
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (jeuDocument.CanAppend())
		{
			GetLocalTime(&dateActuel);
			idDocument = createPublicationID(jeuDocument);
			jeuDocument.AddNew();
			jeuDocument.m_Titre = argPublication->nomDocument;
			jeuDocument.m_IdCategorieRacine = (argPublication->elementPere)->donnerIdentificateur();
			jeuDocument.m_Resume = argPublication->resume;
			jeuDocument.m_DateEntree = dateActuel;
			jeuDocument.m_Login = m_InfoBase.m_utilisateurActuel;
			jeuDocument.m_IdAuteur = argPublication->idAuteur;
			jeuDocument.m_IdSujet = argPublication->idSujet;
			jeuDocument.m_IdGenre = argPublication->idGenre;
			jeuDocument.m_IdType = argPublication->idType;
			jeuDocument.m_FichierExiste = argPublication->fichierValide;
			jeuDocument.m_Extension = extension;
			jeuDocument.m_IdDocument = idDocument;
			jeuDocument.Update();
		}
		else
		{
			AfxMessageBox(_T("Impossible de mettre à jour la base"), MB_OK);
			CFile::Remove(nouveauNomFichier);
			return false;
		}
		jeuDocument.Close();
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		CFile::Remove(nouveauNomFichier);
		return false;
	}

	// ajouter mot cles dans la table mots cles
	try 
	{
		jeuMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [RelationDocMotCles]"));
		if (jeuMotClef.CanAppend())
		{
			aPosition = argPublication->listMotClefs.GetHeadPosition();
			while (aPosition)
			{
				currentMotClefs = argPublication->listMotClefs.GetNext(aPosition);
				jeuMotClef.AddNew();
				jeuMotClef.m_IdDoc = idDocument;
				jeuMotClef.m_IdMotCles = currentMotClefs;
				jeuMotClef.Update();
			}
		}
		else
		{
			AfxMessageBox("Le document est entre mais pas les mots-cles !");
		}
		jeuMotClef.Close();
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	CPubDocument* pNewDocument = new CPubDocument(argPublication->nomDocument, idDocument, argPublication->fichierValide, extension);
	CPubContainer* pContainer = (CPubContainer*) argPublication->elementPere;
	pContainer->ajouterElement(pNewDocument);

	UpdateAllViews(0, 0, (CObject*) pNewDocument);

	return true;
}

long CPublicationDoc::createPublicationID(CDocumentSet & publicationSet)
{
	long newID = 0;

	if (!(publicationSet.IsBOF() && publicationSet.IsEOF()))
	{
		publicationSet.MoveFirst();
		while(!publicationSet.IsEOF())
		{
			if (newID < publicationSet.m_IdDocument)
				newID = publicationSet.m_IdDocument;
			publicationSet.MoveNext();
		}
	}

	return ++newID;
}


bool CPublicationDoc::publicationExisteDeja(CString & nomDoc, CPubElement * elementPere)
{
	CPubContainer* pContainer = (CPubContainer*) elementPere;
	CPubElement* pElement;
	POSITION aPos = pContainer->donnerPositionTete();

	while (aPos)
	{
		pElement = pContainer->donnerProchainElement(aPos);
		switch (pElement->donnerTypeElement())
		{
		case ID_DOCUMENT:
			if (pElement->donnerNom() == nomDoc)
				return true;
			break;

		default:
			break;
		}
	}

	return false;
}

bool CPublicationDoc::supprimerDocument(CPubDocument * pDocument)
{
	// ouvrir la base sur le document
	// effacer le document sur le disque
	// effacer les relations avec les mots-cles
	// effacer le document de la base
	
	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CRelationDocumentMotClefSet jeuRelationMotClef(m_InfoBase.m_pDatabase);
	CString requete;
	CString nomCompletFichier;
	CPubContainer* pContainer;
	BOOL bFileExiste = FALSE;

	pContainer = (CPubContainer*) pDocument->donnerParent();

	requete.Format("[IdDocument] = %i", pDocument->donnerIdentificateur());

	jeuDocument.m_strFilter = requete;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if ( (jeuDocument.CanUpdate() == FALSE) || (jeuDocument.IsEOF() == TRUE))
		{
			AfxMessageBox("Ce document n'est pas répertorié dans la base !");
			jeuDocument.Close();
			return false;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}


	if (jeuDocument.m_FichierExiste == TRUE)
	{
		// recherche du directory, reconstitution du nom complet
		CString nomDocument;
		CString tempString;

		bFileExiste = TRUE;

		nomCompletFichier.Format("%s.%s", jeuDocument.m_Titre, jeuDocument.m_Extension);

		while (pContainer->donnerTypeElement() != ID_RACINE)
		{
			tempString = nomCompletFichier;
			nomDocument = pContainer->donnerNom();
			nomCompletFichier.Format(_T("%s\\%s"), nomDocument, tempString);
			pContainer = (CPubContainer*) pContainer->donnerParent();
		}
		/* ici parent = racine */
		tempString = nomCompletFichier;
		nomCompletFichier.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);
	}


	requete.Format("[IdDoc] = %i", jeuDocument.m_IdDocument);

	jeuRelationMotClef.m_strFilter = requete; 
	try
	{
		jeuRelationMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [RelationDocMotCles]"));
    if (jeuRelationMotClef.IsEOF() == FALSE)
    {
		  if (jeuRelationMotClef.CanUpdate() == TRUE)
		  {
		  	jeuRelationMotClef.MoveFirst();
		  	while (jeuRelationMotClef.IsEOF() == FALSE)
		  	{
		  		jeuRelationMotClef.Delete();
		  		jeuRelationMotClef.MoveNext();
		  	}
		  }
		  else
		  {
		  	AfxMessageBox("Impossible de mettre à jour la base ! ");
		  	jeuRelationMotClef.Close();
		  	return false;
		  }
    }
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuRelationMotClef.Close();
		return false;
	}

	try
	{
		jeuDocument.Delete();
		jeuDocument.MoveNext();
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}


	if (bFileExiste == TRUE)
		CFile::Remove(nomCompletFichier);


	pContainer = (CPubContainer*) pDocument->donnerParent();
	if (pContainer->retirerElement(pDocument) == false)
	{
		AfxMessageBox("Erreur interne, consulter l'auteur !");
	}


	delete pDocument;

	return true;
}

bool CPublicationDoc::donnerInfoPublication(stAjouterPublication * pDonneePub, CPubDocument* pElement)
{
	// lire info pub
	// et mettre a jour la structure
	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CRelationDocumentMotClefSet jeuRelationMotClef(m_InfoBase.m_pDatabase);
	CString requete;
	CString nomFichier;
	CPubContainer* pContainer;

	requete.Format("[IdDocument] = %i", pElement->donnerIdentificateur());

	jeuDocument.m_strFilter = requete;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (jeuDocument.IsEOF())
		{
			AfxMessageBox("Document inconnue !!");
			jeuDocument.Close();
			return false;
		}
		else
		{
			pDonneePub->idAuteur = jeuDocument.m_IdAuteur;
			pDonneePub->idSujet = jeuDocument.m_IdSujet;
			pDonneePub->idGenre = jeuDocument.m_IdGenre;
			pDonneePub->idType = jeuDocument.m_IdType;
			pDonneePub->fichierValide = jeuDocument.m_FichierExiste;
			//pDonneePub->nomFichier = ;
			pDonneePub->resume = jeuDocument.m_Resume;
			pDonneePub->nomDocument = jeuDocument.m_Titre;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}

	(pDonneePub->listMotClefs).RemoveAll();

	requete.Format("[IdDoc] = %i", jeuDocument.m_IdDocument);

	jeuRelationMotClef.m_strFilter = requete; 
	try
	{
		jeuRelationMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [RelationDocMotCles]"));
    
    if (jeuRelationMotClef.IsEOF() == FALSE)
    {
		  jeuRelationMotClef.MoveFirst();
		  while (jeuRelationMotClef.IsEOF() == FALSE)
		  {
		  	(pDonneePub->listMotClefs).AddHead(jeuRelationMotClef.m_IdMotCles);
		  	jeuRelationMotClef.MoveNext();
		  }
    }
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		jeuRelationMotClef.Close();
		return false;
	}

	//  retrouver le mon du fichier
	CString nomDocument;
	CString tempString;

	nomFichier.Format("%s.%s", jeuDocument.m_Titre, jeuDocument.m_Extension);
	pContainer = (CPubContainer*) pElement->donnerParent();

	while (pContainer->donnerTypeElement() != ID_RACINE)
	{
		tempString = nomFichier;
		nomDocument = pContainer->donnerNom();
		nomFichier.Format(_T("%s\\%s"), nomDocument, tempString);
		pContainer = (CPubContainer*) pContainer->donnerParent();
	}
	/* ici parent = racine */
	tempString = nomFichier;
	nomFichier.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);


	pDonneePub->nomFichier = nomFichier;
	
	return true;
}

bool CPublicationDoc::modifierPublication(stAjouterPublication * pDonneesPub, CPubDocument * pElement)
{
  // Modifier titre et autre renseignement 
	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
	CRelationDocumentMotClefSet jeuRelationMotClef(m_InfoBase.m_pDatabase);
  CString requete;
  CString extension;
  POSITION aPosition;
  long currentMotClefs;
  stAjouterPublication DonneesAnciennePub;
 	SYSTEMTIME dateActuel;

  extension = _T(" ");

  // s'occuper du fichier
  donnerInfoPublication(&DonneesAnciennePub, pElement);

  unsigned char byModificationFichier = PAS_MODIFICATION;

  if (pDonneesPub->fichierValide == TRUE)
  {
    // une modification concerne le fichier
    if (DonneesAnciennePub.fichierValide == FALSE)
    {
      byModificationFichier = MODIFICATION_TYPE_1;
    }
    else
    {
      if (pDonneesPub->nomFichier == "")
      {
        byModificationFichier = MODIFICATION_TYPE_4;
      }
      else
      {
        byModificationFichier = MODIFICATION_TYPE_2;
      }
    }

    if (DonneesAnciennePub.nomDocument != pDonneesPub->nomDocument)
       byModificationFichier += MODIFICATION_TYPE_3;
  }
  else
  {
    if ((DonneesAnciennePub.nomDocument != pDonneesPub->nomDocument) &&
        (DonneesAnciennePub.fichierValide == TRUE))
    {
      byModificationFichier += MODIFICATION_TYPE_5;
    }
    else
    {
      byModificationFichier = PAS_MODIFICATION;
    }
  }

    if (DonneesAnciennePub.nomDocument != pDonneesPub->nomDocument)
    {
      if (publicationExisteDeja(pDonneesPub->nomDocument, pDonneesPub->elementPere) == true)
      {
        AfxMessageBox("Ce document existe déjà ! Donner un autre nom.", MB_OK);
        return false;
      }
    }


  CString nouveauNomFichier;
  BOOL resultCopy;
  BOOL bPrendreAncienExtension = FALSE;


  switch(byModificationFichier)
  {
  // transition pas de fichier -> un fichier
  case MODIFICATION_TYPE_1: 
  case (MODIFICATION_TYPE_1|MODIFICATION_TYPE_3):
    // recherche du directory, reconstitution du nom complet
    nouveauNomFichier = rechercheNomDocument(pDonneesPub->nomFichier, pDonneesPub->nomDocument, (CPubContainer*) pDonneesPub->elementPere, extension);
		resultCopy = CopyFile(pDonneesPub->nomFichier, nouveauNomFichier, TRUE);
    if (resultCopy == FALSE)
  	{
  		AfxMessageBox(_T("Copie du fichier impossible !"), MB_OK);
  		return false;
  	}
    break;

  // transition un fichier un autre fichier sans modification de nom
  case MODIFICATION_TYPE_2:
    nouveauNomFichier = rechercheNomDocument(pDonneesPub->nomFichier, pDonneesPub->nomDocument, (CPubContainer*) pDonneesPub->elementPere, extension);
		resultCopy = CopyFile(pDonneesPub->nomFichier, nouveauNomFichier, FALSE);
    if (resultCopy == FALSE)
  	{
  		AfxMessageBox(_T("Copie du fichier impossible !"), MB_OK);
  		return false;
  	}

    // si l'extension est differente alors effacer l'ancien fichier
    if (nouveauNomFichier != DonneesAnciennePub.nomFichier)
      DeleteFile(DonneesAnciennePub.nomFichier);

    break;

  // transition un fichier un autre fichier avec modification de nom
  case (MODIFICATION_TYPE_2|MODIFICATION_TYPE_3):
  	if (publicationExisteDeja(pDonneesPub->nomDocument, pDonneesPub->elementPere) == true)
    {
      AfxMessageBox("Ce document existe déjà !");
      return false;
    }
    else
    {
      nouveauNomFichier = rechercheNomDocument(pDonneesPub->nomFichier, pDonneesPub->nomDocument, (CPubContainer*) pDonneesPub->elementPere, extension);
      if (rename(DonneesAnciennePub.nomFichier,nouveauNomFichier) != 0)
      {
        AfxMessageBox("Renommage du fichier impossible !", MB_OK);
        return false;
      }
    }

    if (DeleteFile(DonneesAnciennePub.nomFichier) == FALSE)
    {
        AfxMessageBox("Impossible d'effacer l'ancien fichier !", MB_OK);
    }
    break;

  // transition un fichier pas de fichier
  case MODIFICATION_TYPE_4:
  case (MODIFICATION_TYPE_4|MODIFICATION_TYPE_3):
      nouveauNomFichier = rechercheNomDocument(DonneesAnciennePub.nomFichier, DonneesAnciennePub.nomDocument, (CPubContainer*) pDonneesPub->elementPere, extension);

      if (DeleteFile(nouveauNomFichier) == FALSE)
      {
        AfxMessageBox("Impossible d'effacer le fichier !", MB_OK);
      }
      pDonneesPub->fichierValide = FALSE;
      break;

  // modification uniquement du nom actuel du fichier
  case MODIFICATION_TYPE_5:
  	if (publicationExisteDeja(pDonneesPub->nomDocument, pDonneesPub->elementPere) == true)
    {
      AfxMessageBox("Ce document existe déjà !");
      return false;
    }
    else
    {
      nouveauNomFichier = rechercheNomDocument(DonneesAnciennePub.nomFichier, pDonneesPub->nomDocument, (CPubContainer*) pDonneesPub->elementPere, extension);
      if (rename(DonneesAnciennePub.nomFichier,nouveauNomFichier) != 0)
      {
        AfxMessageBox("Renommage du fichier impossible !", MB_OK);
        return false;
      }
      else
      {
        pDonneesPub->fichierValide = TRUE;
      }
    }
    break;

  // pas de modification sur le fichier
  default:
    pDonneesPub->fichierValide = DonneesAnciennePub.fichierValide;
    bPrendreAncienExtension = TRUE;
    break;
  }

 	requete.Format("[IdDocument] = %i", pElement->donnerIdentificateur());

  jeuDocument.m_strFilter = requete;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (jeuDocument.IsEOF())
		{
			AfxMessageBox("Document inconnue !!");
			jeuDocument.Close();
			return false;
		}
		else
		{
      GetLocalTime(&dateActuel);
      jeuDocument.MoveFirst();
      jeuDocument.Edit();
			jeuDocument.m_IdAuteur = pDonneesPub->idAuteur;
			jeuDocument.m_IdSujet  = pDonneesPub->idSujet;
			jeuDocument.m_IdGenre  = pDonneesPub->idGenre;
			jeuDocument.m_IdType   = pDonneesPub->idType;
			jeuDocument.m_FichierExiste = pDonneesPub->fichierValide;
			jeuDocument.m_Resume = pDonneesPub->resume;
			jeuDocument.m_Titre  = pDonneesPub->nomDocument;

      if (bPrendreAncienExtension == FALSE)
 	  		jeuDocument.m_Extension = extension;

   		jeuDocument.m_DateEntree = dateActuel;
			jeuDocument.m_Login = m_InfoBase.m_utilisateurActuel;


      jeuDocument.Update();
      jeuDocument.Close();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		return false;
	}

  // effacer les anciennes relations et ajouter les nouvelless

	requete.Format("[IdDoc] = %i", jeuDocument.m_IdDocument);

	jeuRelationMotClef.m_strFilter = requete; 
	try
	{
		jeuRelationMotClef.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [RelationDocMotCles]"));

    if (jeuRelationMotClef.IsEOF() == FALSE)
    {
		  jeuRelationMotClef.MoveFirst();
		  while (jeuRelationMotClef.IsEOF() == FALSE)
		  {
  	  	jeuRelationMotClef.Delete();
  	  	jeuRelationMotClef.MoveNext();
		  }
    }

		aPosition = pDonneesPub->listMotClefs.GetHeadPosition();
		while (aPosition)
		{
			currentMotClefs = pDonneesPub->listMotClefs.GetNext(aPosition);
			jeuRelationMotClef.AddNew();
			jeuRelationMotClef.m_IdDoc = jeuDocument.m_IdDocument;
			jeuRelationMotClef.m_IdMotCles = currentMotClefs;
			jeuRelationMotClef.Update();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
		jeuRelationMotClef.Close();
		return false;
	}

  if (pDonneesPub->fichierValide == TRUE)
    pDonneesPub->nomFichier = nouveauNomFichier;

  //modifier la valeur en mémoire

  pElement->modifierNomElement(jeuDocument.m_Titre);

  UpdateAllViews(0, 1, (CObject*) pElement);

  return true;
}

CString CPublicationDoc::rechercheNomDocument(CString nomComplet, CString nomDocument, CPubContainer * pPere, CString & extension)
{
  int indexPoint;
  CString nouveauNomFichier;
	CString nomDocument1;
  CString tempString;

  // recherche du directory, reconstitution du nom complet
  indexPoint = nomComplet.ReverseFind(_T('.'));
  if (indexPoint == -1)
	  extension = _T("");
  else
	{
	 	extension = nomComplet.Right((nomComplet.GetLength() - 1) - indexPoint);
  }

  
  nouveauNomFichier.Format("%s.%s", nomDocument, extension);

  while (pPere->donnerTypeElement() != ID_RACINE)
  {
	  tempString = nouveauNomFichier;
	  nomDocument1 = pPere->donnerNom();
	  nouveauNomFichier.Format(_T("%s\\%s"), nomDocument1, tempString);
	  pPere = (CPubContainer*) pPere->donnerParent();
	}
	
  /* ici parent = racine */

	tempString = nouveauNomFichier;
	nouveauNomFichier.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);

  return nouveauNomFichier;
}

CString CPublicationDoc::donnerNomFichierDocument(CPubDocument* pDocument)
{
  CString nomDocument;
  CString nomDocument1;
  CString tempString;

  nomDocument.Format("%s.%s", pDocument->donnerNom(), pDocument->donnerExtensionFichier());

  CPubContainer* pPere = (CPubContainer*) pDocument->donnerParent();

  while (pPere->donnerTypeElement() != ID_RACINE)
  {
	  tempString = nomDocument;
	  nomDocument1 = pPere->donnerNom();
	  nomDocument.Format(_T("%s\\%s"), nomDocument1, tempString);
	  pPere = (CPubContainer*) pPere->donnerParent();
	}
	
  /* ici parent = racine */

	tempString = nomDocument;
	nomDocument.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);



  return nomDocument;
}

void CPublicationDoc::OnPublicationRechercher() 
{
	CRechercheDocument aDialog(this);

  aDialog.DoModal();
	
}

void CPublicationDoc::rechercheDocument(CListCtrl & listCtrl, CString & sRequete)
{
	CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
  int resultItem;
  int indiceListCtrl = 0;
  BOOL resultBool;
  CString tempString;
  CString temp;
  COleDateTime temp2;

	jeuDocument.m_strFilter = sRequete;

  listCtrl.DeleteAllItems();
  listCtrl.EnableWindow(FALSE);

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));

    if (jeuDocument.IsEOF() == TRUE)
      AfxMessageBox("Il n'y a pas de reponse à votre requete ");
    else
    {
      listCtrl.EnableWindow(TRUE);
      jeuDocument.MoveFirst();
      while(!jeuDocument.IsEOF())
      {
        // Remplir liste Ctrl
		    resultItem = listCtrl.InsertItem(indiceListCtrl, jeuDocument.m_Titre);
		    resultBool = listCtrl.SetItemData(indiceListCtrl, (DWORD) jeuDocument.m_IdDocument);
  
        if (rechercheSujet(tempString, jeuDocument.m_IdSujet) == true)
		      resultBool = listCtrl.SetItemText(indiceListCtrl, 1, tempString);
        else
		      resultBool = listCtrl.SetItemText(indiceListCtrl, 1, "[aucun sujet]");

        if (rechercherAuteur(tempString, jeuDocument.m_IdAuteur) == true)
		      resultBool = listCtrl.SetItemText(indiceListCtrl, 2, tempString);
        else
		      resultBool = listCtrl.SetItemText(indiceListCtrl, 2, "[aucun auteur]");
        
        if (donnerInfoCategorie(jeuDocument.m_IdCategorieRacine, tempString, temp, temp2) == true)
		      resultBool = listCtrl.SetItemText(indiceListCtrl, 3, tempString);
        else
		      resultBool = listCtrl.SetItemText(indiceListCtrl, 3, "[aucune categorie]");

		    indiceListCtrl++;
		    jeuDocument.MoveNext();
      }
    }
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuDocument.Close();
	}
}

bool CPublicationDoc::rechercherAuteur(CString& nomComplet, long IdAuteur)
{
	// rechercher a partir de l'indentificateur de l'auteur et mettre a jour les champs
	CAuteurSet jeuAuteur(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[IdAuteur] = %i", IdAuteur);

	jeuAuteur.m_strFilter = requeteSQL;

	try
	{
		jeuAuteur.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Auteur]"));

		if (jeuAuteur.IsEOF() != TRUE)
		{
			nomComplet.Format("%s %s", jeuAuteur.m_Nom, jeuAuteur.m_Prenom);
		}		
		else
		{
			jeuAuteur.Close();
			return false;	
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		jeuAuteur.Close();
		return false;
	}

	jeuAuteur.Close();
	return true;

}

CPubDocument* CPublicationDoc::recherchePtrDocument(long identificateur, CPubContainer * pContainer)
{
	POSITION aPos;
  CPubElement* pElement;

	aPos = pContainer->donnerPositionTete();

	while(aPos)
	{
    pElement = pContainer->donnerProchainElement(aPos);

    switch(pElement->donnerTypeElement())
    {
    case ID_DOCUMENT:
      if (identificateur == pElement->donnerIdentificateur())
        return (CPubDocument*) pElement;
      break;


    case ID_CATEGORIE:
    case ID_RACINE:
      pElement = recherchePtrDocument(identificateur, (CPubContainer*) pElement);
      if (pElement != NULL)
        return (CPubDocument*) pElement;
      break;

    default:
      AfxMessageBox("Interne Error type element inconnue !!)");
      AfxAbort();
      break;
    }
	}
  return NULL;
}

void CPublicationDoc::afficherDocumentDansVueCourante(long identificateur)
{
	// rechercher la vue active
	// rechercher l'item tree view correspondant a identificateur
	// selectionner l'element dans le tree view

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*) AfxGetApp()->m_pMainWnd;

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child window.
	CPublicationView *pView = (CPublicationView *) pChild->GetActiveView();


	pView->selectionnerDocument(identificateur);
}

void CPublicationDoc::OnPublicationRechercheavd() 
{
	CRechercheAvdDocument aDialog(this);

  aDialog.DoModal();

}

void CPublicationDoc::OnUpdateUtilisateurAjouter(CCmdUI* pCmdUI) 
{
	if ((m_InfoBase.m_droitUtilisateur & DROIT_AJOUTER_UTILISATEUR) == DROIT_AJOUTER_UTILISATEUR)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

void CPublicationDoc::OnUtilisateurAjouter() 
{
  CDialogNouvelUtilisateur aDialog(this);

  if (aDialog.DoModal() == IDOK)
  {

  }
}

BOOL CPublicationDoc::ajouterUtilisateur(CString nom, CString password, unsigned long dwDroit)
{
  BOOL bValeurRetour = FALSE;
	CLoginSet loginSet(m_InfoBase.m_pDatabase);
  CString requeteSQL;
  // Verifier si login deja mis
  // coder password et droit 
  // ajouter dans base

  requeteSQL.Format(_T("[Nom] = '%s\'"), nom);
  loginSet.m_strFilter = requeteSQL;
  

  try
	{
		loginSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));

    if (loginSet.IsEOF() == TRUE)
    {
      if (loginSet.CanAppend() == TRUE)
      {
        int i;
        unsigned char pPasswordCrypter[9] = {0};
        unsigned char pACrypter[9] = {0};
        long IdUtilisateur;
		    unionLongChar uAutorisation;

        loginSet.Close();
        loginSet.m_strFilter = (char*) NULL;
		    loginSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));

        IdUtilisateur = createUtilisateurID(loginSet);

          // Ajouter le nouveau 
			  loginSet.AddNew();
			  loginSet.m_Nom = nom;
        
        for(i = 0;i<password.GetLength();i++)
          pACrypter[i] = password[i];


			  cryptageTripleDES(pACrypter, pPasswordCrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_CRYPTAGE);
			  loginSet.m_MotDePasse_0 = pPasswordCrypter[0];
			  loginSet.m_MotDePasse_1 = pPasswordCrypter[1];
			  loginSet.m_MotDePasse_2 = pPasswordCrypter[2];
			  loginSet.m_MotDePasse_3 = pPasswordCrypter[3];
			  loginSet.m_MotDePasse_4 = pPasswordCrypter[4];
			  loginSet.m_MotDePasse_5 = pPasswordCrypter[5];
			  loginSet.m_MotDePasse_6 = pPasswordCrypter[6];
			  loginSet.m_MotDePasse_7 = pPasswordCrypter[7];

        uAutorisation.ulongValue = dwDroit;

        for(i = 3;i<8;i++)
          pACrypter[i] = 0;

        for(i = 0;i<sizeof(unsigned long);i++)
          pACrypter[i] = uAutorisation.ucharValue[i];


			  cryptageTripleDES(pACrypter, pPasswordCrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_CRYPTAGE);

			  loginSet.m_Autorisation_0 = pPasswordCrypter[0];
			  loginSet.m_Autorisation_1 = pPasswordCrypter[1];
			  loginSet.m_Autorisation_2 = pPasswordCrypter[2];
			  loginSet.m_Autorisation_3 = pPasswordCrypter[3];
			  loginSet.m_Autorisation_4 = pPasswordCrypter[4];
			  loginSet.m_Autorisation_5 = pPasswordCrypter[5];
			  loginSet.m_Autorisation_6 = pPasswordCrypter[6];
			  loginSet.m_Autorisation_7 = pPasswordCrypter[7];
			  loginSet.m_IdLogin = IdUtilisateur;
			  loginSet.Update();

        bValeurRetour = TRUE;
        AfxMessageBox("Ce nouvel utilisateur a été entré avec succes !");
      }
      else
      {
        AfxMessageBox("Impossible de mettre a jour la base !");
        bValeurRetour = FALSE;
      }
    }
    else
    {
      AfxMessageBox("Il existe déjà un utilisateur à ce nom !");
      bValeurRetour = FALSE;
    }
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
    bValeurRetour = FALSE;
		return FALSE;
	}


	loginSet.Close();
  return bValeurRetour;
}


long CPublicationDoc::createUtilisateurID(CLoginSet & loginSet)
{
	long newID = 0;

	if (!(loginSet.IsBOF() && loginSet.IsEOF()))
	{
		loginSet.MoveFirst();
		while(!loginSet.IsEOF())
		{
			if (newID < loginSet.m_IdLogin)
				newID = loginSet.m_IdLogin;
			loginSet.MoveNext();
		}
	}

	return ++newID;

}

void CPublicationDoc::OnUtilisateurRechercher() 
{
  CRechercheUtilisateurDialog aDialog(this);

  aDialog.DoModal();
}

void CPublicationDoc::rechercheUtilisateur(CListBox & list, CString login)
{
	CLoginSet jeuLogin(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] Like \"%s\"", login);

	jeuLogin.m_strFilter = requeteSQL;

	list.ResetContent();
	list.EnableWindow(TRUE);

	try
	{
		jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));

		if (!jeuLogin.IsEOF())
		{
			// ajouter les elements trouvés dans la liste
			jeuLogin.MoveFirst();
			while (!jeuLogin.IsEOF())
			{
				// ajouter dans la liste l'auteur courant
				list.AddString(jeuLogin.m_Nom);
				jeuLogin.MoveNext();
			}
		}
		else
		{
			AfxMessageBox(_T("Il n'y a pas de réponse à votre demande"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
	}

	jeuLogin.Close();
	return;

}

bool CPublicationDoc::effacerUtilisateur(CString sNomLogin)
{
	CLoginSet jeuLogin(m_InfoBase.m_pDatabase);
	CString requeteSQL;
  bool retour = false;

	requeteSQL.Format("[Nom] = \"%s\"", sNomLogin);

	jeuLogin.m_strFilter = requeteSQL;


	try
	{
		jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));

		if (!jeuLogin.IsEOF() && (jeuLogin.CanAppend()))
		{
			// supprimer l'element
			jeuLogin.MoveFirst();
      jeuLogin.Delete();
      retour = true;
		}
		else
		{
			AfxMessageBox(_T("Cet utilisateur ne peut être effacer ou n'existe pas !"));
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
    retour = false;
	}

	jeuLogin.Close();
	return retour;
}

unsigned long CPublicationDoc::donnerInfoUtilisateur(CString sNomLogin)
{
  unsigned long dwRetour = 0;
  CLoginSet jeuLogin(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", sNomLogin);

	jeuLogin.m_strFilter = requeteSQL;


	try
	{
		jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));

		if (!jeuLogin.IsEOF())
		{
		  char MotdePasse[9];
		  char MotdePasseDecrypter[9];

		  MotdePasseDecrypter[8] = '\0';
		  MotdePasse[8] = '\0';
		  unionLongChar uAutorisation;
		  int i;

      jeuLogin.MoveFirst();

		  /* Mettre a jour autorisation field */
		  MotdePasse[0] = jeuLogin.m_Autorisation_0;
		  MotdePasse[1] = jeuLogin.m_Autorisation_1;
		  MotdePasse[2] = jeuLogin.m_Autorisation_2;
		  MotdePasse[3] = jeuLogin.m_Autorisation_3;
		  MotdePasse[4] = jeuLogin.m_Autorisation_4;
		  MotdePasse[5] = jeuLogin.m_Autorisation_5;
		  MotdePasse[6] = jeuLogin.m_Autorisation_6;
		  MotdePasse[7] = jeuLogin.m_Autorisation_7;

		  cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseDecrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_DECRYPTAGE);

		  for(i=0; i<sizeof(unsigned long); i++)
			  uAutorisation.ucharValue[i] = (unsigned char) MotdePasseDecrypter[i];
		
	    dwRetour = uAutorisation.ulongValue;
		}
		else
		{
			AfxMessageBox(_T("Cet utilisateur n'existe pas !"));
      dwRetour = 0;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
    dwRetour = 0;
	}

	jeuLogin.Close();
	return dwRetour;
}

bool CPublicationDoc::modifierUtilisateur(CString sNomLogin, CString sProchainNom, unsigned long dwDroits)
{
  CLoginSet jeuLogin(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", sProchainNom);

	jeuLogin.m_strFilter = requeteSQL;


  if (sNomLogin != sProchainNom)
  {
	  try
	  {
		  jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));
      if (!jeuLogin.IsEOF())
      {
        AfxMessageBox("Un utilisateur possede deja ce login !");
        jeuLogin.Close();
        return false;
      }
    }
    catch (CException* pEx)
	  {
		  pEx->ReportError();
      jeuLogin.Close();
      return false;
	  }

    jeuLogin.Close();
  }

  // login est ok modif autorise

	requeteSQL.Format("[Nom] = \"%s\"", sNomLogin);
	jeuLogin.m_strFilter = requeteSQL;

	try
	{
		jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));
    if ((!jeuLogin.IsEOF()) && (jeuLogin.CanUpdate()))
    {
      jeuLogin.Edit();
      jeuLogin.m_Nom = sProchainNom;

      char MotdePasse[9] = {0};
      char MotdePasseCrypter[9] = {0};
		  unionLongChar uAutorisation;
		  int i;

      uAutorisation.ulongValue = dwDroits;

		  for(i=0; i<sizeof(unsigned long); i++)
			  MotdePasse[i] = uAutorisation.ucharValue[i];

		  cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseCrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_CRYPTAGE);
   
      /* Mettre a jour autorisation field */
		  jeuLogin.m_Autorisation_0 = MotdePasseCrypter[0];
		  jeuLogin.m_Autorisation_1 = MotdePasseCrypter[1];
		  jeuLogin.m_Autorisation_2 = MotdePasseCrypter[2];
		  jeuLogin.m_Autorisation_3 = MotdePasseCrypter[3];
		  jeuLogin.m_Autorisation_4 = MotdePasseCrypter[4];
		  jeuLogin.m_Autorisation_5 = MotdePasseCrypter[5];
		  jeuLogin.m_Autorisation_6 = MotdePasseCrypter[6];
		  jeuLogin.m_Autorisation_7 = MotdePasseCrypter[7];

      jeuLogin.Update();
    }
    else
    {
      AfxMessageBox("La base ne peut etre mise à jour où l'utilisateur n'existe pas!");
      jeuLogin.Close();
      return false;
    }
  }
  catch (CException* pEx)
	{
		pEx->ReportError();
    jeuLogin.Close();
    return false;
	}

  AfxMessageBox("La modification a été effectuée avec succes !");
  jeuLogin.Close();
  return true;
}

void CPublicationDoc::OnUtilisateurModifierMotdepasse() 
{
  CmodifierPassWordDialog aDialog(this);

  aDialog.DoModal();

}

// Retour :
// 0 autre erreir
// MODIF_OK tout est ok
// ANCIEN_PASSWORD_KO le pasword donne etait

int CPublicationDoc::ModifierMotDePasse(CString sAncien, CString sNouveau)
{
  CLoginSet jeuLogin(m_InfoBase.m_pDatabase);
	CString requeteSQL;

	requeteSQL.Format("[Nom] = \"%s\"", m_InfoBase.m_utilisateurActuel);

	jeuLogin.m_strFilter = requeteSQL;

	try
	{
		jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));
    if ((!jeuLogin.IsEOF()) && (jeuLogin.CanUpdate()))
    {
      // regarder si current password est ok
	    /* Verification du mot de passe */
      char MotdePasse[9] = {0};
      char MotdePasseDecrypter[9] = {0};
	    int i;

	    MotdePasse[0] = jeuLogin.m_MotDePasse_0;
	    MotdePasse[1] = jeuLogin.m_MotDePasse_1;
	    MotdePasse[2] = jeuLogin.m_MotDePasse_2;
	    MotdePasse[3] = jeuLogin.m_MotDePasse_3;
	    MotdePasse[4] = jeuLogin.m_MotDePasse_4;
	    MotdePasse[5] = jeuLogin.m_MotDePasse_5;
	    MotdePasse[6] = jeuLogin.m_MotDePasse_6;
	    MotdePasse[7] = jeuLogin.m_MotDePasse_7;
	    
	    cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseDecrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_DECRYPTAGE);

	    if (sAncien != MotdePasseDecrypter)
      {
        jeuLogin.Close();
		    return ANCIEN_PASSWORD_KO;
      }
      jeuLogin.Edit();

	    // copie du password pour finir avec des 0 CString
      for(i=0;i<9;i++)
        MotdePasse[i] = 0;

	    for(i=0;i<sNouveau.GetLength();i++)
		    MotdePasse[i] = sNouveau[i];

	    cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseDecrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_CRYPTAGE);

      jeuLogin.m_MotDePasse_0 = MotdePasseDecrypter[0];
	    jeuLogin.m_MotDePasse_1 = MotdePasseDecrypter[1];
	    jeuLogin.m_MotDePasse_2 = MotdePasseDecrypter[2];
	    jeuLogin.m_MotDePasse_3 = MotdePasseDecrypter[3];
	    jeuLogin.m_MotDePasse_4 = MotdePasseDecrypter[4];
	    jeuLogin.m_MotDePasse_5 = MotdePasseDecrypter[5];
	    jeuLogin.m_MotDePasse_6 = MotdePasseDecrypter[6];
	    jeuLogin.m_MotDePasse_7 = MotdePasseDecrypter[7];

      jeuLogin.Update();
    }
    else
    {
      AfxMessageBox("La base ne peut etre mise à jour où l'utilisateur n'existe pas!");
      jeuLogin.Close();
      return 0;
    }
  }
  catch (CException* pEx)
	{
		pEx->ReportError();
    jeuLogin.Close();
    return 0;
	}

  jeuLogin.Close();
  return MODIF_OK;
}

void CPublicationDoc::OnUtilisateurListedesutilisateurs() 
{
  CListUtilisateurDialog aDialog(this);

  aDialog.DoModal();
	
}

void CPublicationDoc::mettreAJourListeUtilisateur(CListCtrl & listCtrl)
{
  CLoginSet jeuLogin(m_InfoBase.m_pDatabase);
  int nItem = 0;
  int i = 0;
  char szDroitUtilisateur[8] = {0};
  char MotdePasse[9] = {0};
	char MotdePasseDecrypter[9] = {0};
	unionLongChar uAutorisation;

  listCtrl.DeleteAllItems();

  try
  {
		jeuLogin.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Login]"));

    jeuLogin.MoveFirst();
    while (!jeuLogin.IsEOF())
    {
      //lire droit, mettre a jour listctrl
			// ajouter l'auteur courant bug pe remplacer resultItem par indiceListCtrl
			/*resultItem = */listCtrl.InsertItem(nItem, jeuLogin.m_Nom);
//			resultBool = listAuteur.SetItemData(indiceListCtrl, (DWORD) jeuAuteur.m_IdAuteur);

      // Creation des droits
      MotdePasse[0] = jeuLogin.m_Autorisation_0;
		  MotdePasse[1] = jeuLogin.m_Autorisation_1;
		  MotdePasse[2] = jeuLogin.m_Autorisation_2;
		  MotdePasse[3] = jeuLogin.m_Autorisation_3;
		  MotdePasse[4] = jeuLogin.m_Autorisation_4;
		  MotdePasse[5] = jeuLogin.m_Autorisation_5;
		  MotdePasse[6] = jeuLogin.m_Autorisation_6;
		  MotdePasse[7] = jeuLogin.m_Autorisation_7;
      cryptageTripleDES((unsigned char*) MotdePasse, (unsigned char*) MotdePasseDecrypter, (unsigned char*)CRYPT_PASSWORD, o_DES_DECRYPTAGE);

		  for(i=0; i<sizeof(unsigned long); i++)
			  uAutorisation.ucharValue[i] = (unsigned char) MotdePasseDecrypter[i];

      if ((uAutorisation.ulongValue & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
        szDroitUtilisateur[0] = 'X';
      else
        szDroitUtilisateur[0] = '_';

      if ((uAutorisation.ulongValue & DROIT_MODIFIER_ELEMENT) == DROIT_MODIFIER_ELEMENT)
        szDroitUtilisateur[1] = 'X';
      else
        szDroitUtilisateur[1] = '_';

      if ((uAutorisation.ulongValue & DROIT_SUPPRIMER_ELEMENT) == DROIT_SUPPRIMER_ELEMENT)
        szDroitUtilisateur[2] = 'X';
      else
        szDroitUtilisateur[2] = '_';

      if ((uAutorisation.ulongValue & DROIT_AJOUTER_UTILISATEUR) == DROIT_AJOUTER_UTILISATEUR)
        szDroitUtilisateur[3] = 'X';
      else
        szDroitUtilisateur[3] = '_';

      if ((uAutorisation.ulongValue & DROIT_MODIFIER_DROIT_UTILISATEUR) == DROIT_MODIFIER_DROIT_UTILISATEUR)
        szDroitUtilisateur[4] = 'X';
      else
        szDroitUtilisateur[4] = '_';

      if ((uAutorisation.ulongValue & DROIT_SUPPRIMER_UTILISATEUR) == DROIT_SUPPRIMER_UTILISATEUR)
        szDroitUtilisateur[5] = 'X';
      else
        szDroitUtilisateur[5] = '_';

      if ((uAutorisation.ulongValue & DROIT_MODIFIER_PROPRIETE_BASE) == DROIT_MODIFIER_PROPRIETE_BASE)
        szDroitUtilisateur[6] = 'X';
      else
        szDroitUtilisateur[6] = '_';

			/*resultBool = */listCtrl.SetItemText(nItem, 1, szDroitUtilisateur);
			nItem++;
			jeuLogin.MoveNext();
    }
  }
  catch (CException* pEx)
	{
		pEx->ReportError();
	}
}

void CPublicationDoc::OnOptionsBase() 
{
	COptionBaseDialog aDialog(this);

  aDialog.DoModal();


	
}

bool CPublicationDoc::donnerOptionBase(CString& sVersion, CString& sRepertoire)
{
  CInfoGalSet jeuOption(m_InfoBase.m_pDatabase);
  bool retour = true;

  try
  {
		jeuOption.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [InfoGal]"));

    if (jeuOption.IsEOF())
    {
      AfxMessageBox("Base invalide !");
      retour = false;
    }
    else
    {
      jeuOption.MoveFirst();
      sVersion.Format("%.2f", (float)((jeuOption.m_VersionLogiciel)/10));
      sRepertoire = jeuOption.m_RepertoireRacine;
    }
  }
  catch (CException* pEx)
	{
		pEx->ReportError();
    retour = false;
	}


  jeuOption.Close();

  return retour;
}

bool CPublicationDoc::modifierOptionBase(CString sNouveauRepertoire, BOOL bCopyDirectory, BOOL bEraseOldDir)
{
  if (m_InfoBase.m_repertoireRacine == sNouveauRepertoire)
    return true;
  else
  {
    CString sMessage;

    sMessage.Format("Attention ! Cette opération va déplacer toutes les éléments du répertoire %s vers le répertoire %s, Voulez-vous continuer ?", m_InfoBase.m_repertoireRacine, sNouveauRepertoire);

    if (AfxMessageBox(sMessage, (MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)) == IDNO)
      return false;
    else
    {
      if ((bCopyDirectory == TRUE) &&
          (CopyDirectory(m_InfoBase.m_repertoireRacine, sNouveauRepertoire) == FALSE))
      {
          AfxMessageBox("Le déplacement des objets a échoué !");
          return false;
      }
      else
      {
        CInfoGalSet jeuOption(m_InfoBase.m_pDatabase);
        try
        {
		      jeuOption.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [InfoGal]"));

          if (jeuOption.IsEOF() || !jeuOption.CanUpdate())
          {
            AfxMessageBox("Base invalide ou impossible à mettre à jour !");
            jeuOption.Close();
            return false;
          }
          else
          {
            jeuOption.MoveFirst();
            jeuOption.Edit();
            jeuOption.m_RepertoireRacine = sNouveauRepertoire;
            jeuOption.Update();

            if (bEraseOldDir == TRUE)
            {
              RmDirectory(m_InfoBase.m_repertoireRacine);
            }

            m_InfoBase.m_repertoireRacine = sNouveauRepertoire;
          }
        }
        catch (CException* pEx)
	      {
		      pEx->ReportError();
          jeuOption.Close();
          return false;
	      }
      }
    }
  }

  AfxMessageBox("Mouvement réussi !");

  return true;
}

BOOL CPublicationDoc::CopyDirectory(CString sAncienRepertoire, CString sNouveauRepertoire)
{
  // Rechercher Fichier et Repertoire de l'ancien 
  // Creer Les nouveaux Repertoires et mover les fichiers
  // et le faire pour chaque repertoire
  CFileFind  fileFind;
  BOOL bContinue;

  sAncienRepertoire += "\\*";
  sNouveauRepertoire += '\\';

  bContinue = fileFind.FindFile(sAncienRepertoire);
  if (bContinue == FALSE)
  {
    // repertoire vide, fini
    return TRUE;
  }
  else
  {
    CString strFileName;

    while (bContinue)
    {
      bContinue = fileFind.FindNextFile();
      strFileName = fileFind.GetFileName();
		  if ((strFileName == _T("..")) || (strFileName == _T(".")))
			  continue;

      if (fileFind.IsDirectory())
      {
        CString sNRepertoire = sNouveauRepertoire;
        CFileFind fileRepertoire;
        BOOL bResult;

        sNRepertoire = sNRepertoire + strFileName;
        bResult = fileRepertoire.FindFile(sNRepertoire);

        if (bResult == FALSE)
        {
          if (_mkdir(sNRepertoire) == -1)
          {
            AfxMessageBox("Erreur lors de la creation d'un répertoire");
            return FALSE;
          }
        }

        if (CopyDirectory(fileFind.GetFilePath(), sNRepertoire) == FALSE)
        {
          AfxMessageBox("Erreur de copie dans de fichier dans un répertoire");
          return FALSE;
        }
          
      }
      else
      {
        CString sNouvNom;

        sNouvNom = strFileName;
        sNouvNom = sNouveauRepertoire + sNouvNom;

        if (MoveFile(fileFind.GetFilePath(), sNouvNom) == FALSE)
          return FALSE;
      }
    }
  }
  return TRUE;
}

BOOL CPublicationDoc::RmDirectory(CString sDir)
{
  CFileFind fileFind;
  CString sSearchDir;

  sSearchDir = sDir + "\\*.*";


  if (fileFind.FindFile(sSearchDir) == FALSE)
  {
    // le repertoire est vide
    _rmdir(sDir);
  }
  else
  {
    BOOL bContinue = TRUE;
    CString strFileName;

    while (bContinue)
    {
      bContinue = fileFind.FindNextFile();
      strFileName = fileFind.GetFileName();
		  if ((strFileName == _T("..")) || (strFileName == _T(".")))
			  continue;

      if (fileFind.IsDirectory())
      {
        if (RmDirectory(fileFind.GetFilePath()) == FALSE)
          return FALSE;
      }
      else
      {
        CFile::Remove(fileFind.GetFilePath()); 
      }
    }

    _rmdir(sDir);
  }

  return TRUE;

}

void CPublicationDoc::OnOptionUpdateBase() 
{
  // Il faut 'vider' le doc actuel ainsi que les vues

	if (m_elementRoot != NULL)
		delete m_elementRoot;

  m_elementRoot = 0;

  CInfoGalSet infoSet(m_InfoBase.m_pDatabase);
	infoSet.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [InfoGal]"));
	infoSet.MoveFirst();

//	m_InfoBase.m_repertoireRacine = infoSet.m_RepertoireRacine;
//	m_elementRoot = new CPubRacine(m_InfoBase.m_nomBase, 0, m_InfoBase.m_repertoireRacine);

  ouvrirBase(FALSE);

  UpdateAllViews(0);

}

bool CPublicationDoc::changerNomPublication(CPubDocument * pDocument, CString nouveauNom)
{
  CString sAncienNom;
  CString sNouveauNom;
  CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
  CString requete;

  if (publicationExisteDeja(nouveauNom, pDocument->donnerParent()) == true)
  {
    AfxMessageBox("Ce document existe déjà ?");
    return false;
  }

  if (pDocument->isFile() == TRUE)
  {
    CString sTemp;
    int nIndex;

    sAncienNom = donnerNomFichierDocument(pDocument);
    nIndex = sAncienNom.ReverseFind('\\');
    if (nIndex == (int) -1)
    {
      AfxMessageBox("Err. Interne");
      return false;
    }

    sNouveauNom.Format("%s%s.%s", sAncienNom.Left(nIndex+1), nouveauNom, pDocument->donnerExtensionFichier());

    if (MoveFile(sAncienNom, sNouveauNom) == FALSE)
    {
      AfxMessageBox("Copie du fichier impossible !");
      return false;
    } 
  }


 	requete.Format("[IdDocument] = %i", pDocument->donnerIdentificateur());

  jeuDocument.m_strFilter = requete;

	try
	{
		jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		if (jeuDocument.IsEOF())
		{
			AfxMessageBox("Document inconnue !!");
			jeuDocument.Close();
			return false;
		}
		else
		{
      jeuDocument.MoveFirst();
      jeuDocument.Edit();
			jeuDocument.m_Titre  = nouveauNom;
      jeuDocument.Update();
      jeuDocument.Close();
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
    if (pDocument->isFile() == TRUE)
      MoveFile(sNouveauNom, sAncienNom);

    jeuDocument.Close();
		return false;
	}

  pDocument->modifierNomElement(jeuDocument.m_Titre);

  jeuDocument.Close();
  return true;
}

BOOL CPublicationDoc::deplacerElement(CPubElement * pElementSource, CPubContainer * pElementDest)
{
  if (pElementSource == (CPubElement*) pElementDest)
    return FALSE;

  CDocumentSet jeuDocument(m_InfoBase.m_pDatabase);
  CCategorieSet jeuCategorie(m_InfoBase.m_pDatabase);
  CString sRequete;
  CPubDocument* pDocument;
  CPubContainer* pParent;
  CString sAncienNom;
  CString sNouveauNom;

  // Deplacer element dans la base en tenant compte element source container ou non
  // Deplacer l'element dans la mémoire

  switch (pElementSource->donnerTypeElement())
  {
  case ID_DOCUMENT:
    pDocument = (CPubDocument*) pElementSource;

    if (pDocument->isFile() == TRUE)
    {
      // Deplacer le fichier vers le nouveau répertoire
      sAncienNom = donnerNomFichierDocument(pDocument);

      pParent = (CPubContainer*) pElementSource->donnerParent();
      pParent->retirerElement(pElementSource);
      pElementDest->ajouterElement(pElementSource);

      sNouveauNom = donnerNomFichierDocument(pDocument);

      if (MoveFile(sAncienNom, sNouveauNom) == FALSE)
        return FALSE;
    }

    sRequete.Format("[IdDocument] = %i", pElementSource->donnerIdentificateur());
    jeuDocument.m_strFilter = sRequete;
    try
    {
		  jeuDocument.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Document]"));
		  if (!jeuDocument.IsEOF() && jeuDocument.CanUpdate())
      {
        jeuDocument.Edit();
        jeuDocument.m_IdCategorieRacine = pElementDest->donnerIdentificateur();
        jeuDocument.Update();
      }
      else
        return FALSE;
    }
	  catch (CException* pEx)
    {
		  pEx->ReportError();
      if (pDocument->isFile() == TRUE)
        MoveFile(sNouveauNom, sAncienNom);

      pElementDest->retirerElement(pElementSource);
      pParent->ajouterElement(pElementSource);
      return FALSE;
    }
    break;


  case ID_CATEGORIE:
  case ID_RACINE:

    // Deplacer ancien repertoire vers le nouveau
    sAncienNom = donnerNomRepertoire((CPubContainer*) pElementSource);

    pParent = (CPubContainer*) pElementSource->donnerParent();
    pParent->retirerElement(pElementSource);
    pElementDest->ajouterElement(pElementSource);

    sNouveauNom = donnerNomRepertoire((CPubContainer*) pElementSource);

    if (_mkdir(sNouveauNom) != 0)
    {
      pElementDest->retirerElement(pElementSource);
      pParent->ajouterElement(pElementSource);
      return FALSE;
    }

    if (CopyDirectory(sAncienNom, sNouveauNom) == FALSE)
      return FALSE;
    else
      RmDirectory(sAncienNom);

    sRequete.Format("[IdCategorie] = %i", pElementSource->donnerIdentificateur());
    jeuCategorie.m_strFilter = sRequete;
    try
    {
		  jeuCategorie.Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Categorie]"));
		  if (!jeuCategorie.IsEOF() && jeuCategorie.CanUpdate())
      {
        jeuCategorie.Edit();
        jeuCategorie.m_IdCategorieRacine = pElementDest->donnerIdentificateur();
        jeuCategorie.Update();
      }
      else
        return FALSE;
    }
	  catch (CException* pEx)
    {
		  pEx->ReportError();
      pElementDest->retirerElement(pElementSource);
      pParent->ajouterElement(pElementSource);

      if (_mkdir(sAncienNom) != 0) 
      {
        if (CopyDirectory(sNouveauNom, sAncienNom) != FALSE)
          RmDirectory(sAncienNom);
      }
      return FALSE;
    }
    break;

  default:
    return FALSE;
    break;
  }

  // Si tout ok renv TRUE sinon FALSE

  return TRUE;
}


CString CPublicationDoc::donnerNomRepertoire(CPubContainer* pContainerSrc)
{
  CString nomCompletCategorie = "";// = pContainerSrc->donnerNom();
  CString nomCategorie = "";
  CString tempString = "";
  CPubContainer* pContainer = (CPubContainer*) pContainerSrc;

	while (pContainer->donnerTypeElement() != ID_RACINE)
	{
	  tempString = nomCompletCategorie;
	  nomCategorie = pContainer->donnerNom();
	  nomCompletCategorie.Format(_T("%s\\%s"), nomCategorie, tempString);
	  pContainer = (CPubContainer*) pContainer->donnerParent();
	}
  /* ici parent = racine */
  tempString = nomCompletCategorie;
  nomCompletCategorie.Format(_T("%s\\%s"), m_InfoBase.m_repertoireRacine, tempString);

  return nomCompletCategorie;
}