#if !defined(AFX_RECHERCHEAUTEUR_H__076F05EA_8916_11D5_90A3_906605BF231B__INCLUDED_)
#define AFX_RECHERCHEAUTEUR_H__076F05EA_8916_11D5_90A3_906605BF231B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheAuteur.h : header file
//
#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CRechercheAuteur dialog

class CRechercheAuteur : public CDialog
{
// Construction
public:
	CRechercheAuteur(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheAuteur)
	enum { IDD = IDD_RECHERCHE_AUTEUR };
	CButton	m_buttonModifer;
	CButton	m_buttonEffacer;
	CComboBox	m_NationaliteCtrl;
	CEdit	m_PrenomAuteurCtrl;
	CEdit	m_NomAuteurCtrl;
	CListCtrl	m_ListAuteurCtrl;
	BOOL	m_CheckPrenom;
	BOOL	m_CheckNationalite;
	BOOL	m_CheckNom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheAuteur)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheAuteur)
	virtual BOOL OnInitDialog();
	afx_msg void OnCocheNom();
	afx_msg void OnCochePrenom();
	afx_msg void OnCocheNation();
	afx_msg void OnLancerecherche();
	afx_msg void OnItemchangedListAuteur(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickButtonEffacer();
	afx_msg void OnClickButtonModifier();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_itemSelectionne;
	CPublicationDoc* m_pDocument;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHEAUTEUR_H__076F05EA_8916_11D5_90A3_906605BF231B__INCLUDED_)
