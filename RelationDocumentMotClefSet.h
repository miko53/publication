#if !defined(AFX_RELATIONDOCUMENTMOTCLEFSET_H__9DEAEEC8_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
#define AFX_RELATIONDOCUMENTMOTCLEFSET_H__9DEAEEC8_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RelationDocumentMotClefSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRelationDocumentMotClefSet DAO recordset

class CRelationDocumentMotClefSet : public CDaoRecordset
{
public:
	CRelationDocumentMotClefSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRelationDocumentMotClefSet)

// Field/Param Data
	//{{AFX_FIELD(CRelationDocumentMotClefSet, CDaoRecordset)
	long	m_IdDoc;
	long	m_IdMotCles;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelationDocumentMotClefSet)
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

#endif // !defined(AFX_RELATIONDOCUMENTMOTCLEFSET_H__9DEAEEC8_9D58_11D5_90A3_A84B014FCF0E__INCLUDED_)
