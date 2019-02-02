#if !defined(AFX_MODIFIERPUBLICATIONPROPSHEET_H__28AABF44_B45B_11D5_90A3_CC94B9606E6B__INCLUDED_)
#define AFX_MODIFIERPUBLICATIONPROPSHEET_H__28AABF44_B45B_11D5_90A3_CC94B9606E6B__INCLUDED_

#include "PropPubInfoGal.h"	// Added by ClassView
#include "PropInfoResume.h"	// Added by ClassView
#include "PropInfoMotClef.h"	// Added by ClassView
#include "PropPagePubFileOpen.h"
#include "constElement.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ModifierPublicationPropSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifierPublicationPropSheet

class CModifierPublicationPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CModifierPublicationPropSheet)

// Construction
public:
	CModifierPublicationPropSheet(UINT nIDCaption, CPublicationDoc* pDoc, CPubDocument* pDocument, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CModifierPublicationPropSheet(LPCTSTR pszCaption, CPublicationDoc* pDoc, CPubDocument* pDocument, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	BOOL m_bFichierValide;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifierPublicationPropSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	bool ModifierDocumentDansBase(void);
	bool m_bDocModifier;
  bool m_bFichierModifier;
  bool m_bMotClefModifier;
  bool m_bResumeModifer;
	stAjouterPublication m_donneesDocument;
	virtual ~CModifierPublicationPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CModifierPublicationPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CButton m_BoutonModifier;
	CPubDocument* m_pDocElem;
	void ajoutPage(void);
	CPropPagePubFileOpen m_pageFichier;
	CPropInfoMotClef m_pageMotClef;
	CPropInfoResume m_pageResume;
	CPropPubInfoGal m_pageInfoGal;
	CPublicationDoc* m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFIERPUBLICATIONPROPSHEET_H__28AABF44_B45B_11D5_90A3_CC94B9606E6B__INCLUDED_)
