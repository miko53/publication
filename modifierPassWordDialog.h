#if !defined(AFX_MODIFIERPASSWORDDIALOG_H__3969B286_E653_11D5_90A3_9B5937D51D5D__INCLUDED_)
#define AFX_MODIFIERPASSWORDDIALOG_H__3969B286_E653_11D5_90A3_9B5937D51D5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// modifierPassWordDialog.h : header file
//

#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CmodifierPassWordDialog dialog

class CmodifierPassWordDialog : public CDialog
{
// Construction
public:
	CmodifierPassWordDialog(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CmodifierPassWordDialog)
	enum { IDD = IDD_MODIFIER_PASSWORD };
	CString	m_sAncienPassWord;
	CString	m_sNouveauPassWord1;
	CString	m_sNouveauPassWord2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CmodifierPassWordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CmodifierPassWordDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFIERPASSWORDDIALOG_H__3969B286_E653_11D5_90A3_9B5937D51D5D__INCLUDED_)
