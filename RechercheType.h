#if !defined(AFX_RECHERCHETYPE_H__9DEAEEC4_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
#define AFX_RECHERCHETYPE_H__9DEAEEC4_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRechercheType dialog

class CRechercheType : public CDialog
{
// Construction
public:
	CRechercheType(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheType)
	enum { IDD = IDD_RECHERCHE_TYPE };
	CButton	m_buttonModifier;
	CListBox	m_ListType;
	CButton	m_buttonEffacer;
	CString	m_ValueType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheType)
	afx_msg void OnEffacerType();
	afx_msg void OnModifierType();
	afx_msg void OnLancerecherche();
	afx_msg void OnSelchangeListType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_typeIDCourant;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHETYPE_H__9DEAEEC4_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
