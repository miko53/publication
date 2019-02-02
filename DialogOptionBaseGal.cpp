// DialogOptionBaseGal.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "DialogOptionBaseGal.h"
#include "SelectionRepertoire.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionBaseGal dialog


CDialogOptionBaseGal::CDialogOptionBaseGal(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOptionBaseGal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogOptionBaseGal)
	m_sNomRepertoire = _T("");
	//}}AFX_DATA_INIT
}


void CDialogOptionBaseGal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOptionBaseGal)
	DDX_Control(pDX, IDC_REPERTOIRE_BASE, m_editRepertoire);
	DDX_Control(pDX, IDC_MODIFIER_REP_BASE, m_buttonSelectionRep);
	DDX_Control(pDX, IDC_UPDATE_BUTTON, m_buttonUpdate);
	DDX_Control(pDX, IDC_MODIFY_BUTTON, m_buttonModifier);
	DDX_Text(pDX, IDC_REPERTOIRE_BASE, m_sNomRepertoire);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOptionBaseGal, CDialog)
	//{{AFX_MSG_MAP(CDialogOptionBaseGal)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnModifyButton)
	ON_BN_CLICKED(IDC_UPDATE_BUTTON, OnUpdateButton)
	ON_BN_CLICKED(IDC_MODIFIER_REP_BASE, OnModifierRepBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionBaseGal message handlers

BOOL CDialogOptionBaseGal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_sNomRepertoire = AfxGetApp()->GetProfileString( _T("DataBaseDirectory"), _T("Name"), _T(""));

  m_buttonModifier.EnableWindow(TRUE);

  UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogOptionBaseGal::OnModifyButton() 
{
  m_buttonModifier.EnableWindow(FALSE);
  m_buttonUpdate.EnableWindow(TRUE);
  m_editRepertoire.EnableWindow(TRUE);
  m_buttonSelectionRep.EnableWindow(TRUE);

}

void CDialogOptionBaseGal::OnUpdateButton() 
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


  result = AfxGetApp()->WriteProfileString( _T("DataBaseDirectory"), _T("Name"), m_sNomRepertoire);
  if (result == TRUE)
  {
    AfxMessageBox("Mise à jour réussie");
    pubInfo.databaseDirectory = m_sNomRepertoire;

    m_buttonModifier.EnableWindow(TRUE);
    m_buttonUpdate.EnableWindow(FALSE);
    m_editRepertoire.EnableWindow(FALSE);
    m_buttonSelectionRep.EnableWindow(FALSE);
  }
  else
    AfxMessageBox("Echec lors de la mise à jour de la base de registre !");

}

void CDialogOptionBaseGal::OnModifierRepBase() 
{
	CSelectionRepertoire m_FileDialog;

	UpdateData(TRUE);

	if (m_FileDialog.DoModal() == IDOK)
	{
		m_sNomRepertoire = m_FileDialog.m_snomRepertoire;
		UpdateData(FALSE);
	}

}
