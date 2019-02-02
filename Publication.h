// Publication.h : main header file for the PUBLICATION application
//

#if !defined(AFX_PUBLICATION_H__18AB4728_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_PUBLICATION_H__18AB4728_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "PublicationInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPublicationApp:
// See Publication.cpp for the implementation of this class
//
extern CPublicationInfo pubInfo;


class CPublicationApp : public CWinApp
{
public:
	CPublicationApp();
  BOOL DoMyPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags,	BOOL bOpenFileDialog, CDocTemplate* pTemplate);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPublicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPublicationApp)
	afx_msg void OnAppAbout();
	afx_msg void OnOptionsGenerale();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUBLICATION_H__18AB4728_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
