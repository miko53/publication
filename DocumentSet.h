#if !defined(AFX_DOCUMENTSET_H__D2C33104_B074_11D5_90A3_FFD573BCE44E__INCLUDED_)
#define AFX_DOCUMENTSET_H__D2C33104_B074_11D5_90A3_FFD573BCE44E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DocumentSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocumentSet DAO recordset

class CDocumentSet : public CDaoRecordset
{
public:
	CDocumentSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDocumentSet)

// Field/Param Data
	//{{AFX_FIELD(CDocumentSet, CDaoRecordset)
	CString	m_Titre;
	long	m_IdCategorieRacine;
	CString	m_Resume;
	COleDateTime	m_DateEntree;
	CString	m_Login;
	long	m_IdAuteur;
	long	m_IdSujet;
	long	m_IdGenre;
	long	m_IdType;
	CString	m_Extension;
	BOOL	m_FichierExiste;
	long	m_IdDocument;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocumentSet)
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

#endif // !defined(AFX_DOCUMENTSET_H__D2C33104_B074_11D5_90A3_FFD573BCE44E__INCLUDED_)
