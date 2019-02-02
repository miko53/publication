// AjouterPublicationPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "AjouterPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjouterPublicationPropSheet

IMPLEMENT_DYNAMIC(CAjouterPublicationPropSheet, CPropertySheet)

CAjouterPublicationPropSheet::CAjouterPublicationPropSheet(UINT nIDCaption, CPublicationDoc* pDoc, CPubElement* pElement, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	ASSERT(pDoc != NULL);
	ASSERT(pElement != NULL);

	m_pDoc = pDoc;
	pElementContainer = pElement;

	m_pageInfoGal.AddDocument(pDoc);
	m_pageFichier.AddDocument(pDoc);
	m_pageResume.AddDocument(pDoc);
	m_pageMotClef.AddDocument(pDoc);

	ajoutPage();
}

CAjouterPublicationPropSheet::CAjouterPublicationPropSheet(LPCTSTR pszCaption, CPublicationDoc* pDoc, CPubElement* pElement, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	ASSERT(pDoc != NULL);
	ASSERT(pElement != NULL);

	m_pDoc = pDoc;
	pElementContainer = pElement;

	m_pageInfoGal.AddDocument(pDoc);
	m_pageFichier.AddDocument(pDoc);
	m_pageResume.AddDocument(pDoc);
	m_pageMotClef.AddDocument(pDoc);

	ajoutPage();
}

CAjouterPublicationPropSheet::~CAjouterPublicationPropSheet()
{
}


BEGIN_MESSAGE_MAP(CAjouterPublicationPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CAjouterPublicationPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjouterPublicationPropSheet message handlers

void CAjouterPublicationPropSheet::ajoutPage()
{
	AddPage(&m_pageInfoGal);
	AddPage(&m_pageFichier);
	AddPage(&m_pageResume);
	AddPage(&m_pageMotClef);
}

bool CAjouterPublicationPropSheet::ajouterPublicationDansBase()
{
	stAjouterPublication argPublication;
	int i;
	long currentMotClef;

	argPublication.idAuteur = (long) m_pageInfoGal.m_ComboBoxAuteur.GetItemData( m_pageInfoGal.m_ComboBoxAuteur.GetCurSel() );
	argPublication.idGenre = (long) m_pageInfoGal.m_ComboBoxGenre.GetItemData( m_pageInfoGal.m_ComboBoxGenre.GetCurSel() );
	argPublication.idSujet = (long) m_pageInfoGal.m_ComboBoxSujet.GetItemData( m_pageInfoGal.m_ComboBoxSujet.GetCurSel() );
	argPublication.idType = (long) m_pageInfoGal.m_ComboBoxType.GetItemData( m_pageInfoGal.m_ComboBoxType.GetCurSel() );
	argPublication.nomDocument = m_pageInfoGal.m_StringTitre;

	argPublication.fichierValide = m_pageFichier.m_CheckLink;

	if (m_pageFichier.m_CheckLink == TRUE)
	{
		argPublication.nomFichier = m_pageFichier.m_stringFilename;
	}

	argPublication.resume = m_pageResume.m_stringResume;
	argPublication.elementPere = pElementContainer;

	for (i=0;i<m_pageMotClef.m_ListMotClefPub.GetCount();i++)
	{
		currentMotClef = (long) m_pageMotClef.m_ListMotClefPub.GetItemData(i);
		argPublication.listMotClefs.AddHead(currentMotClef);
	}
	return m_pDoc->ajouterPublication(&argPublication);
}

