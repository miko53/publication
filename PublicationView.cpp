// PublicationView.cpp : implementation of the CPublicationView class
//

#include "stdafx.h"
#include "Publication.h"

#include "PublicationDoc.h"
#include "PublicationView.h"
#include "PubElement.h"
#include "PubDocument.h"
#include "PubContainer.h"
#include "constElement.h"
#include "AddCategorie.h"
#include "PropCategorieDialog.h"
#include "AjouterPublicationPropSheet.h"
#include "ModifierPublicationPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPublicationView

IMPLEMENT_DYNCREATE(CPublicationView, CTreeView)

BEGIN_MESSAGE_MAP(CPublicationView, CTreeView)
	//{{AFX_MSG_MAP(CPublicationView)
	ON_COMMAND(ID_CATEGORIE_AJOUTER, OnCategorieAjouter)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_UPDATE_COMMAND_UI(ID_CATEGORIE_AJOUTER, OnUpdateCategorieAjouter)
	ON_UPDATE_COMMAND_UI(ID_CATEGORIE_SUPPRIMER, OnUpdateCategorieSupprimer)
	ON_COMMAND(ID_CATEGORIE_SUPPRIMER, OnCategorieSupprimer)
	ON_COMMAND(ID_CATEGORIE_PROPRIETES, OnCategorieProprietes)
	ON_UPDATE_COMMAND_UI(ID_CATEGORIE_PROPRIETES, OnUpdateCategorieProprietes)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(ID_PUBLICATION_AJOUTER, OnPublicationAjouter)
	ON_UPDATE_COMMAND_UI(ID_PUBLICATION_AJOUTER, OnUpdatePublicationAjouter)
	ON_UPDATE_COMMAND_UI(ID_PUBLICATION_SUPPRIMER, OnUpdatePublicationSupprimer)
	ON_COMMAND(ID_PUBLICATION_SUPPRIMER, OnPublicationSupprimer)
	ON_UPDATE_COMMAND_UI(ID_PUBLICATION_PROP, OnUpdatePublicationPropriete)
	ON_COMMAND(ID_PUBLICATION_PROP, OnPublicationPropriete)
	ON_UPDATE_COMMAND_UI(ID_PUBLICATION_OUVRIR, OnUpdatePublicationOuvrir)
	ON_COMMAND(ID_PUBLICATION_OUVRIR, OnPublicationOuvrir)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SSMENU_PROPRIETE, OnSsmenuPropriete)
	ON_COMMAND(ID_SSMENU_SUPPR, OnSsmenuSuppr)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPublicationView construction/destruction

CPublicationView::CPublicationView()
{
	m_pImageList = new CImageList();
	m_bDragAndDropEnCours = FALSE;
	m_pTempImageDragDrop = NULL;

}

CPublicationView::~CPublicationView()
{
	/* destruction de la liste d'image */
	if (m_pImageList != NULL)
		delete m_pImageList;

  if (m_pTempImageDragDrop != NULL)
    delete m_pTempImageDragDrop;

}

BOOL CPublicationView::PreCreateWindow(CREATESTRUCT& cs)
{

	BOOL resultatFunction = CTreeView::PreCreateWindow(cs);

	cs.style = cs.style | TVS_HASBUTTONS | TVS_EDITLABELS | TVS_HASLINES;

	return resultatFunction;
}

/////////////////////////////////////////////////////////////////////////////
// CPublicationView drawing

void CPublicationView::OnDraw(CDC* pDC)
{
	CPublicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  HTREEITEM hTI = GetTreeCtrl().GetRootItem();

  TEXTMETRIC textMetric;
  pDC->GetTextMetrics(&textMetric);

  m_nXStep = textMetric.tmMaxCharWidth;
  m_nYStep = textMetric.tmHeight + 6;

  m_nYIndentation = textMetric.tmHeight;

  DrawItem(hTI, pDC, textMetric.tmMaxCharWidth);


}

