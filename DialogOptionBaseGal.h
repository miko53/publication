#if !defined(AFX_DIALOGOPTIONBASEGAL_H__FA77D024_F188_11D5_90A3_FFFFFF000000__INCLUDED_)
#define AFX_DIALOGOPTIONBASEGAL_H__FA77D024_F188_11D5_90A3_FFFFFF000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogOptionBaseGal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionBaseGal dialog

class CDialogOptionBaseGal : public CDialog
{
// Construction
public:
	CDialogOptionBaseGal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogOptionBaseGal)
	enum { IDD = IDD_OPTION_BASE_GAL };
	CEdit	m_editRepertoire;
	CButton	m_buttonSelectionRep;
	CButton	m_buttonUpdate;
	CButton	m_buttonModifier;
	CString	m_sNomRepertoire;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogOptionBaseGal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogOptionBaseGal)
	virtual BOOL OnInitDialog();
	afx_msg void OnModifyButton();
	afx_msg void OnUpdateButton();
	afx_msg void OnModifierRepBase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONBASEGAL_H__FA77D024_F188_11D5_90A3_FFFFFF000000__INCLUDED_)
