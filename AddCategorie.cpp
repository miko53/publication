// AddCategorie.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "AddCategorie.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddCategorie dialog


CAddCategorie::CAddCategorie(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCategorie::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddCategorie)
	m_categorieName = _T("");
	//}}AFX_DATA_INIT
}


void CAddCategorie::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddCategorie)
	DDX_Text(pDX, IDC_ADDCATEGORIE, m_categorieName);
	DDV_MaxChars(pDX, m_categorieName, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddCategorie, CDialog)
	//{{AFX_MSG_MAP(CAddCategorie)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddCategorie message handlers
