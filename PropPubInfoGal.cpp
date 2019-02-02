// PropPubInfoGal.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropPubInfoGal.h"
#include "AjouterAuteurDialog.h"
#include "AjouterGenreDialog.h"
#include "AjouterSujetDialog.h"
#include "AjouterTypeDialog.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPubInfoGal property page

IMPLEMENT_DYNCREATE(CPropPubInfoGal, CPropertyPage)

CPropPubInfoGal::CPropPubInfoGal() : CPropertyPage(CPropPubInfoGal::IDD)
{
	//{{AFX_DATA_INIT(CPropPubInfoGal)
	m_stringTitre = _T("");
	//}}AFX_DATA_INIT
}

CPropPubInfoGal::~CPropPubInfoGal()
{
}

void CPropPubInfoGal::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPubInfoGal)
	DDX_Control(pDX, IDC_LISTE_TYPE, m_ComboBoxType);
	DDX_Control(pDX, IDC_LISTE_SUJET, m_ComboBoxSujet);
	DDX_Control(pDX, IDC_LISTE_GENRE, m_ComboBoxGenre);
	DDX_Control(pDX, IDC_LIST_AUTEUR, m_ComboBoxAuteur);
	DDX_Text(pDX, IDC_EDIT_TITRE_DOCUMENT, m_stringTitre);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPubInfoGal, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPubInfoGal)
	ON_BN_CLICKED(IDC_BUTTON_ADD_AUTEUR, OnButtonAddAuteur)
	ON_BN_CLICKED(IDC_BUTTON_ADD_GENRE, OnButtonAddGenre)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SUJET, OnButtonAddSujet)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TYPE, OnButtonAddType)
	ON_EN_CHANGE(IDC_EDIT_TITRE_DOCUMENT, OnChangeEditTitreDocument)
	ON_CBN_SELCHANGE(IDC_LIST_AUTEUR, OnSelchangeListAuteur)
	ON_CBN_SELCHANGE(IDC_LISTE_GENRE, OnSelchangeListeGenre)
	ON_CBN_SELCHANGE(IDC_LISTE_SUJET, OnSelchangeListeSujet)
	ON_CBN_SELCHANGE(IDC_LISTE_TYPE, OnSelchangeListeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CPropPubInfoGal::AddDocument(CPublicationDoc * pDoc)
{
  m_pDoc = pDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CPropPubInfoGal message handlers

void CPropPubInfoGal::OnButtonAddAuteur() 
{
	CAjouterAuteurDialog ajouterAuteur(o_OUVERTURE_NORMAL, -1, m_pDoc);

	ajouterAuteur.DoModal();

	m_pDoc->mettreAJourListeAuteur(m_ComboBoxAuteur);
}

void CPropPubInfoGal::OnButtonAddGenre() 
{
	CAjouterGenreDialog ajouterGenre(o_OUVERTURE_NORMAL, -1, m_pDoc);

	ajouterGenre.DoModal();

	m_pDoc->mettreAJourListeGenre(m_ComboBoxGenre);
}

void CPropPubInfoGal::OnButtonAddSujet() 
{
	CAjouterSujetDialog addSujet(o_OUVERTURE_NORMAL, -1, m_pDoc);

	addSujet.DoModal();

	m_pDoc->mettreAJourListeSujet(m_ComboBoxSujet);
}

void CPropPubInfoGal::OnButtonAddType() 
{
	CAjouterTypeDialog ajouterType(o_OUVERTURE_NORMAL, -1, m_pDoc);

	ajouterType.DoModal();

	m_pDoc->mettreAJourListeType(m_ComboBoxType);
}

BOOL CPropPubInfoGal::OnInitDialog() 
{
	CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

	int i;

	CPropertyPage::OnInitDialog();
	
	m_pDoc->mettreAJourListeAuteur(m_ComboBoxAuteur);
	m_pDoc->mettreAJourListeSujet(m_ComboBoxSujet);
	m_pDoc->mettreAJourListeType(m_ComboBoxType);
	m_pDoc->mettreAJourListeGenre(m_ComboBoxGenre);

	// mettre a jour auteur
	for(i=0;i<m_ComboBoxAuteur.GetCount();i++)
	{
		if (m_ComboBoxAuteur.GetItemData(i) == (DWORD) (pSheet->m_donneesDocument).idAuteur)
		{
			m_ComboBoxAuteur.SetCurSel(i);
			break;
		}
	}

	for(i=0;i<m_ComboBoxSujet.GetCount();i++)
	{
		if (m_ComboBoxSujet.GetItemData(i) == (DWORD) (pSheet->m_donneesDocument).idSujet)
		{
			m_ComboBoxSujet.SetCurSel(i);
			break;
		}
	}

	for(i=0;i<m_ComboBoxType.GetCount();i++)
	{
		if (m_ComboBoxType.GetItemData(i) == (DWORD) (pSheet->m_donneesDocument).idType)
		{
			m_ComboBoxType.SetCurSel(i);
			break;
		}
	}

	for(i=0;i<m_ComboBoxGenre.GetCount();i++)
	{
		if (m_ComboBoxGenre.GetItemData(i) == (DWORD) (pSheet->m_donneesDocument).idGenre)
		{
			m_ComboBoxGenre.SetCurSel(i);
			break;
		}
	}

	
	m_stringTitre = (pSheet->m_donneesDocument).nomDocument;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropPubInfoGal::OnChangeEditTitreDocument() 
{
	DocumentModifier();
}

void CPropPubInfoGal::OnSelchangeListAuteur() 
{
	DocumentModifier();
}

void CPropPubInfoGal::OnSelchangeListeGenre() 
{
	DocumentModifier();
}

void CPropPubInfoGal::OnSelchangeListeSujet() 
{
	DocumentModifier();
}

void CPropPubInfoGal::OnSelchangeListeType() 
{
	DocumentModifier();
}




BOOL CPropPubInfoGal::OnApply() 
{
  CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

  pSheet->ModifierDocumentDansBase();

  return CPropertyPage::OnApply();
}

void CPropPubInfoGal::OnOK() 
{	
	CPropertyPage::OnOK();
}

void CPropPubInfoGal::DocumentModifier()
{
  CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

  SetModified();
  pSheet->m_bDocModifier = true;
}

bool CPropPubInfoGal::VerifierDonnees()
{
  UpdateData();
  int nCurrentSelection;

  nCurrentSelection = m_ComboBoxType.GetCurSel();
  if (nCurrentSelection == CB_ERR)
  {
    AfxMessageBox(_T("Aucun type n'a été sélectionné !"));
    return false;
  }

  nCurrentSelection = m_ComboBoxSujet.GetCurSel();
  if (nCurrentSelection == CB_ERR)
  {
    AfxMessageBox(_T("Aucun sujet n'a été sélectionné !"));
    return false;
  }

  nCurrentSelection = m_ComboBoxGenre.GetCurSel();
  if (nCurrentSelection == CB_ERR)
  {
    AfxMessageBox(_T("Aucun genre n'a été sélectionné !"));
    return false;
  }

  nCurrentSelection = m_ComboBoxAuteur.GetCurSel();
  if (nCurrentSelection == CB_ERR)
  {
    AfxMessageBox(_T("Aucun auteur n'a été sélectionné !"));
    return false;
  }

  if (m_stringTitre == "") 
  {
    AfxMessageBox(_T("Ce document n'a pas de titre !"));
    return false;
  }


  return true;
}
