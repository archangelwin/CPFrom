#pragma once
#include "afxwin.h"
#include "Stdafx.h"
// CDlgSysGameSet 对话框

#define WM_SYS_GAME_SET WM_USER+105

class CDlgSysGameSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysGameSet)

public:
	CDlgSysGameSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysGameSet();

// 对话框数据
	enum { IDD = IDD_DLGSYSGAMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	tagUMSysGameSet* m_ptagUMSysGameSet;
public:
	CEdit m_FreeTime;                  //空闲时间
	CEdit m_CallBanker;                //叫庄时间
	CEdit m_BetTime;                   //下注时间
	CEdit m_EndTime;                   //结束时间

	CEdit m_StoragStart;               //(库存起始值）
	CEdit m_StorageDeduct;             //（衰减值）

	CEdit m_RobotBankerCount;         //机器人坐庄次数	
	CEdit m_RobotApplyBanker;         //机器人最多申请个数
	CEdit m_RobotWaitBanker;          // 机器人空几盘之后申请上庄 
	CEdit m_RobotScoreMin;            // 机器人取款
	CEdit m_RobotScoreMax;            // 机器人存款
	CEdit m_RobotBankGet;             // 取款最小额数
	CEdit m_RobotBankGetBanker;       // 取款最大额数
	CEdit m_RobotBankStoMul;          // 取款比例
	CEdit m_ORDRobotMaxBetTime;       // 机器人下注范围（上限）
	CEdit m_RobotMinBetTime;          // 机器人下注范围（下限）
	CEdit m_RobotMaxJetton;           // 机器人筹码范围（上限）
	CEdit m_RobotMinJetton;           // 机器人筹码范围（下限）
	CEdit m_RobotBetCount;            // 机器人最多下注个数
	CEdit m_RobotAreaLimit;           // 机器人区域下注限制
	CButton m_RobotBanker;            // 是否允许机器人坐庄
	CButton m_EnableSysBanker;        // 是否系统坐庄
	CEdit m_Score;                    // 坐庄金币
	CEdit m_BankerScore;              // 额外坐庄金币数
	CEdit m_Time;                     // 坐庄次数
	CEdit m_BankerAdd;                // 额外次数
	CEdit m_TimeAdd;                  // 坐庄增加次数
	CEdit m_UserLimitScore;           // 个人下注限制
	CEdit m_AreaLimitScore;           // 区域限制


	CXGroupBox    m_GroupBoxTitle;    
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();

public:
	void GetSysGameData(tagUMSysGameSet* ptagUMSysGameSet,LPCTSTR GameName);
	void SetSysGameData();    //设置信息
	afx_msg void OnBnClickedOk();               
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	
	CEdit m_UsuallyChangePercent;                                   //通常情况下，换牌百分比
	CEdit m_RobotWinScorePercent;                                   // ( > RobotDefineTanking) 扣除机器人赢的分数的百分比
	CEdit m_RobotLoseMax;											//输:最大分数有概率换牌
	CEdit m_RobotLoseChangePercent;									//输:换牌百分比(*RobotLoseMax)
	CEdit m_RobotLoseMaxChange;										//输:的起始分数,百分百换牌
	CEdit m_RobotProbabilityTanking;								//赢:分数，有概率放水
	CEdit m_RobotTankingPercent;									//赢:百分百放水（*RobotProbabilityTanking）
	CEdit m_RobotDefineTanking;										//赢:百分百放水
	CEdit m_RealBankerRobotLoseMax;									 //输: 一局（*人数），最大分数有概率换牌(牛牛出来概率 *人数)
	CEdit m_RealBankerRobotLoseChangePercent;						//输: 一局（*人数），换牌百分比（*RealBankerRobotLoseMax ）
	CEdit m_RealBankerRobotLoseMaxChange;							//输: 一局（*人数），起始分数,百分百换牌（2500001 以上：没使用）
};
