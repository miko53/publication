// ModifierPublicationPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifierPublicationPropSheet

IMPLEMENT_DYNAMIC(CModifierPublicationPropSheet, CPropertySheet)

CModifierPublicationPropSheet::CModifierPublicationPropSheet(UINT nIDCaption, CPublicationDoc* pDoc, CPubDocument* pDocument, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	ASSERT(pDoc != NULL);
	ASSERT(pDocument != NULL);

	m_pDoc = pDoc;
	m_pDocElem = pDocument;

	m_pageInfoGal.AddDocument(pDoc);
	m_pageFichier.AddDocument(pDoc);
	m_pageResume.AddDocument(pDoc);
	m_pageMotClef.AddDocument(pDoc);
  
  m_bDocModifier = false;
  m_bFichierModifier = false;
  m_bMotClefModifier = false;
  m_bResumeModifer = false;
	
  ajoutPage();

}

CModifierPublicationPropSheet::CModifierPublicationPropSheet(LPCTSTR pszCaption, CPublicationDoc* pDoc, CPubDocument* pDocument, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	ASSERT(pDoc != NULL);
	ASSERT(pDocument != NULL);

	m_pDoc = pDoc;
	m_pDocElem = pDocument;

	m_pageInfoGal.AddDocument(pDoc);
	m_pageFichier.AddDocument(pDoc);
	m_pageResume.AddDocument(pDoc);
	m_pageMotClef.AddDocument(pDoc);

  m_bDocModifier = false;
  m_bFichierModifier = false;
  m_bMotClefModifier = false;
  m_bResumeModifer = false;


  ajoutPage();

}

CModifierPublicationPropSheet::~CModifierPublicationPropSheet()
{
}


BEGIN_MESSAGE_MAP(CModifierPublicationPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModifierPublicationPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifierPublicationPropSheet message handlers

void CModifierPublicationPropSheet::ajoutPage()
{
	AddPage(&m_pageInfoGal);
	AddPage(&m_pageFichier);
	AddPage(&m_pageResume);
	AddPage(&m_pageMotClef);
}

BOOL CModifierPublicationPropSheet::OnInitDialog() 
{
	if (m_pDoc->donnerInfoPublication(&m_donneesDocument, m_pDocElem) == false)
		return FALSE;

  if (m_donneesDocument.fichierValide == TRUE)
  {
    m_bFichierValide = TRUE;
    m_donneesDocument.fichierValide = FALSE;
  }
  else
  {
    m_bFichierValide = FALSE;
  }

	BOOL bResult = CPropertySheet::OnInitDialog();
	return bResult;
}

bool CModifierPublicationPropSheet::ModifierDocumentDansBase()
{
  int i;
	long currentMotClef;

  if (m_bDocModifier == false)
    return false;

  //Verification de la base

  //IF ok alors entrer info dans la base en utilisant le document


  //Mise a jour des données dans page gal
  if (m_pageInfoGal.VerifierDonnees() == false)
    return false;

  m_donneesDocument.idAuteur = (long) m_pageInfoGal.m_ComboBoxAuteur.GetItemData( m_pageInfoGal.m_ComboBoxAuteur.GetCurSel() );
  m_donneesDocument.idSujet = (long) m_pageInfoGal.m_ComboBoxSujet.GetItemData( m_pageInfoGal.m_ComboBoxSujet.GetCurSel() );
  m_donneesDocument.idGenre = (long) m_pageInfoGal.m_ComboBoxGenre.GetItemData( m_pageInfoGal.m_ComboBoxGenre.GetCurSel() );
  m_donneesDocument.idType = (long) m_pageInfoGal.m_ComboBoxType.GetItemData( m_pageInfoGal.m_ComboBoxType.GetCurSel() );
  m_donneesDocument.nomDocument = m_pageInfoGal.m_stringTitre;


  if (m_bFichierModifier == true)
  {
    m_pageFichier.UpdateData();
    m_donneesDocument.fichierValide = m_pageFichier.m_CheckLink;
  	if (m_pageFichier.m_CheckLink == TRUE)
  	{
  		m_donneesDocument.nomFichier = m_pageFichier.m_stringFilename;
  	}
  }


  if (m_bMotClefModifier == true)
  {
    m_donneesDocument.listMotClefs.RemoveAll();
    m_pageMotClef.UpdateData();

    for (i=0;i<m_pageMotClef.m_ListMotClefPub.GetCount();i++)
  	{
	  	currentMotClef = (long) m_pageMotClef.m_ListMotClefPub.GetItemData(i);
	  	m_donneesDocument.listMotClefs.AddHead(currentMotClef);
	  }
  }


  if (m_bResumeModifer == true)
  {
    m_pageResume.UpdateData();
    m_donneesDocument.resume = m_pageResume.m_stringResume;
  }

  m_donneesDocument.elementPere = m_pDocElem->donnerParent();

  if (m_pDoc->modifierPublication(&m_donneesDocument, m_pDocElem) == true)
  {
    m_bDocModifier = false;
    // remise a jour de la page file si modifie
    if (m_bFichierModifier == true)
    {
      m_bFichierModifier = false;
      if (m_donneesDocument.fichierValide == TRUE)
      {
        m_bFichierValide = TRUE;
        m_donneesDocument.fichierValide = FALSE;
      }
      else
      {
        m_bFichierValide = FALSE;
      }

      m_pageFichier.MettreAjourDonnees(m_bFichierValide, m_donneesDocument.nomFichier);
    }
    
    if (m_bMotClefModifier == true)
      m_bMotClefModifier = false;

    if (m_bResumeModifer == true)
      m_bResumeModifer = false;
 
    return true;
  }

  return false;
}

