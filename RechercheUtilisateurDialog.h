#if !defined(AFX_RECHERCHEUTILISATEURDIALOG_H__652354E4_E1A7_11D5_90A3_E6D861667E49__INCLUDED_)
#define AFX_RECHERCHEUTILISATEURDIALOG_H__652354E4_E1A7_11D5_90A3_E6D861667E49__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheUtilisateurDialog.h : header file
//

#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CRechercheUtilisateurDialog dialog

class CRechercheUtilisateurDialog : public CDialog
{
// Construction
public:
	CRechercheUtilisateurDialog(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheUtilisateurDialog)
	enum { IDD = IDD_RECHERCHE_UTILISATEUR };
	CListBox	m_listBoxUtilisateur;
	CButton	m_buttonEffacer;
	CButton	m_buttonModifier;
	CString	m_sNomLogin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheUtilisateurDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  CString GetNomLoginCourant(void);
	// Generated message map functions
	//{{AFX_MSG(CRechercheUtilisateurDialog)
	afx_msg void OnEffacerUtilisateur();
	afx_msg void OnLancerecherche();
	afx_msg void OnModifierUtlisateur();
	afx_msg void OnSelchangeListUtilisateur();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nIndiceListBox;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHEUTILISATEURDIALOG_H__652354E4_E1A7_11D5_90A3_E6D861667E49__INCLUDED_)
