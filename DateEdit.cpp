// DateEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "DateEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateEdit

CDateEdit::CDateEdit()
{
	//                  0123456789
	//m_maskValue = _T("__/__/____");
}

CDateEdit::~CDateEdit()
{
}


BEGIN_MESSAGE_MAP(CDateEdit, CEdit)
	//{{AFX_MSG_MAP(CDateEdit)
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateEdit message handlers

void CDateEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nStartChar;
	int nEndChar;

	GetSel(nStartChar, nEndChar);

	if (((nStartChar > 9) && (nChar != 8)) ||
		((nStartChar == 0) && (nChar == 8) && (nStartChar == nEndChar)) )
	{
		Beep(0, 0);
		return;
	}

	if (nChar == 8)
	{
		if (nEndChar == nStartChar)
		{
			UINT Empty = '_';
			if ((nStartChar == 3) || (nStartChar == 6))
				SetSel((nStartChar-2), (nEndChar-1));
			else
				SetSel(nStartChar-1, nEndChar);

			ReplaceSel((char*) &Empty);
	
			if ((nStartChar == 3) || (nStartChar == 6))
				SetSel(nStartChar-2, nEndChar-2);
			else
				SetSel(nStartChar-1, nEndChar-1);

		}
		else
		{
			/* Selection = plusieurs caracteres */
			register int i;
			UINT Empty = '_';
			CString selection;

			GetWindowText(selection);
			for(i=nStartChar;i<(nEndChar);i++)
			{
				if (selection[i] != '/')
				{
					SetSel(i, i+1);
					ReplaceSel((char*) &Empty);
				}
			}
			SetSel(nStartChar, nStartChar);
		}
		return;
	}

	if (nEndChar == nStartChar)
	{
		/* Selection = 1er caractere */

		if ((nStartChar == 2) || (nStartChar == 5))
			SetSel((nStartChar+1), (nEndChar+2));
		else
			SetSel(nStartChar, nEndChar+1);

		ReplaceSel((char*) &nChar);

		if ((nStartChar == 1) || (nStartChar == 4))
			SetSel((nStartChar+2), (nEndChar+2));
	}
	else
	{
		/* Selection = plusieurs caracteres */
		register int i;
		UINT Empty = '_';
		CString selection;

		GetWindowText(selection);
		for(i=nStartChar;i<(nEndChar);i++)
		{
			if (selection[i] != '/')
			{
				SetSel(i, i+1);
				ReplaceSel((char*) &Empty);
			}
		}

		nEndChar = nStartChar;

		if ((nStartChar == 2) || (nStartChar == 5))
			SetSel((nStartChar+1), (nEndChar+2));
		else
			SetSel(nStartChar, nEndChar+1);

		ReplaceSel((char*) &nChar);

		if ((nStartChar == 1) || (nStartChar == 4))
			SetSel((nStartChar+2), (nEndChar+2));
	}
}

void CDateEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
		CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CDateEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	UINT EmptyChar = '_';
	int nStartChar;
	int nEndChar;

	if (nChar == 0x2E)  // Touche [SUPPR]
	{
		GetSel(nStartChar, nEndChar);

		if (nStartChar == nEndChar)
		{
			if (nStartChar != 0)
			{
				if ((nStartChar == 3) || (nStartChar == 6))
					SetSel((nStartChar-2), (nEndChar-1));
				else	
					SetSel(nStartChar-1, nEndChar);

				ReplaceSel((char*) &EmptyChar);

				if ((nStartChar == 3) || (nStartChar == 6))
					SetSel((nStartChar-2), (nStartChar-2));
				else	
					SetSel(nStartChar-1, nStartChar-1);
			}
			else
				Beep(0,0);
		}
		else
		{
			/* Selection = plusieurs caracteres */
			register int i;
			UINT Empty = '_';
			CString selection;

			GetWindowText(selection);
			for(i=nStartChar;i<(nEndChar);i++)
			{
				if (selection[i] != '/')
				{
					SetSel(i, i+1);
					ReplaceSel((char*) &Empty);
				}
			}
			SetSel(nStartChar, nStartChar);
		}
	}
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
