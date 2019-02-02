#if !defined(AFX_OPTIONBASEDIALOG_H__A5BF8504_F011_11D5_90A3_EB280D91627C__INCLUDED_)
#define AFX_OPTIONBASEDIALOG_H__A5BF8504_F011_11D5_90A3_EB280D91627C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptionBaseDialog.h : header file
//
#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// COptionBaseDialog dialog

class COptionBaseDialog : public CDialog
{
// Construction
public:
	COptionBaseDialog(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionBaseDialog)
	enum { IDD = IDD_OPTION_BASE };
	CEdit	m_editRepertoire;
	CButton	m_buttonUpdate;
	CButton	m_buttonSelectionCat;
	CButton	m_buttonModify;
	CString	m_sNomRepertoire;
	CString	m_sVersion;
	BOOL	m_bCopyDirectory;
	BOOL	m_bEraseAncienRepertoire;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionBaseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionBaseDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnModifyButton();
	afx_msg void OnModifierCat();
	afx_msg void OnUpdateButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONBASEDIALOG_H__A5BF8504_F011_11D5_90A3_EB280D91627C__INCLUDED_)
