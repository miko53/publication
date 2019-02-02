// SelectionRepertoire.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "SelectionRepertoire.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectionRepertoire dialog


CSelectionRepertoire::CSelectionRepertoire(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectionRepertoire::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectionRepertoire)
	//}}AFX_DATA_INIT
}


void CSelectionRepertoire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectionRepertoire)
	DDX_Control(pDX, IDC_DISQUE, m_nomDisque);
	DDX_Control(pDX, IDC_TREE_REPERTOIRE, m_Repertoire);
	DDX_Control(pDX, IDC_NOM_REPERTOIRE, m_selectionRepertoire);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectionRepertoire, CDialog)
	//{{AFX_MSG_MAP(CSelectionRepertoire)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectionRepertoire message handlers
extern CPublicationApp theApp;

BOOL CSelectionRepertoire::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int curdrive, curitem, i;
	char pRootPath[] = "a:\\";
	char pName[] = "a:";
	char drive;


	curitem = 0;
	curdrive = _getdrive();

   for( drive = 'a'; drive <= 'z'; drive++ )
   {
	   pRootPath[0] = drive;
	   pName[0] = drive;

	   switch(GetDriveType(pRootPath))
	   {
	   case DRIVE_REMOVABLE:
	   case DRIVE_FIXED:
	   case DRIVE_REMOTE:
	   case DRIVE_CDROM:
	   case DRIVE_RAMDISK:
		    m_nomDisque.AddString(pName);
			m_nomDisque.SetItemData(curitem, (drive-'a'+1));
			curitem++;
		   break;

	   default:
		   break;
	   }
   }

   
	for(i=0; i<m_nomDisque.GetCount(); i++)
	{
		if (curdrive == (int) m_nomDisque.GetItemData(i))
			m_nomDisque.SetCurSel(i);
	}
   	
	/* Mise a jour du treeView */
	BOOL ok;
	HICON icon;

	ok = listeImage.Create(16, 16, (ILC_COLOR32 | ILC_MASK), 2, 2);
	if (ok == FALSE)
	{
		AfxMessageBox("Internal error (4)", MB_OK);
		AfxAbort();
	}


	icon = theApp.LoadIcon(IDI_CATEGORIE);
	if (icon == NULL)
	{
		AfxMessageBox("Internal error (5)", MB_OK);
		AfxAbort();
	}

	listeImage.Add(icon);

	icon = theApp.LoadIcon(IDI_CATEGORIE_SELECT);
	if (icon == NULL)
	{
		AfxMessageBox("Internal error (6)", MB_OK);
		AfxAbort();
	}

	listeImage.Add(icon);

	
	m_Repertoire.SetImageList(&listeImage, TVSIL_NORMAL);

	CString nomRepertoire = "a:\\";
	char tempo[255] = "*.*";
	int retour;

	nomRepertoire.SetAt(0, (curdrive + 'a' - 1));

	rootTreeItem = m_Repertoire.InsertItem(nomRepertoire, 0, 1, TVI_ROOT);

	retour = m_nomDisque.Dir(DDL_DIRECTORY, tempo);


	/*
	m_nomDisque.DlgDirListComboBox(tempo, IDC_COMBO1, IDC_NOM_REPERTOIRE, DDL_DIRECTORY);
	*/


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