void CPublicationView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	BOOL ok = m_pImageList->Create(16, 16, (ILC_COLOR32 | ILC_MASK), 4, 4);

	if (ok != TRUE)
	{
		AfxMessageBox(_T("Error when TreeView created !"));
		AfxAbort();
	}

	m_pImageList->Add(pubInfo.pTabIcon[ICON_CATEGORIE]);
	m_pImageList->Add(pubInfo.pTabIcon[ICON_CATEGORIE_SELECT]);
	m_pImageList->Add(pubInfo.pTabIcon[ICON_ROOT]);
	m_pImageList->Add(pubInfo.pTabIcon[ICON_DOCUMENT]);

	GetTreeCtrl().SetImageList(m_pImageList, TVSIL_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CPublicationView printing

BOOL CPublicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPublicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPublicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPublicationView diagnostics

#ifdef _DEBUG
void CPublicationView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CPublicationView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CPublicationDoc* CPublicationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPublicationDoc)));
	return (CPublicationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPublicationView message handlers
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                         Update Message                                    //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void CPublicationView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if ((lHint == 1) && (pHint != NULL))
	{
		OnUpdateModification(pHint);
    //InvalidateRect(0);
		return;
	}

	if ((lHint == 2) && (pHint != NULL))
	{
		OnUpdateSuppression(pHint);
    //InvalidateRect(0);
		return;
	}

  if ((lHint == 3) && (pHint == NULL))
  {
    InvalidateRect(0);
    return;
  }


	CWaitCursor aCursor;
	CPubElement* pElementAjouter = (CPubElement*) pHint;
	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hThisItem;

	
	if (pHint == NULL)
	{
		// equivaut a une remise a jour total -- essai --
		GetTreeCtrl().DeleteAllItems();
		pElementAjouter = (CPubElement*) GetDocument()->donnerRacine();

		/* ajouter racine */
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = ICON_ROOT;
		tvstruct.item.iSelectedImage = ICON_ROOT;
		tvstruct.item.lParam = 0; //(LPARAM) pElementAjouter;  //le treeView pointe sur son homologue doc
		tvstruct.item.pszText = (char*) ((const char*)(pElementAjouter->donnerNom()));
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		hThisItem = GetTreeCtrl().InsertItem(&tvstruct);
		GetTreeCtrl().SetItemData(hThisItem, (DWORD) pElementAjouter);
		/* parcourir la racine pour ajouter d'eventuelles docu ou repertoire */
		miseAJourTreeView(pElementAjouter, hThisItem);
		GetTreeCtrl().Expand(hThisItem, TVE_EXPAND);
    GetTreeCtrl().SelectItem(GetTreeCtrl().GetRootItem());

		return;
	}

	/* pHint contient l'objet qui vient d'etre ajouter dans la base */

	if (pElementAjouter->donnerParent() == NULL)
	{
		/* remise a jour de toutes la base => initiale update 1 seule fois */
		GetTreeCtrl().DeleteAllItems();

		/* ajouter racine */
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = ICON_ROOT;
		tvstruct.item.iSelectedImage = ICON_ROOT;
		tvstruct.item.lParam = 0; //(LPARAM) pElementAjouter;  //le treeView pointe sur son homologue doc
		tvstruct.item.pszText = (char*) ((const char*)(pElementAjouter->donnerNom()));
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		hThisItem = GetTreeCtrl().InsertItem(&tvstruct);
		GetTreeCtrl().SetItemData(hThisItem, (DWORD) pElementAjouter);
		/* parcourir la racine pour ajouter d'eventuelles docu ou repertoire */
		miseAJourTreeView(pElementAjouter, hThisItem);
		GetTreeCtrl().Expand(hThisItem, TVE_EXPAND);
    GetTreeCtrl().SelectItem(GetTreeCtrl().GetRootItem());

	}
	else
	{
		// [ rechercher parent dans la vue actuelle ] 
		// ajouter dans parent selon le type d'objet 
		// verifier s'il n'existe pas ou tout effacer et mettre a jour

		hThisItem = rechercheParentDsVue(pElementAjouter->donnerParent(), GetTreeCtrl().GetRootItem());
		if (hThisItem != NULL)
		{
			switch (pElementAjouter->donnerTypeElement())
			{
			case ID_CATEGORIE:
				tvstruct.hParent = hThisItem;
				tvstruct.hInsertAfter = TVI_SORT;  //TVI_LAST
				tvstruct.item.iImage = ICON_CATEGORIE;
				tvstruct.item.iSelectedImage = ICON_CATEGORIE_SELECT;
				tvstruct.item.lParam = 0; //(LPARAM) pElementAjouter;  //le treeView pointe sur son homologue doc
				tvstruct.item.pszText = (char*) ((const char*)(pElementAjouter->donnerNom()));
				tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
				hThisItem = GetTreeCtrl().InsertItem(&tvstruct);
				GetTreeCtrl().SetItemData(hThisItem, (DWORD) pElementAjouter);		
				//GetTreeCtrl().Select(hThisItem, TVGN_CARET); //TVGN_CARET TVGN_DROPHILITE TVGN_FIRSTVISIBLE
				break;

			case ID_DOCUMENT:
				tvstruct.hParent = hThisItem;  
				tvstruct.hInsertAfter = TVI_SORT;  //TVI_FIRST
				tvstruct.item.iImage = ICON_DOCUMENT;
				tvstruct.item.iSelectedImage = ICON_DOCUMENT;
				tvstruct.item.lParam = 0; //(LPARAM) pElementAjouter;  //le treeView pointe sur son homologue doc
				tvstruct.item.pszText = (char*) ((const char*)(pElementAjouter->donnerNom()));
				tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
				hThisItem = GetTreeCtrl().InsertItem(&tvstruct);
				GetTreeCtrl().SetItemData(hThisItem, (DWORD) pElementAjouter);
				//GetTreeCtrl().Select(hThisItem, TVGN_CARET);
				break;

			default:
				break;
			}
		}
	}

  InvalidateRect(0);
}

