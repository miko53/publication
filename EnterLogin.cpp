// EnterLogin.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "EnterLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterLogin dialog


CEnterLogin::CEnterLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterLogin)
	m_login = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
}


void CEnterLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterLogin)
	DDX_Text(pDX, IDC_LOGIN, m_login);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterLogin, CDialog)
	//{{AFX_MSG_MAP(CEnterLogin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterLogin message handlers
