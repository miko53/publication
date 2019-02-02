// Publication.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Publication.h"
#include "constElement.h"
#include "PublicationInfo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "PublicationDoc.h"
#include "PublicationView.h"
#include "DialogOptionBaseGal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPublicationApp

BEGIN_MESSAGE_MAP(CPublicationApp, CWinApp)
	//{{AFX_MSG_MAP(CPublicationApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_OPTIONS_GENERALE, OnOptionsGenerale)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

static void AppendMyFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt);

/////////////////////////////////////////////////////////////////////////////
// CPublicationApp construction
//	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)


CPublicationApp::CPublicationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPublicationApp object

CPublicationApp theApp;
CPublicationInfo pubInfo;


/////////////////////////////////////////////////////////////////////////////
// CPublicationApp initialization

BOOL CPublicationApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("PublicSoft"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	pubInfo.databaseDirectory = GetProfileString( _T("DataBaseDirectory"), _T("Name"), _T("C:\\Mes Documents"));

//	if (pubInfo.databaseDirectory == _T(""))
//  {
//    AfxMessageBox("La base de registre est incomplete ! \n utiliser le menu Options/Options Generales, pour mettre à jour le répertoire de sauvegarde des bases");
//		return FALSE;
//  }

	pubInfo.flagFirstDocument = true;

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_PUBLICTYPE,
		RUNTIME_CLASS(CPublicationDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPublicationView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	pubInfo.pTabIcon[ICON_CATEGORIE]        = LoadIcon(IDI_CATEGORIE);
	pubInfo.pTabIcon[ICON_CATEGORIE_SELECT] = LoadIcon(IDI_CATEGORIE_SELECT);
	pubInfo.pTabIcon[ICON_ROOT]             = LoadIcon(IDI_ROOT);
	pubInfo.pTabIcon[ICON_DOCUMENT]         = LoadIcon(IDI_DOCUMENT);

	if ((pubInfo.pTabIcon[0] == NULL) || (pubInfo.pTabIcon[1] == NULL) ||
		(pubInfo.pTabIcon[2] == NULL) || (pubInfo.pTabIcon[3] == NULL))
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPublicationApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPublicationApp commands

void CPublicationApp::OnOptionsGenerale() 
{
	CDialogOptionBaseGal aDialog;

  aDialog.DoModal();

}

void CPublicationApp::OnFileOpen() 
{
  	// prompt the user (with all document templates)
	CString newName;
	if (!DoMyPromptFileName(newName, AFX_IDS_OPENFILE,
	  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		return; // open cancelled

	AfxGetApp()->OpenDocumentFile(newName);
		// if returns NULL, the user has already been alerted

}


BOOL CPublicationApp::DoMyPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags,
	BOOL bOpenFileDialog, CDocTemplate* pTemplate)
		// if pTemplate==NULL => all document templates
{
	ASSERT(m_pDocManager != NULL);

	CFileDialog dlgFile(bOpenFileDialog);
	CString title;


	VERIFY(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

  // La seule chose ajoutée en plus des fonctions Windows
  dlgFile.m_ofn.lpstrInitialDir = pubInfo.databaseDirectory;

	CString strFilter;
	CString strDefault;

	if (pTemplate != NULL)
	{
		ASSERT_VALID(pTemplate);
		AppendMyFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
	}
	else
	{
		// do for all doc template
		POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
		BOOL bFirst = TRUE;
		while (pos != NULL)
		{
			CDocTemplate* pTemplate = (CDocTemplate*) m_pDocManager->GetNextDocTemplate(pos);
			AppendMyFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
				bFirst ? &strDefault : NULL);
			bFirst = FALSE;
		}
	}

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
#ifndef _MAC
	strFilter += _T("*.*");
#else
	strFilter += _T("****");
#endif
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
#ifndef _MAC
	dlgFile.m_ofn.lpstrTitle = title;
#else
	dlgFile.m_ofn.lpstrPrompt = title;
#endif
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;

  
  fileName.ReleaseBuffer();
	return bResult;

	//return m_pDocManager->DoPromptFileName(fileName, nIDSTitle, lFlags,
	//	bOpenFileDialog, pTemplate);
}


static void AppendMyFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
	ASSERT_VALID(pTemplate);
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	CString strFilterExt, strFilterName;
	if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	 !strFilterExt.IsEmpty() &&
	 pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
	 !strFilterName.IsEmpty())
	{
		// a file based document template - add to filter list
#ifndef _MAC
		ASSERT(strFilterExt[0] == '.');
#endif
		if (pstrDefaultExt != NULL)
		{
			// set the default extension
#ifndef _MAC
			*pstrDefaultExt = ((LPCTSTR)strFilterExt) + 1;  // skip the '.'
#else
			*pstrDefaultExt = strFilterExt;
#endif
			ofn.lpstrDefExt = (LPTSTR)(LPCTSTR)(*pstrDefaultExt);
			ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
		}

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\0';  // next string please
#ifndef _MAC
		filter += (TCHAR)'*';
#endif
		filter += strFilterExt;
		filter += (TCHAR)'\0';  // next string please
		ofn.nMaxCustFilter++;
	}
}