// cas d'une modification de texte uniquement
void CPublicationView::OnUpdateModification(CObject * pHint)
{
	// rechercher la categorie ou l'objet dont le nom doit etre modifier
	CPubElement * pElement = (CPubElement*) pHint;

	HTREEITEM hThisItem;

	hThisItem = rechercheParentDsVue(pElement, GetTreeCtrl().GetRootItem());

	if (hThisItem != NULL)
	{
		GetTreeCtrl().SetItemText(hThisItem, (char*) ((const char*)(pElement->donnerNom())));
	}
}


void CPublicationView::OnUpdateSuppression(CObject * pHint)
{
	// rechercher la categorie qui doit etre supprimer
	CPubElement * pElement = (CPubElement*) pHint;

	HTREEITEM hThisItem;
	hThisItem = rechercheParentDsVue(pElement, GetTreeCtrl().GetRootItem());  

	if (hThisItem != NULL)
		GetTreeCtrl().DeleteItem(hThisItem);
}


void CPublicationView::miseAJourTreeView(CPubElement * pElement, HTREEITEM hItem)
{
	/* cette fonction met a jour le treeView pElement est en rapport avec item */

	if (((pElement->donnerTypeElement()) == ID_CATEGORIE) ||
		((pElement->donnerTypeElement()) == ID_RACINE))
	{
		/* parourir les enfants de la categorie ou de la racine */
		register CPubContainer* pContainer = (CPubContainer*) pElement;
		register CPubElement* pElementFils;
		register POSITION aPosition = pContainer->donnerPositionTete();

		while (aPosition)
		{
			TV_INSERTSTRUCT tvstruct;
			HTREEITEM hThisItem;

			pElementFils = pContainer->donnerProchainElement(aPosition);
			switch (pElementFils->donnerTypeElement())
			{
			case ID_CATEGORIE:
				tvstruct.hParent = hItem;
				tvstruct.hInsertAfter = TVI_SORT;  //TVI_FIRST
				tvstruct.item.iImage = ICON_CATEGORIE;
				tvstruct.item.iSelectedImage = ICON_CATEGORIE_SELECT;
				tvstruct.item.lParam = 0; //(LPARAM) pElementFils;  //le treeView pointe sur son homologue doc
				tvstruct.item.pszText = (char*) ((const char*)(pElementFils->donnerNom()));
				tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
				hThisItem = GetTreeCtrl().InsertItem(&tvstruct);
				GetTreeCtrl().SetItemData(hThisItem, (DWORD) pElementFils);

				miseAJourTreeView(pElementFils, hThisItem);

				break;

			case ID_DOCUMENT:
				tvstruct.hParent = hItem;
				tvstruct.hInsertAfter = TVI_SORT;   //TVI_LAST
				tvstruct.item.iImage = ICON_DOCUMENT;
				tvstruct.item.iSelectedImage = ICON_DOCUMENT;
				tvstruct.item.lParam = 0; //(LPARAM) pElementFils;  //le treeView pointe sur son homologue doc
				tvstruct.item.pszText = (char*) ((const char*)(pElementFils->donnerNom()));
				tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
				hThisItem = GetTreeCtrl().InsertItem(&tvstruct);
				GetTreeCtrl().SetItemData(hThisItem, (DWORD) pElementFils);
				break;

			case ID_RACINE:
			default:
				break;
			}
		}
	}
}


HTREEITEM CPublicationView::rechercheParentDsVue(CPubElement * pElement, HTREEITEM itemSearch)
{
	if (pElement == (CPubElement*) GetTreeCtrl().GetItemData(itemSearch))
		return itemSearch;
	else
	{
		register HTREEITEM hChild = GetTreeCtrl().GetChildItem(itemSearch);
		HTREEITEM hFind;

		while (hChild != NULL)
		{
			hFind = rechercheParentDsVue(pElement, hChild);
			if (hFind == NULL)
				hChild = GetTreeCtrl().GetNextSiblingItem(hChild);
			else
				return hFind;
		}

	return NULL;
	}
}


