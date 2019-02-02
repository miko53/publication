// PubRacine.cpp: implementation of the CPubRacine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Publication.h"
#include "PubRacine.h"
#include "constElement.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPubRacine::CPubRacine(CString nom, long identificateur, CString path)
{
/*	if (type != ID_RACINE)
	{
		AfxMessageBox(_T("Internal Error (5)"));
		AfxAbort();
	}*/

	m_identificateur = identificateur;
	m_typeElement = ID_RACINE;
	m_nomElement = nom;
	m_path = path;
	m_pParent = NULL;
}


CPubRacine::CPubRacine()
{
	AfxMessageBox(_T("Internal Error (5)"));
	AfxAbort();
}


CPubRacine::~CPubRacine()
{

}
