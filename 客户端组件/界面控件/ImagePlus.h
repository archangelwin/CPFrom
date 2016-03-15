#ifndef SKIN_IMAGE_PLUS_HEAD_FILE
#define SKIN_IMAGE_PLUS_HEAD_FILE

#pragma once

#include "SkinImage.h"
#include "SkinControlHead.h"

//////////////////////////////////////////////////////////////////////////


//λͼ������
class SKIN_CONTROL_CLASS CImagePlus : public CImage, public IGDIResource
{
	friend class CImagePlusHandle;

	//�ڲ�����
private:
	int									m_nRefCount;						//���ü���
	bool								m_bLoadAlways;						//�Ƿ���
	tagImageLoadInfo					m_LoadInfo;							//���ز���
	COLORREF							m_crTrans;							//͸����ɫ

	//��������
public:
	//���캯��
	CImagePlus(void);
	//��������
	virtual ~CImagePlus(void);

	//�ӿں���
protected:
	//��������
	virtual int LockResource();
	//��������
	virtual int UnLockResource();
	//��ȡ���ü���
	virtual int GetReferenceCount() { return m_nRefCount; }

	//���ܺ���
public:
	//�Ƿ����ü�����Ϣ
	bool IsSetLoadInfo();
	//������ز���
	bool RemoveLoadInfo();
	//��ȡ���ز���
	bool GetLoadInfo(tagImageLoadInfo & LoadInfo);
	//���ò���
	bool SetLoadInfo(const tagImageLoadInfo & LoadInfo, bool bLoadAlways=false);
	//���ü��ز���
	bool SetLoadInfo(LPCTSTR pszFileName, bool bLoadAlways=false);
	//���ü��ز���
	bool SetLoadInfo(UINT uResourceID, HINSTANCE hResourceDLL=NULL, bool bLoadAlways=false, LPCTSTR pszResType=_T("BMP"));
	//����ͼƬ
	BOOL LoadImageFromResource(HINSTANCE hInstance, UINT uResourceID, LPCTSTR pszResourceType);
	BOOL LoadImageFromResource(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszResourceType);
	//͸������
	BOOL AlphaChannelHandle();
	//�滭����
	BOOL DrawImage( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight,
		int xSrc, int ySrc, int nSrcWidth, int nSrcHeight );
	BOOL DrawImage(HDC hDestDC, int xDest, int yDest);
	BOOL DrawImage(HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc);
	BOOL DrawImage(HDC hDestDC, CRect rcDest, CRect rcSrc);
	//����͸��ɫ
	COLORREF SetTransColor(COLORREF crTrans);
	//��ȡ͸��ɫ
	COLORREF GetTransColor();
	//��ɫ����
	BOOL AdjustHSL(int degHue,int perSaturation,int perLuminosity);
	void RGBtoHSL(BYTE Red, BYTE Green, BYTE Blue, float* Hue, float* Sat, float* Lum);
	COLORREF HSLtoRGB(float Hue,float Sat,float Lum);
	BYTE HueToRGB(float rm1,float rm2,float rh);

	//���غ���
public:
	//λͼָ��
	operator CBitmap * () { return CBitmap::FromHandle((HBITMAP)(*this)); }

	//������
public:
	//��������
	bool CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor);
	//��������
	bool CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor);

	//��ͼ����
public:
	//͸���滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor);
	//͸���滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor);

	//��ϻ滭
public:
	//��ϻ滭
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth);
	//��ϻ滭
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth);

	//��������
private:
	//�������
	bool GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender);
};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//λͼ��Դ���
class SKIN_CONTROL_CLASS CImagePlusHandle : public IGDIResourceHandle
{
	//��������
protected:
	CImagePlus							* m_pImage;							//λͼָ��
	
	//��������
public:
	//���캯��
	CImagePlusHandle(CImagePlus * pImageObject=NULL);
	//��������
	virtual ~CImagePlusHandle();
	
	//�ӿں���
public:
	//�Ƿ��
	virtual bool IsAttached();
	//�Ƿ���Ч
	virtual bool IsResourceValid();
	//�����
	virtual bool DetchResource();
	//����Դ
	virtual bool AttachResource(IGDIResource * pImageObject);

	//��������
public:
	//��ȡ���
	HBITMAP GetBitmapHandle();
	//��ȡ����
	CImagePlus * GetImageObject() { return m_pImage; };
	//ָ������
	CImagePlus * operator->() { return GetImageObject(); }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#endif