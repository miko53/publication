// PropPageAjouterPubFile.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropPageAjouterPubFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubFile property page

IMPLEMENT_DYNCREATE(CPropPageAjouterPubFile, CPropertyPage)

CPropPageAjouterPubFile::CPropPageAjouterPubFile() : CPropertyPage(CPropPageAjouterPubFile::IDD)
{
	//{{AFX_DATA_INIT(CPropPageAjouterPubFile)
	m_CheckLink = FALSE;
	m_stringFilename = _T("");
	//}}AFX_DATA_INIT
}

CPropPageAjouterPubFile::~CPropPageAjouterPubFile()
{
}

void CPropPageAjouterPubFile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageAjouterPubFile)
	DDX_Control(pDX, IDC_SEARCH_FICHIER, m_ButtonRechercheFilename);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_editFilename);
	DDX_Check(pDX, IDC_CHECK_LINK, m_CheckLink);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_stringFilename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageAjouterPubFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageAjouterPubFile)
	ON_BN_CLICKED(IDC_SEARCH_FICHIER, OnSearchFichier)
	ON_BN_CLICKED(IDC_CHECK_LINK, OnCheckLink)
	ON_EN_CHANGE(IDC_EDIT_FILENAME, OnChangeEditFilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubFile message handlers

BOOL CPropPageAjouterPubFile::OnSetActive() 
{
	peutContinuer();

	return CPropertyPage::OnSetActive();
}


void CPropPageAjouterPubFile::AddDocument(CPublicationDoc * pDoc)
{
	m_pDoc = pDoc;
}


void CPropPageAjouterPubFile::OnSearchFichier() 
{
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_stringFilename = dlg.GetPathName();
	}

	UpdateData(FALSE);

	peutContinuer();
}


void CPropPageAjouterPubFile::OnCheckLink() 
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

	peutContinuer();
}


BOOL CPropPageAjouterPubFile::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_CheckLink = FALSE;

	m_editFilename.EnableWindow(FALSE);
	m_ButtonRechercheFilename.EnableWindow(FALSE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CPropPageAjouterPubFile::peutContinuer()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	ASSERT_KINDOF(CPropertySheet, pSheet);

	UpdateData();

	if ((m_CheckLink == FALSE) ||
		(m_stringFilename != _T("")))
	{
		pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
		return true;
	}
	else
	{
		pSheet->SetWizardButtons(PSWIZB_BACK);
		return false;
	}
}

void CPropPageAjouterPubFile::OnChangeEditFilename() 
{
	peutContinuer();
}
