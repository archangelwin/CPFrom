#pragma once

#include "Stdafx.h"
#include "PlatformPublicize.h"
// CDlgMobileBind �Ի���

class CDlgMobileBind : public CSkinDialog
{
public:
	CDlgMobileBind();   // ��׼���캯��
	virtual ~CDlgMobileBind();

protected:
	CPlatformPublicize				m_PlatformPublicize;				//����ؼ�


protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
