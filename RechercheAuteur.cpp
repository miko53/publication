// RechercheAuteur.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheAuteur.h"
#include "constElement.h"
#include "AjouterAuteurDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheAuteur dialog


CRechercheAuteur::CRechercheAuteur(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheAuteur::IDD, pParent)
{
	ASSERT(pDoc != NULL);
	m_pDocument = pDoc;

	//{{AFX_DATA_INIT(CRechercheAuteur)
	m_CheckPrenom = FALSE;
	m_CheckNationalite = FALSE;
	m_CheckNom = FALSE;
	//}}AFX_DATA_INIT
}


void CRechercheAuteur::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheAuteur)
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifer);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Control(pDX, IDC_Nationalite, m_NationaliteCtrl);
	DDX_Control(pDX, IDC_PrenomAuteur, m_PrenomAuteurCtrl);
	DDX_Control(pDX, IDC_NomAuteur, m_NomAuteurCtrl);
	DDX_Control(pDX, IDC_LIST_AUTEUR, m_ListAuteurCtrl);
	DDX_Check(pDX, IDC_Prenom, m_CheckPrenom);
	DDX_Check(pDX, IDC_Nation, m_CheckNationalite);
	DDX_Check(pDX, IDC_Nom, m_CheckNom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheAuteur, CDialog)
	//{{AFX_MSG_MAP(CRechercheAuteur)
	ON_BN_CLICKED(IDC_Nom, OnCocheNom)
	ON_BN_CLICKED(IDC_Prenom, OnCochePrenom)
	ON_BN_CLICKED(IDC_Nation, OnCocheNation)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_AUTEUR, OnItemchangedListAuteur)
	ON_BN_CLICKED(IDC_EFFACER, OnClickButtonEffacer)
	ON_BN_CLICKED(IDC_MODIFIER, OnClickButtonModifier)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheAuteur message handlers

BOOL CRechercheAuteur::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ListAuteurCtrl.InsertColumn(0, "Nom", LVCFMT_LEFT, 100, 0);
	m_ListAuteurCtrl.InsertColumn(1, "Prenom", LVCFMT_LEFT, 100, 1);
	m_ListAuteurCtrl.InsertColumn(2, "Nationalite", LVCFMT_LEFT, 100, 2);
	m_ListAuteurCtrl.InsertColumn(3, "Date de naissance", LVCFMT_LEFT, 120, 3);

	m_pDocument->mettreAJourNationalite(&m_NationaliteCtrl);

	m_CheckNom = TRUE;
	m_CheckPrenom = FALSE;
	m_CheckNationalite = FALSE;
	
	m_NomAuteurCtrl.EnableWindow();
	m_PrenomAuteurCtrl.EnableWindow(FALSE);
	m_NationaliteCtrl.EnableWindow(FALSE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRechercheAuteur::OnCocheNom() 
{
	if (m_CheckNom == TRUE)
	{
		m_CheckNom = FALSE;
		m_NomAuteurCtrl.EnableWindow(FALSE);
	}
	else
	{
		m_CheckNom = TRUE;
		m_NomAuteurCtrl.EnableWindow();
	}
}

void CRechercheAuteur::OnCochePrenom() 
{
	if (m_CheckPrenom == TRUE)
	{
		m_CheckPrenom = FALSE;
		m_PrenomAuteurCtrl.EnableWindow(FALSE);
	}
	else
	{
		m_CheckPrenom = TRUE;
		m_PrenomAuteurCtrl.EnableWindow();
	}
}

void CRechercheAuteur::OnCocheNation() 
{
	if (m_CheckNationalite == TRUE)
	{
		m_CheckNationalite = FALSE;
		m_NationaliteCtrl.EnableWindow(FALSE);
	}
	else
	{
		m_CheckNationalite = TRUE;
		m_NationaliteCtrl.EnableWindow();
	}
}

void CRechercheAuteur::OnLancerecherche() 
{
	CString Nationalite;
	CString Nom;
	CString Prenom;
	stRechercheAuteur rechercheAuteur;

	m_NationaliteCtrl.GetWindowText(Nationalite);
	m_NomAuteurCtrl.GetWindowText(Nom);
	m_PrenomAuteurCtrl.GetWindowText(Prenom);

	UpdateData(TRUE);


	if ((m_CheckNom == TRUE) && (Nom != ""))
		rechercheAuteur.pNom = (char*) ((const char*) Nom);
	else
		rechercheAuteur.pNom = NULL;


	if ((m_CheckPrenom == TRUE) && (Prenom != ""))
		rechercheAuteur.pPrenom = (char*) ((const char*) Prenom);
	else
		rechercheAuteur.pPrenom = NULL;

	if ((m_CheckNationalite == TRUE) && (Nationalite != ""))
		rechercheAuteur.pNationalite = (char*) ((const char*) Nationalite);
	else
		rechercheAuteur.pNationalite = NULL;

	if ((rechercheAuteur.pNom != NULL) || (rechercheAuteur.pPrenom != NULL) ||
		(rechercheAuteur.pNationalite != NULL))
		m_pDocument->rechercherAuteur(m_ListAuteurCtrl, rechercheAuteur);
}


//quand la selection a changé
void CRechercheAuteur::OnItemchangedListAuteur(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
	{
		m_itemSelectionne = pNMListView->iItem;

		if (m_pDocument->peutModifierBase() == true)
			m_buttonModifer.EnableWindow();

		if (m_pDocument->peutSupprimerElement() == true)
			m_buttonEffacer.EnableWindow();
	}
	else
	{
		m_buttonModifer.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}

	*pResult = 0;
}

void CRechercheAuteur::OnClickButtonEffacer() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer cet auteur ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
		m_pDocument->effacerAuteur((long) m_ListAuteurCtrl.GetItemData(m_itemSelectionne));

	//OnLancerecherche();
}

void CRechercheAuteur::OnClickButtonModifier() 
{
	CAjouterAuteurDialog ajoutAuteur(o_OUVERTURE_PAR_RECHERCHE, (long) m_ListAuteurCtrl.GetItemData(m_itemSelectionne), m_pDocument);
	ajoutAuteur.DoModal();

	//OnLancerecherche();
}
