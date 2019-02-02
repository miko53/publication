// RechercheMotClef.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheMotClef.h"
#include "AjouterMotClefDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheMotClef dialog


CRechercheMotClef::CRechercheMotClef(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheMotClef::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheMotClef)
	m_valueKeyName = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;

	m_motClefIDCourant = -1;
}


void CRechercheMotClef::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheMotClef)
	DDX_Control(pDX, IDC_LIST_KEYNAME, m_ListKeyName);
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifier);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Text(pDX, IDC_NomKeyName, m_valueKeyName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheMotClef, CDialog)
	//{{AFX_MSG_MAP(CRechercheMotClef)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_BN_CLICKED(IDC_EFFACER, OnEffacerMotClef)
	ON_BN_CLICKED(IDC_MODIFIER, OnModifierMotClef)
	ON_LBN_SELCHANGE(IDC_LIST_KEYNAME, OnSelchangeListKeyname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheMotClef message handlers

void CRechercheMotClef::OnLancerecherche() 
{
	UpdateData(TRUE);

	if (m_valueKeyName != "")
	{
		m_pDoc->rechercheMotClef(m_ListKeyName, m_valueKeyName);
		m_motClefIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}

void CRechercheMotClef::OnEffacerMotClef() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer ce mot clef ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
		m_pDoc->effacerMotClef(m_motClefIDCourant);

	//OnLancerecherche();
}

void CRechercheMotClef::OnModifierMotClef() 
{
	CAjouterMotClefDialog ajoutKeyName(o_OUVERTURE_PAR_RECHERCHE, m_motClefIDCourant, m_pDoc);
	ajoutKeyName.DoModal();

	//OnLancerecherche();
}

void CRechercheMotClef::OnSelchangeListKeyname() 
{
	int indexCurrentSelection;

	//CListBox
	indexCurrentSelection = m_ListKeyName.GetCurSel();

	if (indexCurrentSelection != LB_ERR)
	{
		m_motClefIDCourant = (long) m_ListKeyName.GetItemData(indexCurrentSelection);
		
		if (m_pDoc->peutModifierBase() == true)
			m_buttonModifier.EnableWindow(TRUE);

		if (m_pDoc->peutSupprimerElement() == true)
			m_buttonEffacer.EnableWindow(TRUE);
	}
	else
	{
		m_motClefIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}
