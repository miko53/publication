// PropPagePubFileOpen.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropPagePubFileOpen.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPagePubFileOpen property page

IMPLEMENT_DYNCREATE(CPropPagePubFileOpen, CPropertyPage)

CPropPagePubFileOpen::CPropPagePubFileOpen() : CPropertyPage(CPropPagePubFileOpen::IDD)
{
	//{{AFX_DATA_INIT(CPropPagePubFileOpen)
	m_stringFilename = _T("");
	m_CheckLink = FALSE;
	m_stringFilenameBase = _T("");
	//}}AFX_DATA_INIT
}

CPropPagePubFileOpen::~CPropPagePubFileOpen()
{
}

void CPropPagePubFileOpen::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPagePubFileOpen)
	DDX_Control(pDX, IDC_BUTTON_OUVRIR, m_ButtonOuvrir);
	DDX_Control(pDX, IDC_SEARCH_FICHIER, m_ButtonRechercheFilename);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_editFilename);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_stringFilename);
	DDX_Check(pDX, IDC_CHECK_LINK, m_CheckLink);
	DDX_Text(pDX, IDC_EDIT_FILENAME_BASE, m_stringFilenameBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPagePubFileOpen, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPagePubFileOpen)
	ON_BN_CLICKED(IDC_SEARCH_FICHIER, OnSearchFichier)
	ON_BN_CLICKED(IDC_CHECK_LINK, OnCheckLink)
	ON_BN_CLICKED(IDC_BUTTON_OUVRIR, OnButtonOuvrir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPagePubFileOpen message handlers

void CPropPagePubFileOpen::AddDocument(CPublicationDoc * pDoc)
{
  m_pDoc = pDoc;
}

void CPropPagePubFileOpen::OnSearchFichier() 
{
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_stringFilename = dlg.GetPathName();
	}

	UpdateData(FALSE);

}

BOOL CPropPagePubFileOpen::OnInitDialog() 
{
	CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

	CPropertyPage::OnInitDialog();

	if (pSheet->m_bFichierValide == TRUE)
	{
		m_stringFilenameBase = (pSheet->m_donneesDocument).nomFichier;
  	m_ButtonOuvrir.EnableWindow(TRUE);
  }
  else
  {
		m_stringFilenameBase = "aucun fichier";
  	m_ButtonOuvrir.EnableWindow(FALSE);
  }

  m_CheckLink = FALSE;
	m_editFilename.EnableWindow(FALSE);
	m_ButtonRechercheFilename.EnableWindow(FALSE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropPagePubFileOpen::OnCheckLink() 
{
	if (m_CheckLink == FALSE)
	{
		m_CheckLink = TRUE;
		m_editFilename.EnableWindow(TRUE);
		m_ButtonRechercheFilename.EnableWindow(TRUE);
	}
	else
	{
		m_CheckLink = FALSE;
		m_editFilename.EnableWindow(FALSE);
		m_ButtonRechercheFilename.EnableWindow(FALSE);
	}

	DocumentModifier();
}

void CPropPagePubFileOpen::DocumentModifier()
{
  CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

  SetModified();
  pSheet->m_bDocModifier = true;
  pSheet->m_bFichierModifier = true;
}

void CPropPagePubFileOpen::MettreAjourDonnees(BOOL bFichierValide, CString sNomFichier)
{
//	CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
//	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

	if (bFichierValide == TRUE)
	{
		m_stringFilenameBase = sNomFichier;
  	m_ButtonOuvrir.EnableWindow(TRUE);
  }
  else
  {
		m_stringFilenameBase = "aucun fichier";
  	m_ButtonOuvrir.EnableWindow(FALSE);
  }

  m_CheckLink = FALSE;
	m_editFilename.EnableWindow(FALSE);
  m_stringFilename ="";
	m_ButtonRechercheFilename.EnableWindow(FALSE);

	UpdateData(FALSE);
}

void CPropPagePubFileOpen::OnButtonOuvrir() 
{
  ShellExecute(this->m_hWnd, "open", m_stringFilenameBase, NULL, NULL, SW_SHOWNORMAL);
}
