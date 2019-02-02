// PubDocument.cpp: implementation of the CPubDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Publication.h"
#include "PubDocument.h"
#include "constElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPubDocument::CPubDocument(CString nom, long identificateur, BOOL bFileExiste, CString sExtension)
{
	m_identificateur = identificateur;
	m_nomElement = nom;
	m_typeElement = ID_DOCUMENT;
  m_bFichierExiste = bFileExiste;
  m_sExtension = sExtension;
}


CPubDocument::CPubDocument()
{

}

CPubDocument::~CPubDocument()
{

}
