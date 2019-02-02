#if !defined(AFX_PROPCATEGORIEDIALOG_H__59346CC4_6E73_11D5_90A3_B65842C4A25E__INCLUDED_)
#define AFX_PROPCATEGORIEDIALOG_H__59346CC4_6E73_11D5_90A3_B65842C4A25E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropCategorieDialog.h : header file
//
#include "PubContainer.h"
#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPropCategorieDialog dialog

class CPropCategorieDialog : public CDialog
{
// Construction
public:
	CPropCategorieDialog(CPubContainer* pCategorie, CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropCategorieDialog)
	enum { IDD = IDD_PROPR_CATEGORIE };
	CButton	m_updateButton;
	CEdit	m_CategorieNameControl;
	CButton	m_modifyButton;
	CString	m_CategorieName;
	CString	m_LoginName;
	CString	m_EntryDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropCategorieDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPublicationDoc* pDocument;
	CPubContainer* pContainer;

	// Generated message map functions
	//{{AFX_MSG(CPropCategorieDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnModifyButtonClick();
	afx_msg void OnUpdateButtonClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPCATEGORIEDIALOG_H__59346CC4_6E73_11D5_90A3_B65842C4A25E__INCLUDED_)
