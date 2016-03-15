#pragma once
#include "afxcmn.h"
#include "ServerListData.h"

class CMatchList :	public CListCtrl, public IServerListDataSink
{
public:
	CMatchList(void);
	~CMatchList(void);
protected:
		int                             m_nItemHeight;
public:
	void ResetData(); //重置数据
	//控件绑定
	virtual VOID PreSubclassWindow();
	//绘画函数
	virtual VOID DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//插入函数
public:
	VOID SetItemHeight(UINT nHeight);
	VOID ClearSelMask();

	//状态通知
public:
	//完成通知
	virtual VOID OnGameItemFinish();
	//完成通知
	virtual VOID OnGameKindFinish(WORD wKindID);
	//更新通知
	virtual VOID OnGameItemUpdateFinish();

	//更新通知
public:
	//插入通知
	virtual VOID OnGameItemInsert(CGameListItem * pGameListItem);
	//更新通知
	virtual VOID OnGameItemUpdate(CGameListItem * pGameListItem);
	//删除通知
	virtual VOID OnGameItemDelete(CGameListItem * pGameListItem);

	//绘画控制
protected:
	//获取颜色
	//virtual VOID GetItemColor(LPDRAWITEMSTRUCT lpDrawItemStruct, COLORREF & crColorText, COLORREF & crColorBack);
	//绘画数据
	virtual VOID DrawCustomItem(CDC * pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, CRect & rcSubItem, INT nColumnIndex);

	//消息函数
protected:
	afx_msg void MeasureItem ( LPMEASUREITEMSTRUCT lpMeasureItemStruct );
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//建立消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnNMClick( NMHDR * pNotifyStruct, LRESULT* result); 
};
