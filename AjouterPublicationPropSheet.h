#if !defined(AFX_AJOUTERPUBLICATIONPROPSHEET_H__9EFFC761_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
#define AFX_AJOUTERPUBLICATIONPROPSHEET_H__9EFFC761_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_

#include "PublicationDoc.h"
#include "PropPageAjouterPubFile.h"	// Added by ClassView
#include "PropPageAjouterPubGal.h"	// Added by ClassView
#include "PropPageAjouterPubMotClef.h"	// Added by ClassView
#include "PropPageAjouterPubResume.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AjouterPublicationPropSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAjouterPublicationPropSheet

class CAjouterPublicationPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAjouterPublicationPropSheet)

// Construction
public:
	CAjouterPublicationPropSheet(UINT nIDCaption, CPublicationDoc* pDoc, CPubElement* pElement, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAjouterPublicationPropSheet(LPCTSTR pszCaption, CPublicationDoc* pDoc, CPubElement* pElement, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjouterPublicationPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool ajouterPublicationDansBase(void);
	virtual ~CAjouterPublicationPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAjouterPublicationPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPublicationDoc* m_pDoc;
	CPubElement* pElementContainer;
	CPropPageAjouterPubResume   m_pageResume;
	CPropPageAjouterPubMotClef  m_pageMotClef;
	CPropPageAjouterPubGal      m_pageInfoGal;
	CPropPageAjouterPubFile     m_pageFichier;
	void ajoutPage();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTERPUBLICATIONPROPSHEET_H__9EFFC761_A9E7_11D5_90A3_D7E3A302E05E__INCLUDED_)
