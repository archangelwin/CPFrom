// DlgSysGameSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AdminControl.h"
#include "DlgSysGameSet.h"

// CDlgSysGameSet �Ի���

IMPLEMENT_DYNAMIC(CDlgSysGameSet, CDialog)

CDlgSysGameSet::CDlgSysGameSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSysGameSet::IDD, pParent)
{

	m_ptagUMSysGameSet = new tagUMSysGameSet;
}

CDlgSysGameSet::~CDlgSysGameSet()
{
	if (m_ptagUMSysGameSet != NULL)
	{
		delete m_ptagUMSysGameSet;
		m_ptagUMSysGameSet = NULL;
	}
}

BOOL CDlgSysGameSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;
}

void CDlgSysGameSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_FreeTime);
	DDX_Control(pDX, IDC_EDIT2, m_CallBanker);
	DDX_Control(pDX, IDC_EDIT3, m_BetTime);
	DDX_Control(pDX, IDC_EDIT4, m_EndTime);
	DDX_Control(pDX, IDC_EDIT5, m_StoragStart);
	DDX_Control(pDX, IDC_EDIT6, m_StorageDeduct);
	DDX_Control(pDX, IDC_EDIT7, m_RobotBankerCount);
	DDX_Control(pDX, IDC_EDIT8, m_RobotApplyBanker);
	DDX_Control(pDX, IDC_EDIT9, m_RobotWaitBanker);
	DDX_Control(pDX, IDC_EDIT10, m_RobotScoreMin);
	DDX_Control(pDX, IDC_EDIT12, m_RobotScoreMax);
	DDX_Control(pDX, IDC_EDIT14, m_RobotBankGet);
	DDX_Control(pDX, IDC_EDIT13, m_RobotBankGetBanker);
	DDX_Control(pDX, IDC_EDIT11, m_RobotBankStoMul);
	DDX_Control(pDX, IDC_EDIT15, m_ORDRobotMaxBetTime);
	DDX_Control(pDX, IDC_EDIT16, m_RobotMinBetTime);
	DDX_Control(pDX, IDC_EDIT17, m_RobotMaxJetton);
	DDX_Control(pDX, IDC_EDIT18, m_RobotMinJetton);
	DDX_Control(pDX, IDC_EDIT19, m_RobotBetCount);
	DDX_Control(pDX, IDC_EDIT20, m_RobotAreaLimit);
	DDX_Control(pDX, IDC_CHECK1, m_RobotBanker);
	DDX_Control(pDX, IDC_CHECK2, m_EnableSysBanker);
	DDX_Control(pDX, IDC_EDIT21, m_Score);
	DDX_Control(pDX, IDC_EDIT22, m_BankerScore);
	DDX_Control(pDX, IDC_EDIT23, m_Time);
	DDX_Control(pDX, IDC_EDIT24, m_BankerAdd);
	DDX_Control(pDX, IDC_EDIT25, m_TimeAdd);
	DDX_Control(pDX, IDC_EDIT26, m_UserLimitScore);
	DDX_Control(pDX, IDC_EDIT27, m_AreaLimitScore);


	DDX_Control(pDX, IDC_STATIC_TITLE,m_GroupBoxTitle);
	DDX_Control(pDX, IDC_EDIT28, m_UsuallyChangePercent);
	DDX_Control(pDX, IDC_EDIT29, m_RobotWinScorePercent);
	DDX_Control(pDX, IDC_EDIT30, m_RobotLoseMax);
	DDX_Control(pDX, IDC_EDIT31, m_RobotLoseChangePercent);
	DDX_Control(pDX, IDC_EDIT32, m_RobotLoseMaxChange);
	DDX_Control(pDX, IDC_EDIT33, m_RobotProbabilityTanking);
	DDX_Control(pDX, IDC_EDIT35, m_RobotTankingPercent);
	DDX_Control(pDX, IDC_EDIT34, m_RobotDefineTanking);
	DDX_Control(pDX, IDC_EDIT36, m_RealBankerRobotLoseMax);
	DDX_Control(pDX, IDC_EDIT37, m_RealBankerRobotLoseChangePercent);
	DDX_Control(pDX, IDC_EDIT38, m_RealBankerRobotLoseMaxChange);
}


BEGIN_MESSAGE_MAP(CDlgSysGameSet, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSysGameSet::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSysGameSet::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgSysGameSet::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgSysGameSet::OnBnClickedCheck2)
END_MESSAGE_MAP()

// CDlgSysGameSet ��Ϣ�������

