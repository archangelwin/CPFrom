#ifndef ACCOUNTS_CONTROL_HEAD_FILE
#define ACCOUNTS_CONTROL_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//�˺ſؼ�
class CAccountsCtrl : public CComboBox
{
	//��������
public:
	//���캯��
	CAccountsCtrl();
	//��������
	virtual ~CAccountsCtrl();

	//���غ���
protected:
	//�󶨺���
	virtual VOID PreSubclassWindow();
	//��������
	virtual VOID MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif