#if !defined(AFX_PROGRESSDIALOG_H__85855E44_52EB_11D5_90A3_FB8407057A56__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__85855E44_52EB_11D5_90A3_FB8407057A56__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ProgressDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog

class CProgressDialog : public CDialog
{
// Construction
public:
	CProgressDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDialog)
	enum { IDD = IDD_WAIT_DIALOG };
	CStatic	m_actionActuel;
	CProgressCtrl	m_progressCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__85855E44_52EB_11D5_90A3_FB8407057A56__INCLUDED_)
