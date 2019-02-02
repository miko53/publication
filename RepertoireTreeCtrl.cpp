// RepertoireTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "RepertoireTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepertoireTreeCtrl

CRepertoireTreeCtrl::CRepertoireTreeCtrl()
{
	m_nomDrive = CString(_T(""));
	m_psNomRepertoire = NULL;
	m_pNomRepertoire = NULL;

}

CRepertoireTreeCtrl::~CRepertoireTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CRepertoireTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CRepertoireTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepertoireTreeCtrl message handlers

void CRepertoireTreeCtrl::populateTree(const CString & strDir)
{
	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hThisItem;
	int nIndex;
	CString strTemp;
	CString strSrc = strDir;

	m_nomDrive = strDir;


	CWaitCursor cursor; // this will automatically display a wait cursor

	// Make sure tree is empty before (re)populating it
	DeleteAllItems();


	CString cstr = _T("\\"); // look at the root directory first

	// insert the the root into the tree struct
	

	tvstruct.hParent = NULL;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = (char*) ((const char*) m_nomDrive); //"c:\\";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	
	hThisItem = InsertItem(&tvstruct);

	// the root dir needs to think it has children for Expand() to work
	// Expand() will call ExploreDir() to find the root's real children
	tvstruct.hParent = hThisItem;
	InsertItem(&tvstruct);

	Expand(GetRootItem(), TVE_EXPAND);

	if (!strDir)
		return;

	// expand as far as was indicated in strDir
	HTREEITEM hTI = GetRootItem();
	while (!strSrc.IsEmpty())
	{
		nIndex = strSrc.Find(_T("\\"));
		if (nIndex < 0)
		{
			cstr = strSrc;
			strSrc.Empty();
		}
		else if (nIndex > 0)
		{ // the "/" trailing the directory name is not included
			cstr = strSrc.Left(nIndex);
			strTemp = strSrc.Right(strSrc.GetLength() - (nIndex+1));
			strSrc = strTemp;
		}

		if(!cstr.IsEmpty() && (nIndex != 0))
		{
			// cstr now has the name of a file or dir -- look for a child that matches it
			hTI = GetChildItem(hTI);
			while ((hTI != NULL) && (cstr != GetItemText(hTI)))
			{
				hTI = GetNextItem(hTI, TVGN_NEXT);
			}

			// if you find it, expand the node or select the file
			if ((hTI != NULL) && (cstr == GetItemText(hTI)))
			{
				if (ItemHasChildren(hTI))
					Expand(hTI, TVE_EXPAND);
				else
				{
					SelectItem(hTI);    // focus it here, too...
					TV_ITEM tv;
					tv.hItem = hTI;
					tv.mask = TVIF_HANDLE | TVIF_STATE;
					tv.stateMask = TVIS_BOLD;
					if (GetItem(&tv))
					{
						tv.mask = TVIF_HANDLE | TVIF_STATE;
						tv.stateMask = TVIS_BOLD;
						tv.state = TVIS_BOLD;
						SetItem(&tv);
					}
					strSrc.Empty(); // it's a file, so we're not gonna go any further
				}
			}

			// if it wasn't found, you've gone as far as you can, so quit...
			else strSrc.Empty();
		}
		else // nIndex == 0
		{
			strTemp = strSrc.Right(strSrc.GetLength() - 1);
			strSrc = strTemp;
		}
	} // end expand

	SelectItem(GetRootItem());
}

void CRepertoireTreeCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// find out what item is getting expanded, and send that to Expand(hItem, TVE_EXPAND)
	if (pNMTreeView->hdr.code == TVN_ITEMEXPANDING)
	{
		HTREEITEM hIT = pNMTreeView->itemNew.hItem;
		CString cstr, strPath;

		// build up the path to htreeitem
		strPath = GetItemText(hIT);

		while (hIT != GetRootItem())
		{
			hIT = GetParentItem(hIT);

			if (hIT == GetRootItem())
				cstr.Format(_T("%s%s"), m_nomDrive, (LPCTSTR)strPath);
			else
				cstr.Format(_T("%s\\%s"), (LPCTSTR)GetItemText(hIT), (LPCTSTR)strPath);

			strPath = cstr;
		}

		// use that dir to call ExploreDir
		exploreDir(strPath, pNMTreeView->itemNew.hItem);
	}

	*pResult = 0;
}

