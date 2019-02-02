// RechercheCategorieDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheCategorieDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheCategorieDialog dialog


CRechercheCategorieDialog::CRechercheCategorieDialog(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheCategorieDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheCategorieDialog)
	m_CocheNom = FALSE;
	m_CocheLogin = FALSE;
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;
}


void CRechercheCategorieDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheCategorieDialog)
	DDX_Control(pDX, IDC_AFFICHER, m_buttonAfficher);
	DDX_Control(pDX, IDC_LIST_CATEGORIE, m_listCategorie);
	DDX_Control(pDX, IDC_UtilisantEntrant, m_editNomLogin);
	DDX_Control(pDX, IDC_NomCategorie, m_editNomCategorie);
	DDX_Check(pDX, IDC_Nom, m_CocheNom);
	DDX_Check(pDX, IDC_LOGIN, m_CocheLogin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheCategorieDialog, CDialog)
	//{{AFX_MSG_MAP(CRechercheCategorieDialog)
	ON_BN_CLICKED(IDC_LOGIN, OnCocheLogin)
	ON_BN_CLICKED(IDC_Nom, OnCocheNomCategorie)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_BN_CLICKED(IDC_AFFICHER, OnAfficher)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CATEGORIE, OnItemchangedListCategorie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheCategorieDialog message handlers

BOOL CRechercheCategorieDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listCategorie.InsertColumn(0, "Categorie", LVCFMT_LEFT, 150, 0);
	m_listCategorie.InsertColumn(1, "Categorie racine", LVCFMT_LEFT, 150, 1);
	m_listCategorie.InsertColumn(2, "Login entrant", LVCFMT_LEFT, 100, 2);
	m_listCategorie.InsertColumn(3, "Date d'entrée", LVCFMT_LEFT, 120, 3);

	m_CocheNom = TRUE;
	m_CocheLogin = FALSE;
	
	m_editNomCategorie.EnableWindow();
	m_editNomLogin.EnableWindow(FALSE);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CRechercheCategorieDialog::OnCocheLogin() 
{
	if (m_CocheLogin == TRUE)
	{
		m_CocheLogin = FALSE;
		m_editNomLogin.EnableWindow(FALSE);
	}
	else
	{
		m_CocheLogin = TRUE;
		m_editNomLogin.EnableWindow();
	}
}


void CRechercheCategorieDialog::OnCocheNomCategorie() 
{
	if (m_CocheNom == TRUE)
	{
		m_CocheNom = FALSE;
		m_editNomCategorie.EnableWindow(FALSE);
	}
	else
	{
		m_CocheNom = TRUE;
		m_editNomCategorie.EnableWindow();
	}
}

void CRechercheCategorieDialog::OnLancerecherche() 
{
	CString nomCategorie;
	CString nomLogin;
	stRechercheCategorie rechercheCategorie;

	m_editNomCategorie.GetWindowText(nomCategorie);
	m_editNomLogin.GetWindowText(nomLogin);

	UpdateData(TRUE);

	if ((m_CocheNom == TRUE) && (nomCategorie != ""))
	{
		rechercheCategorie.pNomCategorie = (char*) ((const char*) nomCategorie);
	}
	else
	{
		rechercheCategorie.pNomCategorie = NULL;
	}


	if ((m_CocheLogin == TRUE) && (nomLogin != ""))
	{
		rechercheCategorie.pNomLogin = (char*) ((const char*) nomLogin);
	}
	else
	{
		rechercheCategorie.pNomLogin = NULL;
	}

	if ((rechercheCategorie.pNomLogin != NULL) || (rechercheCategorie.pNomCategorie != NULL))
		m_pDoc->rechercherEtMiseAJourCategorie(m_listCategorie, rechercheCategorie);

}


void CRechercheCategorieDialog::OnItemchangedListCategorie(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
	{
		m_itemSelectionne = pNMListView->iItem;
		m_buttonAfficher.EnableWindow();
	}
	else
	{
		m_buttonAfficher.EnableWindow(FALSE);
	}

	*pResult = 0;
}


void CRechercheCategorieDialog::OnAfficher() 
{
	m_pDoc->afficherCategorieRechercheDansVueCourante((long) m_listCategorie.GetItemData(m_itemSelectionne));
}
