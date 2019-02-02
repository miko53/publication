// DocumentSet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "DocumentSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocumentSet

IMPLEMENT_DYNAMIC(CDocumentSet, CDaoRecordset)

CDocumentSet::CDocumentSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDocumentSet)
	m_Titre = _T("");
	m_IdCategorieRacine = 0;
	m_Resume = _T("");
	m_Login = _T("");
	m_IdAuteur = 0;
	m_IdSujet = 0;
	m_IdGenre = 0;
	m_IdType = 0;
	m_Extension = _T("");
	m_FichierExiste = FALSE;
	m_IdDocument = 0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDocumentSet::GetDefaultSQL()
{
	return _T("[Document]");
}

void CDocumentSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDocumentSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Titre]"), m_Titre);
	DFX_Long(pFX, _T("[IdCategorieRacine]"), m_IdCategorieRacine);
	DFX_Text(pFX, _T("[Resume]"), m_Resume);
	DFX_DateTime(pFX, _T("[DateEntree]"), m_DateEntree);
	DFX_Text(pFX, _T("[Login]"), m_Login);
	DFX_Long(pFX, _T("[IdAuteur]"), m_IdAuteur);
	DFX_Long(pFX, _T("[IdSujet]"), m_IdSujet);
	DFX_Long(pFX, _T("[IdGenre]"), m_IdGenre);
	DFX_Long(pFX, _T("[IdType]"), m_IdType);
	DFX_Text(pFX, _T("[Extension]"), m_Extension);
	DFX_Bool(pFX, _T("[FichierExiste]"), m_FichierExiste);
	DFX_Long(pFX, _T("[IdDocument]"), m_IdDocument);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDocumentSet diagnostics

#ifdef _DEBUG
void CDocumentSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDocumentSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