HTREEITEM CPublicationView::rechercheCategorieDsVue(long identificateur, HTREEITEM itemSearch)
{
	CPubElement *element;

	element = (CPubElement*) (GetTreeCtrl().GetItemData(itemSearch));

	if ((identificateur == element->donnerIdentificateur()) && 
		(element->donnerTypeElement() != ID_DOCUMENT) )
		return itemSearch;
	else
	{
		register HTREEITEM hChild = GetTreeCtrl().GetChildItem(itemSearch);
		HTREEITEM hFind;

		while (hChild != NULL)
		{
			hFind = rechercheCategorieDsVue(identificateur, hChild);
			if (hFind == NULL)
				hChild = GetTreeCtrl().GetNextSiblingItem(hChild);
			else
				return hFind;
		}

	return NULL;
	}
}

HTREEITEM CPublicationView::rechercheDocumentDsVue(long identificateur, HTREEITEM itemSearch)
{
	CPubElement *element;

	element = (CPubElement*) (GetTreeCtrl().GetItemData(itemSearch));

	if ((identificateur == element->donnerIdentificateur()) && 
		(element->donnerTypeElement() == ID_DOCUMENT) )
		return itemSearch;
	else
	{
		register HTREEITEM hChild = GetTreeCtrl().GetChildItem(itemSearch);
		HTREEITEM hFind;

		while (hChild != NULL)
		{
			hFind = rechercheDocumentDsVue(identificateur, hChild);
			if (hFind == NULL)
				hChild = GetTreeCtrl().GetNextSiblingItem(hChild);
			else
				return hFind;
		}

	return NULL;
	}
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                          Evenements                                       //
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Quand la selection du treeView change
void CPublicationView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	
	currentHTreeItem = pNMTreeView->itemNew.hItem;
	*pResult = 0;
}


