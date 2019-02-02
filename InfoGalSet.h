#if !defined(AFX_INFOGALSET_H__AEE1A2E4_5D99_11D5_90A3_BBE3617AC957__INCLUDED_)
#define AFX_INFOGALSET_H__AEE1A2E4_5D99_11D5_90A3_BBE3617AC957__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InfoGalSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoGalSet DAO recordset

class CInfoGalSet : public CDaoRecordset
{
public:
	CInfoGalSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CInfoGalSet)

// Field/Param Data
	//{{AFX_FIELD(CInfoGalSet, CDaoRecordset)
	CString	m_RepertoireRacine;
	BYTE	m_VersionLogiciel;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoGalSet)
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

#endif // !defined(AFX_INFOGALSET_H__AEE1A2E4_5D99_11D5_90A3_BBE3617AC957__INCLUDED_)
