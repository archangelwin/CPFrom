// CressXML.cpp: implementation of the CCressXML class.
//
//////////////////////////////////////////////////////////////////////
#include <afx.h>
#include "stdafx.h"
#include "CressXML.h"
#include <atlconv.h>
#include "des.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCressXML::CCressXML()
{
	m_bLoadError = false;
	::CoInitialize(NULL);
	HRESULT hr = m_plDomDocument.CreateInstance(CLSID_DOMDocument);
	if (FAILED(hr))
	{
		 _com_error er(hr);
		 m_bLoadError = true;
		return ;
	}
}

CCressXML::~CCressXML()
{
}

BOOL CCressXML::LoadFile(LPCTSTR sFileName)
{
	_bstr_t fileName(sFileName);
	VARIANT_BOOL hr = m_plDomDocument->load(fileName);

	if (FAILED(hr))
	{
		m_pDocRoot = m_plDomDocument->documentElement;
		if(m_pDocRoot ==NULL)
			return FALSE;
		return true;
	}
	else
		return false;
}

BOOL CCressXML::SaveFile(LPCTSTR sFileName)
{
	BOOL bResult = FALSE;

	_bstr_t fileName(sFileName);
	
	HRESULT hr;
	try
    {

		hr = m_plDomDocument->save(fileName);
		if(SUCCEEDED(hr))
         bResult = TRUE;
	}
	catch(...)
    {
      //DisplayErrorToUser();
      // Release the IXMLDOMDocument interface.
    }
	return bResult;

}

BOOL CCressXML::LoadXML(LPCTSTR sXML)
{
	_bstr_t xml(sXML);
	VARIANT_BOOL hr = m_plDomDocument->loadXML(xml);
	
	
	if (FAILED(hr))
	{
		m_pDocRoot = m_plDomDocument->documentElement;
		return true;
	}
	else
		return false;
}

BOOL CCressXML::SelectNodeToList(LPCTSTR sExpress)
{
	_bstr_t express(sExpress);
	m_pNodeList = m_pDocRoot->selectNodes(express);

	return m_pNodeList != NULL;
}

BOOL CCressXML::SelectNodeToList(MSXML2::IXMLDOMNodePtr pNode, LPCTSTR sExpress)
{
	
	_bstr_t express(sExpress);
	m_pNodeList = pNode->selectNodes(express);
//	::SysFreeString(tmp);
	return m_pNodeList != NULL;
}

MSXML2::IXMLDOMNodePtr CCressXML::QueryNode(BOOL bReset)
{
	if (bReset)
		m_pNodeList->reset();
	m_pNode = m_pNodeList->nextNode();
	
	return m_pNode;
}

CString CCressXML::GetValueByIndex(int iIndex)
{
	return "";

}

CString CCressXML::GetValueByName(LPCTSTR sName)
{
	_bstr_t name(sName);
	MSXML2::IXMLDOMNodePtr pNode = m_pNode->selectSingleNode(name);
	//::SysFreeString(tmp);
	USES_CONVERSION;
	return (pNode != NULL) ? W2A(pNode->text) : "";
}

CString CCressXML::GetXMLByName(LPCTSTR sName)
{

	_bstr_t name(sName);
	MSXML2::IXMLDOMNodePtr pNode = m_pNode->selectSingleNode(name);
	USES_CONVERSION;
	return (pNode != NULL) ? W2A(pNode->xml) : "";
}

CString CCressXML::GetNodeText()
{
	return "";
}


CString CCressXML::GetAttrValueByName(LPCTSTR sName)
{
	_bstr_t name(sName);
	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = m_pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pNode = pAttr->getQualifiedItem(name, "");
	USES_CONVERSION;
	return (pNode != NULL) ? W2A(pNode->text) : "";
}

void CCressXML::AddChilds(LPCTSTR sExpressm, LPCTSTR sName, CString *sChilds, CString *sValue, int iSize)
{
	VARIANT vtTemp;
    vtTemp.vt=VT_I2;
    vtTemp.iVal = MSXML2::NODE_ELEMENT;
	USES_CONVERSION;
	//BSTR nodeTmp = A2BSTR(sExpressm);

	_bstr_t nodePress(sExpressm);
//	BSTR nameTmp = A2BSTR(sName);
	BSTR tmp, valueTmp;
	MSXML2::IXMLDOMNodePtr pRootNode, pMainNode, pNode;
	pRootNode = (m_pDocRoot->selectNodes(nodePress))->nextNode();
	
	//::MessageBox(0, pRootNode->xml, 0, 0);
	if (sName == "")
		pMainNode = pRootNode;
	else
		pMainNode = m_plDomDocument->createNode(vtTemp, _bstr_t(sName), "");
	for (int i = 0; i < iSize; i ++)
	{
		tmp = A2BSTR(sChilds[i]);
		valueTmp = A2BSTR(sValue[i]);
		pNode = m_plDomDocument->createNode(vtTemp, _bstr_t(tmp, false), "");
		pNode->text = _bstr_t(valueTmp, false);
		pMainNode->appendChild(pNode);
		//::SysFreeString(tmp);
		//::SysFreeString(valueTmp);
	}
	if (sName != "")
		pRootNode->appendChild(pMainNode);
	//::SysFreeString(nodeTmp);
	//::SysFreeString(nameTmp);
	//MessageBox(0, m_plDomDocument->documentElement->xml, 0, 0);
}

