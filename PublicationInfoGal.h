// PublicationInfoGal.h: interface for the CPublicationInfoGal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICATIONINFOGAL_H__9D3E2064_52CF_11D5_90A3_FB8407057A56__INCLUDED_)
#define AFX_PUBLICATIONINFOGAL_H__9D3E2064_52CF_11D5_90A3_FB8407057A56__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPublicationInfoGal  
{
public:
	CDaoDatabase * m_pDatabase;
	CDaoWorkspace * m_pWorkSpace;
	CString m_repertoireRacine;
	CString m_nomBase;
	CString m_nomSauvegardeBase;
	unsigned long m_droitUtilisateur;
	CString m_utilisateurActuel;
	CPublicationInfoGal();
	virtual ~CPublicationInfoGal();

};

#endif // !defined(AFX_PUBLICATIONINFOGAL_H__9D3E2064_52CF_11D5_90A3_FB8407057A56__INCLUDED_)
