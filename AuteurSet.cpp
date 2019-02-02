// AuteurSet.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "AuteurSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuteurSet

IMPLEMENT_DYNAMIC(CAuteurSet, CDaoRecordset)

CAuteurSet::CAuteurSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAuteurSet)
	m_Nom = _T("");
	m_Prenom = _T("");
	m_Login = _T("");
	m_Nationalite = _T("");
	m_RensCompl = _T("");
	m_IdAuteur = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CAuteurSet::GetDefaultSQL()
{
	return _T("[Auteur]");
}

void CAuteurSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAuteurSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_Text(pFX, _T("[Prenom]"), m_Prenom);
	DFX_DateTime(pFX, _T("[DateNaissance]"), m_DateNaissance);
	DFX_DateTime(pFX, _T("[DateMort]"), m_DateMort);
	DFX_DateTime(pFX, _T("[DateEntree]"), m_DateEntree);
	DFX_Text(pFX, _T("[Login]"), m_Login);
	DFX_Text(pFX, _T("[Nationalite]"), m_Nationalite);
	DFX_Text(pFX, _T("[RensCompl]"), m_RensCompl);
	DFX_Long(pFX, _T("[IdAuteur]"), m_IdAuteur);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAuteurSet diagnostics

#ifdef _DEBUG
void CAuteurSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CAuteurSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
