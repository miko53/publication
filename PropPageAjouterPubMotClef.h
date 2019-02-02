#if !defined(AFX_PROPPAGEAJOUTERPUBMOTCLEF_H__9EFFC765_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
#define AFX_PROPPAGEAJOUTERPUBMOTCLEF_H__9EFFC765_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPageAjouterPubMotClef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubMotClef dialog

class CPropPageAjouterPubMotClef : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageAjouterPubMotClef)

// Construction
public:
	virtual void AddDocument(CPublicationDoc* pDoc);
	CPropPageAjouterPubMotClef();
	~CPropPageAjouterPubMotClef();

// Dialog Data
	//{{AFX_DATA(CPropPageAjouterPubMotClef)
	enum { IDD = IDD_AJOUTER_PUBLICATION_4 };
	CListBox	m_ListMotClefPub;
	CListBox	m_ListBoxAllMotClef;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageAjouterPubMotClef)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageAjouterPubMotClef)
	virtual BOOL OnInitDialog();
	afx_msg void OnDansListePub();
	afx_msg void OnRemoveAllElement();
	afx_msg void OnRemoveElementSelectionne();
	afx_msg void OnAddMotClefs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEAJOUTERPUBMOTCLEF_H__9EFFC765_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
