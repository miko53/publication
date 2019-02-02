// DialogNouvelUtilisateur.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "DialogNouvelUtilisateur.h"
#include "constElement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogNouvelUtilisateur dialog


CDialogNouvelUtilisateur::CDialogNouvelUtilisateur(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNouvelUtilisateur::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogNouvelUtilisateur)
	m_bAddElement = FALSE;
	m_bAddUtilisateur = FALSE;
	m_bModifDroitUtilisateur = FALSE;
	m_bModifierElement = FALSE;
	m_bProprieteBase = FALSE;
	m_bSupprElement = FALSE;
	m_sNomLogin = _T("");
	m_sNomPassword1 = _T("");
	m_sNomPassword2 = _T("");
	m_bSupprUtilisateur = FALSE;
	//}}AFX_DATA_INIT

  m_pDoc = pDoc;
}


void CDialogNouvelUtilisateur::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogNouvelUtilisateur)
	DDX_Control(pDX, IDC_CHECK_MODI_DROIT_UTILISATEUR, m_buttonModifDroitUtilisateur);
	DDX_Control(pDX, IDC_CHECK_SUPPRIMER_ELEMENT, m_buttonSupprElement);
	DDX_Control(pDX, IDC_CHECK_SUPPR_UTILISATEUR, m_buttonSupprUtilisateur);
	DDX_Control(pDX, IDC_CHECK_PROP_BASE, m_buttonPropBase);
	DDX_Control(pDX, IDC_CHECK_MODIFIER_ELEMENT, m_buttonModifierElement);
	DDX_Control(pDX, IDC_CHECK_ADD_UTILISATEUR, m_buttonAddUtilisateur);
	DDX_Control(pDX, IDC_CHECK_ADD_ELEMENT, m_buttonAddElement);
	DDX_Check(pDX, IDC_CHECK_ADD_ELEMENT, m_bAddElement);
	DDX_Check(pDX, IDC_CHECK_ADD_UTILISATEUR, m_bAddUtilisateur);
	DDX_Check(pDX, IDC_CHECK_MODI_DROIT_UTILISATEUR, m_bModifDroitUtilisateur);
	DDX_Check(pDX, IDC_CHECK_MODIFIER_ELEMENT, m_bModifierElement);
	DDX_Check(pDX, IDC_CHECK_PROP_BASE, m_bProprieteBase);
	DDX_Check(pDX, IDC_CHECK_SUPPRIMER_ELEMENT, m_bSupprElement);
	DDX_Text(pDX, IDC_NOM_UTLISATEUR, m_sNomLogin);
	DDV_MaxChars(pDX, m_sNomLogin, 8);
	DDX_Text(pDX, IDC_PASSWORD1, m_sNomPassword1);
	DDV_MaxChars(pDX, m_sNomPassword1, 8);
	DDX_Text(pDX, IDC_PASSWORD2, m_sNomPassword2);
	DDV_MaxChars(pDX, m_sNomPassword2, 8);
	DDX_Check(pDX, IDC_CHECK_SUPPR_UTILISATEUR, m_bSupprUtilisateur);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogNouvelUtilisateur, CDialog)
	//{{AFX_MSG_MAP(CDialogNouvelUtilisateur)
	ON_BN_CLICKED(IDC_BUTTON_AUCUN, OnClickButtonAucun)
	ON_BN_CLICKED(IDC_BUTTON_TOUS, OnClickButtonTous)
	ON_BN_CLICKED(IDOK, OnButtonOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogNouvelUtilisateur message handlers

void CDialogNouvelUtilisateur::OnClickButtonAucun() 
{
  UpdateData(TRUE);

  CString sNomLogin = m_sNomLogin;
  CString sNomPassword1 = m_sNomPassword1;
  CString sNomPassword2 = m_sNomPassword2;

	m_bAddElement = FALSE;
	m_bAddUtilisateur = FALSE;
	m_bModifDroitUtilisateur = FALSE;
	m_bModifierElement = FALSE;
	m_bProprieteBase = FALSE;
	m_bSupprElement = FALSE;
	m_bSupprUtilisateur = FALSE;

  m_sNomLogin = sNomLogin;
  m_sNomPassword1 = sNomPassword1;
  m_sNomPassword2 = sNomPassword2;

  UpdateData(FALSE);
}

void CDialogNouvelUtilisateur::OnClickButtonTous() 
{
  UpdateData(TRUE);

  CString sNomLogin = m_sNomLogin;
  CString sNomPassword1 = m_sNomPassword1;
  CString sNomPassword2 = m_sNomPassword2;

	m_bAddElement = TRUE;
	m_bAddUtilisateur = TRUE;
	m_bModifDroitUtilisateur = TRUE;
	m_bModifierElement = TRUE;
	m_bProprieteBase = TRUE;
	m_bSupprElement = TRUE;
	m_bSupprUtilisateur = TRUE;

  m_sNomLogin = sNomLogin;
  m_sNomPassword1 = sNomPassword1;
  m_sNomPassword2 = sNomPassword2;

  UpdateData(FALSE);
}


void CDialogNouvelUtilisateur::OnButtonOK() 
{
  // Verification des elements
  // si ko l'indiquer

  unsigned long dwDroitUtilisateur = 0;

  UpdateData(TRUE);



  if (m_sNomPassword1 != m_sNomPassword2)
  {
    AfxMessageBox("Le mot de passe entré est incorrecte !", MB_OK);
    return;
  }

  //Creer le mot des droits de l'utilisateur
  if (m_bAddElement == TRUE)
    dwDroitUtilisateur += DROIT_AJOUTER_ELEMENT;

  if (m_bAddUtilisateur == TRUE)
    dwDroitUtilisateur += DROIT_AJOUTER_UTILISATEUR;

  if (m_bModifDroitUtilisateur == TRUE)
    dwDroitUtilisateur += DROIT_MODIFIER_DROIT_UTILISATEUR;

  if (m_bModifierElement == TRUE)
    dwDroitUtilisateur += DROIT_MODIFIER_ELEMENT;

  if (m_bProprieteBase == TRUE)
    dwDroitUtilisateur += DROIT_MODIFIER_PROPRIETE_BASE;

  if (m_bSupprElement == TRUE)
    dwDroitUtilisateur += DROIT_SUPPRIMER_ELEMENT;

  if (m_bSupprUtilisateur == TRUE)
    dwDroitUtilisateur += DROIT_SUPPRIMER_UTILISATEUR;

  if (m_pDoc->ajouterUtilisateur(m_sNomLogin, m_sNomPassword1, dwDroitUtilisateur) == TRUE)
	  CDialog::OnOK();

}

BOOL CDialogNouvelUtilisateur::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  unsigned long dwDroitUtilisateur;

  dwDroitUtilisateur = m_pDoc->GetDroitUtilisateurCourant();

  // autoriser les checkbox seulement si l'utilisateur a le meme droit
  // i.e. on peut autoriser ce que l'on a deja *, ni +, ni -

  if ((dwDroitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
    m_buttonAddElement.EnableWindow(TRUE);
  else
    m_buttonAddElement.EnableWindow(FALSE);


  if ((dwDroitUtilisateur & DROIT_MODIFIER_ELEMENT) == DROIT_MODIFIER_ELEMENT)
    m_buttonModifierElement.EnableWindow(TRUE);
  else
    m_buttonModifierElement.EnableWindow(FALSE);


  if ((dwDroitUtilisateur & DROIT_SUPPRIMER_ELEMENT) == DROIT_SUPPRIMER_ELEMENT)
    m_buttonSupprElement.EnableWindow(TRUE);
  else
    m_buttonSupprElement.EnableWindow(FALSE);


  if ((dwDroitUtilisateur & DROIT_AJOUTER_UTILISATEUR) == DROIT_AJOUTER_UTILISATEUR)
    m_buttonAddUtilisateur.EnableWindow(TRUE);
  else
    m_buttonAddUtilisateur.EnableWindow(FALSE);


  if ((dwDroitUtilisateur & DROIT_MODIFIER_DROIT_UTILISATEUR) == DROIT_MODIFIER_DROIT_UTILISATEUR)
    m_buttonModifDroitUtilisateur.EnableWindow(TRUE);
  else
    m_buttonModifDroitUtilisateur.EnableWindow(FALSE);


  if ((dwDroitUtilisateur & DROIT_SUPPRIMER_UTILISATEUR) == DROIT_SUPPRIMER_UTILISATEUR)
    m_buttonSupprUtilisateur.EnableWindow(TRUE);
  else
    m_buttonSupprUtilisateur.EnableWindow(FALSE);


  if ((dwDroitUtilisateur & DROIT_MODIFIER_PROPRIETE_BASE) == DROIT_MODIFIER_PROPRIETE_BASE)
    m_buttonPropBase.EnableWindow(TRUE);
  else
    m_buttonPropBase.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
