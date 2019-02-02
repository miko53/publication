// TypeSet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "TypeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypeSet

IMPLEMENT_DYNAMIC(CTypeSet, CDaoRecordset)

CTypeSet::CTypeSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTypeSet)
	m_Nom = _T("");
	m_IdType = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CTypeSet::GetDefaultSQL()
{
	return _T("[Type]");
}

void CTypeSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTypeSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_Long(pFX, _T("[IdType]"), m_IdType);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTypeSet diagnostics

#ifdef _DEBUG
void CTypeSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CTypeSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG


bool CTypeSet::ExisteDeja(CString nom)
{
	CString filter;
	bool result = false;

	filter.Format(_T("[Nom] = \"%s\""), nom);

	m_strFilter = filter;

	try
	{
		Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Type]"));

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
