// SujetSet.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "SujetSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSujetSet

IMPLEMENT_DYNAMIC(CSujetSet, CDaoRecordset)

CSujetSet::CSujetSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSujetSet)
	m_Nom = _T("");
	m_IdSujet = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CSujetSet::GetDefaultSQL()
{
	return _T("[Sujet]");
}

void CSujetSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSujetSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_Long(pFX, _T("[IdSujet]"), m_IdSujet);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSujetSet diagnostics

#ifdef _DEBUG
void CSujetSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSujetSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

bool CSujetSet::ExisteDeja(CString nom)
{
	CString filter;
	bool result = false;

	filter.Format(_T("[Nom] = \"%s\""), nom);

	m_strFilter = filter;

	try
	{
		Open(AFX_DAO_USE_DEFAULT_TYPE, _T("SELECT * FROM [Sujet]"));

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
