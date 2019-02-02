// PropInfoMotClef.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropInfoMotClef.h"
#include "AjouterMotClefDialog.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropInfoMotClef property page

IMPLEMENT_DYNCREATE(CPropInfoMotClef, CPropertyPage)

CPropInfoMotClef::CPropInfoMotClef() : CPropertyPage(CPropInfoMotClef::IDD)
{
	//{{AFX_DATA_INIT(CPropInfoMotClef)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropInfoMotClef::~CPropInfoMotClef()
{
}

void CPropInfoMotClef::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropInfoMotClef)
	DDX_Control(pDX, IDC_LIST_MOT_CLEF, m_ListMotClefPub);
	DDX_Control(pDX, IDC_LIST_ALL_MOT_CLEF, m_ListBoxAllMotClef);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropInfoMotClef, CPropertyPage)
	//{{AFX_MSG_MAP(CPropInfoMotClef)
	ON_BN_CLICKED(IDC_ADD_MOT_CLEFS, OnAddMotClefs)
	ON_BN_CLICKED(IDC_DANS_LISTE_PUB, OnDansListePub)
	ON_BN_CLICKED(IDC_REMOVE_ALL_ELEMENT, OnRemoveAllElement)
	ON_BN_CLICKED(IDC_REMOVE_DE_PUB, OnRemoveElementSelectionne)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPropInfoMotClef::AddDocument(CPublicationDoc * pDoc)
{
  m_pDoc = pDoc;
}


/////////////////////////////////////////////////////////////////////////////
// CPropInfoMotClef message handlers

void CPropInfoMotClef::OnAddMotClefs() 
{
	CAjouterMotClefDialog aDlg(o_OUVERTURE_NORMAL, -1, m_pDoc);

	aDlg.DoModal();

	m_pDoc->mettreAJourMotClef(m_ListBoxAllMotClef);

}

void CPropInfoMotClef::OnDansListePub() 
{
	int i;
	int j;
	int nbDonnees;
	int *piBufferSelectedItem;
	DWORD dwId;
	BOOL bFind;
	int nIndex;
	CString tempo;


	nbDonnees = m_ListBoxAllMotClef.GetSelCount();

	if (nbDonnees == LB_ERR)
		return;

	piBufferSelectedItem = new int[nbDonnees];


	if (m_ListBoxAllMotClef.GetSelItems(nbDonnees, piBufferSelectedItem) == LB_ERR)
	{
		delete [] piBufferSelectedItem;
		return;
	}


	for(i=0;i<nbDonnees;i++)
	{
		nIndex = piBufferSelectedItem[i];
		dwId = m_ListBoxAllMotClef.GetItemData(nIndex);
		bFind = FALSE;

		for(j = 0;j<m_ListMotClefPub.GetCount();j++)
		{
			if (dwId == m_ListMotClefPub.GetItemData(j))
				bFind = TRUE;
		}

		if (bFind == FALSE)
		{
			m_ListBoxAllMotClef.GetText(nIndex, tempo);
			nIndex = m_ListMotClefPub.InsertString(-1, tempo);
			m_ListMotClefPub.SetItemData(nIndex, dwId);
      DocumentModifier();
		}
	}

	delete [] piBufferSelectedItem;

}

BOOL CPropInfoMotClef::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

	int i;
	POSITION aPos;
	long idMotClef;
	int indexListeMC;
	CString tempoMotClef;
  CList<long, long&> listTemporaire;

  aPos = (pSheet->m_donneesDocument).listMotClefs.GetHeadPosition();
  long tempoID;

  while (aPos)
  {
    tempoID = (pSheet->m_donneesDocument).listMotClefs.GetNext(aPos);
    listTemporaire.AddHead(tempoID);
  }



	m_pDoc->mettreAJourMotClef(m_ListBoxAllMotClef);

	// mettre a jour la liste des mots clef pour ce document
	for(i = 0; i<m_ListBoxAllMotClef.GetCount();i++)
	{
		if (listTemporaire.IsEmpty() == FALSE)
		{
			aPos = listTemporaire.GetHeadPosition();
			while (aPos)
			{
				idMotClef = listTemporaire.GetAt(aPos);
				if (idMotClef == (long) m_ListBoxAllMotClef.GetItemData(i))
				{
					m_ListBoxAllMotClef.GetText(i, tempoMotClef);
					indexListeMC = m_ListMotClefPub.AddString(tempoMotClef);
					m_ListMotClefPub.SetItemData(indexListeMC, (DWORD) idMotClef);
					listTemporaire.RemoveAt(aPos);
					break;
				}
				listTemporaire.GetNext(aPos);
			}
		}
		else
		 break;
	}

	if (listTemporaire.IsEmpty() == FALSE)
		return FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropInfoMotClef::OnRemoveAllElement() 
{
	m_ListMotClefPub.ResetContent();
	DocumentModifier();	
}

void CPropInfoMotClef::OnRemoveElementSelectionne() 
{
	int i;
	int nbDonnees;
	int *piBufferSelectedItem;

	nbDonnees = m_ListMotClefPub.GetSelCount();

	if (nbDonnees == LB_ERR)
		return;

	piBufferSelectedItem = new int[nbDonnees];

	if (m_ListMotClefPub.GetSelItems(nbDonnees, piBufferSelectedItem) == LB_ERR)
	{
		delete [] piBufferSelectedItem;
		return;
	}

	for(i=0;i<nbDonnees;i++)
	{
		m_ListMotClefPub.DeleteString(piBufferSelectedItem[0]);
		m_ListMotClefPub.GetSelItems(nbDonnees, piBufferSelectedItem);
	}

	delete [] piBufferSelectedItem;

  if (nbDonnees != 0)
  	DocumentModifier();
}

void CPropInfoMotClef::DocumentModifier()
{
  CModifierPublicationPropSheet* pSheet = (CModifierPublicationPropSheet*) GetParent();
	ASSERT_KINDOF(CModifierPublicationPropSheet, pSheet);

  SetModified();
  pSheet->m_bDocModifier = true;
  pSheet->m_bMotClefModifier = true;

}
