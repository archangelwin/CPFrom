// #ifndef USER_MANAGER_HEAD_H
// #define USER_MANAGER_HEAD_H
// 
// //MFC �ļ�
// #include <Nb30.h>
// #include <Afxmt.h>
// #include <AtlBase.h>
// 
// #include "..\..\��Ϣ����\CMD_UserManage.h"
// 
// //�û��ӿ�
// interface ICUserManagerItem : public IUnknownEx
// {
// public:
// 	virtual tagUMUserScoreSet * GetAllUserScoreInfo = NULL;
// 	
// 	virtual DWORD GetdwUserID() = NULL;
// 
// 	virtual DWORD GetdwServerID() = NULL;
// 
// 	//�û��ǳ�
// 	virtual DWORD GetszNickName() = NULL;
// 
// 	//��Ϸ��ʼʱ��
// 	virtual DWORD GetdwBeginTime() = NULL;
// 
// 	//�û�����
// 	virtual SCORE GetlScore() = NULL;
// 
// 	//�û�����
// 	virtual SCORE GetlInsure() = NULL;
// 
// 	//��Ӯ����
// 	virtual SCORE GetlWinScore() = NULL;
// 
// 	//���ú���Ӯ����
// 	virtual SCORE GetlTempScore() = NULL;
// 
// 	//Ӯ����
// 	virtual SCORE GetlMaxWin() = NULL;
// 
// 	//�����
// 	virtual SCORE GetlMaxLose() = NULL;
// 
// 	//Ӯ����(����)
// 	virtual SCORE KeeplMaxWin1() = NULL;
// 
// 	//�����(����)
// 	virtual SCORE KeeplMaxLose1() = NULL;
// 
// 	//Ԥ��Ӯ����
// 	virtual SCORE GetlNotifyMaxWin() = NULL;
// 
// 	//Ԥ�������
// 	virtual SCORE GetlNotifyMaxLost() = NULL;
// 
// 	//����
// 	virtual SetType GetdwType() = NULL;
// 
// 	//���Ʊ��ʣ��ٷֱȣ�
// 	virtual DWORD GetdwWinOrLostRate() = NULL;
// 
// 	//���Ʊ��ʣ��ٷֱȣ�������)
// 	virtual DWORD KeepdwWinOrLostRate1() = NULL;
// 
// 	//���õ�ʱ��
// 	virtual DWORD GetdwSetTime() = NULL;
// 
// };
// 
// 
// #endif