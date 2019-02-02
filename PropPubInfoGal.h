#if !defined(AFX_PROPPUBINFOGAL_H__6D07C08C_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
#define AFX_PROPPUBINFOGAL_H__6D07C08C_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPubInfoGal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPubInfoGal dialog

class CPropPubInfoGal : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPubInfoGal)

// Construction
public:
	bool VerifierDonnees(void);
	void DocumentModifier(void);
	void AddDocument(CPublicationDoc * pDoc);
	CPropPubInfoGal();
	~CPropPubInfoGal();

// Dialog Data
	//{{AFX_DATA(CPropPubInfoGal)
	enum { IDD = IDD_AJOUTER_PUBLICATION_1BIS };
	CComboBox	m_ComboBoxType;
	CComboBox	m_ComboBoxSujet;
	CComboBox	m_ComboBoxGenre;
	CComboBox	m_ComboBoxAuteur;
	CString	m_stringTitre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPubInfoGal)
	public:
	virtual BOOL OnApply();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPubInfoGal)
	afx_msg void OnButtonAddAuteur();
	afx_msg void OnButtonAddGenre();
	afx_msg void OnButtonAddSujet();
	afx_msg void OnButtonAddType();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTitreDocument();
	afx_msg void OnSelchangeListAuteur();
	afx_msg void OnSelchangeListeGenre();
	afx_msg void OnSelchangeListeSujet();
	afx_msg void OnSelchangeListeType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPublicationDoc * m_pDoc;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPUBINFOGAL_H__6D07C08C_B4E6_11D5_90A3_E1C6BFF53359__INCLUDED_)
