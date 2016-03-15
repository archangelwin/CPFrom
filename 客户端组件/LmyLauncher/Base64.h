
#ifndef Base64_H
#define Base64_H
#include "ServiceCoreHead.h"
//#include "stdafx.h"
#include <string.h>

class SERVICE_CORE_CLASS CBase64
{

public:
	static unsigned int m_LineWidth;						//指定编码后每行的长度，缺省是76
	static const char BASE64_ENCODE_TABLE[64];				//Base64编码表
	static const unsigned int BASE64_DECODE_TABLE[256];		//Base64解码表
public:
	CBase64(){};
	static int Base64EncodeSize(int iSize);		//根据文件实际长度获取编码Base64后的长度  
	static int Base64DecodeSize(int iSize);		//根据已编码文件长度获取Base64的解码长度
	/*
	*  对一段Buffer进行Base64编码
	*
	*	 	pSrc	输入Buffer
	*		nSize	Buffer长度
	*		pDest	输出缓冲
	*
	*	 注: 输出Buffer的长度可以使用 Base64EncodeSize(int) 方法取得
	*/
	static int base64_encode(char *pSrc, unsigned int nSize, char *pDest);

	/*
	*  对一段Buffer进行Base64解码
	*	
	*	 	pSrc	输入Buffer
	*		nSize	Buffer长度
	*		pDest	输出缓冲
	*		return	解码后的实际长度
	*
	*	 注: 输出Buffer的长度可以使用 Base64DecodeSize(int) 方法取得
	*/
	static int  base64_decode(char *pSrc, unsigned int nSize, char *pDest);


	
};

class CEasySecret
{	
public:
	CEasySecret();
	~CEasySecret();
	static CString Encrypt(CString sIn);
	static CString Decrypt(CString sIn);
};

#endif