//��ȡ��Ϣ
void CDlgSysGameSet::GetSysGameData(tagUMSysGameSet* ptagUMSysGameSet,LPCTSTR GameName)
{
	ASSERT(ptagUMSysGameSet!=NULL);
	if(ptagUMSysGameSet==NULL) return;
	if (GameName == NULL)
	{
		return;
	}
	CString szText;

	if (ptagUMSysGameSet->dwServerID==0)
	{
		//AfxMessageBox("û�л�ȡ����!");
		ShowWindow(SW_HIDE);
		return;
	}

	CString TitleName = GameName;
	if (TitleName.Find("ͨ��ţţ") != 0)
	{
		m_UsuallyChangePercent.EnableWindow(TRUE);
		m_RobotWinScorePercent.EnableWindow(TRUE);
		m_RobotLoseMax.EnableWindow(TRUE);
		m_RobotLoseChangePercent.EnableWindow(TRUE);
		m_RobotLoseMaxChange.EnableWindow(TRUE);
		m_RobotProbabilityTanking.EnableWindow(TRUE);
		m_RobotTankingPercent.EnableWindow(TRUE);
		m_RobotDefineTanking.EnableWindow(TRUE);
		m_RealBankerRobotLoseMax.EnableWindow(TRUE);
		m_RealBankerRobotLoseChangePercent.EnableWindow(TRUE);
		m_RealBankerRobotLoseMaxChange.EnableWindow(TRUE);
	}
// 	else
// 	{
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwUsuallyChangePercent);
// 		m_UsuallyChangePercent.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRobotWinScorePercent);
// 		m_RobotWinScorePercent.SetWindowText(szText);
// 
// 		szText.Format(_T("%lld"),ptagUMSysGameSet->dwRobotLoseMax);
// 		m_RobotLoseMax.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRobotLoseChangePercent);
// 		m_RobotLoseChangePercent.SetWindowText(szText);
// 
// 		szText.Format(_T("%lld"),ptagUMSysGameSet->dwRobotLoseMaxChange);
// 		m_RobotLoseMaxChange.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRobotProbabilityTanking);
// 		m_RobotProbabilityTanking.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRobotTankingPercent);
// 		m_RobotTankingPercent.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRobotDefineTanking);
// 		m_RobotDefineTanking.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRealBankerRobotLoseMax);
// 		m_RealBankerRobotLoseMax.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRealBankerRobotLoseChangePercent);
// 		m_RealBankerRobotLoseChangePercent.SetWindowText(szText);
// 
// 		szText.Format(_T("%ld"),ptagUMSysGameSet->dwRealBankerRobotLoseMaxChange);
// 		m_RealBankerRobotLoseMaxChange.SetWindowText(szText);
// 
// 		return;
// 	}
// 	
// 	//groupͷ
// 	m_GroupBoxTitle.SetWindowText(GameName);
// 
// 
// 	//��עʱ��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwFreeTime);
// 	m_FreeTime.SetWindowText(szText);
// 
// 	//��ׯʱ��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwCallBanker);
// 	m_CallBanker.SetWindowText(szText);
// 
// 	//��עʱ��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwBetTime);
// 	m_BetTime.SetWindowText(szText);
// 
// 	//����ʱ��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwEndTime);
// 	m_EndTime.SetWindowText(szText);
// 
// 	//(�����ʼֵ��
// 	szText.Format(_T("%lld"),ptagUMSysGameSet->dwStoragStart);
// 	m_StoragStart.SetWindowText(szText);
// 
// 	//��˥��ֵ��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwStorageDeduct);
// 	m_StorageDeduct.SetWindowText(szText);
// 
// 	 //��������ׯ����	
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotBankerCount);
// 	m_RobotBankerCount.SetWindowText(szText);
// 
// 	//����������������
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotApplyBanker);
// 	m_RobotApplyBanker.SetWindowText(szText);
// 
// 	// �����˿ռ���֮��������ׯ
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotWaitBanker);
// 	m_RobotWaitBanker.SetWindowText(szText);
// 
// 	// ������ȡ��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotScoreMin);
// 	m_RobotScoreMin.SetWindowText(szText);
// 
// 	// �����˴��
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotScoreMax);
// 	m_RobotScoreMax.SetWindowText(szText);
// 
// 	 // ȡ����С����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotBankGet);
// 	m_RobotBankGet.SetWindowText(szText);
// 
// 	// ȡ��������
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotBankGetBanker);
// 	m_RobotBankGetBanker.SetWindowText(szText);
// 
// 	// ȡ�����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotBankStoMul);
// 	m_RobotBankStoMul.SetWindowText(szText);
// 
// 	// ��������ע��Χ�����ޣ�
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwORDRobotMaxBetTime);
// 	m_ORDRobotMaxBetTime.SetWindowText(szText);
// 
// 	// ��������ע��Χ�����ޣ�
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotMinBetTime);
// 	m_RobotMinBetTime.SetWindowText(szText);
// 
// 	// �����˳��뷶Χ�����ޣ�
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotMaxJetton);
// 	m_RobotMaxJetton.SetWindowText(szText);
// 
// 	// �����˳��뷶Χ�����ޣ�
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotMinJetton);
// 	m_RobotMinJetton.SetWindowText(szText);
// 
// 	// �����������ע����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotBetCount);
// 	m_RobotBetCount.SetWindowText(szText);
// 
// 	// ������������ע����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwRobotAreaLimit);
// 	m_RobotAreaLimit.SetWindowText(szText);
// 	
// 	 // �Ƿ������������ׯ
// 	DWORD state = ptagUMSysGameSet->dwRobotBanker;
// 	if (state==1)
// 	{
// 		m_RobotBanker.SetCheck(0);
// 		m_RobotBankerCount.EnableWindow(TRUE);
// 		m_RobotApplyBanker.EnableWindow(TRUE);
// 		m_RobotWaitBanker.EnableWindow(TRUE);
// 	}else
// 		m_RobotBanker.SetCheck(1);
// 
// 	// �Ƿ�ϵͳ��ׯ
// 	state = ptagUMSysGameSet->dwEnableSysBanker;
// 	if (state==1)
// 	{
// 		m_EnableSysBanker.SetCheck(0);
// 		m_Score.EnableWindow(TRUE);
// 		m_BankerScore.EnableWindow(TRUE);
// 		m_Time.EnableWindow(TRUE);
// 		m_BankerAdd.EnableWindow(TRUE);
// 		m_TimeAdd.EnableWindow(TRUE);
// 	}else
// 		m_EnableSysBanker.SetCheck(1);
// 
// 	// ��ׯ���
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwScore);
// 	m_Score.SetWindowText(szText);
// 
// 	 // ������ׯ�����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwBankerScore);
// 	m_BankerScore.SetWindowText(szText);
// 
// 	// ��ׯ����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwTime);
// 	m_Time.SetWindowText(szText);
// 
// 	// �������
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwBankerAdd);
// 	m_BankerAdd.SetWindowText(szText);
// 
// 	// ��ׯ���Ӵ���
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwTimeAdd);
// 	m_TimeAdd.SetWindowText(szText);
// 
// 	 // ������ע����
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwUserLimitScore);
// 	m_UserLimitScore.SetWindowText(szText);
// 
// 	 // ��������
// 	szText.Format(_T("%d"),ptagUMSysGameSet->dwAreaLimitScore);
// 	m_AreaLimitScore.SetWindowText(szText);
}


