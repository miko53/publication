#if !defined(AFX_DATEEDIT_H__3D0D75E6_7FB8_11D5_90A3_833D0A78E25D__INCLUDED_)
#define AFX_DATEEDIT_H__3D0D75E6_7FB8_11D5_90A3_833D0A78E25D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DateEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateEdit window

class CDateEdit : public CEdit
{
// Construction
public:
	CDateEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDateEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDateEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEEDIT_H__3D0D75E6_7FB8_11D5_90A3_833D0A78E25D__INCLUDED_)
