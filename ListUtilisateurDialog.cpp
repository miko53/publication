// ListUtilisateurDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "ListUtilisateurDialog.h"
#include "ModifierUtilisateurDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListUtilisateurDialog dialog


CListUtilisateurDialog::CListUtilisateurDialog(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CListUtilisateurDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListUtilisateurDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pDoc = pDoc;
}


void CListUtilisateurDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListUtilisateurDialog)
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifer);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Control(pDX, IDC_LIST_UTILISATEUR, m_listCtrlUtilisateur);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListUtilisateurDialog, CDialog)
	//{{AFX_MSG_MAP(CListUtilisateurDialog)
	ON_BN_CLICKED(IDC_MODIFIER, OnModifier)
	ON_BN_CLICKED(IDC_EFFACER, OnEffacer)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_UTILISATEUR, OnItemchangedListUtilisateur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListUtilisateurDialog message handlers

BOOL CListUtilisateurDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listCtrlUtilisateur.InsertColumn(0, "Login", LVCFMT_LEFT, 170, 0);
	m_listCtrlUtilisateur.InsertColumn(1, "Droits (AMS-AMS-M)", LVCFMT_LEFT, 200, 1);
  
  m_pDoc->mettreAJourListeUtilisateur(m_listCtrlUtilisateur);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CListUtilisateurDialog::OnModifier() 
{
  CModifierUtilisateurDialog aDialog(m_pDoc, m_listCtrlUtilisateur.GetItemText(m_itemSelectionne, 0));

  if (aDialog.DoModal() == IDOK)
    m_pDoc->mettreAJourListeUtilisateur(m_listCtrlUtilisateur);
	
}

void CListUtilisateurDialog::OnEffacer() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer cet utilisateur ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
  {
		m_pDoc->effacerUtilisateur(m_listCtrlUtilisateur.GetItemText(m_itemSelectionne, 0));
    m_pDoc->mettreAJourListeUtilisateur(m_listCtrlUtilisateur);
  }
}


void CListUtilisateurDialog::OnItemchangedListUtilisateur(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
	{
		m_itemSelectionne = pNMListView->iItem;

    if (m_listCtrlUtilisateur.GetItemText(m_itemSelectionne, 0) != m_pDoc->GetNomUtilisateurCourant())
    {
	    if (m_pDoc->peutModifierBase() == true)
		    m_buttonModifer.EnableWindow();

	    if (m_pDoc->peutSupprimerElement() == true)
		    m_buttonEffacer.EnableWindow();
    }
    else
    {
		  m_buttonModifer.EnableWindow(FALSE);
		  m_buttonEffacer.EnableWindow(FALSE);
    }
	}
	else
	{
		m_buttonModifer.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}

	*pResult = 0;
}
