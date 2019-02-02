#if !defined(AFX_NOUVELLEPUBLICATION_H__18AB475D_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_NOUVELLEPUBLICATION_H__18AB475D_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NouvellePublication.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNouvellePublication dialog

class CNouvellePublication : public CDialog
{
// Construction
public:
	CNouvellePublication(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNouvellePublication)
	enum { IDD = IDD_NEW_PUBLICATION };
	CString	m_nomBase;
	CString	m_nomSauvegarde;
	CString	m_passWord1;
	CString	m_passWord2;
	CString	m_repertoireSauvegarde;
	CString	m_nomRoot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNouvellePublication)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNouvellePublication)
	afx_msg void OnButton1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOUVELLEPUBLICATION_H__18AB475D_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
