// PubElement.cpp: implementation of the CPubElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Publication.h"
#include "PubElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPubElement::CPubElement()
{

}

CPubElement::~CPubElement()
{

}

void CPubElement::miseAJourParent(CPubElement * pParent)
{
	m_pParent = pParent;
}

bool CPubElement::modifierNomElement(CString nouveauNom)
{
	m_nomElement = nouveauNom;
	return true;
}
