#if !defined(AFX_PROPINFORESUME_H__6D07C08D_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
#define AFX_PROPINFORESUME_H__6D07C08D_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropInfoResume.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropInfoResume dialog

class CPropInfoResume : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropInfoResume)

// Construction
public:
	void DocumentModifier(void);
	void AddDocument(CPublicationDoc * pDoc);
	CPropInfoResume();
	~CPropInfoResume();

// Dialog Data
	//{{AFX_DATA(CPropInfoResume)
	enum { IDD = IDD_AJOUTER_PUBLICATION_3BIS };
	CString	m_stringResume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropInfoResume)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropInfoResume)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditResumeDoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPublicationDoc * m_pDoc;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPINFORESUME_H__6D07C08D_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
