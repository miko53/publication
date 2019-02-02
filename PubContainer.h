// PubContainer.h: interface for the CPubContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBCONTAINER_H__18AB4757_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_PUBCONTAINER_H__18AB4757_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PubElement.h"

class CPubContainer : public CPubElement  
{
public:
	bool retirerElement(CPubElement* pElement);
	void ajouterElement(CPubElement* pElement);
	CPubContainer(CString nom, long identificateur);

	POSITION donnerPositionTete() const
	{
		return m_elementList.GetHeadPosition();
	}

	CPubElement* donnerProchainElement(POSITION& position)
	{
		return m_elementList.GetNext(position);
	}

	virtual ~CPubContainer();

protected:
	CTypedPtrList<CObList, CPubElement*> m_elementList;
	CPubContainer();

};

#endif // !defined(AFX_PUBCONTAINER_H__18AB4757_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