//������Ϣ
void CDlgSysGameSet::SetSysGameData()
{
// 	CString sText;
// 	m_ptagUMSysGameSet->dwFreeTime = GetDlgItemInt(IDC_EDIT1);
// 	m_ptagUMSysGameSet->dwCallBanker = GetDlgItemInt(IDC_EDIT2);
// 	m_ptagUMSysGameSet->dwBetTime = GetDlgItemInt(IDC_EDIT3);
// 	m_ptagUMSysGameSet->dwEndTime = GetDlgItemInt(IDC_EDIT4);
// 
// 	GetDlgItemText(IDC_EDIT5,sText);
// 	m_ptagUMSysGameSet->dwStoragStart = _ttoi(sText);
// 	m_ptagUMSysGameSet->dwStorageDeduct = GetDlgItemInt(IDC_EDIT6);
// 
// 	DWORD state = m_RobotBanker.GetCheck();
// 	if (state==0)
// 	{
// 		m_ptagUMSysGameSet->dwRobotBanker = state;
// 		m_ptagUMSysGameSet->dwRobotBankerCount = GetDlgItemInt(IDC_EDIT7);
// 		m_ptagUMSysGameSet->dwRobotApplyBanker = GetDlgItemInt(IDC_EDIT8);
// 		m_ptagUMSysGameSet->dwRobotWaitBanker = GetDlgItemInt(IDC_EDIT9);
// 	}else
// 		m_ptagUMSysGameSet->dwRobotBanker = state;
// 
// 	m_ptagUMSysGameSet->dwRobotScoreMin = GetDlgItemInt(IDC_EDIT10);
// 	m_ptagUMSysGameSet->dwRobotScoreMax = GetDlgItemInt(IDC_EDIT12);
// 	m_ptagUMSysGameSet->dwRobotBankGetBanker = GetDlgItemInt(IDC_EDIT13);
// 	m_ptagUMSysGameSet->dwRobotBankGet = GetDlgItemInt(IDC_EDIT14);
// 	m_ptagUMSysGameSet->dwRobotBankStoMul = GetDlgItemInt(IDC_EDIT11);
// 	m_ptagUMSysGameSet->dwORDRobotMaxBetTime = GetDlgItemInt(IDC_EDIT15);
// 	m_ptagUMSysGameSet->dwRobotMinBetTime = GetDlgItemInt(IDC_EDIT16);
// 	m_ptagUMSysGameSet->dwRobotMaxJetton = GetDlgItemInt(IDC_EDIT17);
// 	m_ptagUMSysGameSet->dwRobotMinJetton = GetDlgItemInt(IDC_EDIT18);
// 	m_ptagUMSysGameSet->dwRobotBetCount = GetDlgItemInt(IDC_EDIT19);
// 	m_ptagUMSysGameSet->dwRobotAreaLimit = GetDlgItemInt(IDC_EDIT20);
// 
// 	state = m_EnableSysBanker.GetCheck();
// 	if (state==0)
// 	{
// 		m_ptagUMSysGameSet->dwEnableSysBanker = state;
// 		m_ptagUMSysGameSet->dwScore = GetDlgItemInt(IDC_EDIT21);
// 		m_ptagUMSysGameSet->dwBankerScore = GetDlgItemInt(IDC_EDIT22);
// 		m_ptagUMSysGameSet->dwTime = GetDlgItemInt(IDC_EDIT23);
// 		m_ptagUMSysGameSet->dwBankerAdd = GetDlgItemInt(IDC_EDIT24);
// 		m_ptagUMSysGameSet->dwTimeAdd = GetDlgItemInt(IDC_EDIT25);
// 
// 	}else
// 		m_ptagUMSysGameSet->dwEnableSysBanker = state;
// 
// 
// 	m_ptagUMSysGameSet->dwUserLimitScore = GetDlgItemInt(IDC_EDIT26);
// 	m_ptagUMSysGameSet->dwAreaLimitScore = GetDlgItemInt(IDC_EDIT27);
// 
// 
// 	m_ptagUMSysGameSet->dwUsuallyChangePercent = GetDlgItemInt(IDC_EDIT28);
// 	m_ptagUMSysGameSet->dwRobotWinScorePercent = GetDlgItemInt(IDC_EDIT29);
// 	m_ptagUMSysGameSet->dwRealBankerRobotLoseMax = GetDlgItemInt(IDC_EDIT36);
// 	m_ptagUMSysGameSet->dwRealBankerRobotLoseChangePercent = GetDlgItemInt(IDC_EDIT37);
// 	m_ptagUMSysGameSet->dwRealBankerRobotLoseMaxChange = GetDlgItemInt(IDC_EDIT38);
// 	GetDlgItemText(IDC_EDIT30,sText);
// 	m_ptagUMSysGameSet->dwRobotLoseMax = _ttoi(sText);
// 	m_ptagUMSysGameSet->dwRobotLoseChangePercent = GetDlgItemInt(IDC_EDIT31);
// 	GetDlgItemText(IDC_EDIT32,sText);
// 	m_ptagUMSysGameSet->dwRobotLoseMaxChange = _ttoi(sText);
// 	m_ptagUMSysGameSet->dwRobotProbabilityTanking = GetDlgItemInt(IDC_EDIT33);
// 	m_ptagUMSysGameSet->dwRobotTankingPercent = GetDlgItemInt(IDC_EDIT35);
// 	m_ptagUMSysGameSet->dwRobotDefineTanking = GetDlgItemInt(IDC_EDIT34);	
}

void CDlgSysGameSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//��ȡ��Ϣ
	SetSysGameData();

	CMissionUserInfo* pMissionUserInfo = CMissionUserInfo::GetInstance();
	if (pMissionUserInfo!=NULL)
	{
		pMissionUserInfo->SetSysGameInfo();
	}

	OnOK();
}

void CDlgSysGameSet::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CDlgSysGameSet::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int state = m_RobotBanker.GetCheck();
	if (state == 1)
	{
		m_RobotBankerCount.EnableWindow(TRUE);
		m_RobotApplyBanker.EnableWindow(TRUE);
		m_RobotWaitBanker.EnableWindow(TRUE);
	}
	else{
		m_RobotBankerCount.EnableWindow(FALSE);
		m_RobotApplyBanker.EnableWindow(FALSE);
		m_RobotWaitBanker.EnableWindow(FALSE);
	}
}

void CDlgSysGameSet::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int state = m_EnableSysBanker.GetCheck();
	if (state == 1)
	{
		m_Score.EnableWindow(TRUE);
		m_BankerScore.EnableWindow(TRUE);
		m_Time.EnableWindow(TRUE);
		m_BankerAdd.EnableWindow(TRUE);
		m_TimeAdd.EnableWindow(TRUE);

	}else
	{
		m_Score.EnableWindow(FALSE);
		m_BankerScore.EnableWindow(FALSE);
		m_Time.EnableWindow(FALSE);
		m_BankerAdd.EnableWindow(FALSE);
		m_TimeAdd.EnableWindow(FALSE);
	}
}
