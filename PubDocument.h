// PubDocument.h: interface for the CPubDocument class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBDOCUMENT_H__18AB475C_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_PUBDOCUMENT_H__18AB475C_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PubElement.h"

class CPubDocument : public CPubElement  
{
public:
	CPubDocument(CString nom, long identificateur, BOOL bFileExiste, CString sExtension);

  BOOL isFile()
  {
    return m_bFichierExiste;
  }

  CString donnerExtensionFichier()
  {
    return m_sExtension;
  }

  virtual ~CPubDocument();

protected:
	CString m_sExtension;
	BOOL m_bFichierExiste;
	CPubDocument();

};

#endif // !defined(AFX_PUBDOCUMENT_H__18AB475C_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
