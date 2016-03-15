// #ifndef USER_MANAGER_HEAD_H
// #define USER_MANAGER_HEAD_H
// 
// //MFC 文件
// #include <Nb30.h>
// #include <Afxmt.h>
// #include <AtlBase.h>
// 
// #include "..\..\消息定义\CMD_UserManage.h"
// 
// //用户接口
// interface ICUserManagerItem : public IUnknownEx
// {
// public:
// 	virtual tagUMUserScoreSet * GetAllUserScoreInfo = NULL;
// 	
// 	virtual DWORD GetdwUserID() = NULL;
// 
// 	virtual DWORD GetdwServerID() = NULL;
// 
// 	//用户昵称
// 	virtual DWORD GetszNickName() = NULL;
// 
// 	//游戏开始时间
// 	virtual DWORD GetdwBeginTime() = NULL;
// 
// 	//用户分数
// 	virtual SCORE GetlScore() = NULL;
// 
// 	//用户银行
// 	virtual SCORE GetlInsure() = NULL;
// 
// 	//输赢分数
// 	virtual SCORE GetlWinScore() = NULL;
// 
// 	//设置后输赢分数
// 	virtual SCORE GetlTempScore() = NULL;
// 
// 	//赢分数
// 	virtual SCORE GetlMaxWin() = NULL;
// 
// 	//输分数
// 	virtual SCORE GetlMaxLose() = NULL;
// 
// 	//赢分数(保留)
// 	virtual SCORE KeeplMaxWin1() = NULL;
// 
// 	//输分数(保留)
// 	virtual SCORE KeeplMaxLose1() = NULL;
// 
// 	//预警赢分数
// 	virtual SCORE GetlNotifyMaxWin() = NULL;
// 
// 	//预警输分数
// 	virtual SCORE GetlNotifyMaxLost() = NULL;
// 
// 	//类型
// 	virtual SetType GetdwType() = NULL;
// 
// 	//换牌比率（百分比）
// 	virtual DWORD GetdwWinOrLostRate() = NULL;
// 
// 	//换牌比率（百分比）（保留)
// 	virtual DWORD KeepdwWinOrLostRate1() = NULL;
// 
// 	//设置的时间
// 	virtual DWORD GetdwSetTime() = NULL;
// 
// };
// 
// 
// #endif