// PropInfoResume.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropInfoResume.h"
#include "ModifierPublicationPropSheet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropInfoResume property page

IMPLEMENT_DYNCREATE(CPropInfoResume, CPropertyPage)

CPropInfoResume::CPropInfoResume() : CPropertyPage(CPropInfoResume::IDD)
{
	//{{AFX_DATA_INIT(CPropInfoResume)
	m_stringResume = _T("");
	//}}AFX_DATA_INIT
}

CPropInfoResume::~CPropInfoResume()
{
}

void CPropInfoResume::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropInfoResume)
	DDX_Text(pDX, IDC_EDIT_RESUME_DOC, m_stringResume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropInfoResume, CPropertyPage)
	//{{AFX_MSG_MAP(CPropInfoResume)
	ON_EN_CHANGE(IDC_EDIT_RESUME_DOC, OnChangeEditResumeDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CPropInfoResume::AddDocument(CPublicationDoc * pDoc)
{
  m_pDoc = pDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CPropInfoResume message handlers

BOOL CPropInfoResume::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

	m_stringResume = (pSheet->m_donneesDocument).resume;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropInfoResume::OnChangeEditResumeDoc() 
{
	DocumentModifier();
}

void CPropInfoResume::DocumentModifier()
{
  CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

  SetModified();
  pSheet->m_bDocModifier = true;
  pSheet->m_bResumeModifer = true;
}
