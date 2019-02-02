// RechercheSujet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheSujet.h"
#include "AjouterSujetDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheSujet dialog


CRechercheSujet::CRechercheSujet(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheSujet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheSujet)
	m_ValueSujet = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;

	m_sujetIDCourant = -1;

}


void CRechercheSujet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheSujet)
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifier);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Control(pDX, IDC_LIST_SUJET, m_ListSujet);
	DDX_Text(pDX, IDC_NomSujet, m_ValueSujet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheSujet, CDialog)
	//{{AFX_MSG_MAP(CRechercheSujet)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_LBN_SELCHANGE(IDC_LIST_SUJET, OnSelectionchangeListSujet)
	ON_BN_CLICKED(IDC_EFFACER, OnEffacerSujet)
	ON_BN_CLICKED(IDC_MODIFIER, OnModifierSujet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheSujet message handlers

void CRechercheSujet::OnLancerecherche() 
{
	UpdateData(TRUE);

	if (m_ValueSujet != "")
	{
		m_pDoc->rechercheSujet(m_ListSujet, m_ValueSujet);
		m_sujetIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}

void CRechercheSujet::OnSelectionchangeListSujet() 
{
	int indexCurrentSelection;

	//CListBox
	indexCurrentSelection = m_ListSujet.GetCurSel();

	if (indexCurrentSelection != LB_ERR)
	{
		m_sujetIDCourant = (long) m_ListSujet.GetItemData(indexCurrentSelection);
		
		if (m_pDoc->peutModifierBase() == true)
			m_buttonModifier.EnableWindow(TRUE);

		if (m_pDoc->peutSupprimerElement() == true)
			m_buttonEffacer.EnableWindow(TRUE);
	}
	else
	{
		m_sujetIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}

void CRechercheSujet::OnEffacerSujet() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer ce sujet ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
		m_pDoc->effacerSujet(m_sujetIDCourant);

	//OnLancerecherche();
}

void CRechercheSujet::OnModifierSujet() 
{
	CAjouterSujetDialog ajoutSujet(o_OUVERTURE_PAR_RECHERCHE, m_sujetIDCourant, m_pDoc);
	ajoutSujet.DoModal();

	//OnLancerecherche();
}
