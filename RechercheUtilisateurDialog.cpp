// RechercheUtilisateurDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheUtilisateurDialog.h"
#include "ModifierUtilisateurDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheUtilisateurDialog dialog


CRechercheUtilisateurDialog::CRechercheUtilisateurDialog(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheUtilisateurDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheUtilisateurDialog)
	m_sNomLogin = _T("");
	//}}AFX_DATA_INIT

  ASSERT(pDoc !=NULL);
  m_pDoc = pDoc;
  m_nIndiceListBox = -1;
}


void CRechercheUtilisateurDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheUtilisateurDialog)
	DDX_Control(pDX, IDC_LIST_UTILISATEUR, m_listBoxUtilisateur);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifier);
	DDX_Text(pDX, IDC_NomLogin, m_sNomLogin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheUtilisateurDialog, CDialog)
	//{{AFX_MSG_MAP(CRechercheUtilisateurDialog)
	ON_BN_CLICKED(IDC_EFFACER, OnEffacerUtilisateur)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_BN_CLICKED(IDC_MODIFIER, OnModifierUtlisateur)
	ON_LBN_SELCHANGE(IDC_LIST_UTILISATEUR, OnSelchangeListUtilisateur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheUtilisateurDialog message handlers

void CRechercheUtilisateurDialog::OnEffacerUtilisateur() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer cet utilisateur ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
		m_pDoc->effacerUtilisateur(GetNomLoginCourant());
}

void CRechercheUtilisateurDialog::OnLancerecherche() 
{
	UpdateData(TRUE);

	if (m_sNomLogin != "")
	{
		m_pDoc->rechercheUtilisateur(m_listBoxUtilisateur, m_sNomLogin);
		m_nIndiceListBox = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}

void CRechercheUtilisateurDialog::OnModifierUtlisateur() 
{
  CModifierUtilisateurDialog aDialog(m_pDoc, GetNomLoginCourant());
	UpdateData(TRUE);

  aDialog.DoModal();
	
}

void CRechercheUtilisateurDialog::OnSelchangeListUtilisateur() 
{
	int indexCurrentSelection;
	indexCurrentSelection = m_listBoxUtilisateur.GetCurSel();

	if (indexCurrentSelection != LB_ERR)
	{
		m_nIndiceListBox = indexCurrentSelection;
		
		if ((m_pDoc->peutModifierDroitUtilisateur() == true) &&
        (GetNomLoginCourant() != m_pDoc->GetNomUtilisateurCourant()))
			m_buttonModifier.EnableWindow(TRUE);
    else
			m_buttonModifier.EnableWindow(FALSE);


		if ((m_pDoc->peutSupprimerUtilisateur() == true) &&
        (GetNomLoginCourant() != m_pDoc->GetNomUtilisateurCourant()))
			m_buttonEffacer.EnableWindow(TRUE);
    else
			m_buttonEffacer.EnableWindow(FALSE);
	}
	else
	{
		m_nIndiceListBox = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}


CString CRechercheUtilisateurDialog::GetNomLoginCourant()
{
  CString nomRetour;
  m_listBoxUtilisateur.GetText(m_nIndiceListBox, nomRetour);
  return nomRetour;
}
