#if !defined(AFX_AUTEURSET_H__B1181212_7DF2_11D5_90A3_B9E15DF49774__INCLUDED_)
#define AFX_AUTEURSET_H__B1181212_7DF2_11D5_90A3_B9E15DF49774__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AuteurSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuteurSet DAO recordset

class CAuteurSet : public CDaoRecordset
{
public:
	CAuteurSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAuteurSet)

// Field/Param Data
	//{{AFX_FIELD(CAuteurSet, CDaoRecordset)
	CString	m_Nom;
	CString	m_Prenom;
	COleDateTime	m_DateNaissance;
	COleDateTime	m_DateMort;
	COleDateTime	m_DateEntree;
	CString	m_Login;
	CString	m_Nationalite;
	CString	m_RensCompl;
	long	m_IdAuteur;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuteurSet)
	public:
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTEURSET_H__B1181212_7DF2_11D5_90A3_B9E15DF49774__INCLUDED_)
