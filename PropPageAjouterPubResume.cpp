// PropPageAjouterPubResume.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropPageAjouterPubResume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubResume property page

IMPLEMENT_DYNCREATE(CPropPageAjouterPubResume, CPropertyPage)

CPropPageAjouterPubResume::CPropPageAjouterPubResume() : CPropertyPage(CPropPageAjouterPubResume::IDD)
{
	//{{AFX_DATA_INIT(CPropPageAjouterPubResume)
	m_stringResume = _T("");
	//}}AFX_DATA_INIT
}

CPropPageAjouterPubResume::~CPropPageAjouterPubResume()
{
}

void CPropPageAjouterPubResume::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageAjouterPubResume)
	DDX_Text(pDX, IDC_EDIT_RESUME_DOC, m_stringResume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageAjouterPubResume, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageAjouterPubResume)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubResume message handlers

BOOL CPropPageAjouterPubResume::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	ASSERT_KINDOF(CPropertySheet, pSheet);
	
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	
	return CPropertyPage::OnSetActive();
}

void CPropPageAjouterPubResume::AddDocument(CPublicationDoc * pDoc)
{
	m_pDoc = pDoc;
}