void CPublicationView::OnUpdateCategorieAjouter(CCmdUI* pCmdUI) 
{
  if (GetDocument()->peutAjouterElemBase() == false)
  {
    pCmdUI->Enable(FALSE);
    return;
  }

	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

	switch(pElement->donnerTypeElement())
	{
	case ID_RACINE:
	case ID_CATEGORIE:
		pCmdUI->Enable();
		break;

	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CPublicationView::OnUpdateCategorieSupprimer(CCmdUI* pCmdUI) 
{
	if (GetDocument()->peutSupprimerElement() == false)
  {
		pCmdUI->Enable(FALSE);
    return;
  }

	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

	switch(pElement->donnerTypeElement())
	{
	//case ID_RACINE:
	case ID_CATEGORIE:
		pCmdUI->Enable();
		break;

	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}


void CPublicationView::OnUpdateCategorieProprietes(CCmdUI* pCmdUI) 
{
	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

	switch(pElement->donnerTypeElement())
	{
	case ID_RACINE:
	case ID_CATEGORIE:
		pCmdUI->Enable();
		break;

	default:
		pCmdUI->Enable(FALSE);
		break;
	}	
}

void CPublicationView::OnCategorieAjouter() 
{
	CAddCategorie ajouterCategorie;

	if (ajouterCategorie.DoModal() == IDOK)
	{
		GetDocument()->ajouterCategorie(ajouterCategorie.m_categorieName, (CPubElement*) GetTreeCtrl().GetItemData(currentHTreeItem));

	}
}


void CPublicationView::OnCategorieSupprimer() 
{
	if (AfxMessageBox(_T("Attention En effacant la categorie vous effacer toutes categories/documents s'y referant, voulez vous continuer ?"), (MB_DEFBUTTON2 | MB_YESNO)) == IDYES)
	{
		if (GetDocument()->supprimerCategorie((CPubContainer*) GetTreeCtrl().GetItemData(currentHTreeItem)) == true)
		{
			GetDocument()->UpdateAllViews(0, 2, (CObject*) GetTreeCtrl().GetItemData(currentHTreeItem));
		}
		else
		{
			// on ne sait jamais ce qui peut se passer
			GetDocument()->UpdateAllViews(0);
		}
	}	
}


void CPublicationView::OnCategorieProprietes() 
{

	CPropCategorieDialog dialogBox((CPubContainer*) GetTreeCtrl().GetItemData(currentHTreeItem), GetDocument());

	dialogBox.DoModal();
	
}

void CPublicationView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
  if (GetDocument()->peutModifierBase() == false)
  {
    *pResult = 0;
    return;
  }


	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	CPubElement *pElement = (CPubElement*) GetTreeCtrl().GetItemData(pTVDispInfo->item.hItem);

	if (pTVDispInfo->item.pszText == 0)
	{
		*pResult = 0;
	}
	else
	{
		bool result;
    stAjouterPublication DonneesPub;// = {0};

		switch (pElement->donnerTypeElement())
		{
		case ID_RACINE:
		case ID_CATEGORIE:
			result = GetDocument()->modifierCategorie((CPubContainer*) GetTreeCtrl().GetItemData(pTVDispInfo->item.hItem), pTVDispInfo->item.pszText);
			break;

		case ID_DOCUMENT:
      result = GetDocument()->changerNomPublication((CPubDocument*) GetTreeCtrl().GetItemData(pTVDispInfo->item.hItem), pTVDispInfo->item.pszText);
			break;

		default:
			result = false;
			break;
		}

		if (result == true)
		{
			*pResult = -1;
		}
		else
		{
			*pResult = 0;
		}
	}
}

void CPublicationView::selectionnerCategorie(long identificateur)
{
	HTREEITEM hThisItem;

	hThisItem = rechercheCategorieDsVue(identificateur, GetTreeCtrl().GetRootItem());

	if (hThisItem != NULL)
	{
		GetTreeCtrl().SelectItem(hThisItem);
	}
	else
	{
		AfxMessageBox(_T("Cette categorie n'est pas visible, erreur interne "));
	}
}


void CPublicationView::OnPublicationAjouter() 
{
	CAjouterPublicationPropSheet dlg("Ajouter un document", GetDocument(), (CPubElement*) GetTreeCtrl().GetItemData(currentHTreeItem));

	dlg.SetWizardMode();
	dlg.DoModal();
}


void CPublicationView::OnUpdatePublicationAjouter(CCmdUI* pCmdUI) 
{
  if (GetDocument()->peutAjouterElemBase() == false)
  {
    pCmdUI->Enable(FALSE);
    return;
  }

	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

	switch(pElement->donnerTypeElement())
	{
	case ID_RACINE:
	case ID_CATEGORIE:
		pCmdUI->Enable();
		break;

	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CPublicationView::OnUpdatePublicationSupprimer(CCmdUI* pCmdUI) 
{
	if (GetDocument()->peutSupprimerElement() == false)
  {
		pCmdUI->Enable(FALSE);
    return;
  }

	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

	switch(pElement->donnerTypeElement())
	{
	case ID_DOCUMENT:
		pCmdUI->Enable();
		break;

	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CPublicationView::OnPublicationSupprimer() 
{
	if (AfxMessageBox(_T("Etes-vous de vouloir effacer ce document ?"), (MB_DEFBUTTON2 | MB_YESNO)) == IDYES)
	{
		if (GetDocument()->supprimerDocument((CPubDocument*) GetTreeCtrl().GetItemData(currentHTreeItem)) == true)
		{
			GetDocument()->UpdateAllViews(0, 2, (CObject*) GetTreeCtrl().GetItemData(currentHTreeItem));
		}
		else
		{
			// on ne sait jamais ce qui peut se passer
			GetDocument()->UpdateAllViews(0);
		}
	}	
}

void CPublicationView::OnUpdatePublicationPropriete(CCmdUI* pCmdUI) 
{
	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

	switch(pElement->donnerTypeElement())
	{
	case ID_RACINE:
	case ID_CATEGORIE:
		pCmdUI->Enable(FALSE);
		break;

	default:
		pCmdUI->Enable();
		break;
	}	
}

void CPublicationView::OnPublicationPropriete() 
{
	CModifierPublicationPropSheet aPropSheet("Propriétés du document", GetDocument(), (CPubDocument*) GetTreeCtrl().GetItemData(currentHTreeItem));

	aPropSheet.DoModal();
}

void CPublicationView::OnUpdatePublicationOuvrir(CCmdUI* pCmdUI) 
{
	CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));
  CPubDocument* pDocument;

	switch(pElement->donnerTypeElement())
	{
	case ID_DOCUMENT:
    pDocument = (CPubDocument*) pElement;

    if (pDocument->isFile() == TRUE)
		  pCmdUI->Enable();
    else
		  pCmdUI->Enable(FALSE);

		break;

	default:
		pCmdUI->Enable(FALSE);
		break;
	}		
}

void CPublicationView::OnPublicationOuvrir() 
{
  CString nomFichier;
  
  nomFichier = GetDocument()->donnerNomFichierDocument((CPubDocument*) (GetTreeCtrl().GetItemData(currentHTreeItem)));

  ShellExecute(this->m_hWnd, "open", nomFichier, NULL, NULL, SW_SHOWNORMAL);
	
}

void CPublicationView::selectionnerDocument(long identificateur)
{
	HTREEITEM hThisItem;

	hThisItem = rechercheDocumentDsVue(identificateur, GetTreeCtrl().GetRootItem());

	if (hThisItem != NULL)
	{
		GetTreeCtrl().SelectItem(hThisItem);
	}
	else
	{
		AfxMessageBox(_T("Ce document n'est pas visible, erreur interne "));
	}
}

void CPublicationView::OnRButtonDown(UINT nFlags, CPoint point) 
{
  HTREEITEM hTreeItem;

  hTreeItem = GetTreeCtrl().HitTest(point, &nFlags);
  if (hTreeItem != NULL)
  {
	  currentHTreeItem = hTreeItem;
    GetTreeCtrl().SelectItem(currentHTreeItem);
  }
//	CTreeView::OnRButtonDown(nFlags, point);
}

void CPublicationView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menuTreeView;
  CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));
  CPubDocument* pDocument;
  
//	HTREEITEM currentTreeItem;
//  currentHTreeItem

//	currentHTreeItem = GetTreeCtrl().HitTest(point, &nFlags);
//  GetTreeCtrl().SelectItem(currentHTreeItem);

	menuTreeView.LoadMenu(IDR_MENU_CONTEXT_TREEVW);
	ClientToScreen(&point);

  switch (pElement->donnerTypeElement())
  {
	case ID_DOCUMENT:
    menuTreeView.EnableMenuItem(ID_CATEGORIE_AJOUTER, MF_DISABLED|MF_GRAYED);
    menuTreeView.EnableMenuItem(ID_PUBLICATION_AJOUTER, MF_DISABLED|MF_GRAYED);

    if (GetDocument()->peutSupprimerElement() == false)
    {
      menuTreeView.EnableMenuItem(ID_SSMENU_SUPPR, MF_DISABLED|MF_GRAYED);
    }

    pDocument = (CPubDocument*) pElement;
    if (pDocument->isFile() == FALSE)
      menuTreeView.EnableMenuItem(ID_PUBLICATION_OUVRIR, MF_DISABLED|MF_GRAYED);
    break;


	case ID_CATEGORIE:
    menuTreeView.EnableMenuItem(ID_PUBLICATION_OUVRIR, MF_DISABLED|MF_GRAYED);

    if (GetDocument()->peutSupprimerElement() == false)
    {
      menuTreeView.EnableMenuItem(ID_SSMENU_SUPPR, MF_DISABLED|MF_GRAYED);
    }


    if (GetDocument()->peutAjouterElemBase() == false)
    {
      menuTreeView.EnableMenuItem(ID_CATEGORIE_AJOUTER, MF_DISABLED|MF_GRAYED);
      menuTreeView.EnableMenuItem(ID_PUBLICATION_AJOUTER, MF_DISABLED|MF_GRAYED);
    }
    break;


	case ID_RACINE:
    if (GetDocument()->peutAjouterElemBase() == false)
    {
      menuTreeView.EnableMenuItem(ID_CATEGORIE_AJOUTER, MF_DISABLED|MF_GRAYED);
      menuTreeView.EnableMenuItem(ID_PUBLICATION_AJOUTER, MF_DISABLED|MF_GRAYED);
    }

    menuTreeView.EnableMenuItem(ID_SSMENU_SUPPR, MF_DISABLED|MF_GRAYED);
    menuTreeView.EnableMenuItem(ID_PUBLICATION_OUVRIR, MF_DISABLED|MF_GRAYED);
    break;

  default:
    menuTreeView.EnableMenuItem(ID_CATEGORIE_AJOUTER, MF_DISABLED|MF_GRAYED);
    menuTreeView.EnableMenuItem(ID_PUBLICATION_AJOUTER, MF_DISABLED|MF_GRAYED);
    menuTreeView.EnableMenuItem(ID_SSMENU_SUPPR, MF_DISABLED|MF_GRAYED);
    menuTreeView.EnableMenuItem(ID_PUBLICATION_OUVRIR, MF_DISABLED|MF_GRAYED);
    menuTreeView.EnableMenuItem(ID_SSMENU_PROPRIETE, MF_DISABLED|MF_GRAYED);
    break;
  }

	menuTreeView.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this);

//	CTreeView::OnRButtonUp(nFlags, point);
}


