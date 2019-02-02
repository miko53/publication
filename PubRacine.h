// PubRacine.h: interface for the CPubRacine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBRACINE_H__9D3E206A_52CF_11D5_90A3_FB8407057A56__INCLUDED_)
#define AFX_PUBRACINE_H__9D3E206A_52CF_11D5_90A3_FB8407057A56__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PubContainer.h"

class CPubRacine : public CPubContainer  
{
public:
	CPubRacine(CString nom, long identificateur, CString path);
	virtual ~CPubRacine();

protected:
	CString m_path;
	CPubRacine();
};

#endif // !defined(AFX_PUBRACINE_H__9D3E206A_52CF_11D5_90A3_FB8407057A56__INCLUDED_)
