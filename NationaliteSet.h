#if !defined(AFX_NATIONALITESET_H__B1181204_7DF2_11D5_90A3_B9E15DF49774__INCLUDED_)
#define AFX_NATIONALITESET_H__B1181204_7DF2_11D5_90A3_B9E15DF49774__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NationaliteSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNationaliteSet DAO recordset

class CNationaliteSet : public CDaoRecordset
{
public:
	CNationaliteSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CNationaliteSet)

// Field/Param Data
	//{{AFX_FIELD(CNationaliteSet, CDaoRecordset)
	CString	m_Pays;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNationaliteSet)
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

#endif // !defined(AFX_NATIONALITESET_H__B1181204_7DF2_11D5_90A3_B9E15DF49774__INCLUDED_)
