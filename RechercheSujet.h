#if !defined(AFX_RECHERCHESUJET_H__9EACA784_9BEC_11D5_90A3_F97CCD10F80E__INCLUDED_)
#define AFX_RECHERCHESUJET_H__9EACA784_9BEC_11D5_90A3_F97CCD10F80E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheSujet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRechercheSujet dialog

class CRechercheSujet : public CDialog
{
// Construction
public:
	CRechercheSujet(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheSujet)
	enum { IDD = IDD_RECHERCHE_SUJET };
	CButton	m_buttonModifier;
	CButton	m_buttonEffacer;
	CListBox	m_ListSujet;
	CString	m_ValueSujet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheSujet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheSujet)
	afx_msg void OnLancerecherche();
	afx_msg void OnSelectionchangeListSujet();
	afx_msg void OnEffacerSujet();
	afx_msg void OnModifierSujet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_sujetIDCourant;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHESUJET_H__9EACA784_9BEC_11D5_90A3_F97CCD10F80E__INCLUDED_)
