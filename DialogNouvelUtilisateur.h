#if !defined(AFX_DIALOGNOUVELUTILISATEUR_H__2918E984_DC5F_11D5_90A3_BBAF88E6499F__INCLUDED_)
#define AFX_DIALOGNOUVELUTILISATEUR_H__2918E984_DC5F_11D5_90A3_BBAF88E6499F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogNouvelUtilisateur.h : header file
//

#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogNouvelUtilisateur dialog

class CDialogNouvelUtilisateur : public CDialog
{
// Construction
public:
	CDialogNouvelUtilisateur(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogNouvelUtilisateur)
	enum { IDD = IDD_NEW_UTILISATEUR };
	CButton	m_buttonModifDroitUtilisateur;
	CButton	m_buttonSupprElement;
	CButton	m_buttonSupprUtilisateur;
	CButton	m_buttonPropBase;
	CButton	m_buttonModifierElement;
	CButton	m_buttonAddUtilisateur;
	CButton	m_buttonAddElement;
	BOOL	m_bAddElement;
	BOOL	m_bAddUtilisateur;
	BOOL	m_bModifDroitUtilisateur;
	BOOL	m_bModifierElement;
	BOOL	m_bProprieteBase;
	BOOL	m_bSupprElement;
	CString	m_sNomLogin;
	CString	m_sNomPassword1;
	CString	m_sNomPassword2;
	BOOL	m_bSupprUtilisateur;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogNouvelUtilisateur)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogNouvelUtilisateur)
	afx_msg void OnClickButtonAucun();
	afx_msg void OnClickButtonTous();
	afx_msg void OnButtonOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGNOUVELUTILISATEUR_H__2918E984_DC5F_11D5_90A3_BBAF88E6499F__INCLUDED_)
