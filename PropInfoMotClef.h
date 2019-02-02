#if !defined(AFX_PROPINFOMOTCLEF_H__6D07C08E_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
#define AFX_PROPINFOMOTCLEF_H__6D07C08E_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropInfoMotClef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropInfoMotClef dialog

class CPropInfoMotClef : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropInfoMotClef)

// Construction
public:
	void DocumentModifier(void);
	void AddDocument(CPublicationDoc * pDoc);
	CPropInfoMotClef();
	~CPropInfoMotClef();

// Dialog Data
	//{{AFX_DATA(CPropInfoMotClef)
	enum { IDD = IDD_AJOUTER_PUBLICATION_4BIS };
	CListBox	m_ListMotClefPub;
	CListBox	m_ListBoxAllMotClef;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropInfoMotClef)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropInfoMotClef)
	afx_msg void OnAddMotClefs();
	afx_msg void OnDansListePub();
	virtual BOOL OnInitDialog();
	afx_msg void OnRemoveAllElement();
	afx_msg void OnRemoveElementSelectionne();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPublicationDoc * m_pDoc;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPINFOMOTCLEF_H__6D07C08E_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
