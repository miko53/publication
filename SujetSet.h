#if !defined(AFX_SUJETSET_H__587AA345_9BD1_11D5_90A3_F97CCD10F80E__INCLUDED_)
#define AFX_SUJETSET_H__587AA345_9BD1_11D5_90A3_F97CCD10F80E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SujetSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSujetSet DAO recordset

class CSujetSet : public CDaoRecordset
{
public:
	bool ExisteDeja(CString nom);
	CSujetSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSujetSet)

// Field/Param Data
	//{{AFX_FIELD(CSujetSet, CDaoRecordset)
	CString	m_Nom;
	long	m_IdSujet;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSujetSet)
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

#endif // !defined(AFX_SUJETSET_H__587AA345_9BD1_11D5_90A3_F97CCD10F80E__INCLUDED_)
