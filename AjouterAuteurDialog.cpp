// AjouterAuteurDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Publication.h"
#include "AjouterAuteurDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjouterAuteurDialog dialog


CAjouterAuteurDialog::CAjouterAuteurDialog(unsigned char typeOuverture, long IDAuteur, CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CAjouterAuteurDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjouterAuteurDialog)
	m_NaissanceString = _T("");
	m_MortString = _T("");
	m_NomAuteur = _T("");
	m_PrenomAuteur = _T("");
	m_RenseignementAuteur = _T("");
	m_Nationalite = _T("");
	//}}AFX_DATA_INIT

	m_IDAuteur = (-1);

	ASSERT(pDoc != NULL);

	m_pDoc = pDoc;
	m_appel = typeOuverture;
	m_IDAuteur = IDAuteur;
}


void CAjouterAuteurDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjouterAuteurDialog)
	DDX_Control(pDX, IDC_AUTHOR_PRENAME, m_CtrlPrenom);
	DDX_Control(pDX, IDC_AUTHOR_NAME, m_CtrlName);
	DDX_Control(pDX, IDC_AUTHOR_NAISSANCE, m_CtrlNaissance);
	DDX_Control(pDX, IDC_AUTHOR_MORT, m_CtrlMortDate);
	DDX_Control(pDX, IDC_AUTHOR_COMPLEMENT, m_CtrlRenseignement);
	DDX_Control(pDX, IDNOUVEAU, m_BouttonNouveau);
	DDX_Control(pDX, IDMODIFY, m_BouttonModifier);
	DDX_Control(pDX, IDADD, m_BouttonAjouter);
	DDX_Control(pDX, IDC_AUTHOR_NATIONALITY, m_ControlNationalite);
	DDX_Text(pDX, IDC_AUTHOR_NAISSANCE, m_NaissanceString);
	DDX_Text(pDX, IDC_AUTHOR_MORT, m_MortString);
	DDX_Text(pDX, IDC_AUTHOR_NAME, m_NomAuteur);
	DDX_Text(pDX, IDC_AUTHOR_PRENAME, m_PrenomAuteur);
	DDX_Text(pDX, IDC_AUTHOR_COMPLEMENT, m_RenseignementAuteur);
	DDX_CBString(pDX, IDC_AUTHOR_NATIONALITY, m_Nationalite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjouterAuteurDialog, CDialog)
	//{{AFX_MSG_MAP(CAjouterAuteurDialog)
	ON_BN_CLICKED(IDADD, OnAddAuteur)
	ON_BN_CLICKED(IDMODIFY, OnModifyAuteur)
	ON_BN_CLICKED(IDNOUVEAU, OnNouveauAuteur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjouterAuteurDialog message handlers

BOOL CAjouterAuteurDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	COleDateTime dateNaissance;
	COleDateTime dateMort;	



	m_pDoc->mettreAJourNationalite(&m_ControlNationalite);

	if (m_appel == o_OUVERTURE_NORMAL)
	{
		m_NaissanceString = _T("__/__/____");
		m_MortString = _T("__/__/____");
		m_BouttonAjouter.EnableWindow(TRUE);
		m_BouttonModifier.EnableWindow(FALSE);
		m_BouttonNouveau.EnableWindow(FALSE);
	}
	else // OUVERTURE PAR FENETRE DE RECHERCHE
	{
		OnModifyAuteur();
		m_pDoc->rechercherAuteur(m_NomAuteur, m_PrenomAuteur, dateNaissance, dateMort, m_Nationalite, m_RenseignementAuteur, m_IDAuteur);

		if (dateNaissance.GetStatus() == COleDateTime::valid)
			m_NaissanceString = dateNaissance.Format(_T("%d/%m/%Y"));
		else
			m_NaissanceString = _T("__/__/____");


		if (dateMort.GetStatus() == COleDateTime::valid)
			m_MortString = dateMort.Format(_T("%d/%m/%Y"));	
		else
			m_MortString = _T("__/__/____");
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAjouterAuteurDialog::OnAddAuteur() 
{
	CString temp;
	m_BouttonAjouter.GetWindowText(temp);

	UpdateData(TRUE);

	COleDateTime dateNaissance;
	COleDateTime dateMort;
	bool ok;
	long IDAuteur;

	dateNaissance.ParseDateTime(m_NaissanceString, VAR_DATEVALUEONLY);
	dateMort.ParseDateTime(m_MortString, VAR_DATEVALUEONLY);

	if (temp != "Mettre à jour")
	{
		// Appeler le doc pour ajouter l'auteur
		ok = m_pDoc->ajouterAuteur(m_NomAuteur, m_PrenomAuteur, dateNaissance, dateMort, m_Nationalite, m_RenseignementAuteur,
									m_ControlNationalite, IDAuteur);
		if (ok == true)
			m_IDAuteur = IDAuteur;
	}
	else
	{
		// Appeler le doc pour modifier l'auteur
		ok = m_pDoc->modifierAuteur(m_NomAuteur, m_PrenomAuteur, dateNaissance, dateMort, m_Nationalite, m_RenseignementAuteur,
									m_ControlNationalite, m_IDAuteur);
	}

	if (ok == true)
	{
		m_BouttonAjouter.EnableWindow(FALSE);
		m_BouttonModifier.EnableWindow(TRUE);
		m_BouttonNouveau.EnableWindow(TRUE);
	
		m_CtrlName.EnableWindow(FALSE);
		m_CtrlPrenom.EnableWindow(FALSE);
		m_CtrlNaissance.EnableWindow(FALSE);
		m_CtrlMortDate.EnableWindow(FALSE);
		m_ControlNationalite.EnableWindow(FALSE);
		m_CtrlRenseignement.EnableWindow(FALSE);
	}
}

void CAjouterAuteurDialog::OnModifyAuteur() 
{
	m_CtrlName.EnableWindow(TRUE);
	m_CtrlPrenom.EnableWindow(TRUE);
	m_CtrlNaissance.EnableWindow(TRUE);
	m_CtrlMortDate.EnableWindow(TRUE);
	m_ControlNationalite.EnableWindow(TRUE);
	m_CtrlRenseignement.EnableWindow(TRUE);

	m_BouttonAjouter.SetWindowText("Mettre à jour");

	m_BouttonAjouter.EnableWindow(TRUE);
	m_BouttonModifier.EnableWindow(FALSE);
	m_BouttonNouveau.EnableWindow(TRUE);
}


void CAjouterAuteurDialog::OnNouveauAuteur() 
{
	m_CtrlName.EnableWindow(TRUE);
	m_CtrlPrenom.EnableWindow(TRUE);
	m_CtrlNaissance.EnableWindow(TRUE);
	m_CtrlMortDate.EnableWindow(TRUE);
	m_ControlNationalite.EnableWindow(TRUE);
	m_CtrlRenseignement.EnableWindow(TRUE);

	m_MortString = "__/__/____";
	m_NaissanceString = "__/__/____";
	m_Nationalite = "";
	m_NomAuteur = "";
	m_PrenomAuteur = "";
	m_RenseignementAuteur = "";
	m_IDAuteur = -1;

	UpdateData(FALSE);

	m_BouttonAjouter.EnableWindow(TRUE);
	m_BouttonModifier.EnableWindow(FALSE);
	m_BouttonNouveau.EnableWindow(FALSE);

	m_BouttonAjouter.SetWindowText("Ajouter");

}
