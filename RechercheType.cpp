// RechercheType.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheType.h"
#include "AjouterTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheType dialog


CRechercheType::CRechercheType(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheType)
	m_ValueType = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;

	m_typeIDCourant = -1;

}


void CRechercheType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheType)
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifier);
	DDX_Control(pDX, IDC_LIST_TYPE, m_ListType);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Text(pDX, IDC_NomType, m_ValueType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheType, CDialog)
	//{{AFX_MSG_MAP(CRechercheType)
	ON_BN_CLICKED(IDC_EFFACER, OnEffacerType)
	ON_BN_CLICKED(IDC_MODIFIER, OnModifierType)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_LBN_SELCHANGE(IDC_LIST_TYPE, OnSelchangeListType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheType message handlers

void CRechercheType::OnEffacerType() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer ce type de document ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
		m_pDoc->effacerType(m_typeIDCourant);

	//OnLancerecherche();
}

void CRechercheType::OnModifierType() 
{
	CAjouterTypeDialog ajoutType(o_OUVERTURE_PAR_RECHERCHE, m_typeIDCourant, m_pDoc);
	ajoutType.DoModal();

	//OnLancerecherche();
}

void CRechercheType::OnLancerecherche() 
{
	UpdateData(TRUE);

	if (m_ValueType != "")
	{
		m_pDoc->rechercheType(m_ListType, m_ValueType);
		m_typeIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}

void CRechercheType::OnSelchangeListType() 
{
	int indexCurrentSelection;

	indexCurrentSelection = m_ListType.GetCurSel();

	if (indexCurrentSelection != LB_ERR)
	{
		m_typeIDCourant = (long) m_ListType.GetItemData(indexCurrentSelection);
		
		if (m_pDoc->peutModifierBase() == true)
			m_buttonModifier.EnableWindow(TRUE);

		if (m_pDoc->peutSupprimerElement() == true)
			m_buttonEffacer.EnableWindow(TRUE);
	}
	else
	{
		m_typeIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}
