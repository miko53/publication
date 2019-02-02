#if !defined(AFX_CATEGORIESET_H__AEE1A2E9_5D99_11D5_90A3_BBE3617AC957__INCLUDED_)
#define AFX_CATEGORIESET_H__AEE1A2E9_5D99_11D5_90A3_BBE3617AC957__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CategorieSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategorieSet DAO recordset

class CCategorieSet : public CDaoRecordset
{
public:
	CCategorieSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCategorieSet)

// Field/Param Data
	//{{AFX_FIELD(CCategorieSet, CDaoRecordset)
	CString	m_Nom;
	COleDateTime	m_DateEntree;
	CString	m_Login;
	long	m_IdCategorieRacine;
	long	m_IdCategorie;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategorieSet)
	public:
//	virtual CString GetDefaultDBName();		// Default database name
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

#endif // !defined(AFX_CATEGORIESET_H__AEE1A2E9_5D99_11D5_90A3_BBE3617AC957__INCLUDED_)
