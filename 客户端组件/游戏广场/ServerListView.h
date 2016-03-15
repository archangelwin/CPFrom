#ifndef SERVER_LIST_VIEW_HEAD_FILE
#define SERVER_LIST_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerListData.h"

//////////////////////////////////////////////////////////////////////////////////

//����˵��
typedef CMap<WORD,WORD,UINT,UINT>	CGameImageMap;						//��Ϸͼ��
typedef CList<WORD>	                CLastGameServerList;				//��Ϸ����
#define SHOW_LAST_COUNT             3                                   //�����Ϸ��

//////////////////////////////////////////////////////////////////////////////////

//�����б�
class CServerListView : public CTreeCtrl, public IServerListDataSink
{
	//λ�ñ���
protected:
	INT								m_nXScroll;							//����ƫ��
	INT								m_nYScroll;							//����ƫ��
	bool                            m_bInsertLastRoom;

	//�б���
protected:
	HTREEITEM						m_TreeListRoot;						//������
	HTREEITEM						m_TreeAssistant;					//�������
	

	//��Դ����
protected:
	CFont							m_FontBold;							//��������
	CFont							m_FontGameKind;						//��Ϸ���
	CFont							m_FontGameServer;					//��Ϸ����

	CPngImageSB						m_ImageArrow;						//��ͷͼ��
	CPngImageSB                     m_ImageArrowType;                   //����ͷ
	CPngImageSB                     m_ImageGameType;                    //��Ϸ���
	CSkinScrollBar					m_SkinScrollBar;					//��������

	CRect                           m_rcLastRoom[SHOW_LAST_COUNT];                   //�����Ϸ���� 
	CGameServerItem *               m_pLastGameServerItem[SHOW_LAST_COUNT];

	//��Դ����
protected:
	CImageList						m_ImageList;						//ͼƬ��Դ
	CGameImageMap					m_GameImageMap;						//ͼ������
	CLastGameServerList             m_LastPlayGameList;                 //��������Ϸ

	//��������
protected:
	HTREEITEM						m_hItemMouseHover;					//��������
	HTREEITEM						m_hTreeClickExpand;					//��������
	CGameTypeItem                   m_LastServerItem;                   //�����Ϸ

	//�������
protected:

	//��������
public:
	//���캯��
	CServerListView();
	//��������
	virtual ~CServerListView();

	//״̬֪ͨ
public:
	//��ȡ֪ͨ
	virtual VOID OnGameItemFinish();
	//��ȡ֪ͨ
	virtual VOID OnGameKindFinish(WORD wKindID);
	//����֪ͨ
	virtual VOID OnGameItemUpdateFinish();

	//����֪ͨ
public:
	//����֪ͨ
	virtual VOID OnGameItemInsert(CGameListItem * pGameListItem);
	//����֪ͨ
	virtual VOID OnGameItemUpdate(CGameListItem * pGameListItem);
	//ɾ��֪ͨ
	virtual VOID OnGameItemDelete(CGameListItem * pGameListItem);

	//���غ���
protected:
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//���ں���
	virtual LRESULT DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam);

	//���ܺ���
public:
	//����ͨ��
	VOID InitAssistantItem();
	//���ú���
	VOID InitServerTreeView();

	//���ܺ���
public:
	void ResetData(); //��������
	//��ȡѡ��
	HTREEITEM GetCurrentSelectItem(bool bOnlyText);
	//��Ӽ�¼
	void AddLastPlayGame(WORD wServerID, CGameServerItem *pGameServerItem);
	//�жϼ�¼
	bool IsLastPlayGame(WORD wServerID);
	//ö�ټ�¼
	HTREEITEM EmunGameServerItem(HTREEITEM hParentItem, WORD wServerID);
	VOID ExpandTreeItem(HTREEITEM hTreeItem);
	//����Ϊ��
	bool IsEmptySubitem(WORD wKindID);
	void InsertLastPlayGame();
	UINT GetServerImageIndex();

	//չ������
public:
	//չ���ж�
	bool ExpandVerdict(HTREEITEM hTreeItem);
	//չ���б�
	bool ExpandListItem(HTREEITEM hTreeItem);
	//չ���б�
	bool ExpandListItem(CGameListItem * pGameListItem);

	//�滭����
private:
	//�滭����
	VOID DrawTreeItem(CDC * pDC, CRect & rcClient, CRect & rcClipBox);
	//�滭����
	VOID DrawTreeBack(CDC * pDC, CRect & rcClient, CRect & rcClipBox);

	//�滭����
private:
	//����ͼ��
	VOID DrawListImage(CDC * pDC, CRect rcRect, HTREEITEM hTreeItem);
	//�����ı�
	VOID DrawItemString(CDC * pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected);

	//ͼ�꺯��
private:
	//��ȡͼ��
	UINT GetGameKindImageIndex(CGameKindItem * pGameKindItem);
	//��ȡͼ��
	UINT GetGameServerImageIndex(CGameServerItem * pGameServerItem);

	//���⺯��
private:
	//��ȡ����
	LPCTSTR GetGameKindItemTitle(CGameKindItem * pGameKindItem, LPTSTR pszTitle, UINT uMaxCount);
	//��ȡ����
	LPCTSTR GetGameServerItemTitle(CGameServerItem * pGameServerItem, LPTSTR pszTitle, UINT uMaxCount);

	//��������
private:
	//ɾ������
	VOID DeleteUpdateItem(CGameListItem * pGameListItem);
	//�޸�����
	VOID ModifyGameListItem(HTREEITEM hTreeItem, LPCTSTR pszTitle, UINT uImage);
	//��������
	HTREEITEM InsertInsideItem(LPCTSTR pszTitle, UINT uImage, DWORD dwInsideID, HTREEITEM hParentItem);
	//��������
	HTREEITEM InsertGameListItem(LPCTSTR pszTitle, UINT uImage, CGameListItem * pGameListItem, HTREEITEM hParentItem,UINT nIntegral=26,bool bFirst = false);

	//ϵͳ��Ϣ
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//ʱ����Ϣ
	VOID OnTimer(UINT nIDEvent);
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	//�б���Ϣ
protected:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//�Ҽ��б�
	VOID OnNMRClick(NMHDR * pNMHDR, LRESULT * pResult);
	//����б�
	VOID OnNMLClick(NMHDR * pNMHDR, LRESULT * pResult);
	//�б�ı�
	VOID OnTvnSelchanged(NMHDR * pNMHDR, LRESULT * pResult);
	//�б�չ��
	VOID OnTvnItemexpanding(NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()

protected:
	//��÷��为����Ϣ
	LPCTSTR GetLoadInfo(DWORD dwOnLineCount, DWORD dwMaxCount, LPTSTR pszBuffer, WORD wBufferSize);
	//��÷��为����Ϣ
	LPCTSTR GetLoadInfoOfServer(tagGameServer * pGameServer, LPTSTR pszBuffer, WORD wBufferSize);
	//��÷��为����Ϣ
	LPCTSTR GetLoadInfoOfGameKind(tagGameKind * pGameKind, LPTSTR pszBuffer, WORD wBufferSize);
	//���ؼ�¼
	void LoadLastPlayGame();
	//�����¼
	void SaveLastPlayGame();
};

//////////////////////////////////////////////////////////////////////////////////

#endif