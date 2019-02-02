// PubElement.h: interface for the CPubElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBELEMENT_H__18AB4756_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
#define AFX_PUBELEMENT_H__18AB4756_46E9_11D5_90A3_907DCAD10C53__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPubElement : public CObject  
{
public:
	bool modifierNomElement(CString nouveauNom);
	void miseAJourParent(CPubElement* pParent);
	CPubElement* donnerParent()
	{
		return m_pParent;
	}

	unsigned char donnerTypeElement()
	{
		return m_typeElement;
	}

	long donnerIdentificateur()
	{
		return m_identificateur;
	}
	
	CString donnerNom()
	{
		return m_nomElement;
	}

	virtual ~CPubElement();

protected:
	CPubElement* m_pParent;
	long m_identificateur;
	CString m_nomElement;
	unsigned char m_typeElement;
	CPubElement();
};

#endif // !defined(AFX_PUBELEMENT_H__18AB4756_46E9_11D5_90A3_907DCAD10C53__INCLUDED_)
