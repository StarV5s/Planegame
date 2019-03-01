// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once

class CMyPlane;
class CLifeLogo;
class CPlaneGameView : public CView
{

	enum ObjType{ enEnemy, enBomb, enBall, enExplosion, enBasicBoss, enBasicBossBall, enStar, enHeart, enShield, enBoss, enBossBall, enHPLogo, enLifeLogo, enStarNumLogo,enSkill };

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);
	CDC m_cacheDC;//����DC
	CBitmap m_cacheCBitmap;//����λͼ
	int y = 0;

	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	CLifeLogo* m_Life1 = NULL;
	CLifeLogo* m_Life2 = NULL;
	CLifeLogo* m_Life3 = NULL;

	CObList    m_ObjList[15];
	int PlayerScoreNum = 0;
	int PlaneLifeNum = 15;//�ɻ�����ֵ
	int PlaneLife = 3;//�ɻ�������
	int Planeflag = 0;//����ս����
	int flag = 0;//���ƿ�ʼ������flag
	int UnbeatableFlag = 0;//�ж��޵�ģʽ��
	int BossFlag = 0;//ʹbossֻ����һ��
	int StarNum = 0;//������
	int StorageStarNum = 0;//�洢������
	int StorageBossLifeNum = 0;//�洢Boss����ֵ
	int n = 0;
	int ChapterFlag = 1;//�ؿ���
	int flag1 = 0;//����Boss�����ӵ���Ƶ��
	int LogoFlag = 0;//ʹlogoֻ�ܲ���һ��
	int SuperFlag = 0;
	int MusicFlag = 0;
	int BossDieFlag = 0;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	bool DrawBG(CDC* pDC, UINT bmpID, CRect DestRect);
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

