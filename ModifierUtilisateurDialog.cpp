// ModifierUtilisateurDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "ModifierUtilisateurDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifierUtilisateurDialog dialog


CModifierUtilisateurDialog::CModifierUtilisateurDialog(CPublicationDoc* pDoc, CString sNomLogin, CWnd* pParent /*=NULL*/)
	: CDialog(CModifierUtilisateurDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifierUtilisateurDialog)
	m_sNomLoginEntrer = _T("");
	//}}AFX_DATA_INIT

  ASSERT(pDoc != NULL);

  m_pDoc = pDoc;
  m_sNomLogin = sNomLogin;
}


void CModifierUtilisateurDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifierUtilisateurDialog)
	DDX_Control(pDX, IDC_CHECK_SUPPRIMER_ELEMENT, m_buttonSupprElement);
	DDX_Control(pDX, IDC_CHECK_SUPPR_UTILISATEUR, m_buttonSupprUtilisateur);
	DDX_Control(pDX, IDC_CHECK_PROP_BASE, m_buttonPropBase);
	DDX_Control(pDX, IDC_CHECK_MODIFIER_ELEMENT, m_buttonModifierElement);
	DDX_Control(pDX, IDC_CHECK_MODI_DROIT_UTILISATEUR, m_buttonModifDroitUtilisateur);
	DDX_Control(pDX, IDC_CHECK_ADD_UTILISATEUR, m_buttonAddUtilisateur);
	DDX_Control(pDX, IDC_CHECK_ADD_ELEMENT, m_buttonAddElement);
	DDX_Text(pDX, IDC_NOM_UTLISATEUR, m_sNomLoginEntrer);
	DDV_MaxChars(pDX, m_sNomLoginEntrer, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifierUtilisateurDialog, CDialog)
	//{{AFX_MSG_MAP(CModifierUtilisateurDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifierUtilisateurDialog message handlers

BOOL CModifierUtilisateurDialog::OnInitDialog() 
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


  //checker les droits que possede deja l'utilisateur
  m_sNomLoginEntrer = m_sNomLogin;
  dwDroitUtilisateur = m_pDoc->donnerInfoUtilisateur(m_sNomLogin);

  if ((dwDroitUtilisateur & DROIT_AJOUTER_ELEMENT) == DROIT_AJOUTER_ELEMENT)
    m_buttonAddElement.SetCheck(1);
  else
    m_buttonAddElement.SetCheck(0);


  if ((dwDroitUtilisateur & DROIT_MODIFIER_ELEMENT) == DROIT_MODIFIER_ELEMENT)
    m_buttonModifierElement.SetCheck(1);
  else
    m_buttonModifierElement.SetCheck(0);


  if ((dwDroitUtilisateur & DROIT_SUPPRIMER_ELEMENT) == DROIT_SUPPRIMER_ELEMENT)
    m_buttonSupprElement.SetCheck(1);
  else
    m_buttonSupprElement.SetCheck(0);


  if ((dwDroitUtilisateur & DROIT_AJOUTER_UTILISATEUR) == DROIT_AJOUTER_UTILISATEUR)
    m_buttonAddUtilisateur.SetCheck(1);
  else
    m_buttonAddUtilisateur.SetCheck(0);


  if ((dwDroitUtilisateur & DROIT_MODIFIER_DROIT_UTILISATEUR) == DROIT_MODIFIER_DROIT_UTILISATEUR)
    m_buttonModifDroitUtilisateur.SetCheck(1);
  else
    m_buttonModifDroitUtilisateur.SetCheck(0);


  if ((dwDroitUtilisateur & DROIT_SUPPRIMER_UTILISATEUR) == DROIT_SUPPRIMER_UTILISATEUR)
    m_buttonSupprUtilisateur.SetCheck(1);
  else
    m_buttonSupprUtilisateur.SetCheck(0);


  if ((dwDroitUtilisateur & DROIT_MODIFIER_PROPRIETE_BASE) == DROIT_MODIFIER_PROPRIETE_BASE)
    m_buttonPropBase.SetCheck(1);
  else
    m_buttonPropBase.SetCheck(0);


  UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModifierUtilisateurDialog::OnOK() 
{
  // effectuer la modification si droit OK

  // compter le nombre de 1 chacun
  // effectuer les modifs
  unsigned long dwDroitUtilisateur = 0;

  UpdateData();

  // calculer les nouveaux droits
  if (m_buttonAddElement.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_AJOUTER_ELEMENT;

  if (m_buttonAddUtilisateur.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_AJOUTER_UTILISATEUR;

  if (m_buttonModifDroitUtilisateur.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_MODIFIER_DROIT_UTILISATEUR;

  if (m_buttonModifierElement.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_MODIFIER_ELEMENT;

  if (m_buttonPropBase.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_MODIFIER_PROPRIETE_BASE;

  if (m_buttonSupprElement.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_SUPPRIMER_ELEMENT;

  if (m_buttonSupprUtilisateur.GetCheck() == 1)
    dwDroitUtilisateur += DROIT_SUPPRIMER_UTILISATEUR;



  if (m_pDoc->modifierUtilisateur(m_sNomLogin, m_sNomLoginEntrer, dwDroitUtilisateur) == true)
	  CDialog::OnOK();
}
