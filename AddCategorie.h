#if !defined(AFX_ADDCATEGORIE_H__E43CF844_68E8_11D5_90A3_A14A23586945__INCLUDED_)
#define AFX_ADDCATEGORIE_H__E43CF844_68E8_11D5_90A3_A14A23586945__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddCategorie.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddCategorie dialog

class CAddCategorie : public CDialog
{
// Construction
public:
	CAddCategorie(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddCategorie)
	enum { IDD = IDD_NEW_CATEGORIE };
	CString	m_categorieName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddCategorie)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddCategorie)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDCATEGORIE_H__E43CF844_68E8_11D5_90A3_A14A23586945__INCLUDED_)