void CCressXML::AddChild(LPCTSTR sExpress, LPCTSTR sName, CString &sChilds, CString &sValue)
{
	AddChilds(sExpress, sName, &sChilds, &sValue, 1);
}

void CCressXML::DeleteAllNode(LPCTSTR sNode, LPCTSTR sDelNode)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList, pDelNodeList;
	MSXML2::IXMLDOMNodePtr pNode, pDelNode;
//	USES_CONVERSION;
//	BSTR tmp = A2BSTR(sNode);
//	BSTR delTmp = A2BSTR(sDelNode);
	_bstr_t nodePress(sNode);
	pNodeList = m_pDocRoot->selectNodes(nodePress);
	while((pNode = pNodeList->nextNode()) != NULL)
	{
		_bstr_t delNodePress(sDelNode);
		pDelNodeList = pNode->selectNodes(delNodePress);
		while ((pDelNode = pDelNodeList->nextNode()) != NULL)
		{
			pNode->removeChild(pDelNode);
		}
	}
	//::SysFreeString(tmp);
	//::SysFreeString(delTmp);
}

int CCressXML::GetNodeNum(LPCTSTR sExpress)
{
//	USES_CONVERSION;
//	BSTR tmp = A2BSTR(sExpress);
	_bstr_t express(sExpress);
	m_pNodeList = m_pDocRoot->selectNodes(express);
	//::SysFreeString(tmp);
	if (m_pNodeList != NULL) 
		return (int)(m_pNodeList->length);
	else return 0;
}

CString CCressXML::GetXMLToString()
{
	USES_CONVERSION;
	return W2A(m_pDocRoot->xml);
}

CString CCressXML::GetFullXMLToString()
{
	USES_CONVERSION;
	return W2A(m_plDomDocument->xml);
}

void CCressXML::SetXMLTitle(LPCTSTR sTitle)
{
	//AfxMessageBox(m_plDomDocument->);
//	USES_CONVERSION;
//	BSTR tmp = A2BSTR(sTitle);

	MSXML2::IXMLDOMProcessingInstructionPtr pMainNode;
	pMainNode = m_plDomDocument->createProcessingInstruction(_bstr_t("xml"), 
		_bstr_t("version=\"1.0\" encoding=\"") + _bstr_t(sTitle) + _bstr_t("\""));
	//m_plDomDocument->appendChild(pMainNode);
	//::SysFreeString(tmp);
	m_plDomDocument->insertBefore(pMainNode, (_variant_t)m_plDomDocument->childNodes->item[0]);		
}

BOOL CCressXML::GetLoadError()
{
	return m_bLoadError;
}

void CCressXML::DeleteNode(const CString &sExpress)
{
/*	USES_CONVERSION;
	BSTR tmp = A2BSTR(sExpress);
	
	_bstr_t express(tmp, false);
	IXMLDOMElementPtr pElement = m_pDocRoot->selectNodes(express);
	::SysFreeString(tmp);
	if (pElement != NULL)
		m_pDocRoot->removeChild(pElement);
*/
	MSXML2::IXMLDOMNodeListPtr pNodeList, pDelNodeList;
	MSXML2::IXMLDOMNodePtr pNode, pDelNode, pParentNode;
	USES_CONVERSION;
	BSTR tmp = A2BSTR(sExpress);
	_bstr_t nodePress(tmp, false);
	pNodeList = m_pDocRoot->selectNodes(nodePress);
	while((pNode = pNodeList->nextNode()) != NULL)
	{
	//	m_pDocRoot->removeChild(pNode);
		pParentNode = NULL;
		pNode->get_parentNode(&pParentNode);
		if (pParentNode != NULL)
			pParentNode->removeChild(pNode);

	}
}
BOOL CCressXML::LoadDesFile(LPCTSTR sFileName)
{
	CFile file;
	char *pOutData;
	CString m_str;
	int nDataLen;
	DES des;
	if (!des.Des_decodeFile((char *)(LPCTSTR)sFileName, &pOutData, nDataLen))
	{	
		return false;
	}
	else
	{
	
	}
	m_str = pOutData;
	delete []pOutData;

	return LoadXML((LPCTSTR)m_str);
}