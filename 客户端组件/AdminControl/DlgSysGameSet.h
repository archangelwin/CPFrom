#pragma once
#include "afxwin.h"
#include "Stdafx.h"
// CDlgSysGameSet �Ի���

#define WM_SYS_GAME_SET WM_USER+105

class CDlgSysGameSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysGameSet)

public:
	CDlgSysGameSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSysGameSet();

// �Ի�������
	enum { IDD = IDD_DLGSYSGAMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	tagUMSysGameSet* m_ptagUMSysGameSet;
public:
	CEdit m_FreeTime;                  //����ʱ��
	CEdit m_CallBanker;                //��ׯʱ��
	CEdit m_BetTime;                   //��עʱ��
	CEdit m_EndTime;                   //����ʱ��

	CEdit m_StoragStart;               //(�����ʼֵ��
	CEdit m_StorageDeduct;             //��˥��ֵ��

	CEdit m_RobotBankerCount;         //��������ׯ����	
	CEdit m_RobotApplyBanker;         //����������������
	CEdit m_RobotWaitBanker;          // �����˿ռ���֮��������ׯ 
	CEdit m_RobotScoreMin;            // ������ȡ��
	CEdit m_RobotScoreMax;            // �����˴��
	CEdit m_RobotBankGet;             // ȡ����С����
	CEdit m_RobotBankGetBanker;       // ȡ��������
	CEdit m_RobotBankStoMul;          // ȡ�����
	CEdit m_ORDRobotMaxBetTime;       // ��������ע��Χ�����ޣ�
	CEdit m_RobotMinBetTime;          // ��������ע��Χ�����ޣ�
	CEdit m_RobotMaxJetton;           // �����˳��뷶Χ�����ޣ�
	CEdit m_RobotMinJetton;           // �����˳��뷶Χ�����ޣ�
	CEdit m_RobotBetCount;            // �����������ע����
	CEdit m_RobotAreaLimit;           // ������������ע����
	CButton m_RobotBanker;            // �Ƿ������������ׯ
	CButton m_EnableSysBanker;        // �Ƿ�ϵͳ��ׯ
	CEdit m_Score;                    // ��ׯ���
	CEdit m_BankerScore;              // ������ׯ�����
	CEdit m_Time;                     // ��ׯ����
	CEdit m_BankerAdd;                // �������
	CEdit m_TimeAdd;                  // ��ׯ���Ӵ���
	CEdit m_UserLimitScore;           // ������ע����
	CEdit m_AreaLimitScore;           // ��������


	CXGroupBox    m_GroupBoxTitle;    
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();

public:
	void GetSysGameData(tagUMSysGameSet* ptagUMSysGameSet,LPCTSTR GameName);
	void SetSysGameData();    //������Ϣ
	afx_msg void OnBnClickedOk();               
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	
	CEdit m_UsuallyChangePercent;                                   //ͨ������£����ưٷֱ�
	CEdit m_RobotWinScorePercent;                                   // ( > RobotDefineTanking) �۳�������Ӯ�ķ����İٷֱ�
	CEdit m_RobotLoseMax;											//��:�������и��ʻ���
	CEdit m_RobotLoseChangePercent;									//��:���ưٷֱ�(*RobotLoseMax)
	CEdit m_RobotLoseMaxChange;										//��:����ʼ����,�ٷְٻ���
	CEdit m_RobotProbabilityTanking;								//Ӯ:�������и��ʷ�ˮ
	CEdit m_RobotTankingPercent;									//Ӯ:�ٷְٷ�ˮ��*RobotProbabilityTanking��
	CEdit m_RobotDefineTanking;										//Ӯ:�ٷְٷ�ˮ
	CEdit m_RealBankerRobotLoseMax;									 //��: һ�֣�*���������������и��ʻ���(ţţ�������� *����)
	CEdit m_RealBankerRobotLoseChangePercent;						//��: һ�֣�*�����������ưٷֱȣ�*RealBankerRobotLoseMax ��
	CEdit m_RealBankerRobotLoseMaxChange;							//��: һ�֣�*����������ʼ����,�ٷְٻ��ƣ�2500001 ���ϣ�ûʹ�ã�
};
