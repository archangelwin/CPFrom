#ifndef SKIN_CONTROL_HEAD_FILE
#define SKIN_CONTROL_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//�����ļ�

//ƽ̨�ļ�
#include "..\..\ȫ�ֶ���\Platform.h"

//����ļ�
#include "..\ͼ��ؼ�\WHImageHead.h"
#include "..\..\�������\�������\ServiceCoreHead.h"

//////////////////////////////////////////////////////////////////////////////////
//��������
//����λͼ�ṹ
struct tagImageLoadInfo
{
	//��������
	UINT								uResourceID;						//��Դ ID
	CString								strFileName;						//�ļ�����
	HINSTANCE							hResourceDLL;						//��Դ���
	//LPCTSTR								pszResource;						//��Դ��ʶ
	CString								strResType;							//��Դ����

	//��������
	tagImageLoadInfo()
	{
		uResourceID=0;
		hResourceDLL=NULL;
	}
};

//�༭��Դ
struct tagSkinEditResource
{
	COLORREF						crFocusTX;							//������ɫ
	COLORREF						crFocusBK;							//������ɫ
	COLORREF						crNoFocusTX;						//������ɫ
	COLORREF						crNoFocusBK;						//������ɫ
	COLORREF						crDisFocusTX;						//������ɫ
	COLORREF						crDisFocusBK;						//������ɫ
	//COLORREF						crBoradNormal;						//�߿���ɫ
	tagImageLoadInfo				m_ImageBottom;						//����ͼƬ
	tagImageLoadInfo				m_ImageBottom1;						//����ͼƬ
};

//��ť��Դ
struct tagSkinButtonResource
{
	COLORREF						crButtonText;						//������ɫ
	tagImageLoadInfo				LoadInfoButton;						//������Ϣ
};

//������Դ
struct tagSkinDialogResource
{
	//��ɫ��Ϣ
	COLORREF						crTitleText;						//������ɫ
	COLORREF						crBackGround;						//������ɫ
	COLORREF						crControlText;						//������ɫ
	COLORREF						crInsideBorder;						//�߿���ɫ
	COLORREF						crBackFrame;						//������ɫ

	//������Ϣ
	tagImageLoadInfo				LoadInfoImageTL;					//������Ϣ
	tagImageLoadInfo				LoadInfoImageTM;					//������Ϣ
	tagImageLoadInfo				LoadInfoImageTR;					//������Ϣ

	//������Ϣ
	tagImageLoadInfo				LoadInfoButtonMin;					//������Ϣ
	tagImageLoadInfo				LoadInfoButtonMax;					//������Ϣ
	tagImageLoadInfo				LoadInfoButtonRes;					//������Ϣ
	tagImageLoadInfo				LoadInfoButtonClose;				//������Ϣ

	tagImageLoadInfo                Left;                                  
	tagImageLoadInfo                Right;
	tagImageLoadInfo                Bottom;
	tagImageLoadInfo                LeftL;
	tagImageLoadInfo                RightR;
};

//�б���Դ
struct tagSkinListCtrlResource
{
	//��ɫ��Ϣ
	COLORREF						crListTX;							//�б�����

	//��Դ��Ϣ
	tagImageLoadInfo				LoadInfoImageBack;					//������Ϣ
};

//�����Դ
struct tagSkinSplitterResource
{
	tagImageLoadInfo				LoadInfoVor;						//������Ϣ
	tagImageLoadInfo				LoadInfoHor;						//������Ϣ
};

//�ȵ���Դ
struct tagSkinHyperLinkResource
{
	COLORREF						crBackColor;						//������ɫ
	COLORREF						crHoverText;						//������ɫ
	COLORREF						crNormalText;						//������ɫ
	COLORREF						crVisitedText;						//������ɫ
};

//��������Դ
struct tagProgressCtrlResource
{
	COLORREF						crText;								//������ɫ
	tagImageLoadInfo				LoadInfoBkg;						//������Ϣ
	tagImageLoadInfo				LoadInfoAct;						//������Ϣ
};

//������Դ
interface ISkinResource : public IUnknownEx
{
	//��Դ�ӿ�
public:
	//��������
	virtual bool __cdecl CreateDefaultFont(CFont & Font)=NULL;

	//��Դ�ӿ�
public:
	//��ȡ��Ϣ
	// 	virtual bool __cdecl GetResourceInfo(tagSkinEditResource & SkinEditResource)=NULL;
	// 	//��ȡ��Ϣ
	// 	virtual bool __cdecl GetResourceInfo(tagSkinDialogResource & SkinDialogResource)=NULL;
	// 	//��ȡ��Ϣ
	// 	virtual bool __cdecl GetResourceInfo(tagSkinButtonResource & SkinButtonResource)=NULL;
	// 	//��ȡ��Ϣ
	// 	virtual bool __cdecl GetResourceInfo(tagSkinSplitterResource & SkinSplitterResource)=NULL;
	// 	//��ȡ��Ϣ
	// 	virtual bool __cdecl GetResourceInfo(tagSkinListCtrlResource & SkinListCtrlResource)=NULL;
	// 	//��ȡ��Ϣ
	// 	virtual bool __cdecl GetResourceInfo(tagSkinHyperLinkResource & SkinHyperLinkResource)=NULL;
	// 	//��ȡ��Ϣ
	virtual bool __cdecl GetResourceInfo(tagProgressCtrlResource & ProgressCtrlResource)=NULL;
};

//��������
#ifndef SKIN_CONTROL_CLASS
	#ifdef  SKIN_CONTROL_DLL
		#define SKIN_CONTROL_CLASS _declspec(dllexport)
	#else
		#define SKIN_CONTROL_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifndef _DEBUG
	#define SKIN_CONTROL_DLL_NAME	TEXT("SkinControl.dll")			//�������
#else
	#define SKIN_CONTROL_DLL_NAME	TEXT("SkinControlD.dll")		//�������
#endif

//////////////////////////////////////////////////////////////////////////////////
//�����ļ�

#ifndef SKIN_CONTROL_DLL
	#include "SkinEdit.h"
	#include "SkinMenu.h"
	#include "SkinDpi.h"
	#include "SkinDialog.h"
	#include "SkinButton.h"
	#include "SkinTabCtrl.h"
	#include "SkinSplitter.h"
	#include "SkinComboBox.h"
	#include "SkinEncircle.h"
	#include "SkinListCtrl.h"
	#include "SkinRichEdit.h"
	#include "SkinScrollBar.h"
    #include "SkinHyperLink.h"
    #include "SkinCheckBox.h"
	#include "SkinRenderManager.h"
    #include "SkinResourceManager.h"
    #include "GifButton.h"
    #include "GroupBox.h "
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif