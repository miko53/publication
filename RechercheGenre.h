#if !defined(AFX_RECHERCHEGENRE_H__291C5225_9E28_11D5_90A3_9898D788064B__INCLUDED_)
#define AFX_RECHERCHEGENRE_H__291C5225_9E28_11D5_90A3_9898D788064B__INCLUDED_

#include "PublicationDoc.h"


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheGenre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRechercheGenre dialog

class CRechercheGenre : public CDialog
{
// Construction
public:
	CRechercheGenre(CPublicationDoc* pdoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheGenre)
	enum { IDD = IDD_RECHERCHE_GENRE };
	CButton	m_buttonModifier;
	CListBox	m_ListGenre;
	CButton	m_buttonEffacer;
	CString	m_ValueGenre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheGenre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheGenre)
	afx_msg void OnEffacerGenre();
	afx_msg void OnLancerecherche();
	afx_msg void OnModifierGenre();
	afx_msg void OnSelchangeListGenre();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_genreIDCourant;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHEGENRE_H__291C5225_9E28_11D5_90A3_9898D788064B__INCLUDED_)
