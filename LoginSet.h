#if !defined(AFX_LOGINSET_H__AEE1A2E5_5D99_11D5_90A3_BBE3617AC957__INCLUDED_)
#define AFX_LOGINSET_H__AEE1A2E5_5D99_11D5_90A3_BBE3617AC957__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LoginSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginSet DAO recordset

class CLoginSet : public CDaoRecordset
{
public:
//	CString m_nomParametre;
	CLoginSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLoginSet)

// Field/Param Data
	//{{AFX_FIELD(CLoginSet, CDaoRecordset)
	CString	m_Nom;
	BYTE	m_MotDePasse_0;
	BYTE	m_MotDePasse_1;
	BYTE	m_MotDePasse_2;
	BYTE	m_MotDePasse_3;
	BYTE	m_MotDePasse_4;
	BYTE	m_MotDePasse_5;
	BYTE	m_MotDePasse_6;
	BYTE	m_MotDePasse_7;
	BYTE	m_Autorisation_0;
	BYTE	m_Autorisation_1;
	BYTE	m_Autorisation_2;
	BYTE	m_Autorisation_3;
	BYTE	m_Autorisation_4;
	BYTE	m_Autorisation_5;
	BYTE	m_Autorisation_6;
	BYTE	m_Autorisation_7;
	long	m_IdLogin;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginSet)
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

#endif // !defined(AFX_LOGINSET_H__AEE1A2E5_5D99_11D5_90A3_BBE3617AC957__INCLUDED_)
