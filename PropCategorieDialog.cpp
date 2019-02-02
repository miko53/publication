// PropCategorieDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "PropCategorieDialog.h"
#include "constElement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropCategorieDialog dialog


CPropCategorieDialog::CPropCategorieDialog(CPubContainer* pCategorie, CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CPropCategorieDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropCategorieDialog)
	m_CategorieName = _T("");
	m_LoginName = _T("");
	m_EntryDate = _T("");
	//}}AFX_DATA_INIT

	pContainer = pCategorie;
	pDocument = pDoc;
}


void CPropCategorieDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropCategorieDialog)
	DDX_Control(pDX, IDC_UPDATE_BUTTON, m_updateButton);
	DDX_Control(pDX, IDC_CATEGORIE_NAME, m_CategorieNameControl);
	DDX_Control(pDX, IDC_MODIFY_BUTTON, m_modifyButton);
	DDX_Text(pDX, IDC_CATEGORIE_NAME, m_CategorieName);
	DDX_Text(pDX, IDC_LOGIN_NAME, m_LoginName);
	DDX_Text(pDX, IDC_ENTER_DATE, m_EntryDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropCategorieDialog, CDialog)
	//{{AFX_MSG_MAP(CPropCategorieDialog)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnModifyButtonClick)
	ON_BN_CLICKED(IDC_UPDATE_BUTTON, OnUpdateButtonClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropCategorieDialog message handlers


BOOL CPropCategorieDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	bool ok;
	COleDateTime date;

	// [ lire info de la base ]
	// [ mettre a jour les champs en consequence ]
	// [ lire droit utilisateur afin de mettre a jour etat des bouttons ]
	ok = pDocument->donnerInfoCategorie(pContainer->donnerIdentificateur(), m_CategorieName, m_LoginName, date);

	if (pDocument->peutModifierBase() == true)
		m_modifyButton.EnableWindow(TRUE);
	

	m_EntryDate = date.Format();
	if (ok == true)
	{
		UpdateData(FALSE);
		return TRUE;
	}
	else 
		return FALSE;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropCategorieDialog::OnModifyButtonClick() 
{
	m_CategorieNameControl.EnableWindow(TRUE);
	m_updateButton.EnableWindow(TRUE);
}

void CPropCategorieDialog::OnUpdateButtonClick() 
{
	bool result;
	COleDateTime date;

	UpdateData(TRUE);

	result = pDocument->modifierCategorie(pContainer, m_CategorieName);

	m_CategorieNameControl.EnableWindow(FALSE);
	m_updateButton.EnableWindow(FALSE);	

	result = pDocument->donnerInfoCategorie(pContainer->donnerIdentificateur(), m_CategorieName, m_LoginName, date);

	m_EntryDate = date.Format();

	if (result == true)
		UpdateData(FALSE);

}
