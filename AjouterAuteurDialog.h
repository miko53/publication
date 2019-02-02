#if !defined(AFX_AJOUTERAUTEURDIALOG_H__A40FD724_7BBB_11D5_90A3_B021A846777C__INCLUDED_)
#define AFX_AJOUTERAUTEURDIALOG_H__A40FD724_7BBB_11D5_90A3_B021A846777C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AjouterAuteurDialog.h : header file
//
#include "PublicationDoc.h"
#include "DateEdit.h"
#include "constElement.h"

/////////////////////////////////////////////////////////////////////////////
// CAjouterAuteurDialog dialog

class CAjouterAuteurDialog : public CDialog
{
// Construction
public:
	CAjouterAuteurDialog (unsigned char typeOuverture, long IDAuteur, CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjouterAuteurDialog)
	enum { IDD = IDD_AJOUTER_AUTEUR };
	CEdit	m_CtrlPrenom;
	CEdit	m_CtrlName;
	CDateEdit	m_CtrlNaissance;
	CDateEdit	m_CtrlMortDate;
	CEdit	m_CtrlRenseignement;
	CButton	m_BouttonNouveau;
	CButton	m_BouttonModifier;
	CButton	m_BouttonAjouter;
	CComboBox	m_ControlNationalite;
	CString	m_NaissanceString;
	CString	m_MortString;
	CString	m_NomAuteur;
	CString	m_PrenomAuteur;
	CString	m_RenseignementAuteur;
	CString	m_Nationalite;
	//}}AFX_DATA

	long m_IDAuteur;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjouterAuteurDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjouterAuteurDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddAuteur();
	afx_msg void OnModifyAuteur();
	afx_msg void OnNouveauAuteur();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPublicationDoc* m_pDoc;
	unsigned char m_appel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTERAUTEURDIALOG_H__A40FD724_7BBB_11D5_90A3_B021A846777C__INCLUDED_)
