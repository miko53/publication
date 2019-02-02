#if !defined(AFX_RECHERCHEMOTCLEF_H__9DEAEEC7_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
#define AFX_RECHERCHEMOTCLEF_H__9DEAEEC7_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_


#include "PublicationDoc.h"


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheMotClef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRechercheMotClef dialog

class CRechercheMotClef : public CDialog
{
// Construction
public:
	CRechercheMotClef(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheMotClef)
	enum { IDD = IDD_RECHERCHE_MOT_CLEF };
	CListBox	m_ListKeyName;
	CButton	m_buttonModifier;
	CButton	m_buttonEffacer;
	CString	m_valueKeyName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheMotClef)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheMotClef)
	afx_msg void OnLancerecherche();
	afx_msg void OnEffacerMotClef();
	afx_msg void OnModifierMotClef();
	afx_msg void OnSelchangeListKeyname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_motClefIDCourant;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHEMOTCLEF_H__9DEAEEC7_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
