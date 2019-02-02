#if !defined(AFX_PROPPAGEAJOUTERPUBRESUME_H__9EFFC764_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
#define AFX_PROPPAGEAJOUTERPUBRESUME_H__9EFFC764_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPageAjouterPubResume.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubResume dialog

class CPropPageAjouterPubResume : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageAjouterPubResume)

// Construction
public:
	virtual void AddDocument(CPublicationDoc* pDoc);
	CPropPageAjouterPubResume();
	~CPropPageAjouterPubResume();

// Dialog Data
	//{{AFX_DATA(CPropPageAjouterPubResume)
	enum { IDD = IDD_AJOUTER_PUBLICATION_3 };
	CString	m_stringResume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageAjouterPubResume)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageAjouterPubResume)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEAJOUTERPUBRESUME_H__9EFFC764_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
