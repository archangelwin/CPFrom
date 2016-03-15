#ifndef D3D_SPRITE_HEAD_FILE
#define D3D_SPRITE_HEAD_FILE

#pragma once

#include "D3DDevice.h"
#include "GameEngineHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CD3DSprite;

//����˵��
typedef CWHArray<CD3DSprite *>		CD3DSpritePtrArray;					//��������

//////////////////////////////////////////////////////////////////////////////////

//�������
class /*GAME_ENGINE_CLASS*/ CD3DSprite
{
	//��ת��Ϣ
protected:
	FLOAT							m_fAngle;							//��ת����
	FLOAT							m_fRotationX;						//��ת����
	FLOAT							m_fRotationY;						//��ת����

	//ͼƬ��Ϣ
public:
	CSize							m_ImageSize;						//ͼƬ��С
	CSize							m_MemorySize;						//�ڴ��С

	//�ӿڱ���
protected:
	ID3DXSprite	*					m_pISprite;							//����ӿ�
	IDirect3DTexture9 *				m_pITexture;						//����ӿ�

	//��̬����
protected:
	static CD3DSpritePtrArray		m_D3DSpritePtrArray;				//��������

	//��������
public:
	//���캯��
	CD3DSprite(){}
	//��������
	virtual ~CD3DSprite(){}

	//��ȡ����
public:
	//�������
	ID3DXSprite * GetSprite() { return m_pISprite; }
	//�������
	IDirect3DTexture9 * GetTexture() { return m_pITexture; }

	//ͼƬ��Ϣ
public:
	//�����ж�
	bool IsNull(){ return true;};
	//������
	INT GetWidth() { return m_ImageSize.cx; }
	//����߶�
	INT GetHeight() { return m_ImageSize.cy; }

	//���ƺ���
public:
	//������ת
	VOID SetRotation(FLOAT fRotationX, FLOAT fRotationY, FLOAT fAngle);

	//�������
public:
	//���پ���
	bool Destory(){return true;}
	//��������
	bool CreateImage(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight){return true;}

	//���ܺ���
public:
	//���ؾ���
	bool LoadImage(CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, DWORD dwColorKey){return true;}
	//���ؾ���
	bool LoadImage(CD3DDevice * pD3DDevice, HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName){return true;}

	//�滭����
public:
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest){return true;}
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource){return true;}
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight){return true;}

	//�滭����
public:
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, D3DCOLOR Color){return true;}
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, D3DCOLOR Color){return true;}
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, D3DCOLOR Color){return true;}

	//�滭����
public:
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, BYTE cbAlpha){return true;}
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, BYTE cbAlpha){return true;}
	//�滭ͼƬ
	bool DrawImage(CD3DDevice * pD3DDevice, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXSource, INT nYSource, INT nSourceWidth, INT nSourceHeight, BYTE cbAlpha){return true;}

	//�ڲ�����
protected:
	//��ȡ��Դ
	bool GetResourceInfo(HINSTANCE hInstance, LPCTSTR pszResource, LPCTSTR pszTypeName, tagResourceInfo & ResourceInfo){return true;}

	//��̬����
public:
	//�ͷ���Դ
	static VOID OnDeviceLost(CD3DDevice * pD3DDevice){}
	//������Դ
	static VOID OnDeviceReset(CD3DDevice * pD3DDevice){}
};

//////////////////////////////////////////////////////////////////////////////////

#endif