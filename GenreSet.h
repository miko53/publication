#if !defined(AFX_GENRESET_H__291C5224_9E28_11D5_90A3_9898D788064B__INCLUDED_)
#define AFX_GENRESET_H__291C5224_9E28_11D5_90A3_9898D788064B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GenreSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenreSet DAO recordset

class CGenreSet : public CDaoRecordset
{
public:
	bool ExisteDeja(CString nom);
	CGenreSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGenreSet)

// Field/Param Data
	//{{AFX_FIELD(CGenreSet, CDaoRecordset)
	CString	m_Nom;
	long	m_IdGenre;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenreSet)
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

#endif // !defined(AFX_GENRESET_H__291C5224_9E28_11D5_90A3_9898D788064B__INCLUDED_)
