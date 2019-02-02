// RechercheAvdDocument.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "RechercheAvdDocument.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechercheAvdDocument dialog


CRechercheAvdDocument::CRechercheAvdDocument(CPublicationDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CRechercheAvdDocument::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechercheAvdDocument)
	m_bNomDocument = FALSE;
	m_bNomAuteur = FALSE;
	m_bNomSujet = FALSE;
	m_bNomGenre = FALSE;
	m_bMotClefs = FALSE;
	//}}AFX_DATA_INIT

  m_pDoc = pDoc;
}


void CRechercheAvdDocument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechercheAvdDocument)
	DDX_Control(pDX, IDC_PROPRIETE, m_buttonPropriete);
	DDX_Control(pDX, IDC_AFFICHER, m_buttonAfficher);
	DDX_Control(pDX, IDC_LIST_DOCUMENT, m_listCtrlDocument);
	DDX_Control(pDX, IDC_LIST_MOT_CLEF, m_listBoxMotClef);
	DDX_Control(pDX, IDC_NomMotClef, m_comboBoxNomMotClef);
	DDX_Control(pDX, IDC_AJOUTER_MOTCLES, m_buttonAjouterMotClef);
	DDX_Control(pDX, IDC_RETIRER_MOTCLES, m_buttonRetirerMotClef);
	DDX_Control(pDX, IDC_NomGenre, m_comboBoxNomGenre);
	DDX_Control(pDX, IDC_NomSujet, m_comboBoxNomSujet);
	DDX_Control(pDX, IDC_NomDocument, m_editNomDocument);
	DDX_Control(pDX, IDC_NomAuteur, m_comboBoxNomAuteur);
	DDX_Check(pDX, IDC_Nom, m_bNomDocument);
	DDX_Check(pDX, IDC_NOM_AUTEUR, m_bNomAuteur);
	DDX_Check(pDX, IDC_SUJET, m_bNomSujet);
	DDX_Check(pDX, IDC_GENRE, m_bNomGenre);
	DDX_Check(pDX, IDC_MOT_CLEF, m_bMotClefs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechercheAvdDocument, CDialog)
	//{{AFX_MSG_MAP(CRechercheAvdDocument)
	ON_BN_CLICKED(IDC_Nom, OnCocheNomDocument)
	ON_BN_CLICKED(IDC_NOM_AUTEUR, OnCocheNomAuteur)
	ON_BN_CLICKED(IDC_SUJET, OnCocheNomSujet)
	ON_BN_CLICKED(IDC_GENRE, OnCocheGenre)
	ON_BN_CLICKED(IDC_MOT_CLEF, OnCocheMotClef)
	ON_BN_CLICKED(IDLANCERECHERCHE, OnLancerecherche)
	ON_BN_CLICKED(IDC_AJOUTER_MOTCLES, OnAjouterMotcles)
	ON_BN_CLICKED(IDC_RETIRER_MOTCLES, OnRetirerMotcles)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DOCUMENT, OnItemchangedListDocument)
	ON_BN_CLICKED(IDC_AFFICHER, OnClickAfficher)
	ON_BN_CLICKED(IDC_PROPRIETE, OnClickPropriete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechercheAvdDocument message handlers

BOOL CRechercheAvdDocument::OnInitDialog() 
{
	CDialog::OnInitDialog();


  m_listCtrlDocument.InsertColumn(0, "Titre", LVCFMT_LEFT, 150, 0);
	m_listCtrlDocument.InsertColumn(1, "Sujet", LVCFMT_LEFT, 150, 1);
	m_listCtrlDocument.InsertColumn(2, "Auteur", LVCFMT_LEFT, 100, 2);
	m_listCtrlDocument.InsertColumn(3, "Categorie", LVCFMT_LEFT, 120, 3);

  // init valeur par defaut 
	m_bNomDocument = TRUE;
  m_editNomDocument.EnableWindow(TRUE);
  m_bNomAuteur = FALSE;
	m_bNomSujet = FALSE;
	m_bNomGenre = FALSE;
	m_bMotClefs = FALSE;

  // remplissage des comboBox
  m_pDoc->mettreAJourListeAuteur(m_comboBoxNomAuteur);
  m_pDoc->mettreAJourListeSujet(m_comboBoxNomSujet);
  m_pDoc->mettreAJourListeGenre(m_comboBoxNomGenre);
  m_pDoc->mettreAJourMotClef(m_comboBoxNomMotClef);
  UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRechercheAvdDocument::OnCocheNomDocument() 
{
  if (m_bNomDocument == FALSE)
  {
    m_bNomDocument = TRUE;
    m_editNomDocument.EnableWindow();
  }
  else
  {
    m_bNomDocument = FALSE;
    m_editNomDocument.EnableWindow(FALSE);
  }
}

void CRechercheAvdDocument::OnCocheNomAuteur() 
{
  if (m_bNomAuteur == TRUE)
  {
    m_bNomAuteur = FALSE;
    m_comboBoxNomAuteur.EnableWindow(FALSE);
  }
  else
  {
    m_bNomAuteur = TRUE;
    m_comboBoxNomAuteur.EnableWindow(TRUE);
  }
}

void CRechercheAvdDocument::OnCocheNomSujet() 
{
  if (m_bNomSujet == TRUE)
  {
    m_bNomSujet = FALSE;
    m_comboBoxNomSujet.EnableWindow(FALSE);
  }
  else
  {
    m_bNomSujet = TRUE;
    m_comboBoxNomSujet.EnableWindow(TRUE);
  }
}

void CRechercheAvdDocument::OnCocheGenre() 
{
  if (m_bNomGenre == TRUE)
  {
    m_bNomGenre = FALSE;
    m_comboBoxNomGenre.EnableWindow(FALSE);
  }
  else
  {
    m_bNomGenre = TRUE;
    m_comboBoxNomGenre.EnableWindow(TRUE);
  }
}

void CRechercheAvdDocument::OnCocheMotClef() 
{
  if ( m_bMotClefs == TRUE)
  {
    m_bMotClefs = FALSE;
    m_buttonAjouterMotClef.EnableWindow(FALSE);
    m_buttonRetirerMotClef.EnableWindow(FALSE);
    m_comboBoxNomMotClef.EnableWindow(FALSE);
    m_listBoxMotClef.EnableWindow(FALSE);
  }
  else
  {
    m_bMotClefs = TRUE;
    m_buttonAjouterMotClef.EnableWindow(TRUE);
    m_buttonRetirerMotClef.EnableWindow(TRUE);
    m_comboBoxNomMotClef.EnableWindow(TRUE);
    m_listBoxMotClef.EnableWindow(TRUE);
  }
}

void CRechercheAvdDocument::OnAjouterMotcles() 
{
  int nIndex = m_comboBoxNomMotClef.GetCurSel();
  CString sNomChamp;
  m_comboBoxNomMotClef.GetWindowText(sNomChamp);

  if (nIndex == CB_ERR)
  { 
    // recherche la string exactement
    if (m_listBoxMotClef.FindString(-1, sNomChamp) == LB_ERR)
    {
      // il n'existe pas l'ajouter
      int nIndex2;
      nIndex2 = m_listBoxMotClef.InsertString(-1, sNomChamp);
			m_listBoxMotClef.SetItemData(nIndex2, (DWORD) -1);
    }
  }
  else
  {
    int i;
    DWORD dwID;
    BOOL bFind = FALSE;

    dwID = m_comboBoxNomMotClef.GetItemData(nIndex);

    // recherche avec l'identifier du mot clef
    for(i = 0; i< m_listBoxMotClef.GetCount(); i++)
    {
      if (dwID == m_listBoxMotClef.GetItemData(i))
      {
				bFind = TRUE;
        break;
      }
    }

    if (bFind == FALSE)
    {
      int nIndex2;
      nIndex2 = m_listBoxMotClef.InsertString(-1, sNomChamp);
			m_listBoxMotClef.SetItemData(nIndex2, dwID);
    }
  }	
}

void CRechercheAvdDocument::OnRetirerMotcles() 
{
  // Lire la selection 
  // et les retirer de la liste si il y au moins une selection
	int i;
	int nbDonnees;
	int *piBufferSelectedItem;

	nbDonnees = m_listBoxMotClef.GetSelCount();

	if (nbDonnees == LB_ERR)
		return;

	piBufferSelectedItem = new int[nbDonnees];

	if (m_listBoxMotClef.GetSelItems(nbDonnees, piBufferSelectedItem) == LB_ERR)
	{
		delete [] piBufferSelectedItem;
		return;
	}

	for(i=0;i<nbDonnees;i++)
	{
		m_listBoxMotClef.DeleteString(piBufferSelectedItem[0]);  // 0 est normal
		m_listBoxMotClef.GetSelItems(nbDonnees, piBufferSelectedItem);
	}

	delete [] piBufferSelectedItem;

}



void CRechercheAvdDocument::OnLancerecherche() 
{
  // ecrire la requete SQL
  // l'executer
  // puis c'est tout
  CString sRequete;
  CString sNomChamp;
  int nTailleSRequete = 0;
  unsigned char byIndiceRSQL = 0;
  CString sRequeteSQL[4];
  CString* psRequeteMotClef = NULL;

/*  if (m_bMotClefs == TRUE)
  {
    nTailleSRequete = m_listBoxMotClef.GetCount();
  }

  sRequeteSQL = new CString[4 + nTailleSRequete];
*/

  //Calcul de nombre de requete
  int nNbString = 0;
   

  if (m_bNomDocument == TRUE)
  {
    m_editNomDocument.GetWindowText(sNomChamp);
    if (sNomChamp != "")
    {
      sRequeteSQL[byIndiceRSQL].Format("([Titre] Like \"%s\")", sNomChamp);
      byIndiceRSQL++;
    }
  }

  if (m_bNomAuteur == TRUE)
  {
    int nIndex = m_comboBoxNomAuteur.GetCurSel();
    m_comboBoxNomAuteur.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdAuteur] IN (SELECT [IdAuteur] FROM [Auteur] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdAuteur] = %i)", (long) m_comboBoxNomAuteur.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }
  }

  if (m_bNomSujet == TRUE)
  {
    int nIndex = m_comboBoxNomSujet.GetCurSel();
    m_comboBoxNomSujet.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdSujet] IN (SELECT [IdSujet] FROM [Sujet] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdSujet] = %i)", (long) m_comboBoxNomSujet.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }
  }

  if (m_bNomGenre == TRUE)
  {
    int nIndex = m_comboBoxNomGenre.GetCurSel();
    m_comboBoxNomGenre.GetWindowText(sNomChamp);

    if (sNomChamp != "")
    {
      if (nIndex == CB_ERR)
      {
        // nous avons un champ different que les choix donnés
        sRequeteSQL[byIndiceRSQL].Format("([IdGenre] IN (SELECT [IdGenre] FROM [Genre] WHERE [Nom] Like \"%s\"))", sNomChamp);
        byIndiceRSQL++;
      }
      else
      {
        sRequeteSQL[byIndiceRSQL].Format("([IdGenre] = %i)", (long) m_comboBoxNomGenre.GetItemData(nIndex));
        byIndiceRSQL++;
      }
    }

  }

  if (m_bMotClefs == TRUE)
  {
    DWORD dwIDMotCles;
    int i;
    int nIndiceAjoutOr;
    psRequeteMotClef = new CString[m_listBoxMotClef.GetCount()];
    unsigned char byIndiceMotClef = 0;

    for(i = 0;i < m_listBoxMotClef.GetCount(); i++)
    {
      dwIDMotCles = m_listBoxMotClef.GetItemData(i);
      if (dwIDMotCles == (DWORD) -1)
      {
        CString nom;
        m_listBoxMotClef.GetText(i, nom);
        // faire la recherche par nom
        psRequeteMotClef[byIndiceMotClef].Format("([IdDocument] IN (SELECT [IdDoc] FROM [RelationDocMotCles] WHERE ([IdMotCles] IN (SELECT [IdMotCles] FROM [MotCles] WHERE [nom] LIKE \"%s\"))))", nom);
      }
      else
      {
        // faire la recherche par Id
        psRequeteMotClef[byIndiceMotClef].Format("([IdDocument] IN (SELECT [IdDoc] FROM [RelationDocMotCles] WHERE [IdMotCles] = %i))", (long) dwIDMotCles);
      }
      byIndiceMotClef++;
    }

    // Formatage de la requete mot clef

    switch (byIndiceMotClef)
    {
    case 0:
      // pas de requete on ne fait rien
      break;

    case 1:
      // une seul requete
      sRequeteSQL[byIndiceRSQL] = psRequeteMotClef[0];
      byIndiceRSQL++;
      break;

    default:
      sRequeteSQL[byIndiceRSQL].Format("(%s ", psRequeteMotClef[0]);
      for(nIndiceAjoutOr = 1; nIndiceAjoutOr<(int) byIndiceMotClef; nIndiceAjoutOr++)
      {
        sRequeteSQL[byIndiceRSQL] += " OR ";
        sRequeteSQL[byIndiceRSQL] += psRequeteMotClef[nIndiceAjoutOr];
      }
      sRequeteSQL[byIndiceRSQL] += ")";
      byIndiceRSQL++;
      break;
    }

    delete [] psRequeteMotClef;
  }


  // Formatage de la requete dans sRequete
  int nIndiceAjoutAnd;

  switch (byIndiceRSQL)
  {
  case 0:
    // pas de requete on ne fait rien
    return;
    break;

  case 1:
    // une seul requete
    sRequete = sRequeteSQL[0];
    break;

  default:
    sRequete.Format("%s ", sRequeteSQL[0]);
    for(nIndiceAjoutAnd = 1; nIndiceAjoutAnd<(int) byIndiceRSQL; nIndiceAjoutAnd++)
    {
      sRequete += " AND ";
      sRequete += sRequeteSQL[nIndiceAjoutAnd];
    }
    break;
  }

//  AfxMessageBox(sRequete);

  m_pDoc->rechercheDocument(m_listCtrlDocument, sRequete);

}


void CRechercheAvdDocument::OnItemchangedListDocument(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
	{
		m_itemSelectionne = pNMListView->iItem;

		m_buttonAfficher.EnableWindow();
		m_buttonPropriete.EnableWindow();
	}
	else
	{
		m_buttonAfficher.EnableWindow(FALSE);
		m_buttonPropriete.EnableWindow(FALSE);
	}

	*pResult = 0;
}

void CRechercheAvdDocument::OnClickAfficher() 
{
	m_pDoc->afficherDocumentDansVueCourante((long) m_listCtrlDocument.GetItemData(m_itemSelectionne));
}

void CRechercheAvdDocument::OnClickPropriete() 
{
  CPubDocument* pDocument = m_pDoc->recherchePtrDocument((long) m_listCtrlDocument.GetItemData(m_itemSelectionne), m_pDoc->donnerRacine());
	CModifierPublicationPropSheet aPropSheet("Propriétés du document", m_pDoc, pDocument);

	aPropSheet.DoModal();
}