void CPublicationView::OnSsmenuPropriete() 
{
  CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

  switch (pElement->donnerTypeElement())
  {
	case ID_DOCUMENT:
    OnPublicationPropriete();
    break;

	case ID_CATEGORIE:
  case ID_RACINE:
    OnCategorieProprietes();
    break;

  default:
    break;
  }	
}


void CPublicationView::OnSsmenuSuppr() 
{
  CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

  switch (pElement->donnerTypeElement())
  {
	case ID_DOCUMENT:
    OnPublicationSupprimer();
    break;

	case ID_CATEGORIE:
    OnCategorieSupprimer();
    break;

  default:
    break;
  }	
}

void CPublicationView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	CTreeView::OnLButtonDblClk(nFlags, point);
  HTREEITEM hTreeItem;

  hTreeItem = GetTreeCtrl().HitTest(point, &nFlags);

  if (hTreeItem == currentHTreeItem) 
  {
    CPubElement* pElement = (CPubElement*) (GetTreeCtrl().GetItemData(currentHTreeItem));

    switch (pElement->donnerTypeElement())
    {
    case ID_DOCUMENT:
      OnPublicationOuvrir();
      break;

    default:
      break;
    }
  }
}

void CPublicationView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  HTREEITEM hTreeItem;
  UINT nFlags = 0;

  if (GetDocument()->peutModifierBase() == false)
  {
    AfxMessageBox("Vous ne possèdez pas les droits d'effectuer ce déplacement !");
    *pResult = 0;
    return;
  }

  hTreeItem = GetTreeCtrl().HitTest(pNMTreeView->ptDrag, &nFlags);

  if ((hTreeItem != NULL) && (hTreeItem != GetTreeCtrl().GetRootItem()))
  {
    SetCapture();
    m_bDragAndDropEnCours = true;
    GetTreeCtrl().SelectItem(hTreeItem);

    CPoint point;
    CPoint origine(0, 0);

    if (m_pTempImageDragDrop != NULL)
    {
      delete m_pTempImageDragDrop;
    }
    m_pTempImageDragDrop = GetTreeCtrl().CreateDragImage(hTreeItem);
    point = pNMTreeView->ptDrag;
    ClientToScreen(&point);

    m_pTempImageDragDrop->BeginDrag(0, origine);
    m_pTempImageDragDrop->DragEnter(NULL, point);
    m_pTempImageDragDrop->DragMove(point);
    GetTreeCtrl().SetItemState(hTreeItem, TVIS_DROPHILITED, TVIS_DROPHILITED);

    *pResult = -1;
  }
  else
  {
	  *pResult = 0;
  }
}


