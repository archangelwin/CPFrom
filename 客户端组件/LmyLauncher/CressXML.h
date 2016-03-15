// CressXML.h: interface for the CCressXML class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRESSXML_H__E249B3A5_3A53_4CFE_A877_04AB96A8954B__INCLUDED_)
#define AFX_CRESSXML_H__E249B3A5_3A53_4CFE_A877_04AB96A8954B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import <msxml3.dll>
using namespace MSXML2;

#include "LmyLauncher.h "
class CCressXML : public CObject
{
public:
	CString GetXMLByName(LPCTSTR  sName);
	void DeleteNode(const CString &sExpress);
	BOOL GetLoadError();
	void SetXMLTitle(LPCTSTR  sTitle);
	CString GetXMLToString();
	CString GetFullXMLToString();
	CString GetNodeText();
	int GetNodeNum(LPCTSTR  sExpress);
	void DeleteAllNode(LPCTSTR  sNode, LPCTSTR  sDelNode);
	CCressXML();
	virtual ~CCressXML();
	
	BOOL LoadFile(LPCTSTR  sFileName);
	BOOL LoadDesFile(LPCTSTR sFileName);
	BOOL LoadXML(LPCTSTR sXML);
	BOOL SaveFile(LPCTSTR  sFileName);

	BOOL SelectNodeToList(LPCTSTR  sExpress);
	BOOL SelectNodeToList(MSXML2::IXMLDOMNodePtr pNode, LPCTSTR  sExpress);
	MSXML2::IXMLDOMNodePtr QueryNode(BOOL bReset = false);

	void AddChilds(LPCTSTR  sExpressm, LPCTSTR  sName, CString *sChilds, CString *sValue, int iSize);
	void AddChild(LPCTSTR  sExpressm, LPCTSTR  sName, CString &sChilds, CString &sValue);
	
	CString GetValueByIndex(int iIndex);
	CString GetValueByName(LPCTSTR  sName);
	CString GetAttrValueByName(LPCTSTR  sName);


protected:
	BOOL m_bLoadError;
	MSXML2::IXMLDOMDocumentPtr	m_plDomDocument;
	MSXML2::IXMLDOMElementPtr	m_pDocRoot;
	MSXML2::IXMLDOMNodeListPtr	m_pNodeList;
	MSXML2::IXMLDOMNodePtr		m_pNode;

};

#endif // !defined(AFX_CRESSXML_H__E249B3A5_3A53_4CFE_A877_04AB96A8954B__INCLUDED_)
