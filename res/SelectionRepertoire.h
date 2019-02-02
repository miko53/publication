#if !defined(AFX_SELECTIONREPERTOIRE_H__18AB4771_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_SELECTIONREPERTOIRE_H__18AB4771_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

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

	CSelectionRepertoire(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectionRepertoire)
	enum { IDD = IDD_SELECTION_DIRECTORY };
	CComboBox	m_nomDisque;
	CTreeCtrl	m_Repertoire;
	CStatic	m_selectionRepertoire;
	//}}AFX_DATA
	CImageList listeImage;  // liste d'images 
	HTREEITEM rootTreeItem;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectionRepertoire)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectionRepertoire)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIONREPERTOIRE_H__18AB4771_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
