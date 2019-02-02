// AjouterGenreDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "AjouterGenreDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjouterGenreDialog dialog


CAjouterGenreDialog::CAjouterGenreDialog(unsigned char typeOuverture, long IDGenre, CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CAjouterGenreDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjouterGenreDialog)
	m_valeurGenre = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;
	m_appel = typeOuverture;
	m_IdGenreActuel = IDGenre;

}


void CAjouterGenreDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjouterGenreDialog)
	DDX_Control(pDX, IDNOUVEAU, m_buttonNouveau);
	DDX_Control(pDX, IDMODIFY, m_buttonModifier);
	DDX_Control(pDX, IDC_GENRE_NAME, m_editGenre);
	DDX_Control(pDX, IDADD, m_buttonAjouter);
	DDX_Text(pDX, IDC_GENRE_NAME, m_valeurGenre);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjouterGenreDialog, CDialog)
	//{{AFX_MSG_MAP(CAjouterGenreDialog)
	ON_BN_CLICKED(IDADD, OnAjouterGenre)
	ON_BN_CLICKED(IDMODIFY, OnModificationGenre)
	ON_BN_CLICKED(IDNOUVEAU, OnNouveauGenre)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjouterGenreDialog message handlers

BOOL CAjouterGenreDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// mettre a jour les controles 
	if (m_appel == o_OUVERTURE_NORMAL)
	{
		m_buttonAjouter.EnableWindow(TRUE);
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonNouveau.EnableWindow(FALSE);
		m_editGenre.EnableWindow(TRUE);
	}
	else
	{
		OnModificationGenre();
		m_pDoc->rechercheGenre(m_valeurGenre, m_IdGenreActuel);
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAjouterGenreDialog::OnAjouterGenre() 
{
	CString valueTextWindow;
	bool ok = false;
	long idGenre;

	m_buttonAjouter.GetWindowText(valueTextWindow);
	UpdateData(TRUE);

	if (m_valeurGenre == "")
	{
		AfxMessageBox(_T("Il faut donner un nom au genre !"));
		return;
	}


	if (valueTextWindow != "Mettre à jour")
	{
		// ajouter
		idGenre = m_pDoc->ajouterGenre(&ok, m_valeurGenre);

		if (ok == true)
			m_IdGenreActuel = idGenre;
	}
	else
	{
		// modifier
		ok = m_pDoc->modifierGenre(m_IdGenreActuel, m_valeurGenre);
	}

	if (ok == true)
	{
		m_buttonAjouter.EnableWindow(FALSE);
		m_buttonModifier.EnableWindow(TRUE);
		m_buttonNouveau.EnableWindow(TRUE);
		m_editGenre.EnableWindow(FALSE);
	}
}

void CAjouterGenreDialog::OnModificationGenre() 
{
	m_buttonAjouter.SetWindowText("Mettre à jour");
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(TRUE);

	m_editGenre.EnableWindow(TRUE);
}

void CAjouterGenreDialog::OnNouveauGenre() 
{
	m_editGenre.EnableWindow(TRUE);
	m_buttonAjouter.EnableWindow(TRUE);
	m_buttonModifier.EnableWindow(FALSE);
	m_buttonNouveau.EnableWindow(FALSE);
	m_buttonAjouter.SetWindowText("Ajouter");

	m_valeurGenre = "";
	UpdateData(FALSE);
}
