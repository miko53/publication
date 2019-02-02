#if !defined(AFX_AJOUTERGENREDIALOG_H__E826F764_9E14_11D5_90A3_9898D788064B__INCLUDED_)
#define AFX_AJOUTERGENREDIALOG_H__E826F764_9E14_11D5_90A3_9898D788064B__INCLUDED_

#include "PublicationDoc.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AjouterGenreDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAjouterGenreDialog dialog

class CAjouterGenreDialog : public CDialog
{
// Construction
public:
	CAjouterGenreDialog(unsigned char typeOuverture, long IDGenre, CPublicationDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjouterGenreDialog)
	enum { IDD = IDD_AJOUTER_GENRE };
	CButton	m_buttonNouveau;
	CButton	m_buttonModifier;
	CEdit	m_editGenre;
	CButton	m_buttonAjouter;
	CString	m_valeurGenre;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjouterGenreDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjouterGenreDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAjouterGenre();
	afx_msg void OnModificationGenre();
	afx_msg void OnNouveauGenre();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_IdGenreActuel;
	CPublicationDoc* m_pDoc;
	unsigned char m_appel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTERGENREDIALOG_H__E826F764_9E14_11D5_90A3_9898D788064B__INCLUDED_)
