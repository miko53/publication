// PropPageAjouterPubMotClef.cpp : implementation file
//

#include "stdafx.h"
#include "publication.h"
#include "PropPageAjouterPubMotClef.h"
#include "AjouterPublicationPropSheet.h"
#include "AjouterMotClefDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubMotClef property page

IMPLEMENT_DYNCREATE(CPropPageAjouterPubMotClef, CPropertyPage)

CPropPageAjouterPubMotClef::CPropPageAjouterPubMotClef() : CPropertyPage(CPropPageAjouterPubMotClef::IDD)
{
	//{{AFX_DATA_INIT(CPropPageAjouterPubMotClef)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropPageAjouterPubMotClef::~CPropPageAjouterPubMotClef()
{
}

void CPropPageAjouterPubMotClef::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageAjouterPubMotClef)
	DDX_Control(pDX, IDC_LIST_MOT_CLEF, m_ListMotClefPub);
	DDX_Control(pDX, IDC_LIST_ALL_MOT_CLEF, m_ListBoxAllMotClef);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageAjouterPubMotClef, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageAjouterPubMotClef)
	ON_BN_CLICKED(IDC_DANS_LISTE_PUB, OnDansListePub)
	ON_BN_CLICKED(IDC_REMOVE_ALL_ELEMENT, OnRemoveAllElement)
	ON_BN_CLICKED(IDC_REMOVE_DE_PUB, OnRemoveElementSelectionne)
	ON_BN_CLICKED(IDC_ADD_MOT_CLEFS, OnAddMotClefs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageAjouterPubMotClef message handlers

BOOL CPropPageAjouterPubMotClef::OnSetActive() 
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	ASSERT_KINDOF(CPropertySheet, pSheet);

	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	
	return CPropertyPage::OnSetActive();
}


void CPropPageAjouterPubMotClef::AddDocument(CPublicationDoc * pDoc)
{
	m_pDoc = pDoc;
}


BOOL CPropPageAjouterPubMotClef::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_pDoc->mettreAJourMotClef(m_ListBoxAllMotClef);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPropPageAjouterPubMotClef::OnRemoveAllElement() 
{
	m_ListMotClefPub.ResetContent();
}


void CPropPageAjouterPubMotClef::OnRemoveElementSelectionne() 
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
}


void CPropPageAjouterPubMotClef::OnDansListePub() 
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
		}
	}

	delete [] piBufferSelectedItem;
}

BOOL CPropPageAjouterPubMotClef::OnWizardFinish() 
{
	CAjouterPublicationPropSheet* pSheet = (CAjouterPublicationPropSheet*) GetParent();
	bool ajoutOK;

	ASSERT_KINDOF(CPropertySheet, pSheet);

	ajoutOK = pSheet->ajouterPublicationDansBase();


	if (ajoutOK == true)
		return CPropertyPage::OnWizardFinish();
	else
		return FALSE;
}

void CPropPageAjouterPubMotClef::OnAddMotClefs() 
{
	CAjouterMotClefDialog aDlg(o_OUVERTURE_NORMAL, -1, m_pDoc);

	aDlg.DoModal();

	m_pDoc->mettreAJourMotClef(m_ListBoxAllMotClef);

}
