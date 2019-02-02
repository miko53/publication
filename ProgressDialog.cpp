// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog


CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Create(IDD_WAIT_DIALOG);
}


void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDialog)
	DDX_Control(pDX, IDC_ACTION, m_actionActuel);
	DDX_Control(pDX, IDC_PROGRES_BAR, m_progressCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
	//{{AFX_MSG_MAP(CProgressDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog message handlers

BOOL CProgressDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_progressCtrl.SetRange(0, 170);  // valeur par defaut = creation d'une base + steip a 10

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
