// LoginSet.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "LoginSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginSet

IMPLEMENT_DYNAMIC(CLoginSet, CDaoRecordset)

CLoginSet::CLoginSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLoginSet)
	m_Nom = _T("");
	m_MotDePasse_0 = 0;
	m_MotDePasse_1 = 0;
	m_MotDePasse_2 = 0;
	m_MotDePasse_3 = 0;
	m_MotDePasse_4 = 0;
	m_MotDePasse_5 = 0;
	m_MotDePasse_6 = 0;
	m_MotDePasse_7 = 0;
	m_Autorisation_0 = 0;
	m_Autorisation_1 = 0;
	m_Autorisation_2 = 0;
	m_Autorisation_3 = 0;
	m_Autorisation_4 = 0;
	m_Autorisation_5 = 0;
	m_Autorisation_6 = 0;
	m_Autorisation_7 = 0;
	m_IdLogin = 0;
	m_nFields = 18;
	//}}AFX_FIELD_INIT

/*	m_nomParametre = _T("");
	m_nParams = 1;*/
	m_nDefaultType = dbOpenDynaset;
}

/*
CString CLoginSet::GetDefaultDBName()
{
	return _T("");
}
*/

CString CLoginSet::GetDefaultSQL()
{
	return _T("[Login]");
}

void CLoginSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLoginSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nom]"), m_Nom);
	DFX_Byte(pFX, _T("[MotDePasse_0]"), m_MotDePasse_0);
	DFX_Byte(pFX, _T("[MotDePasse_1]"), m_MotDePasse_1);
	DFX_Byte(pFX, _T("[MotDePasse_2]"), m_MotDePasse_2);
	DFX_Byte(pFX, _T("[MotDePasse_3]"), m_MotDePasse_3);
	DFX_Byte(pFX, _T("[MotDePasse_4]"), m_MotDePasse_4);
	DFX_Byte(pFX, _T("[MotDePasse_5]"), m_MotDePasse_5);
	DFX_Byte(pFX, _T("[MotDePasse_6]"), m_MotDePasse_6);
	DFX_Byte(pFX, _T("[MotDePasse_7]"), m_MotDePasse_7);
	DFX_Byte(pFX, _T("[Autorisation_0]"), m_Autorisation_0);
	DFX_Byte(pFX, _T("[Autorisation_1]"), m_Autorisation_1);
	DFX_Byte(pFX, _T("[Autorisation_2]"), m_Autorisation_2);
	DFX_Byte(pFX, _T("[Autorisation_3]"), m_Autorisation_3);
	DFX_Byte(pFX, _T("[Autorisation_4]"), m_Autorisation_4);
	DFX_Byte(pFX, _T("[Autorisation_5]"), m_Autorisation_5);
	DFX_Byte(pFX, _T("[Autorisation_6]"), m_Autorisation_6);
	DFX_Byte(pFX, _T("[Autorisation_7]"), m_Autorisation_7);
	DFX_Long(pFX, _T("[IdLogin]"), m_IdLogin);
	//}}AFX_FIELD_MAP

	//Definit le type de colonne comme parametre
/*	pFX->SetFieldType(CDaoFieldExchange::param);
	DFX_Text(pFX, _T("NomParametre"), m_nomParametre);*/

}

/////////////////////////////////////////////////////////////////////////////
// CLoginSet diagnostics

#ifdef _DEBUG
void CLoginSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CLoginSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
