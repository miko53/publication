// InfoGalSet.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "InfoGalSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoGalSet

IMPLEMENT_DYNAMIC(CInfoGalSet, CDaoRecordset)

CInfoGalSet::CInfoGalSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CInfoGalSet)
	m_RepertoireRacine = _T("");
	m_VersionLogiciel = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

/*
CString CInfoGalSet::GetDefaultDBName()
{
	return _T("");
}
*/

CString CInfoGalSet::GetDefaultSQL()
{
	return _T("[InfoGal]");
}

void CInfoGalSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CInfoGalSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[RepertoireRacine]"), m_RepertoireRacine);
	DFX_Byte(pFX, _T("[VersionLogiciel]"), m_VersionLogiciel);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CInfoGalSet diagnostics

#ifdef _DEBUG
void CInfoGalSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CInfoGalSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
