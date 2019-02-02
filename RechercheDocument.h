#if !defined(AFX_RECHERCHEDOCUMENT_H__6788E207_D2E7_11D5_90A3_AE7E5305394C__INCLUDED_)
#define AFX_RECHERCHEDOCUMENT_H__6788E207_D2E7_11D5_90A3_AE7E5305394C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheDocument.h : header file
//

#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CRechercheDocument dialog

class CRechercheDocument : public CDialog
{
// Construction
public:
	CRechercheDocument(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheDocument)
	enum { IDD = IDD_RECHERCHE_DOCUMENT };
	CButton	m_buttonAfficher;
	CButton	m_buttonPropriete;
	CListCtrl	m_listCtrlDocument;
	CEdit	m_editNomLogin;
	CComboBox	m_comboBoxNomType;
	CComboBox	m_comboBoxNomGenre;
	CComboBox	m_comboBoxNomSujet;
	CComboBox	m_comboBoxNomAuteur;
	CEdit	m_editNomDocument;
	BOOL	m_bNomDocument;
	BOOL	m_bNomAuteur;
	BOOL	m_bNomSujet;
	BOOL	m_bNomGenre;
	BOOL	m_bNomType;
	BOOL	m_bNomLogin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheDocument)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheDocument)
	virtual BOOL OnInitDialog();
	afx_msg void OnCocheNomDocument();
	afx_msg void OnCocheNomAuteur();
	afx_msg void OnCocheSujet();
	afx_msg void OnCocheGenre();
	afx_msg void OnCocheType();
	afx_msg void OnCocheLogin();
	afx_msg void OnLancerecherche();
	afx_msg void OnItemchangedListDocument(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickPropriete();
	afx_msg void OnClickAfficher();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_itemSelectionne;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHEDOCUMENT_H__6788E207_D2E7_11D5_90A3_AE7E5305394C__INCLUDED_)
