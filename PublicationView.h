// PublicationView.h : interface of the CPublicationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICATIONVIEW_H__18AB4732_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_PUBLICATIONVIEW_H__18AB4732_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPublicationView : public CTreeView
{
protected: // create from serialization only
	CPublicationView();
	DECLARE_DYNCREATE(CPublicationView)

// Attributes
public:
	CPublicationDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPublicationView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void selectionnerDocument(long identificateur);
	void selectionnerCategorie(long identificateur);
	virtual ~CPublicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_nYIndentation;
 	int m_nYStep;
	int m_nXStep;
	void DrawItem(HTREEITEM hItem, CDC * pDC, int nXIndent);
	bool m_bDragAndDropEnCours;
	CImageList* m_pTempImageDragDrop;
	BOOL isParentItem(HTREEITEM hItem, HTREEITEM hItemTested);
	void MoveTreeItem(HTREEITEM hSource, HTREEITEM hDestination);
	void OnUpdateSuppression(CObject* pHint);
	void OnUpdateModification(CObject* pHint);
	HTREEITEM currentHTreeItem;
	HTREEITEM rechercheParentDsVue(CPubElement* pElement, HTREEITEM itemSearch);
	HTREEITEM rechercheCategorieDsVue(long identificateur, HTREEITEM itemSearch);
  HTREEITEM rechercheDocumentDsVue(long identificateur, HTREEITEM itemSearch);
	void miseAJourTreeView(CPubElement* pElement, HTREEITEM hItem);
	//{{AFX_MSG(CPublicationView)
	afx_msg void OnCategorieAjouter();
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateCategorieAjouter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCategorieSupprimer(CCmdUI* pCmdUI);
	afx_msg void OnCategorieSupprimer();
	afx_msg void OnCategorieProprietes();
	afx_msg void OnUpdateCategorieProprietes(CCmdUI* pCmdUI);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPublicationAjouter();
	afx_msg void OnUpdatePublicationAjouter(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePublicationSupprimer(CCmdUI* pCmdUI);
	afx_msg void OnPublicationSupprimer();
	afx_msg void OnUpdatePublicationPropriete(CCmdUI* pCmdUI);
	afx_msg void OnPublicationPropriete();
	afx_msg void OnUpdatePublicationOuvrir(CCmdUI* pCmdUI);
	afx_msg void OnPublicationOuvrir();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSsmenuPropriete();
	afx_msg void OnSsmenuSuppr();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImageList* m_pImageList;
};

#ifndef _DEBUG  // debug version in PublicationView.cpp
inline CPublicationDoc* CPublicationView::GetDocument()
   { return (CPublicationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUBLICATIONVIEW_H__18AB4732_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
