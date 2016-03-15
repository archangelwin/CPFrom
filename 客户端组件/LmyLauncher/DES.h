// DES.h: interface for the DES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__30E4BD94_DC18_40DA_88E2_7C79D13DF16E__INCLUDED_)
#define AFX_DES_H__30E4BD94_DC18_40DA_88E2_7C79D13DF16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum    {ENCRYPT1,DECRYPT};

#include "LmyLauncher.h "
class DES 
{
public:
	bool Des_Go(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type);
    CString DES_encode(CString sPlaintext,CString sKey);  // 加密
	CString DES_decode(CString scryptograph,CString sKey);  // 解密
	void Des_encode(char *szData, int nDataLen, char *szKey, char **szOutPut, int &nOutLen);  //加密
	void Des_decode(char *szData, int nDataLen, char *szKey, char **szOutPut, int &nOutLen); //解密

	bool Des_encodeFile(char *szFileName, char **szOutData, int &nOutLen);
	bool Des_encodeFile(char *szFileName, char *szOutFileName);
	bool Des_encodeFile(char *szInData, int nInLen, char *szOutFileName);
	bool Des_decodeFile(char *szFileName, char **szOutData, int &nOutLen);
	bool Des_decodeFile(char *szFileName, char *szOutFileName);
	DES();
	virtual ~DES();

};

#endif // !defined(AFX_DES_H__30E4BD94_DC18_40DA_88E2_7C79D13DF16E__INCLUDED_)
