#if !defined(AFX_TYPESET_H__409EEFC9_9CB1_11D5_90A3_E4830B63DD5F__INCLUDED_)
#define AFX_TYPESET_H__409EEFC9_9CB1_11D5_90A3_E4830B63DD5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TypeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTypeSet DAO recordset

class CTypeSet : public CDaoRecordset
{
public:
	bool ExisteDeja(CString nom);
	CTypeSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTypeSet)

// Field/Param Data
	//{{AFX_FIELD(CTypeSet, CDaoRecordset)
	CString	m_Nom;
	long	m_IdType;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypeSet)
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

#endif // !defined(AFX_TYPESET_H__409EEFC9_9CB1_11D5_90A3_E4830B63DD5F__INCLUDED_)
