// PublicationInfo.h: interface for the CPublicationInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICATIONINFO_H__F4CA2BC4_5163_11D5_90A3_DDC2DCBBB253__INCLUDED_)
#define AFX_PUBLICATIONINFO_H__F4CA2BC4_5163_11D5_90A3_DDC2DCBBB253__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPublicationInfo  
{
public:
	bool flagFirstDocument;
	CString databaseDirectory;
	HICON pTabIcon[4];
	CPublicationInfo();
	virtual ~CPublicationInfo();

};

#endif // !defined(AFX_PUBLICATIONINFO_H__F4CA2BC4_5163_11D5_90A3_DDC2DCBBB253__INCLUDED_)
