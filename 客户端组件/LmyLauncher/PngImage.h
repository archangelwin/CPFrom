#ifndef PNG_IMAGE_HEAD_FILE
#define PNG_IMAGE_HEAD_FILE

#pragma once

//�����ַ�ʽ����png,1:GDI+, 2:CImage

#include "LmyLauncher.h"

//////////////////////////////////////////////////////////////////////////////////

//ͼƬ����
class CPngImageSB
{
	//��������
protected:
	Image *							m_pImage;							//ͼƬ����
	TCHAR							m_strImageName[MAX_PATH];			//ͼƬ����
	CImage 							m_CImage;							//ͼƬ����
	//��������
public:
	//���캯��
	CPngImageSB();
	//��������
	virtual ~CPngImageSB();

	//״̬����
public:
	//�Ƿ����
	bool IsNull();
	//��ȡ���
	INT GetWidth();
	//��ȡ�߶�
	INT GetHeight();

	//�Ƿ����(CImage)
	bool IsCNull();
	//��ȡ���(CImage)
	INT GetCWidth();
	//��ȡ�߶�(CImage)
	INT GetCHeight();
	//������
public:
	//����ͼƬ
	bool DestroyImage();
	//����ͼƬ
	bool LoadImage(LPCTSTR pszFileName);
	//����ͼƬ
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName);
	//����ͼƬ(CImage)
	bool DestroyCImage();
	//����ͼƬ(CImage)
	bool LoadCImage(HINSTANCE hInstance,LPCTSTR pszResourceName);
	//�滭����
public:
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);
	//�滭ͼ��(CImage)
	bool DrawCImage(CDC * pDC, INT nXPos, INT nYPos);
	//�滭ͼ��(CImage)
	bool DrawCImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);
	//�滭ͼ��(CImage)
	bool DrawCImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//͸���滭
public:
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);
};

//////////////////////////////////////////////////////////////////////////////////

#endif