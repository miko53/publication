#if !defined(AFX_REPERTOIRETREECTRL_H__FA40EFE5_47DA_11D5_90A3_9C8005CA2C5B__INCLUDED_)
#define AFX_REPERTOIRETREECTRL_H__FA40EFE5_47DA_11D5_90A3_9C8005CA2C5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RepertoireTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRepertoireTreeCtrl window

class CRepertoireTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CRepertoireTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepertoireTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetNomRepertoire(CString* pNom);
	void SetStaticControl(CStatic* pStatic);
	void exploreDir (const CString& strDir, HTREEITEM hParent);
	void populateTree(const CString& strDir = CString((LPCTSTR) NULL));
	virtual ~CRepertoireTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRepertoireTreeCtrl)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CString m_nomDrive;
	CString* m_psNomRepertoire;
	CStatic* m_pNomRepertoire;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPERTOIRETREECTRL_H__FA40EFE5_47DA_11D5_90A3_9C8005CA2C5B__INCLUDED_)
