// AjouterMotClefDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "AjouterMotClefDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjouterMotClefDialog dialog


CAjouterMotClefDialog::CAjouterMotClefDialog(unsigned char typeOuverture, long IDType, CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CAjouterMotClefDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjouterMotClefDialog)
	m_valueKeyName = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);
	m_pDoc = pDoc;
	m_appel = typeOuverture;
	m_currentIDKeyName = IDType;

}


void CAjouterMotClefDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjouterMotClefDialog)
	DDX_Control(pDX, IDC_KEY_NAME, m_editKeyName);
	DDX_Control(pDX, IDNOUVEAU, m_buttonNouveau);
	DDX_Control(pDX, IDMODIFY, m_buttonModifier);
	DDX_Control(pDX, IDADD, m_buttonAjouter);
	DDX_Text(pDX, IDC_KEY_NAME, m_valueKeyName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjouterMotClefDialog, CDialog)
	//{{AFX_MSG_MAP(CAjouterMotClefDialog)
	ON_BN_CLICKED(IDADD, OnAjouterMotClef)
	ON_BN_CLICKED(IDMODIFY, OnModifierMotClef)
	ON_BN_CLICKED(IDNOUVEAU, OnNouveauMotClef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjouterMotClefDialog message handlers

void CAjouterMotClefDialog::OnAjouterMotClef() 
{
	CString valueTextWindow;
	bool ok = false;
	long idKeyName;

	m_buttonAjouter.GetWindowText(valueTextWindow);
	UpdateData(TRUE);

	if (m_valueKeyName == "")
	{
		AfxMessageBox(_T("Il faut donner un nom au mot clef !"));
		return;
	}


	if (valueTextWindow != "Mettre à jour")
	{
		// ajouter
		idKeyName = m_pDoc->ajouterMotClef(&ok, m_valueKeyName);

		if (ok == true)
			m_currentIDKeyName = idKeyName;
	}
	else
	{
		// modifier
		ok = m_pDoc->modifierMotClef(m_currentIDKeyName, m_valueKeyName);
	}

	if (ok == true)
	{
		m_buttonAjouter.EnableWindow(FALSE);
		m_buttonModifier.EnableWindow(TRUE);
		m_buttonNouveau.EnableWindow(TRUE);
		m_editKeyName.EnableWindow(FALSE);
	}
}

void CAjouterMotClefDialog::OnModifierMotClef() 
{
	m_buttonAjouter.SetWindowText("Mettre à jour");
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(TRUE);

	m_editKeyName.EnableWindow(TRUE);
}

void CAjouterMotClefDialog::OnNouveauMotClef() 
{
	m_editKeyName.EnableWindow(TRUE);
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(FALSE);
	m_buttonAjouter.SetWindowText("Ajouter");

	m_valueKeyName = "";
	UpdateData(FALSE);
}

BOOL CAjouterMotClefDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// mettre a jour les controles 
	if (m_appel == o_OUVERTURE_NORMAL)
	{
		m_buttonAjouter.EnableWindow(TRUE);
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonNouveau.EnableWindow(FALSE);
		m_editKeyName.EnableWindow(TRUE);
	}
	else
	{
		OnModifierMotClef();
		m_pDoc->rechercheMotClef(m_valueKeyName, m_currentIDKeyName);
		UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
