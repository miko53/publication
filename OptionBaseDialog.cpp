// OptionBaseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "SelectionRepertoire.h"
#include "OptionBaseDialog.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COptionBaseDialog dialog


COptionBaseDialog::COptionBaseDialog(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(COptionBaseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionBaseDialog)
	m_sNomRepertoire = _T("");
	m_sVersion = _T("");
	m_bCopyDirectory = FALSE;
	m_bEraseAncienRepertoire = FALSE;
	//}}AFX_DATA_INIT

  ASSERT(pDoc != NULL);

  m_pDoc = pDoc;

}


void COptionBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionBaseDialog)
	DDX_Control(pDX, IDC_REPERTOIRE_RACINE, m_editRepertoire);
	DDX_Control(pDX, IDC_UPDATE_BUTTON, m_buttonUpdate);
	DDX_Control(pDX, IDC_MODIFIER_CAT, m_buttonSelectionCat);
	DDX_Control(pDX, IDC_MODIFY_BUTTON, m_buttonModify);
	DDX_Text(pDX, IDC_REPERTOIRE_RACINE, m_sNomRepertoire);
	DDX_Text(pDX, IDC_VERSION, m_sVersion);
	DDX_Check(pDX, IDC_CHECK_COPY, m_bCopyDirectory);
	DDX_Check(pDX, IDC_CHECK_ERASE, m_bEraseAncienRepertoire);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionBaseDialog, CDialog)
	//{{AFX_MSG_MAP(COptionBaseDialog)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnModifyButton)
	ON_BN_CLICKED(IDC_MODIFIER_CAT, OnModifierCat)
	ON_BN_CLICKED(IDC_UPDATE_BUTTON, OnUpdateButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionBaseDialog message handlers

BOOL COptionBaseDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pDoc->peutModifierBase() == true)
		m_buttonModify.EnableWindow(TRUE);

  m_pDoc->donnerOptionBase(m_sVersion, m_sNomRepertoire);
  m_buttonSelectionCat.EnableWindow(FALSE);
  m_bCopyDirectory = TRUE;
  m_bEraseAncienRepertoire = TRUE;

  UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionBaseDialog::OnModifyButton() 
{
  m_buttonModify.EnableWindow(FALSE);
  m_buttonSelectionCat.EnableWindow(TRUE);
  m_buttonUpdate.EnableWindow(TRUE);
  m_editRepertoire.EnableWindow(TRUE);
}

void COptionBaseDialog::OnModifierCat() 
{
	CSelectionRepertoire m_FileDialog;

	UpdateData(TRUE);

	if (m_FileDialog.DoModal() == IDOK)
	{
		m_sNomRepertoire = m_FileDialog.m_snomRepertoire;
		UpdateData(FALSE);
	}

}

void COptionBaseDialog::OnUpdateButton() 
{
  UpdateData();

  //Verification existance nouveau repertoire 
	CFileFind searchDir;
	BOOL result;
	result = searchDir.FindFile(m_sNomRepertoire);
	if (result == FALSE)
	{
		if (AfxMessageBox(_T("Le répertoire de sauvegarde n'existe pas \n  voulez-vous le creer ?"), MB_YESNO) == IDYES)
		{
			if (_mkdir(m_sNomRepertoire) != 0)
			{
				AfxMessageBox(_T("Création du répertoire impossible !"));
				return;
			}
		}
	}



  if (m_pDoc->modifierOptionBase(m_sNomRepertoire, m_bCopyDirectory, m_bEraseAncienRepertoire) == true)
  {
    m_buttonModify.EnableWindow(TRUE);
    m_buttonSelectionCat.EnableWindow(FALSE);
    m_buttonUpdate.EnableWindow(FALSE);
    m_editRepertoire.EnableWindow(FALSE);
  }
}
