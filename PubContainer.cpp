// PubContainer.cpp: implementation of the CPubContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Publication.h"
#include "PubContainer.h"
#include "constElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPubContainer::CPubContainer(CString nom, long identificateur)
{
	m_identificateur = identificateur;
	m_nomElement = nom;
	m_typeElement = ID_CATEGORIE;

/*	if (type != ID_CATEGORIE)
	{
		AfxMessageBox(_T("Internal Error (3)"), MB_OK);
		AfxAbort();
	}
*/
}


CPubContainer::CPubContainer()
{

}


CPubContainer::~CPubContainer()
{
	POSITION aPosition = m_elementList.GetHeadPosition();

	while(aPosition)
		delete m_elementList.GetNext(aPosition);

	m_elementList.RemoveAll();
}


void CPubContainer::ajouterElement(CPubElement * pElement)
{
	unsigned char typeElement = pElement->donnerTypeElement();

	switch(typeElement)
	{
	case ID_CATEGORIE:
		m_elementList.AddHead(pElement);
		pElement->miseAJourParent(this);
		break;

	case ID_DOCUMENT:
		m_elementList.AddTail(pElement);
		pElement->miseAJourParent(this);
		break;

	case ID_RACINE:
		AfxMessageBox(_T("Internal Error (1) !"), MB_OK);
		AfxAbort();
		break;

	default:
		AfxMessageBox(_T("Internal Error (2) !"), MB_OK);
		AfxAbort();
		break;

	}
}



bool CPubContainer::retirerElement(CPubElement * pElement)
{
	/* rechercher element */
	POSITION aPosition;

	aPosition = m_elementList.Find(pElement, NULL);

	if (aPosition != NULL)
	{
		m_elementList.RemoveAt(aPosition);
		//delete pElement; peut etre a voir
		return true;
	}
	else
		return false;
}
