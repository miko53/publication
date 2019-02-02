// PublicationDoc.h : interface of the CPublicationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICATIONDOC_H__18AB4730_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_PUBLICATIONDOC_H__18AB4730_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#include "PubRacine.h"
#include "PubDocument.h"
#include "PublicationInfoGal.h"	// Added by ClassView
#include "CategorieSet.h"
#include "AuteurSet.h"
#include "SujetSet.h"
#include "TypeSet.h"
#include "MotClefSet.h"
#include "GenreSet.h"
#include "DocumentSet.h"
#include "LoginSet.h"
#include "RelationDocumentMotClefSet.h"
#include "constElement.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPublicationDoc : public CDocument
{
protected: // create from serialization only
	CPublicationDoc();
	DECLARE_DYNCREATE(CPublicationDoc)

// Attributes
public:
	inline CPubRacine* donnerRacine()
	{
		return m_elementRoot;
	}

  inline CString GetNomUtilisateurCourant()
  {
    return m_InfoBase.m_utilisateurActuel;
  }

  inline unsigned long GetDroitUtilisateurCourant()
  {
    return m_InfoBase.m_droitUtilisateur;
  }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPublicationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
  CString donnerNomRepertoire(CPubContainer* pContainerSrc);
	BOOL deplacerElement(CPubElement* pElementSource, CPubContainer* pElementDest);
	bool changerNomPublication(CPubDocument* pDocument, CString nouveauNom);
	bool modifierOptionBase(CString sNouveauRepertoire, BOOL bCopyDirectory, BOOL bEraseOldDir);
	bool donnerOptionBase(CString& sVersion, CString& sRepertoire);
	void mettreAJourListeUtilisateur(CListCtrl& listCtrl);
	int ModifierMotDePasse(CString sAncien, CString sNouveau);
	bool modifierUtilisateur(CString sNomLogin, CString sProchainNom, unsigned long dwDroits);
	unsigned long donnerInfoUtilisateur(CString sNomLogin);
	bool effacerUtilisateur(CString sNomLogin);
	bool peutSupprimerUtilisateur(void);
	bool peutModifierDroitUtilisateur(void);
	void rechercheUtilisateur(CListBox& list, CString login);
  bool peutAjouterElemBase();
  long createUtilisateurID(CLoginSet & loginSet);
	BOOL ajouterUtilisateur(CString nom, CString password, unsigned long dwDroit);
  void mettreAJourMotClef(CComboBox & listeMotClef);
	void afficherDocumentDansVueCourante(long identificateur);
	CPubDocument* recherchePtrDocument(long identificateur, CPubContainer* pContainer);
	void rechercheDocument(CListCtrl& listCtrl, CString& sRequete);
  CString donnerNomFichierDocument(CPubDocument* pDocument);
	bool modifierPublication(stAjouterPublication* pDonneesPub, CPubDocument* pElement);
	bool donnerInfoPublication(stAjouterPublication* pDonneePub, CPubDocument* pElement);
	bool supprimerDocument(CPubDocument* pDocument);
	bool ajouterPublication(stAjouterPublication* argPublication);
	void mettreAJourMotClef(CListBox &listeMotClef);
	void mettreAJourListeType(CComboBox& listeType);
	void mettreAJourListeGenre(CComboBox& listeGenre);
	void mettreAJourListeSujet (CComboBox & listeSujet);
	void mettreAJourListeAuteur(CComboBox &listeAuteur);
	void afficherCategorieRechercheDansVueCourante ( long identificateur );
	void rechercherEtMiseAJourCategorie (CListCtrl & listCategorie, stRechercheCategorie & rechercheCategorie);
	void rechercheGenre (CListBox &liste, CString genre);
	bool effacerGenre (long IDGenre);
	bool modifierGenre (long idGenre, CString newValue);
	long createGenreID(CGenreSet & jeuGenre);
	long ajouterGenre (bool* resultatFonction, CString genre);
	bool rechercheGenre (CString & valeurGenre, long IDGenre);
	bool effacerMotClef (long IDMotClef);
	void rechercheMotClef(CListBox & liste, CString motClef);
	bool modifierMotClef (long idMotClef, CString newValue);
	long createKeyNameID(CMotClefSet & jeuMotClef);
	long ajouterMotClef(bool* resultatFonction, CString motClef);
	bool rechercheMotClef (CString& valeurMotClef, long IDMotClef);
	bool rechercheType(CString & valeurType, long IDType);
	void rechercheType (CListBox& liste, CString type);
	bool effacerType (long IDType);
	bool modifierType(long idType, CString newValue);
	long ajouterType (bool * resultatFonction, CString type);
	bool rechercheSujet(CString& valeurSujet, long IDSujet);
	bool effacerSujet(long IDSujet);
	void rechercheSujet(CListBox& liste, CString sujet);
	bool modifierSujet(long idSujet, CString newValue);
	long ajouterSujet(bool* resultatFonction, CString sujet);
	bool effacerAuteur(long IdAuteur);
	bool rechercherAuteur(CString & nomAuteur, CString & prenomAuteur, COleDateTime & dateNaissance, COleDateTime & dateMort, CString& nationalite, CString & renseignement, long IDAuteur);
	void rechercherAuteur(CListCtrl& listAuteur, stRechercheAuteur& stRechercheAuteur);
	bool modifierAuteur(CString& nomAuteur, CString& prenomAuteur, COleDateTime& dateNaissance, COleDateTime& dateMort, CString& nationalite, CString& renseignement, CComboBox& ctrlNationality, long IDAuteur);	
	bool ajouterAuteur(CString& nomAuteur, CString& prenomAuteur, COleDateTime& dateNaissance, COleDateTime& dateMort, CString& nationalite, CString& renseignement, CComboBox& ctrlNationality, long& IDAuteur);
	void mettreAJourNationalite(CComboBox* pBoxCtrl);
	bool supprimerCategorie(CPubContainer* pContainer);
	bool peutSupprimerElement();
	bool modifierCategorie(CPubContainer* pCategorie, CString nouveauNom);
	bool donnerInfoCategorie(long categorieID, CString& nom, CString& login, COleDateTime& date);
	bool peutModifierBase(void);
	bool ajouterCategorie(CString categorieName, CPubElement* categoriePere);
	virtual ~CPublicationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL RmDirectory(CString sDir);
	bool rechercherAuteur(CString& nomComplet, long IdAuteur);
	long createTypeID(CTypeSet& jeuType);
	long createSujetID(CSujetSet &jeuSujet);
	long createAuteurID(CAuteurSet& auteurSet);
	CPubElement* rechercherCategorieRacine(long identificateur, CPubElement* pElement);
	BOOL ouvrirBase(BOOL isOpen);
	CString m_documentTitle;
	BOOL creerNouvelleBase(CString* password);
	CPublicationInfoGal m_InfoBase;
	CPubRacine* m_elementRoot;
	//{{AFX_MSG(CPublicationDoc)
	afx_msg void OnAuteurAjouter();
	afx_msg void OnAuteurRechercher();
	afx_msg void OnUpdateAuteurAjouter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSujetAjouter(CCmdUI* pCmdUI);
	afx_msg void OnSujetAjouter();
	afx_msg void OnSujetRechercher();
	afx_msg void OnUpdateTypeAjouter(CCmdUI* pCmdUI);
	afx_msg void OnTypeAjouter();
	afx_msg void OnTypeRechercher();
	afx_msg void OnUpdateMotClefsAjouter(CCmdUI* pCmdUI);
	afx_msg void OnMotClefsAjouter();
	afx_msg void OnMotClefsRechercher();
	afx_msg void OnUpdateGenreAjouter(CCmdUI* pCmdUI);
	afx_msg void OnGenreAjouter();
	afx_msg void OnGenreRechercher();
	afx_msg void OnCategorieRechercher();
	afx_msg void OnPublicationRechercher();
	afx_msg void OnPublicationRechercheavd();
	afx_msg void OnUpdateUtilisateurAjouter(CCmdUI* pCmdUI);
	afx_msg void OnUtilisateurAjouter();
	afx_msg void OnUtilisateurRechercher();
	afx_msg void OnUtilisateurModifierMotdepasse();
	afx_msg void OnUtilisateurListedesutilisateurs();
	afx_msg void OnOptionsBase();
	afx_msg void OnOptionUpdateBase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL CopyDirectory(CString sAncienRepertoire, CString sNouveauRepertoire);
	CString rechercheNomDocument(CString nomComplet, CString nomDocument, CPubContainer* pPere, CString& extension);
	bool publicationExisteDeja(CString& nomDoc, CPubElement* elementPere);
	long createPublicationID(CDocumentSet & publicationSet);
	long createCategorieID(CCategorieSet& categorie);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUBLICATIONDOC_H__18AB4730_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
