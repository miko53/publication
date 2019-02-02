#if !defined(AFX_PROPPAGEPUBFILEOPEN_H__6D07C088_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
#define AFX_PROPPAGEPUBFILEOPEN_H__6D07C088_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPagePubFileOpen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPagePubFileOpen dialog

class CPropPagePubFileOpen : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPagePubFileOpen)

// Construction
public:
	void MettreAjourDonnees(BOOL bFichierValide, CString sNomFichier);
	void DocumentModifier(void);
	void AddDocument(CPublicationDoc * pDoc);
	CPropPagePubFileOpen();
	~CPropPagePubFileOpen();

// Dialog Data
	//{{AFX_DATA(CPropPagePubFileOpen)
	enum { IDD = IDD_AJOUTER_PUBLICATION_2BIS };
	CButton	m_ButtonOuvrir;
	CButton	m_ButtonRechercheFilename;
	CEdit	m_editFilename;
	CString	m_stringFilename;
	BOOL	m_CheckLink;
	CString	m_stringFilenameBase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPagePubFileOpen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPagePubFileOpen)
	afx_msg void OnSearchFichier();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLink();
	afx_msg void OnButtonOuvrir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPublicationDoc * m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEPUBFILEOPEN_H__6D07C088_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
