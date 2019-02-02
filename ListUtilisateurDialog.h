#if !defined(AFX_LISTUTILISATEURDIALOG_H__A4392AE4_E744_11D5_90A3_A3B463377C5D__INCLUDED_)
#define AFX_LISTUTILISATEURDIALOG_H__A4392AE4_E744_11D5_90A3_A3B463377C5D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListUtilisateurDialog.h : header file
//

#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CListUtilisateurDialog dialog

class CListUtilisateurDialog : public CDialog
{
// Construction
public:
	CListUtilisateurDialog(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListUtilisateurDialog)
	enum { IDD = IDD_LISTE_UTILISATEUR };
	CButton	m_buttonModifer;
	CButton	m_buttonEffacer;
	CListCtrl	m_listCtrlUtilisateur;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListUtilisateurDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListUtilisateurDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnModifier();
	afx_msg void OnEffacer();
	afx_msg void OnItemchangedListUtilisateur(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  CPublicationDoc* m_pDoc;
  int m_itemSelectionne;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTUTILISATEURDIALOG_H__A4392AE4_E744_11D5_90A3_A3B463377C5D__INCLUDED_)
