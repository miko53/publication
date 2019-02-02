// RechercheGenre.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheGenre.h"
#include "AjouterGenreDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheGenre dialog


CRechercheGenre::CRechercheGenre(CPublicationDoc* pdoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheGenre::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheGenre)
	m_ValueGenre = _T("");
	//}}AFX_DATA_INIT

	ASSERT(pdoc != NULL);

	m_pDoc = pdoc;

	m_genreIDCourant = -1;

}


void CRechercheGenre::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheGenre)
	DDX_Control(pDX, IDC_MODIFIER, m_buttonModifier);
	DDX_Control(pDX, IDC_LIST_GENRE, m_ListGenre);
	DDX_Control(pDX, IDC_EFFACER, m_buttonEffacer);
	DDX_Text(pDX, IDC_NomGenre, m_ValueGenre);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheGenre, CDialog)
	//{{AFX_MSG_MAP(CRechercheGenre)
	ON_BN_CLICKED(IDC_EFFACER, OnEffacerGenre)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_BN_CLICKED(IDC_MODIFIER, OnModifierGenre)
	ON_LBN_SELCHANGE(IDC_LIST_GENRE, OnSelchangeListGenre)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheGenre message handlers

void CRechercheGenre::OnEffacerGenre() 
{
	if (AfxMessageBox(_T("Etes-vous sur de vouloir effacer ce genre ?"), (MB_YESNO | MB_ICONQUESTION)) == IDYES)
		m_pDoc->effacerGenre(m_genreIDCourant);

	//OnLancerecherche();
}

void CRechercheGenre::OnLancerecherche() 
{
	UpdateData(TRUE);

	if (m_ValueGenre != "")
	{
		m_pDoc->rechercheGenre(m_ListGenre, m_ValueGenre);
		m_genreIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}

void CRechercheGenre::OnModifierGenre() 
{
	CAjouterGenreDialog ajoutGenre(o_OUVERTURE_PAR_RECHERCHE, m_genreIDCourant, m_pDoc);
	ajoutGenre.DoModal();

	//OnLancerecherche();
}

void CRechercheGenre::OnSelchangeListGenre() 
{
	int indexCurrentSelection;

	//CListBox
	indexCurrentSelection = m_ListGenre.GetCurSel();

	if (indexCurrentSelection != LB_ERR)
	{
		m_genreIDCourant = (long) m_ListGenre.GetItemData(indexCurrentSelection);
		
		if (m_pDoc->peutModifierBase() == true)
			m_buttonModifier.EnableWindow(TRUE);

		if (m_pDoc->peutSupprimerElement() == true)
			m_buttonEffacer.EnableWindow(TRUE);
	}
	else
	{
		m_genreIDCourant = -1;
		m_buttonModifier.EnableWindow(FALSE);
		m_buttonEffacer.EnableWindow(FALSE);
	}
}
