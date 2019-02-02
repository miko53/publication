// RechercheDocument.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheDocument.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheDocument dialog


CRechercheDocument::CRechercheDocument(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheDocument::IDD, pParent)
{
  ASSERT( pDoc != NULL);

  m_pDoc = pDoc;
  m_itemSelectionne = 0;

	//{{AFX_DATA_INIT(CRechercheDocument)
	m_bNomDocument = FALSE;
	m_bNomAuteur = FALSE;
	m_bNomSujet = FALSE;
	m_bNomGenre = FALSE;
	m_bNomType = FALSE;
	m_bNomLogin = FALSE;
	//}}AFX_DATA_INIT
}


void CRechercheDocument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheDocument)
	DDX_Control(pDX, IDC_AFFICHER, m_buttonAfficher);
	DDX_Control(pDX, IDC_PROPRIETE, m_buttonPropriete);
	DDX_Control(pDX, IDC_LIST_DOCUMENT, m_listCtrlDocument);
	DDX_Control(pDX, IDC_NomLogin, m_editNomLogin);
	DDX_Control(pDX, IDC_NomType, m_comboBoxNomType);
	DDX_Control(pDX, IDC_NomGenre, m_comboBoxNomGenre);
	DDX_Control(pDX, IDC_NomSujet, m_comboBoxNomSujet);
	DDX_Control(pDX, IDC_NomAuteur, m_comboBoxNomAuteur);
	DDX_Control(pDX, IDC_NomDocument, m_editNomDocument);
	DDX_Check(pDX, IDC_Nom, m_bNomDocument);
	DDX_Check(pDX, IDC_NOM_AUTEUR, m_bNomAuteur);
	DDX_Check(pDX, IDC_SUJET, m_bNomSujet);
	DDX_Check(pDX, IDC_GENRE, m_bNomGenre);
	DDX_Check(pDX, IDC_TYPE, m_bNomType);
	DDX_Check(pDX, IDC_LOGIN, m_bNomLogin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheDocument, CDialog)
	//{{AFX_MSG_MAP(CRechercheDocument)
	ON_BN_CLICKED(IDC_Nom, OnCocheNomDocument)
	ON_BN_CLICKED(IDC_NOM_AUTEUR, OnCocheNomAuteur)
	ON_BN_CLICKED(IDC_SUJET, OnCocheSujet)
	ON_BN_CLICKED(IDC_GENRE, OnCocheGenre)
	ON_BN_CLICKED(IDC_TYPE, OnCocheType)
	ON_BN_CLICKED(IDC_LOGIN, OnCocheLogin)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DOCUMENT, OnItemchangedListDocument)
	ON_BN_CLICKED(IDC_PROPRIETE, OnClickPropriete)
	ON_BN_CLICKED(IDC_AFFICHER, OnClickAfficher)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheDocument message handlers

BOOL CRechercheDocument::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_listCtrlDocument.InsertColumn(0, "Titre", LVCFMT_LEFT, 150, 0);
	m_listCtrlDocument.InsertColumn(1, "Sujet", LVCFMT_LEFT, 150, 1);
	m_listCtrlDocument.InsertColumn(2, "Auteur", LVCFMT_LEFT, 100, 2);
	m_listCtrlDocument.InsertColumn(3, "Categorie", LVCFMT_LEFT, 120, 3);

  // init valeur par defaut 
	m_bNomDocument = TRUE;
  m_editNomDocument.EnableWindow(TRUE);
  m_bNomAuteur = FALSE;
  m_bNomSujet = FALSE;
  m_bNomGenre = FALSE;
  m_bNomType = FALSE;
  m_bNomLogin = FALSE;

  // remplissage des comboBox
  m_pDoc->mettreAJourListeAuteur(m_comboBoxNomAuteur);
  m_pDoc->mettreAJourListeSujet(m_comboBoxNomSujet);
  m_pDoc->mettreAJourListeGenre(m_comboBoxNomGenre);
  m_pDoc->mettreAJourListeType(m_comboBoxNomType);

  UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRechercheDocument::OnCocheNomDocument() 
{
  if (m_bNomDocument == TRUE)
  {
    m_bNomDocument = FALSE;
    m_editNomDocument.EnableWindow(FALSE);
  }
  else
  {
    m_bNomDocument = TRUE;
    m_editNomDocument.EnableWindow(TRUE);
  }
}

void CRechercheDocument::OnCocheNomAuteur() 
{
  if (m_bNomAuteur == TRUE)
  {
    m_bNomAuteur = FALSE;
    m_comboBoxNomAuteur.EnableWindow(FALSE);
  }
  else
  {
    m_bNomAuteur = TRUE;
    m_comboBoxNomAuteur.EnableWindow(TRUE);
  }
}

void CRechercheDocument::OnCocheSujet() 
{
  if (m_bNomSujet == TRUE)
  {
    m_bNomSujet = FALSE;
    m_comboBoxNomSujet.EnableWindow(FALSE);
  }
  else
  {
    m_bNomSujet = TRUE;
    m_comboBoxNomSujet.EnableWindow(TRUE);
  }
}

