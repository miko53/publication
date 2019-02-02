// modifierPassWordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "modifierPassWordDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CmodifierPassWordDialog dialog


CmodifierPassWordDialog::CmodifierPassWordDialog(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CmodifierPassWordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CmodifierPassWordDialog)
	m_sAncienPassWord = _T("");
	m_sNouveauPassWord1 = _T("");
	m_sNouveauPassWord2 = _T("");
	//}}AFX_DATA_INIT

  ASSERT(pDoc != NULL);
  m_pDoc = pDoc;
}


void CmodifierPassWordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CmodifierPassWordDialog)
	DDX_Text(pDX, IDC_ANCIEN_PASSWORD, m_sAncienPassWord);
	DDV_MaxChars(pDX, m_sAncienPassWord, 8);
	DDX_Text(pDX, IDC_NOUVEAU_PASSWORD, m_sNouveauPassWord1);
	DDV_MaxChars(pDX, m_sNouveauPassWord1, 8);
	DDX_Text(pDX, IDC_NOUVEAU_PASSWORD_2, m_sNouveauPassWord2);
	DDV_MaxChars(pDX, m_sNouveauPassWord2, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CmodifierPassWordDialog, CDialog)
	//{{AFX_MSG_MAP(CmodifierPassWordDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CmodifierPassWordDialog message handlers

void CmodifierPassWordDialog::OnOK() 
{
  int nRetour;

	UpdateData();
/*
	CString	m_sAncienPassWord;
	CString	m_sNouveauPassWord1;
	CString	m_sNouveauPassWord2;
*/
  if (m_sNouveauPassWord1 != m_sNouveauPassWord2)
  {
    AfxMessageBox("Vous devez répéter exactement votre nouveau mot de passe !");
    return;
  }

  nRetour = m_pDoc->ModifierMotDePasse(m_sAncienPassWord, m_sNouveauPassWord1);

  switch (nRetour)
  {
  case MODIF_OK: //1
    AfxMessageBox("Modification du mot de passe réussi");
	  CDialog::OnOK();
    break;

  case ANCIEN_PASSWORD_KO: //2
  default:  //0
    CDialog::OnOK();    
    break;    
  }


}
