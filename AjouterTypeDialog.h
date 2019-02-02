#if !defined(AFX_AJOUTERTYPEDIALOG_H__409EEFC8_9CB1_11D5_90A3_E4830B63DD5F__INCLUDED_)
#define AFX_AJOUTERTYPEDIALOG_H__409EEFC8_9CB1_11D5_90A3_E4830B63DD5F__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AjouterTypeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAjouterTypeDialog dialog

class CAjouterTypeDialog : public CDialog
{
// Construction
public:
	CAjouterTypeDialog (unsigned char typeOuverture, long IDType, CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(CAjouterTypeDialog)
	enum { IDD = IDD_AJOUTER_TYPE };
	CEdit	m_editType;
	CButton	m_buttonAjouter;
	CButton	m_buttonModifier;
	CButton	m_buttonNouveau;
	CString	m_valueType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjouterTypeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjouterTypeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAjouterType();
	afx_msg void OnModifierType();
	afx_msg void OnNouveauType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	unsigned char m_appel;
	long m_currentIDType;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTERTYPEDIALOG_H__409EEFC8_9CB1_11D5_90A3_E4830B63DD5F__INCLUDED_)
