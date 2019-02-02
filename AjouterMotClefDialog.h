#if !defined(AFX_AJOUTERMOTCLEFDIALOG_H__9DEAEEC5_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
#define AFX_AJOUTERMOTCLEFDIALOG_H__9DEAEEC5_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AjouterMotClefDialog.h : header file
//

#include "PublicationDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CAjouterMotClefDialog dialog

class CAjouterMotClefDialog : public CDialog
{
// Construction
public:
	CAjouterMotClefDialog(unsigned char typeOuverture, long IDType, CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjouterMotClefDialog)
	enum { IDD = IDD_AJOUTER_MOT_CLEF };
	CEdit	m_editKeyName;
	CButton	m_buttonNouveau;
	CButton	m_buttonModifier;
	CButton	m_buttonAjouter;
	CString	m_valueKeyName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjouterMotClefDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjouterMotClefDialog)
	afx_msg void OnAjouterMotClef();
	afx_msg void OnModifierMotClef();
	afx_msg void OnNouveauMotClef();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	unsigned char m_appel;
	long m_currentIDKeyName;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTERMOTCLEFDIALOG_H__9DEAEEC5_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
