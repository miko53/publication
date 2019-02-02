#if !defined(AFX_SELECTIONREPERTOIRE_H__FA40EFE4_47DA_11D5_90A3_9C8005CA2C5B__INCLUDED_)
#define AFX_SELECTIONREPERTOIRE_H__FA40EFE4_47DA_11D5_90A3_9C8005CA2C5B__INCLUDED_

#include "RepertoireTreeCtrl.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SelectionRepertoire.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectionRepertoire dialog

class CSelectionRepertoire : public CDialog
{
// Construction
public:
	CString m_nomDrive;
	CString m_snomRepertoire;
	CImageList listeImage;
	CSelectionRepertoire(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectionRepertoire)
	enum { IDD = IDD_SELECTION_DIRECTORY };
	CRepertoireTreeCtrl	m_SelectionRepertoire;
	CStatic	m_nomRepertoire;
	CComboBox	m_nomDisque;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectionRepertoire)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectionRepertoire)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDisque();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_currentDrive;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIONREPERTOIRE_H__FA40EFE4_47DA_11D5_90A3_9C8005CA2C5B__INCLUDED_)