void CPublicationView::OnLButtonUp(UINT nFlags, CPoint point) 
{
  HTREEITEM hDestItem;
  HTREEITEM hNewItem;
  CString sText;
  int iImage;
  int iSelectedImage;
  DWORD dwParam;
  bool bSuiteOk = true;

  if (this == GetCapture())
    ReleaseCapture();

  if (m_bDragAndDropEnCours == true)
  {
    hDestItem = GetTreeCtrl().HitTest(point, &nFlags);

    if (hDestItem == NULL)
    {
      AfxMessageBox("Impossible de déplacer vers l'élément choisi");
      bSuiteOk = false;
    }

    if ((hDestItem == currentHTreeItem) && (bSuiteOk == true))
    {
      AfxMessageBox("Déplacement impossible, l'élement source est identique à l'élément destination");
      bSuiteOk = false;
    }

    if ((isParentItem(hDestItem, currentHTreeItem) == TRUE) && (bSuiteOk == true))
    {
      AfxMessageBox("Déplacement impossible, l'élément de destination est un sous élément de l'élément source");
      bSuiteOk = false;
    }

    if ((hDestItem == GetTreeCtrl().GetParentItem(currentHTreeItem)) && (bSuiteOk == true))
    {
      AfxMessageBox("Déplacement non necessaire !");
      bSuiteOk = false;
    }

    if (bSuiteOk == true)
    {
      sText = GetTreeCtrl().GetItemText(currentHTreeItem);
      GetTreeCtrl().GetItemImage(currentHTreeItem, iImage, iSelectedImage);
      dwParam = GetTreeCtrl().GetItemData(currentHTreeItem);
      
      CPubElement* pElement = (CPubElement*) GetTreeCtrl().GetItemData(hDestItem);
      switch (pElement->donnerTypeElement())
      {
      case ID_CATEGORIE:
      case ID_RACINE:  //Déplacement ok car element dest. est container
        
        if (GetDocument()->deplacerElement((CPubElement*) dwParam, (CPubContainer*) pElement) == TRUE)
        {
          hNewItem = GetTreeCtrl().InsertItem(sText, iImage, iSelectedImage, hDestItem);
          if (hNewItem != NULL)
          {
            GetTreeCtrl().SetItemData(hNewItem, dwParam);
            MoveTreeItem(currentHTreeItem, hNewItem);
            GetTreeCtrl().DeleteItem(currentHTreeItem);
            GetTreeCtrl().SelectItem(hNewItem);
            GetTreeCtrl().SetItemState(currentHTreeItem, ~TVIS_DROPHILITED, TVIS_DROPHILITED);
            GetDocument()->UpdateAllViews(0, 3, 0);
          }
          else
          {
            AfxMessageBox("Déplacement non réussi");
          }
        }
        else
        {
          AfxMessageBox("Déplacement impossible !!");
        }
        break;

      default:
        AfxMessageBox("L'element destination ne peut contenir l'(les) élément(s) source");
        GetTreeCtrl().SetItemState(currentHTreeItem, ~TVIS_DROPHILITED, TVIS_DROPHILITED);
        break;
      }
    }
    else
    {
      GetTreeCtrl().SetItemState(currentHTreeItem, ~TVIS_DROPHILITED, TVIS_DROPHILITED);
    }

    m_pTempImageDragDrop->DragLeave(0);
    m_pTempImageDragDrop->EndDrag();

    delete m_pTempImageDragDrop;
    m_pTempImageDragDrop = 0;

    m_bDragAndDropEnCours = false;
  }
	

	CTreeView::OnLButtonUp(nFlags, point);
}


