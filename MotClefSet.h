#if !defined(AFX_MOTCLEFSET_H__9DEAEEC6_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
#define AFX_MOTCLEFSET_H__9DEAEEC6_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MotClefSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotClefSet DAO recordset

class CMotClefSet : public CDaoRecordset
{
public:
	bool ExisteDeja(CString nom);
	CMotClefSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMotClefSet)

// Field/Param Data
	//{{AFX_FIELD(CMotClefSet, CDaoRecordset)
	CString	m_Nom;
	long	m_IdMotCles;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotClefSet)
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

#endif // !defined(AFX_MOTCLEFSET_H__9DEAEEC6_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
