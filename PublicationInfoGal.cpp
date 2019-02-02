// PublicationInfoGal.cpp: implementation of the CPublicationInfoGal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Publication.h"
#include "PublicationInfoGal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPublicationInfoGal::CPublicationInfoGal()
{
	m_repertoireRacine = _T("");
	m_nomBase = _T("");
	m_nomSauvegardeBase = _T("");
	m_droitUtilisateur = 0;
	m_utilisateurActuel = _T("");

	m_pDatabase = NULL;
	m_pWorkSpace = NULL;

}

CPublicationInfoGal::~CPublicationInfoGal()
{
	if (m_pDatabase != NULL)
	{
		m_pDatabase->Close();
		delete m_pDatabase;
	}


	if (m_pWorkSpace != NULL)
	{
		m_pWorkSpace->Close();
		delete m_pWorkSpace;
	}
}