void CPublicationView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTreeView::OnMouseMove(nFlags, point);

  if ((m_bDragAndDropEnCours == true) && (m_pTempImageDragDrop != NULL))
  {
    ClientToScreen(&point);
    m_pTempImageDragDrop->DragMove(point);
  }
}


void CPublicationView::MoveTreeItem(HTREEITEM hSource, HTREEITEM hDestination)
{
  HTREEITEM hTI;
  HTREEITEM hNewItem;
  CString sText;
  DWORD dwParam;
  int iImage;
  int iSelectedImage;

  hTI = GetTreeCtrl().GetChildItem(hSource);

  while (hTI != NULL)
  {
    sText = GetTreeCtrl().GetItemText(hTI);
    GetTreeCtrl().GetItemImage(hTI, iImage, iSelectedImage);
    dwParam = GetTreeCtrl().GetItemData(hTI);

    hNewItem = GetTreeCtrl().InsertItem(sText, iImage, iSelectedImage, hDestination);
    GetTreeCtrl().SetItemData(hNewItem, dwParam);

    if (GetTreeCtrl().ItemHasChildren(hTI) == TRUE)
      MoveTreeItem(hTI, hNewItem);

    hTI = GetTreeCtrl().GetNextItem(hTI, TVGN_NEXT);
  }

}


BOOL CPublicationView::isParentItem(HTREEITEM hItem, HTREEITEM hItemTested)
{
  HTREEITEM hTI;
  hTI = hItem;

  while ((hTI != GetTreeCtrl().GetRootItem()) && (hTI != NULL))
  {
    if (hTI != hItemTested)
      hTI = GetTreeCtrl().GetParentItem(hTI);
    else
      return TRUE;
  }

  return FALSE;
}

void CPublicationView::DrawItem(HTREEITEM hItem, CDC * pDC, int nXIndent)
{
  CPubElement* pElement;

  pElement = (CPubElement*) GetTreeCtrl().GetItemData(hItem);

  switch (pElement->donnerTypeElement())
  {
  case ID_CATEGORIE:
  case ID_RACINE:
    {
      // ecrire en souligne

      LOGFONT logFont;
      CFont aFont;
      CFont* pOldFont;
      CFont* pDefaultFont;

      pDefaultFont = pDC->GetCurrentFont();

      pDefaultFont->GetLogFont(&logFont);

      logFont.lfUnderline = TRUE;
      aFont.CreateFontIndirect(&logFont);

      pOldFont = pDC->SelectObject(&aFont);
      pDC->TextOut(nXIndent, m_nYIndentation, GetTreeCtrl().GetItemText(hItem));

      pDC->SelectObject(pOldFont);
    }
    break;

  case ID_DOCUMENT:
    // ecrire en normal
    pDC->TextOut(nXIndent, m_nYIndentation, GetTreeCtrl().GetItemText(hItem));
    break;

  default:
    break;
  }

  m_nYIndentation = m_nYIndentation + m_nYStep;

  if (GetTreeCtrl().ItemHasChildren(hItem) == TRUE)
  {
    hItem = GetTreeCtrl().GetChildItem(hItem);
    while (hItem != NULL)
    {
      DrawItem(hItem, pDC, nXIndent + 2*m_nXStep);
      hItem = GetTreeCtrl().GetNextItem(hItem, TVGN_NEXT);
    }
  }
}
