#pragma once


// CSkinLayered
#include "PngImage.h"

class CSkinLayered : public CWnd
{
	//��������
protected:
	CWnd *							m_pWndControl;						//�ؼ�����

	//��������
public:
	//���캯��
	CSkinLayered();
	//��������
	virtual ~CSkinLayered();

	//���ܺ���
public:
	//��������
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//��������
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//��������
	VOID InitLayeredArea(CPngImageSB & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//��Ϣӳ��
protected:
	//�ر���Ϣ
	VOID OnClose();
	//������Ϣ
	VOID OnSetFocus(CWnd * pOldWnd);

	//��̬����
protected:
	//ö�ٺ���
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};


