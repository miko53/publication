// AjouterSujetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "AjouterSujetDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjouterSujetDialog dialog


CAjouterSujetDialog::CAjouterSujetDialog(unsigned char typeOuverture, long IDSujet, CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CAjouterSujetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjouterSujetDialog)
	m_valeurSujet = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;
	m_appel = typeOuverture;
	m_IdSujetActuel = IDSujet;

}


void CAjouterSujetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjouterSujetDialog)
	DDX_Control(pDX, IDC_SUJET_NAME, m_editSujet);
	DDX_Control(pDX, IDADD, m_buttonAjouter);
	DDX_Control(pDX, IDMODIFY, m_buttonModifier);
	DDX_Control(pDX, IDNOUVEAU, m_buttonNouveau);
	DDX_Text(pDX, IDC_SUJET_NAME, m_valeurSujet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjouterSujetDialog, CDialog)
	//{{AFX_MSG_MAP(CAjouterSujetDialog)
	ON_BN_CLICKED(IDADD, OnAjouterSujet)
	ON_BN_CLICKED(IDMODIFY, OnModificationSujet)
	ON_BN_CLICKED(IDNOUVEAU, OnNouveauSujet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjouterSujetDialog message handlers

BOOL CAjouterSujetDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// mettre a jour les controles 
	if (m_appel == o_OUVERTURE_NORMAL)
	{
		m_buttonAjouter.EnableWindow(TRUE);
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonNouveau.EnableWindow(FALSE);
		m_editSujet.EnableWindow(TRUE);
	}
	else
	{
		OnModificationSujet();
		m_pDoc->rechercheSujet(m_valeurSujet, m_IdSujetActuel);
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAjouterSujetDialog::OnAjouterSujet() 
{
	CString valueTextWindow;
	bool ok = false;
	long idSujet;

	m_buttonAjouter.GetWindowText(valueTextWindow);
	UpdateData(TRUE);

	if (m_valeurSujet == "")
	{
		AfxMessageBox(_T("Il faut donner un nom au sujet !"));
		return;
	}


	if (valueTextWindow != "Mettre à jour")
	{
		// ajouter
		idSujet = m_pDoc->ajouterSujet(&ok, m_valeurSujet);

		if (ok == true)
			m_IdSujetActuel = idSujet;
	}
	else
	{
		// modifier
		ok = m_pDoc->modifierSujet(m_IdSujetActuel, m_valeurSujet);
	}

	if (ok == true)
	{
		m_buttonAjouter.EnableWindow(FALSE);
		m_buttonModifier.EnableWindow(TRUE);
		m_buttonNouveau.EnableWindow(TRUE);
		m_editSujet.EnableWindow(FALSE);
	}
}


void CAjouterSujetDialog::OnModificationSujet() 
{
	m_buttonAjouter.SetWindowText("Mettre à jour");
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(TRUE);

	m_editSujet.EnableWindow(TRUE);
}


void CAjouterSujetDialog::OnNouveauSujet() 
{
	m_editSujet.EnableWindow(TRUE);
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(FALSE);
	m_buttonAjouter.SetWindowText("Ajouter");

	m_valeurSujet = "";
	UpdateData(FALSE);
}
