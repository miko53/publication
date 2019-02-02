// MotClefSet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "MotClefSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotClefSet

IMPLEMENT_DYNAMIC(CMotClefSet, CDaoRecordset)

CMotClefSet::CMotClefSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMotClefSet)
	m_Nom = _T("");
	m_IdMotCles = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CMotClefSet::GetDefaultSQL()
{
	return _T("[MotCles]");
}

void CMotClefSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMotClefSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_Long(pFX, _T("[IdMotCles]"), m_IdMotCles);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMotClefSet diagnostics

#ifdef _DEBUG
void CMotClefSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CMotClefSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG


bool CMotClefSet::ExisteDeja(CString nom)
{
	CString filter;
	bool result = false;

	filter.Format(_T("[Nom] = \"%s\""), nom);

	m_strFilter = filter;

	try
	{
		Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [MotCles]"));

		if (IsEOF() == TRUE)
		{
			result = false;
		}
		else
		{
			result = true;
		}
	}
	catch (CException* pEx)
	{
		pEx->ReportError();
		result = false;
	}

	Close();

	return result;
}
