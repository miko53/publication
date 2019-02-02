#if !defined(AFX_PROPPAGEAJOUTERPUBFILE_H__9EFFC763_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
#define AFX_PROPPAGEAJOUTERPUBFILE_H__9EFFC763_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPageAjouterPubFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubFile dialog

class CPropPageAjouterPubFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageAjouterPubFile)

// Construction
public:
	virtual void AddDocument(CPublicationDoc* pDoc);
	CPropPageAjouterPubFile();
	~CPropPageAjouterPubFile();

// Dialog Data
	//{{AFX_DATA(CPropPageAjouterPubFile)
	enum { IDD = IDD_AJOUTER_PUBLICATION_2 };
	CButton	m_ButtonRechercheFilename;
	CEdit	m_editFilename;
	BOOL	m_CheckLink;
	CString	m_stringFilename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageAjouterPubFile)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageAjouterPubFile)
	afx_msg void OnSearchFichier();
	afx_msg void OnCheckLink();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool peutContinuer();
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEAJOUTERPUBFILE_H__9EFFC763_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
