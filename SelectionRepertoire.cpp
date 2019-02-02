// SelectionRepertoire.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "constElement.h"
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_snomRepertoire = CString(_T(""));
	m_nomDrive = CString(_T(""));
	m_currentDrive = -1;
}


void CSelectionRepertoire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectionRepertoire)
	DDX_Control(pDX, IDC_TREE_REPERTOIRE, m_SelectionRepertoire);
	DDX_Control(pDX, IDC_NOM_REPERTOIRE, m_nomRepertoire);
	DDX_Control(pDX, IDC_DISQUE, m_nomDisque);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectionRepertoire, CDialog)
	//{{AFX_MSG_MAP(CSelectionRepertoire)
	ON_CBN_SELCHANGE(IDC_DISQUE, OnSelchangeDisque)
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
	BOOL ok;
	char tempo[255] = "*.*";

	m_nomDrive = "a:\\";
	
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
		{
			m_nomDisque.SetCurSel(i);
			m_currentDrive = i;
		}
	}
   	
	/* Mise a jour du treeView */

	ok = listeImage.Create(16, 16, (ILC_COLOR32 | ILC_MASK), 2, 2);
	if (ok == FALSE)
	{
		AfxMessageBox(_T("Internal error (4)"), MB_OK);
		AfxAbort();
	}

	listeImage.Add(pubInfo.pTabIcon[ICON_CATEGORIE]);
	listeImage.Add(pubInfo.pTabIcon[ICON_CATEGORIE_SELECT]);


	m_SelectionRepertoire.SetImageList(&listeImage, TVSIL_NORMAL);

	m_nomDrive.SetAt(0, (curdrive + 'a' - 1));

	m_SelectionRepertoire.SetStaticControl(&m_nomRepertoire);
	m_SelectionRepertoire.SetNomRepertoire(&m_snomRepertoire);

	m_SelectionRepertoire.populateTree(m_nomDrive);
	m_nomRepertoire.SetWindowText(m_nomDrive);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectionRepertoire::OnSelchangeDisque() 
{
	int currentDisk = m_nomDisque.GetItemData(m_nomDisque.GetCurSel());

	m_nomDrive.SetAt(0, (currentDisk + 'a' - 1));

	if (!_chdrive(currentDisk))
	{
		m_SelectionRepertoire.populateTree(m_nomDrive);
		m_currentDrive = m_nomDisque.GetCurSel();
	}
	else
	{
		AfxMessageBox(" Ce disque n'est pas accesible", MB_OK);
		m_nomDisque.SetCurSel(m_currentDrive);
	}

}
