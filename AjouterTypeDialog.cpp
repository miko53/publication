// AjouterTypeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "AjouterTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjouterTypeDialog dialog


CAjouterTypeDialog::CAjouterTypeDialog(unsigned char typeOuverture, long IDType, CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CAjouterTypeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjouterTypeDialog)
	m_valueType = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);
	m_pDoc = pDoc;
	m_appel = typeOuverture;
	m_currentIDType = IDType;

}


void CAjouterTypeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjouterTypeDialog)
	DDX_Control(pDX, IDC_TYPE_NAME, m_editType);
	DDX_Control(pDX, IDADD, m_buttonAjouter);
	DDX_Control(pDX, IDMODIFY, m_buttonModifier);
	DDX_Control(pDX, IDNOUVEAU, m_buttonNouveau);
	DDX_Text(pDX, IDC_TYPE_NAME, m_valueType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjouterTypeDialog, CDialog)
	//{{AFX_MSG_MAP(CAjouterTypeDialog)
	ON_BN_CLICKED(IDADD, OnAjouterType)
	ON_BN_CLICKED(IDMODIFY, OnModifierType)
	ON_BN_CLICKED(IDNOUVEAU, OnNouveauType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjouterTypeDialog message handlers

BOOL CAjouterTypeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// mettre a jour les controles 
	if (m_appel == o_OUVERTURE_NORMAL)
	{
		m_buttonAjouter.EnableWindow(TRUE);
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonNouveau.EnableWindow(FALSE);
		m_editType.EnableWindow(TRUE);
	}
	else
	{
		OnModifierType();
		m_pDoc->rechercheType(m_valueType, m_currentIDType);
		UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAjouterTypeDialog::OnAjouterType() 
{
	CString valueTextWindow;
	bool ok = false;
	long idType;

	m_buttonAjouter.GetWindowText(valueTextWindow);
	UpdateData(TRUE);

	if (m_valueType == "")
	{
		AfxMessageBox(_T("Il faut donner un nom au type !"));
		return;
	}


	if (valueTextWindow != "Mettre à jour")
	{
		// ajouter
		idType = m_pDoc->ajouterType(&ok, m_valueType);

		if (ok == true)
			m_currentIDType = idType;
	}
	else
	{
		// modifier
		ok = m_pDoc->modifierType(m_currentIDType, m_valueType);
	}

	if (ok == true)
	{
		m_buttonAjouter.EnableWindow(FALSE);
		m_buttonModifier.EnableWindow(TRUE);
		m_buttonNouveau.EnableWindow(TRUE);
		m_editType.EnableWindow(FALSE);
	}}

void CAjouterTypeDialog::OnModifierType() 
{
	m_buttonAjouter.SetWindowText("Mettre à jour");
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(TRUE);

	m_editType.EnableWindow(TRUE);
}

void CAjouterTypeDialog::OnNouveauType() 
{
	m_editType.EnableWindow(TRUE);
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(FALSE);
	m_buttonAjouter.SetWindowText("Ajouter");

	m_valueType = "";
	UpdateData(FALSE);
}
