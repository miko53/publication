#if !defined(AFX_RECHERCHECATEGORIEDIALOG_H__2AAF0724_A46A_11D5_90A3_BEF1C027DC47__INCLUDED_)
#define AFX_RECHERCHECATEGORIEDIALOG_H__2AAF0724_A46A_11D5_90A3_BEF1C027DC47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechercheCategorieDialog.h : header file
//

#include "constElement.h"
#include "PublicationDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CRechercheCategorieDialog dialog

class CRechercheCategorieDialog : public CDialog
{
// Construction
public:
	CRechercheCategorieDialog(CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechercheCategorieDialog)
	enum { IDD = IDD_RECHERCHE_CATEGORIE };
	CButton	m_buttonAfficher;
	CListCtrl	m_listCategorie;
	CEdit	m_editNomLogin;
	CEdit	m_editNomCategorie;
	BOOL	m_CocheNom;
	BOOL	m_CocheLogin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechercheCategorieDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRechercheCategorieDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnCocheLogin();
	afx_msg void OnCocheNomCategorie();
	afx_msg void OnLancerecherche();
	afx_msg void OnAfficher();
	afx_msg void OnItemchangedListCategorie(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_itemSelectionne;
	CPublicationDoc* m_pDoc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHECATEGORIEDIALOG_H__2AAF0724_A46A_11D5_90A3_BEF1C027DC47__INCLUDED_)
