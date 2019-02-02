// NationaliteSet.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "NationaliteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNationaliteSet

IMPLEMENT_DYNAMIC(CNationaliteSet, CDaoRecordset)

CNationaliteSet::CNationaliteSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CNationaliteSet)
	m_Pays = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CNationaliteSet::GetDefaultSQL()
{
	return _T("[Nationalite]");
}

void CNationaliteSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CNationaliteSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Pays]"), m_Pays);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CNationaliteSet diagnostics

#ifdef _DEBUG
void CNationaliteSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CNationaliteSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
