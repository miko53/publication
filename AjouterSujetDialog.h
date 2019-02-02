#if !defined(AFX_AJOUTERSUJETDIALOG_H__587AA344_9BD1_11D5_90A3_F97CCD10F80E__INCLUDED_)
#define AFX_AJOUTERSUJETDIALOG_H__587AA344_9BD1_11D5_90A3_F97CCD10F80E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AjouterSujetDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAjouterSujetDialog dialog

class CAjouterSujetDialog : public CDialog
{
// Construction
public:
	CAjouterSujetDialog(unsigned char typeOuverture, long IDSujet, CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjouterSujetDialog)
	enum { IDD = IDD_AJOUTER_SUJET };
	CEdit	m_editSujet;
	CButton	m_buttonAjouter;
	CButton	m_buttonModifier;
	CButton	m_buttonNouveau;
	CString	m_valeurSujet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjouterSujetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjouterSujetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAjouterSujet();
	afx_msg void OnModificationSujet();
	afx_msg void OnNouveauSujet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	unsigned char m_appel;
	long m_IdSujetActuel;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTERSUJETDIALOG_H__587AA344_9BD1_11D5_90A3_F97CCD10F80E__INCLUDED_)