void CRechercheDocument::OnCocheGenre() 
{
  if (m_bNomGenre == TRUE)
  {
    m_bNomGenre = FALSE;
    m_comboBoxNomGenre.EnableWindow(FALSE);
  }
  else
  {
    m_bNomGenre = TRUE;
    m_comboBoxNomGenre.EnableWindow(TRUE);
  }
}

void CRechercheDocument::OnCocheType() 
{
  if (m_bNomType == TRUE)
  {
    m_bNomType = FALSE;
    m_comboBoxNomType.EnableWindow(FALSE);
  }
  else
  {
    m_bNomType = TRUE;
    m_comboBoxNomType.EnableWindow(TRUE);
  }
}

void CRechercheDocument::OnCocheLogin() 
{
  if (m_bNomLogin == TRUE)
  {
    m_bNomLogin = FALSE;
    m_editNomLogin.EnableWindow(FALSE);
  }
  else
  {
    m_bNomLogin = TRUE;
    m_editNomLogin.EnableWindow(TRUE);
  }
}

void CRechercheDocument::OnLancerecherche() 
{
  // creation de la chaine SQL de recherche 
  // et demande au document
  CString sRequeteSQL[6];
  CString sRequete;
  CString sNomChamp;
  unsigned char byIndiceRSQL;

  byIndiceRSQL = 0;


  // le titre
  if (m_bNomDocument == TRUE)
  {
    m_editNomDocument.GetWindowText(sNomChamp);
    if (sNomChamp != "")
    {
      sRequeteSQL[byIndiceRSQL].Format("([Titre] Like \"%s\")", sNomChamp);
      byIndiceRSQL++;
    }
  }

  // l'auteur
  if (m_bNomAuteur == TRUE)
  {
    int nIndex = m_comboBoxNomAuteur.GetCurSel();
    m_comboBoxNomAuteur.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdAuteur] IN (SELECT [IdAuteur] FROM [Auteur] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdAuteur] = %i)", (long) m_comboBoxNomAuteur.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }
  }

  // le sujet 
  if (m_bNomSujet == TRUE)
  {
    int nIndex = m_comboBoxNomSujet.GetCurSel();
    m_comboBoxNomSujet.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdSujet] IN (SELECT [IdSujet] FROM [Sujet] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdSujet] = %i)", (long) m_comboBoxNomSujet.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }
  }

  // le genre 
  if (m_bNomGenre == TRUE)
  {
    int nIndex = m_comboBoxNomGenre.GetCurSel();
    m_comboBoxNomGenre.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdGenre] IN (SELECT [IdGenre] FROM [Genre] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdGenre] = %i)", (long) m_comboBoxNomGenre.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }
  }

  // le type 
  if (m_bNomType == TRUE)
  {
    int nIndex = m_comboBoxNomType.GetCurSel();
    m_comboBoxNomType.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdType] IN (SELECT [IdType] FROM [Type] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdType] = %i)", (long) m_comboBoxNomType.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }
  }

  // le login 
  if (m_bNomLogin == TRUE)
  {
    m_editNomLogin.GetWindowText(sNomChamp);
    if (sNomChamp != "")
    {
      sRequeteSQL[byIndiceRSQL].Format("([Login] Like \"%s\")", sNomChamp);
      byIndiceRSQL++;
    }
  }

  // Formatage de la requete dans sRequete
  int nIndiceAjoutAnd;

  switch (byIndiceRSQL)
  {
  case 0:
    // pas de requete on ne fait rien
    return;
    break;

  case 1:
    // une seul requete
    sRequete = sRequeteSQL[0];
    break;

  default:
    sRequete.Format("%s ", sRequeteSQL[0]);
    for(nIndiceAjoutAnd = 1; nIndiceAjoutAnd<(int) byIndiceRSQL; nIndiceAjoutAnd++)
    {
      sRequete += " AND ";
      sRequete += sRequeteSQL[nIndiceAjoutAnd];
    }
    break;
  }

//  AfxMessageBox(sRequete);

  m_pDoc->rechercheDocument(m_listCtrlDocument, sRequete);


}

void CRechercheDocument::OnItemchangedListDocument(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
	{
		m_itemSelectionne = pNMListView->iItem;

		m_buttonAfficher.EnableWindow();
		m_buttonPropriete.EnableWindow();
	}
	else
	{
		m_buttonAfficher.EnableWindow(FALSE);
		m_buttonPropriete.EnableWindow(FALSE);
	}

	*pResult = 0;
}

void CRechercheDocument::OnClickPropriete() 
{
  CPubDocument* pDocument = m_pDoc->recherchePtrDocument((long) m_listCtrlDocument.GetItemData(m_itemSelectionne), m_pDoc->donnerRacine());
	CModifierPublicationPropSheet aPropSheet("Propriétés du document", m_pDoc, pDocument);

	aPropSheet.DoModal();
}

void CRechercheDocument::OnClickAfficher() 
{
	m_pDoc->afficherDocumentDansVueCourante((long) m_listCtrlDocument.GetItemData(m_itemSelectionne));
}
