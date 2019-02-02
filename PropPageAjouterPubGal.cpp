// PropPageAjouterPubGal.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropPageAjouterPubGal.h"
#include "AjouterAuteurDialog.h"
#include "AjouterGenreDialog.h"
#include "AjouterSujetDialog.h"
#include "AjouterTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubGal property page

IMPLEMENT_DYNCREATE(CPropPageAjouterPubGal, CPropertyPage)

CPropPageAjouterPubGal::CPropPageAjouterPubGal() : CPropertyPage(CPropPageAjouterPubGal::IDD)
{
	//{{AFX_DATA_INIT(CPropPageAjouterPubGal)
	m_StringTitre = _T("");
	//}}AFX_DATA_INIT
}

CPropPageAjouterPubGal::~CPropPageAjouterPubGal()
{
}

void CPropPageAjouterPubGal::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageAjouterPubGal)
	DDX_Control(pDX, IDC_LISTE_TYPE, m_ComboBoxType);
	DDX_Control(pDX, IDC_LISTE_GENRE, m_ComboBoxGenre);
	DDX_Control(pDX, IDC_LISTE_SUJET, m_ComboBoxSujet);
	DDX_Control(pDX, IDC_LIST_AUTEUR, m_ComboBoxAuteur);
	DDX_Text(pDX, IDC_EDIT_TITRE_DOCUMENT, m_StringTitre);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageAjouterPubGal, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageAjouterPubGal)
	ON_EN_CHANGE(IDC_EDIT_TITRE_DOCUMENT, OnChangeEditTitreDocument)
	ON_CBN_SELCHANGE(IDC_LIST_AUTEUR, OnSelchangeListAuteur)
	ON_CBN_SELCHANGE(IDC_LISTE_GENRE, OnSelchangeListeGenre)
	ON_CBN_SELCHANGE(IDC_LISTE_SUJET, OnSelchangeListeSujet)
	ON_CBN_SELCHANGE(IDC_LISTE_TYPE, OnSelchangeListeType)
	ON_BN_CLICKED(IDC_BUTTON_ADD_AUTEUR, OnButtonAddAuteur)
	ON_BN_CLICKED(IDC_BUTTON_ADD_GENRE, OnButtonAddGenre)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SUJET, OnButtonAddSujet)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TYPE, OnButtonAddType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubGal message handlers

BOOL CPropPageAjouterPubGal::OnSetActive() 
{
	peutContinuer();
	
	return CPropertyPage::OnSetActive();
}


void CPropPageAjouterPubGal::AddDocument(CPublicationDoc * pDoc)
{
	m_pDoc = pDoc;
}


BOOL CPropPageAjouterPubGal::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_pDoc->mettreAJourListeAuteur(m_ComboBoxAuteur);
	m_pDoc->mettreAJourListeSujet(m_ComboBoxSujet);
	m_pDoc->mettreAJourListeType(m_ComboBoxType);
	m_pDoc->mettreAJourListeGenre(m_ComboBoxGenre);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPropPageAjouterPubGal::OnChangeEditTitreDocument() 
{
	peutContinuer();
}

void CPropPageAjouterPubGal::OnSelchangeListAuteur() 
{
	peutContinuer();
}

void CPropPageAjouterPubGal::OnSelchangeListeGenre() 
{
	peutContinuer();
}

void CPropPageAjouterPubGal::OnSelchangeListeSujet() 
{
	peutContinuer();
}

void CPropPageAjouterPubGal::OnSelchangeListeType() 
{
	peutContinuer();
}


bool CPropPageAjouterPubGal::peutContinuer()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	ASSERT_KINDOF(CPropertySheet, pSheet);

	UpdateData();

	if ((m_ComboBoxAuteur.GetCurSel() != CB_ERR) &&
		(m_ComboBoxGenre.GetCurSel() != CB_ERR) &&
		(m_ComboBoxSujet.GetCurSel() != CB_ERR) &&
		(m_ComboBoxType.GetCurSel() != CB_ERR) &&
		(m_StringTitre != _T("")) )
	{
		pSheet->SetWizardButtons(PSWIZB_NEXT);
		return true;
	}
	else
	{
		pSheet->SetWizardButtons(0);
		return false;
	}
}

void CPropPageAjouterPubGal::OnButtonAddAuteur() 
{
	CAjouterAuteurDialog ajouterAuteur(o_OUVERTURE_NORMAL, -1, m_pDoc);

	ajouterAuteur.DoModal();

	m_pDoc->mettreAJourListeAuteur(m_ComboBoxAuteur);
}

void CPropPageAjouterPubGal::OnButtonAddGenre() 
{
	CAjouterGenreDialog ajouterGenre(o_OUVERTURE_NORMAL, -1, m_pDoc);

	ajouterGenre.DoModal();

	m_pDoc->mettreAJourListeGenre(m_ComboBoxGenre);
}

void CPropPageAjouterPubGal::OnButtonAddSujet() 
{
	CAjouterSujetDialog addSujet(o_OUVERTURE_NORMAL, -1, m_pDoc);

	addSujet.DoModal();

	m_pDoc->mettreAJourListeSujet(m_ComboBoxSujet);
}

void CPropPageAjouterPubGal::OnButtonAddType() 
{
	CAjouterTypeDialog ajouterType(o_OUVERTURE_NORMAL, -1, m_pDoc);

	ajouterType.DoModal();

	m_pDoc->mettreAJourListeType(m_ComboBoxType);
}
