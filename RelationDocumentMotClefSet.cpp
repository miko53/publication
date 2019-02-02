// RelationDocumentMotClefSet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RelationDocumentMotClefSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelationDocumentMotClefSet

IMPLEMENT_DYNAMIC(CRelationDocumentMotClefSet, CDaoRecordset)

CRelationDocumentMotClefSet::CRelationDocumentMotClefSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRelationDocumentMotClefSet)
	m_IdDoc = 0;
	m_IdMotCles = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CRelationDocumentMotClefSet::GetDefaultSQL()
{
	return _T("[RelationDocMotCles]");
}

void CRelationDocumentMotClefSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRelationDocumentMotClefSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[IdDoc]"), m_IdDoc);
	DFX_Long(pFX, _T("[IdMotCles]"), m_IdMotCles);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRelationDocumentMotClefSet diagnostics

#ifdef _DEBUG
void CRelationDocumentMotClefSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CRelationDocumentMotClefSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
