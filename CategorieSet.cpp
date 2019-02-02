// CategorieSet.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "CategorieSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategorieSet

IMPLEMENT_DYNAMIC(CCategorieSet, CDaoRecordset)

CCategorieSet::CCategorieSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCategorieSet)
	m_Nom = _T("");
	m_Login = _T("");
	m_IdCategorieRacine = 0;
	m_IdCategorie = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

/*
CString CCategorieSet::GetDefaultDBName()
{
	return _T("");
}*/


CString CCategorieSet::GetDefaultSQL()
{
	return _T("[Categorie]");
}

void CCategorieSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCategorieSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_DateTime(pFX, _T("[DateEntree]"), m_DateEntree);
	DFX_Text(pFX, _T("[Login]"), m_Login);
	DFX_Long(pFX, _T("[IdCategorieRacine]"), m_IdCategorieRacine);
	DFX_Long(pFX, _T("[IdCategorie]"), m_IdCategorie);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCategorieSet diagnostics

#ifdef _DEBUG
void CCategorieSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CCategorieSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
