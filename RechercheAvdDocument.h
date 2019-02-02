#if !defined(AFX_RECHERCHEAVDDOCUMENT_H__2F15FFE4_DB82_11D5_90A3_FFFFFF000000__INCLUDED_)
#define AFX_RECHERCHEAVDDOCUMENT_H__2F15FFE4_DB82_11D5_90A3_FFFFFF000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheAvdDocument.h : header file
//
#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CRechercheAvdDocument dialog

class CRechercheAvdDocument : public CDialog
{
// Construction
public:
	CRechercheAvdDocument(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheAvdDocument)
	enum { IDD = IDD_RECHERCHE_AVANCE_DOCUMENT };
	CButton	m_buttonPropriete;
	CButton	m_buttonAfficher;
	CListCtrl	m_listCtrlDocument;
	CListBox	m_listBoxMotClef;
	CComboBox	m_comboBoxNomMotClef;
	CButton	m_buttonAjouterMotClef;
	CButton	m_buttonRetirerMotClef;
	CComboBox	m_comboBoxNomGenre;
	CComboBox	m_comboBoxNomSujet;
	CEdit	m_editNomDocument;
	CComboBox	m_comboBoxNomAuteur;
	BOOL	m_bNomDocument;
	BOOL	m_bNomAuteur;
	BOOL	m_bNomSujet;
	BOOL	m_bNomGenre;
	BOOL	m_bMotClefs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheAvdDocument)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheAvdDocument)
	virtual BOOL OnInitDialog();
	afx_msg void OnCocheNomDocument();
	afx_msg void OnCocheNomAuteur();
	afx_msg void OnCocheNomSujet();
	afx_msg void OnCocheGenre();
	afx_msg void OnCocheMotClef();
	afx_msg void OnLancerecherche();
	afx_msg void OnAjouterMotcles();
	afx_msg void OnRetirerMotcles();
	afx_msg void OnItemchangedListDocument(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAfficher();
	afx_msg void OnClickPropriete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_itemSelectionne;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHEAVDDOCUMENT_H__2F15FFE4_DB82_11D5_90A3_FFFFFF000000__INCLUDED_)
