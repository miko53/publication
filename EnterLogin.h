#if !defined(AFX_ENTERLOGIN_H__2E659267_6272_11D5_90A3_DAF6D16A305B__INCLUDED_)
#define AFX_ENTERLOGIN_H__2E659267_6272_11D5_90A3_DAF6D16A305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EnterLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterLogin dialog

class CEnterLogin : public CDialog
{
// Construction
public:
	CEnterLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterLogin)
	enum { IDD = IDD_LOGIN };
	CString	m_login;
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterLogin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTERLOGIN_H__2E659267_6272_11D5_90A3_DAF6D16A305B__INCLUDED_)
