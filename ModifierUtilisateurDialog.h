#if !defined(AFX_MODIFIERUTILISATEURDIALOG_H__F74FE984_E5D2_11D5_90A3_F431A9A7544C__INCLUDED_)
#define AFX_MODIFIERUTILISATEURDIALOG_H__F74FE984_E5D2_11D5_90A3_F431A9A7544C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ModifierUtilisateurDialog.h : header file
//
#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CModifierUtilisateurDialog dialog

class CModifierUtilisateurDialog : public CDialog
{
// Construction
public:
	CModifierUtilisateurDialog(CPublicationDoc* pDoc, CString sNomLogin, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifierUtilisateurDialog)
	enum { IDD = IDD_MODIFIER_UTILISATEUR };
	CButton	m_buttonSupprElement;
	CButton	m_buttonSupprUtilisateur;
	CButton	m_buttonPropBase;
	CButton	m_buttonModifierElement;
	CButton	m_buttonModifDroitUtilisateur;
	CButton	m_buttonAddUtilisateur;
	CButton	m_buttonAddElement;
	CString	m_sNomLoginEntrer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifierUtilisateurDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifierUtilisateurDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_sNomLogin;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFIERUTILISATEURDIALOG_H__F74FE984_E5D2_11D5_90A3_F431A9A7544C__INCLUDED_)
