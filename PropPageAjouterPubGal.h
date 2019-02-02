#if !defined(AFX_PROPPAGEAJOUTERPUBGAL_H__9EFFC762_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
#define AFX_PROPPAGEAJOUTERPUBGAL_H__9EFFC762_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPageAjouterPubGal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubGal dialog

class CPropPageAjouterPubGal : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageAjouterPubGal)

// Construction
public:
	virtual void AddDocument(CPublicationDoc* pDoc);
	CPropPageAjouterPubGal();
	~CPropPageAjouterPubGal();

// Dialog Data
	//{{AFX_DATA(CPropPageAjouterPubGal)
	enum { IDD = IDD_AJOUTER_PUBLICATION_1 };
	CComboBox	m_ComboBoxType;
	CComboBox	m_ComboBoxGenre;
	CComboBox	m_ComboBoxSujet;
	CComboBox	m_ComboBoxAuteur;
	CString	m_StringTitre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageAjouterPubGal)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageAjouterPubGal)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTitreDocument();
	afx_msg void OnSelchangeListAuteur();
	afx_msg void OnSelchangeListeGenre();
	afx_msg void OnSelchangeListeSujet();
	afx_msg void OnSelchangeListeType();
	afx_msg void OnButtonAddAuteur();
	afx_msg void OnButtonAddGenre();
	afx_msg void OnButtonAddSujet();
	afx_msg void OnButtonAddType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool peutContinuer();
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEAJOUTERPUBGAL_H__9EFFC762_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