void CRepertoireTreeCtrl::exploreDir(const CString & strDir, HTREEITEM hParent)
{
	TV_INSERTSTRUCT tvstruct;
	CString strSearchDir;

	// remove any children of this directory
	HTREEITEM hIT = GetChildItem(hParent);
	HTREEITEM hTemp;

	while (hIT != NULL)
	{
		hTemp = GetNextSiblingItem(hIT);
		DeleteItem(hIT);
		hIT = hTemp;
	}

	// prepare to find all the files in the specified directory
	if (hParent != GetRootItem())
	{
		strSearchDir = strDir + _T("\\*");
	}
	else
	{
		strSearchDir = strDir + _T("*");/**/
	}


	CFileFind ftpFind;

	BOOL bContinue = ftpFind.FindFile(strSearchDir);
	if (!bContinue)
	{
		// the directory is empty; just close up and return.
		ftpFind.Close();
		return;
	}

	BOOL bDir = FALSE;
	HTREEITEM hThisItem;
	CString strFileName;

	while (bContinue) // set up and insert a tvstruct for each item in the directory
	{
		// FindNextFile muxt be called before info can be gleaned from ftpFind
		bContinue = ftpFind.FindNextFile();
		strFileName = ftpFind.GetFileName();
		
		if ((strFileName == _T("..")) || (strFileName == _T(".")))
			continue;

		if (ftpFind.IsDirectory())
		{
			// found a directory.  MUST find out if it has a child, and if so

			bDir = TRUE;

			tvstruct.item.iImage = 0;
			tvstruct.item.iSelectedImage = 1;

			tvstruct.hParent = hParent;
		    tvstruct.hInsertAfter = TVI_SORT;
     		tvstruct.item.pszText = (LPTSTR)(LPCTSTR)strFileName;   // GetFileName() returns a CString
	     	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
 
	    	hThisItem = InsertItem(&tvstruct);

		}
		else
		{

			tvstruct.item.iImage = 2;
			tvstruct.item.iSelectedImage = 2;
		}
	}

	ftpFind.Close();

	// If any directories were found, and if they are not empty, a dummy child
	// must be created so they can be expanded later.  This check is done AFTER
	// all of strDir has been explored because only one CFtpFileFind object can
	// be open for any given FTP session.
	if (bDir)
	{
		CFileFind* pTempFtpFind = NULL;
		CString strFullSearchPath;
		int nImage, nSelectedImage;

		hThisItem = GetChildItem(hParent);

		while (hThisItem != NULL)
		{
			GetItemImage(hThisItem, nImage, nSelectedImage);
			if (nImage == 0) // this item is a directory
			{
				int length = strDir.GetLength() - 1;

				strFileName = GetItemText(hThisItem);

				// build the full path to the current directory
				if (strDir.GetAt(length) != _T('\\'))
				{
					strFullSearchPath = strDir + _T("\\") + strFileName + _T("\\*");
				}
				else
					strFullSearchPath = strDir + strFileName + _T("\\*");
				
				pTempFtpFind = new CFileFind();

				if (pTempFtpFind->FindFile(strFullSearchPath))
				{
					tvstruct.hParent = hThisItem;
					tvstruct.hInsertAfter = TVI_LAST;
					tvstruct.item.iImage = 0;
					tvstruct.item.iSelectedImage = 1;
					tvstruct.item.pszText = _T("1");;
					tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
					InsertItem(&tvstruct);
				}
				pTempFtpFind->Close();
				delete pTempFtpFind;
			}
			hThisItem = GetNextSiblingItem(hThisItem);
		}
	}

	return;

}

void CRepertoireTreeCtrl::SetStaticControl(CStatic * pStatic)
{
	ASSERT(pStatic != NULL);

	m_pNomRepertoire = pStatic;

}

void CRepertoireTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM itemSelected = GetSelectedItem();
	if (itemSelected != NULL)
	{
		CString RepertoireName = _T(""); //GetItemText(GetRootItem());
		bool firstTime = true;

		while (itemSelected != GetRootItem())
		{
			if (firstTime != true)
				RepertoireName = _T("\\") + RepertoireName;
			else
				firstTime = false;

			RepertoireName = GetItemText(itemSelected) + RepertoireName;
			itemSelected = GetParentItem(itemSelected);
		} 

		RepertoireName = GetItemText(itemSelected) + RepertoireName;

		m_pNomRepertoire->SetWindowText(RepertoireName);

		(*m_psNomRepertoire) = RepertoireName;
	}

	*pResult = 0;
}

void CRepertoireTreeCtrl::SetNomRepertoire(CString * pNom)
{
	ASSERT(pNom != NULL);

	m_psNomRepertoire = pNom;
}
