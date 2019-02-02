// GenreSet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "GenreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenreSet

IMPLEMENT_DYNAMIC(CGenreSet, CDaoRecordset)

CGenreSet::CGenreSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGenreSet)
	m_Nom = _T("");
	m_IdGenre = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CGenreSet::GetDefaultSQL()
{
	return _T("[Genre]");
}

void CGenreSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGenreSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_Long(pFX, _T("[IdGenre]"), m_IdGenre);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGenreSet diagnostics

#ifdef _DEBUG
void CGenreSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CGenreSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG


bool CGenreSet::ExisteDeja(CString nom)
{
	CString filter;
	bool result = false;

	filter.Format(_T("[Nom] = \"%s\""), nom);

	m_strFilter = filter;

	try
	{
		Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Genre]"));

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
