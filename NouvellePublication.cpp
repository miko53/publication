// NouvellePublication.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "direct.h"
#include "NouvellePublication.h"
#include "SelectionRepertoire.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNouvellePublication dialog


CNouvellePublication::CNouvellePublication(CWnd* pParent /*=NULL*/)
	: CDialog(CNouvellePublication::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNouvellePublication)
	m_nomBase = _T("");
	m_nomSauvegarde = _T("");
	m_passWord1 = _T("");
	m_passWord2 = _T("");
	m_repertoireSauvegarde = _T("");
	m_nomRoot = _T("");
	//}}AFX_DATA_INIT
}


void CNouvellePublication::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNouvellePublication)
	DDX_Text(pDX, IDC_NOM_BASE, m_nomBase);
	DDX_Text(pDX, IDC_NOM_SAUVEGARDE, m_nomSauvegarde);
	DDX_Text(pDX, IDC_PASSWORD1, m_passWord1);
	DDV_MaxChars(pDX, m_passWord1, 8);
	DDX_Text(pDX, IDC_PASSWORD2, m_passWord2);
	DDV_MaxChars(pDX, m_passWord2, 8);
	DDX_Text(pDX, IDC_REPERTOIRE_SAUVEGARDE, m_repertoireSauvegarde);
	DDX_Text(pDX, IDC_ROOTNAME, m_nomRoot);
	DDV_MaxChars(pDX, m_nomRoot, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNouvellePublication, CDialog)
	//{{AFX_MSG_MAP(CNouvellePublication)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNouvellePublication message handlers

void CNouvellePublication::OnButton1() 
{
	CSelectionRepertoire m_FileDialog;

	UpdateData(TRUE);

	if (m_FileDialog.DoModal() == IDOK)
	{
		m_repertoireSauvegarde = m_FileDialog.m_snomRepertoire;
		UpdateData(FALSE);
	}
}

void CNouvellePublication::OnOK() 
{
	/* verification des infos */
	UpdateData(TRUE);
	
	/* utilisateur */
	if (m_nomRoot.IsEmpty() == TRUE)
	{
		AfxMessageBox(_T("Il faut entrer un nom pour le super utilisateur !"), MB_OK);
		return;
	}

	if (m_nomBase.IsEmpty() == TRUE)
	{
		AfxMessageBox(_T("Votre base n'a pas de nom !"), MB_OK);
		return;
	}


	/* mot de passe */
	if ((m_passWord1 != m_passWord2) ||	(m_passWord1.IsEmpty() == TRUE))
	{
		AfxMessageBox(_T("Votre mot de passe est incorrecte !"), MB_OK);
		return;
	}

	/* Verification directory de sauvegarde */
	if (m_repertoireSauvegarde.IsEmpty())
	{
		AfxMessageBox(_T("Pas de répertoire de sauvegarde specifié"));
		return;
	}

	if (m_repertoireSauvegarde[1] != ':' && m_repertoireSauvegarde[1] != '\\')
	{
		AfxMessageBox(_T("Répertoire de sauvegarde incorrect !"));
		return;
	}

	CFileFind searchDir;
	BOOL result;
	result = searchDir.FindFile(m_repertoireSauvegarde);
	if (result == FALSE)
	{
		if (AfxMessageBox(_T("Le répertoire de sauvegarde n'existe pas \n  voulez-vous le creer ?"), MB_YESNO) == IDYES)
		{
			if (_mkdir(m_repertoireSauvegarde) != 0)
			{
				AfxMessageBox(_T("Création du répertoire impossible !"));
				return;
			}
		}
	}

	/* nomSauvegarde  */
	/* extension .pub */
	CString tempo;

	if (m_nomSauvegarde.IsEmpty())
	{
		AfxMessageBox(_T("Pas de nom de sauvegarde specifié"));
		return;
	}

	if (m_nomSauvegarde.Right(4) != _T(".pub"))
	{
		tempo = m_nomSauvegarde;
		m_nomSauvegarde.Format(_T("%s.pub"), tempo);
	}

	tempo = m_nomSauvegarde;
	m_nomSauvegarde.Format(_T("%s\\%s"), pubInfo.databaseDirectory, tempo);

	/* exist-il deja ? format correct */
	result = searchDir.FindFile(m_nomSauvegarde);
	if (result == TRUE)
	{
		AfxMessageBox(_T("Cette base existe déjà !"));
		return;
	}

	CFile dataBaseFile;
	CFileException exceptionFile;
	if (!dataBaseFile.Open(m_nomSauvegarde, CFile::modeCreate | CFile::modeWrite, &exceptionFile))
	{
		AfxMessageBox(_T("Le fichier de sauvegarde ne peut être créer !"));
		dataBaseFile.Close();
		return;
	}

	dataBaseFile.Close();
	dataBaseFile.Remove(m_nomSauvegarde);

	UpdateData(FALSE);
	
	CDialog::OnOK();
}
