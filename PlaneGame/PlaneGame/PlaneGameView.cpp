// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "resource.h"
#include <mmsystem.h>

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include "BasicBoss.h"
#include "BasicBossBall.h"
#include "Star.h"
#include "Heart.h"
#include "Shield.h"
#include "Boss.h"
#include "BossBall.h"
#include "HPLogo.h"
#include "LifeLogo.h"
#include "StarNumLogo.h"
#include "Skill.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	
}


CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE | SND_NODEFAULT | SND_LOOP);
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_Life1;
	delete m_Life2;
	delete m_Life3;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBasicBoss::LoadImage();
	CBasicBossBall::LoadImage();
	CStar::LoadImage();
	CHeart::LoadImage();
	CShield::LoadImage();
	CMyPlane::LoadImageShield();
	CBoss::LoadImage();
	CBossBall::LoadImage();
	CHPLogo::LoadImage();
	CLifeLogo::LoadImage();
	CStarNumLogo::LoadImage();
	CSkill::LoadImage();
	
	//��������(ս��)
	m_pMe = new CMyPlane;
	m_Life1 = new CLifeLogo(1);
	m_Life2 = new CLifeLogo(2);
	m_Life3 = new CLifeLogo(3);
	//������Ϸ
	SetTimer(1,30,NULL);
	

	return TRUE;
}

bool CPlaneGameView::DrawBG(CDC* pDC, UINT bmpID, CRect DestRect)
{
	CBitmap bmp;
	bmp.LoadBitmap(bmpID);//����ͼ

	BITMAP   bitmap;//�������������Ϊ���Եõ�ͼƬ�Ŀ�͸ߣ����һ�仰��
	bmp.GetBitmap(&bitmap);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);//�����ڴ�dc
	dcMem.SelectObject(&bmp);//��ͼƬ���ص��ڴ�dc
	CBitmap *pbmpOld = dcMem.SelectObject(&bmp);
	pDC->StretchBlt(0, 0, 600, 800, &dcMem, 0, 0, 600, 800, SRCCOPY);  //���ڴ�dc�������ȫ�����Ƶ���ǰdc����
	return true;
}


void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//���ƿ�ʼ����
    CRect rect;
	GetClientRect(&rect);
	DrawBG(pMemDC, IDB_STARTUI, rect);//���ú�������

    //���س����������
	if (GetKey(VK_RETURN) == 1)
		flag = 1;
	if (flag == 1)
	{
		CPaintDC dc(this);//���ڻ����ļ�������
		CRect rect;
		CDC *cDC = this->GetDC();//��õ�ǰ���ڵ�DC
		GetClientRect(&rect);//��ô��ڵĳߴ�
		CDC m_bgcDC;//������ʾ�豸����
		m_bgcDC.CreateCompatibleDC(NULL);//��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
		CBitmap m_bgBitmap;// ����λͼ����
		m_bgBitmap.LoadBitmap(IDB_BITMAP1);
		m_bgcDC.SelectObject(&m_bgBitmap);
		//��ȡ���ڴ�С  
		GetClientRect(&rect);
		//��������DC  
		m_cacheDC.CreateCompatibleDC(NULL);
		m_cacheCBitmap.CreateCompatibleBitmap(cDC, rect.Width(), rect.Height());
		m_cacheDC.SelectObject(&m_cacheCBitmap);
		pMemDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_bgcDC, 0, y, SRCCOPY);//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
		pMemDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_bgcDC, 0, y + 900, SRCCOPY);

		y -= 1;
		if (y <= -900)
			y = 0;
		//�ڻ�����ͼ��,ʹ��������Ч  
		ValidateRect(&rect);
		//��ͼ��ɺ������ 
		//�ͷŻ���DC  
		m_cacheDC.DeleteDC();
		//�ͷŶ���  
		m_cacheCBitmap.DeleteObject();
		//�ͷŴ���DC  
		ReleaseDC(cDC);
	}

	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
		if (flag == 1)
		{
			m_pMe->Draw(m_pMemDC, FALSE);
			CRect liferectFr(40, 12, 185, 27);
			CRect liferect(40, 12, PlaneLifeNum*10+35, 27);
			CBrush lifebrush(RGB(255, 80, 46));
		    pMemDC->FrameRect(liferectFr, &lifebrush);
			pMemDC->FillRect(liferect, &lifebrush);
		}
	}
	else
	{   
		//���ɻ�����ֵ
		if (PlaneLife == 0)
		{   //Game Over
			CString str = _T("Game Over!");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
			CString str1 = _T("��H������");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2+30, str1);
			if (GetKey('H'))
			{
				PlaneLife = 1;
			}
		}
		else
		{
			m_pMe = new CMyPlane;
			PlaneLifeNum = 15;
			m_pMe->Draw(m_pMemDC, FALSE);
			CRect liferectFr(25, 10, 165, 25);
			CRect liferect(25, 10, PlaneLifeNum * 10 + 15, 25);
			CBrush lifebrush(RGB(255, 80, 46));
			pMemDC->FrameRect(liferectFr, &lifebrush);
			pMemDC->FillRect(liferect, &lifebrush);
		}
	}
	if (m_Life1 != NULL)
	{
		if (flag == 1)
			m_Life1->Draw(m_pMemDC, FALSE);
	}
	if (m_Life2 != NULL)
	{
		if (flag == 1)
			m_Life2->Draw(m_pMemDC, FALSE);
	}
	if (m_Life3 != NULL)
	{
		if (flag == 1)
			m_Life3->Draw(m_pMemDC, FALSE);
	}

	//���� ��������ը���л����ӵ�
	for(int i=0;i<15;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	//����ͼ��
	if (LogoFlag == 0)
	{
		//HPͼ��
		m_ObjList[enHPLogo].AddTail(new CHPLogo);
		//������ͼ��
		m_ObjList[enStarNumLogo].AddTail(new CStarNumLogo);
		//����ͼ��
		m_ObjList[enSkill].AddTail(new CSkill);
		LogoFlag = 1;
	}
	//�ɻ�������ͼ��
	if (PlaneLife == 2)
	{
		delete m_Life3;
		m_Life3 = NULL;
	}
	else if (PlaneLife == 1)
	{
		delete m_Life2;
		m_Life2 = NULL;
	}
	else if (PlaneLife == 0)
	{
		delete m_Life1;
		m_Life1 = NULL;
	}
	      
	//�����
	static int nCreator = rand() %5+10;
	static int nCreator1 = rand() % 80 + 10 - ChapterFlag * 2;
	static int nCreatorStar = rand() % 2 + 3;
	static int nCreatorHeart = rand() % 70 + 10;
	static int nCreatorShield = rand() % 50 + 10;
	//��ͣ��Ϸ

	if (GetKey('M'))
	{
		KillTimer(1);
		if (AfxMessageBox(_T("������Ϸ"), MB_OK) == 1)
			SetTimer(1, 20, NULL);
		else(1);
	}

	//30�����ǿ�����ս���ӵ�
	if (GetKey('Q') && StarNum >= 30)
	{
		if (Planeflag < 1)
		{
			Planeflag = 1;
			StarNum -= 30;
		}
	}
	//10�����ǿɿ�������
	if (GetKey('W') && StarNum >= 10 && m_pMe->ShieldFlag == 0)
	{	
		StarNum -= 10;
		m_pMe->ShieldFlag = 1;
		m_pMe->ShieldFlag1 = 1;
		
	}
	//����ȫ�����ܲ�����������
	if (GetKey('R') && StarNum >= 20 && m_pMe->RFlag == 0)
	{
		StarNum -= 10;
		m_pMe->ShieldFlag = 1;
		for (int i = 0; i <= 600; i+=16)
		{
			for (int j = 800; j <=900; j+=50)
			{
				m_ObjList[enBomb].AddTail(new CBomb(i, j, 1));
			}
		}
		m_pMe->RFlag = 1;
	}
	//�����޵�ģʽ
	if (GetKey('F'))
	{
		UnbeatableFlag = 1;
	}
	//�ر��޵�ģʽ
	if (GetKey('D'))
	{
		UnbeatableFlag = 0;
	}
    
	//��������ģʽ
	if (GetKey('V'))
	{
		StarNum = 10000;
		UnbeatableFlag = 1;
		SuperFlag = 1;
	}
	//�رճ���ģʽ
	if (GetKey('B'))
	{
		StarNum = 100;
		UnbeatableFlag = 0;
		SuperFlag = 0;
	}
	//�رչ���Աģʽ
	if (GetKey('B'))
	{
		StarNum = StorageStarNum;
		UnbeatableFlag = 0;
	}
	//��������л�
	if (nCreator <= 0 && ChapterFlag != 3)
	{
		nCreator = rand() % 5 + 10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--; 
	//�������BasicBoss
	if ((nCreator1 <= 0 && PlayerScoreNum >= 1000 && ChapterFlag != 3) || (nCreator1 <= 0 && ChapterFlag == 2 && ChapterFlag != 3))
	{
		nCreator1 = rand() % 80 + 10;
		m_ObjList[enBasicBoss].AddTail(new CBasicBoss);
	}
	nCreator1--;
	//�����֣����ùؿ�
	if (PlayerScoreNum == 1000 || GetKey('2'))
	{
		ChapterFlag = 2;
		PlaneLifeNum = 15;
	}
	//����Boss
	if ((PlayerScoreNum >= 3000 || GetKey('3')) && BossFlag == 0)
	{
		ChapterFlag = 3;
		m_ObjList[enBoss].AddTail(new CBoss);
		BossFlag = 1;
	}
	if(m_pMe==NULL)
		return;

	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	
	//����ս������
	CRect mRect = m_pMe->GetRect();
	if(GetKey(VK_SPACE)==1)//�����˿ո��
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (Planeflag == 0)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 17, pt.y - 25,1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 32, pt.y - 25,2));
			}
			else if (Planeflag == 1)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 17, pt.y - 25,1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 32, pt.y - 25,2));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 3, pt.y - 5,3));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 47, pt.y - 5,4));
			}
		}
	}


	//�л������ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  if(ePt.y<PlanePt.y)
		         by=  TRUE;

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	//BasicBoss�����ӵ�

	for (POSITION ePos = m_ObjList[enBasicBoss].GetHeadPosition(); ePos != NULL;)
	{
		
		CBasicBoss* pBasicBoss = (CBasicBoss*)m_ObjList[enBasicBoss].GetNext(ePos);
		
		//���BasicBossѪ��
		if (pBasicBoss->BasicBossLifeFlag == 1)
		{
			CRect mRect = pBasicBoss->GetRect();
			CPaintDC dc(this);//���ڻ����ļ�������
			CDC *cDC = this->GetDC();//��õ�ǰ���ڵ�DC
			cDC->FillSolidRect(mRect.left + 10, mRect.bottom + 3, 50, 4, RGB(0, 0, 0));
			cDC->FillSolidRect(mRect.left + 10, mRect.bottom + 3, pBasicBoss->BasicBossLifeNum*5, 4, RGB(255, 80, 46));
		}
		if (!pBasicBoss->Fired())
			continue;
		CPoint  ePt = pBasicBoss->GetPoint();

		BOOL by = FALSE;
		by = TRUE;
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 1));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 2));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 3));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 4));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 5));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 6));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 7));
		m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 33, ePt.y + 40, pBasicBoss->GetMontion(), 8));
	}
	//Boss�����ӵ�

	for (POSITION ePos = m_ObjList[enBoss].GetHeadPosition(); ePos != NULL;)
	{
		CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos);
		//���BossѪ��
		if (pBoss->BossLifeFlag == 1)
		{
			CRect mRect = pBoss->GetRect();
			CPaintDC dc(this);//���ڻ����ļ�������
			CDC *cDC = this->GetDC();//��õ�ǰ���ڵ�DC
			cDC->FillSolidRect(mRect.left + 10, mRect.bottom + 3, 150, 4, RGB(0, 0, 0));
			cDC->FillSolidRect(mRect.left + 10, mRect.bottom + 3, pBoss->BossLifeNum/6, 4, RGB(255, 80, 46));
		}
		if (!pBoss->Fired())
			continue;
		CPoint  ePt = pBoss->GetPoint();
		if (StorageBossLifeNum - pBoss->BossLifeNum >= 50)
		{
			for (int i = 0; i < 100; i+=20)
			{
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x - 5, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 15, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 35, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 55, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 75, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 95, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 115, ePt.y + 140 + i, pBoss->GetMontion(), 2));
				m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x + 135, ePt.y + 140 + i, pBoss->GetMontion(), 2));
			}
			flag1 = 0;
		}
		BOOL by = FALSE;

		if (ePt.y<PlanePt.y)
			by = TRUE;

		if (by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 1));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 2));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 3));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 4));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 5));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 6));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 7));
			m_ObjList[enBasicBossBall].AddTail(new CBasicBossBall(ePt.x + 93, ePt.y + 40, pBoss->GetMontion(), 8));
		}
	
		if (flag1 == 0)
		{
			StorageBossLifeNum = pBoss->BossLifeNum;
			flag1 = 1;
		}

	}
	
	if (UnbeatableFlag == 0 && m_pMe->ShieldFlag == 0 && BossDieFlag == 0)//�ж��޵�ģʽ�Ƿ���
	{
		//�л��ӵ�ը��ս��
		POSITION bPos1 = NULL, bPos2 = NULL;
		
		for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
				CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
				CRect bRect = pBall->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);

					//ɾ���ӵ�
					m_ObjList[enBall].RemoveAt(bPos2);
					delete pBall;

					//ɾ��ս��
					PlaneLifeNum -= 1;
					if (PlaneLifeNum == 0)
					{
						PlaneLife--;
						delete m_pMe;
						m_pMe = NULL;
						break;
					}

				}
		}

		//BasicBoss�ӵ�ը��ս��
		POSITION bPos3 = NULL, bPos4 = NULL;
		for (bPos3 = m_ObjList[enBasicBossBall].GetHeadPosition(); (bPos4 = bPos3) != NULL;)
		{
			CBasicBossBall* pBasicBossBall = (CBasicBossBall*)m_ObjList[enBasicBossBall].GetNext(bPos3);
			CRect bRect = pBasicBossBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enBasicBossBall].RemoveAt(bPos4);
				delete pBasicBossBall;

				//ɾ��ս��
				PlaneLifeNum -= 1;
				if (PlaneLifeNum == 0)
				{
					PlaneLife--;
					delete m_pMe;
					m_pMe = NULL;
					break;
				}

			}
		}
		//Boss�ӵ�ը��ս��
		POSITION bPos11 = NULL, bPos12 = NULL;
		for (bPos11 = m_ObjList[enBossBall].GetHeadPosition(); (bPos12 = bPos11) != NULL;)
		{
			CBossBall* pBossBall = (CBossBall*)m_ObjList[enBossBall].GetNext(bPos11);
			CRect bRect = pBossBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enBossBall].RemoveAt(bPos12);
				delete pBossBall;

				//ɾ��ս��
				PlaneLifeNum -= 1;
				if (PlaneLifeNum == 0)
				{
					PlaneLife--;
					delete m_pMe;
					m_pMe = NULL;
					break;
				}

			}
		}
	}
	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				PlayerScoreNum += 10;
				//�����������
				if (nCreatorShield <= 0)
				{
					nCreatorShield = rand() % 50 + 10;
					m_ObjList[enShield].AddTail(new CShield(mRect.left, mRect.top));
				}
				nCreatorShield--;
				//�����������
				if (nCreatorStar <= 0)
				{
					nCreatorStar = rand() % 2 + 3;
					m_ObjList[enStar].AddTail(new CStar(mRect.left, mRect.top));
				}
				nCreatorStar--;
				break;

			}
		}
	}
	//ս������ը��BasicBoss
	POSITION mPos3 = NULL, mPos4 = NULL;
	for (mPos3 = m_ObjList[enBomb].GetHeadPosition(); (mPos4 = mPos3) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos3);
		CRect bRect = pBomb->GetRect();

		POSITION ePos3 = NULL, ePos4 = NULL;
		for (ePos3 = m_ObjList[enBasicBoss].GetHeadPosition(); (ePos4 = ePos3) != NULL;)
		{
			
			
			CBasicBoss* pBasicBoss = (CBasicBoss*)m_ObjList[enBasicBoss].GetNext(ePos3);
			CRect mRect = pBasicBoss->GetRect();
			CRect tmpRect;
			
			
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				pBasicBoss->BasicBossLifeFlag = 1;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos4);
				delete pBomb;
				pBasicBoss->BasicBossLifeNum -= 1;
				//BasicBoss����ֵΪ0ʱ��ɾ���л�
				if (pBasicBoss->BasicBossLifeNum == 0)
				{
					CPoint BasicBossPt;
					m_ObjList[enBasicBoss].RemoveAt(ePos4);
				    delete pBasicBoss;
					
				    PlayerScoreNum += 30;
					pBasicBoss->BasicBossLifeNum = 5;
					pBasicBoss->BasicBossLifeFlag = 0;
					//���������Ѫ��
					if (nCreatorHeart <= 0)
					{
						nCreatorHeart = rand() % 30 + 5;
						m_ObjList[enHeart].AddTail(new CHeart(mRect.left, mRect.top));
					}
					nCreatorHeart--;
					//�����������
					if (nCreatorShield <= 0)
					{
						nCreatorShield = rand() % 50 + 10;
						m_ObjList[enShield].AddTail(new CShield(mRect.left, mRect.top));
					}
					nCreatorShield--;
					//��������
					m_ObjList[enStar].AddTail(new CStar(mRect.left, mRect.top));
					m_ObjList[enStar].AddTail(new CStar(mRect.left+30, mRect.top+30));
				}
				break;

			}
		}
	}
	//ս������ը��Boss
	POSITION mPos11 = NULL, mPos12 = NULL;
	for (mPos11 = m_ObjList[enBomb].GetHeadPosition(); (mPos12 = mPos11) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos11);
		CRect bRect = pBomb->GetRect();

		POSITION ePos3 = NULL, ePos4 = NULL;
		for (ePos3 = m_ObjList[enBoss].GetHeadPosition(); (ePos4 = ePos3) != NULL;)
		{


			CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos3);
			CRect mRect = pBoss->GetRect();
			CRect tmpRect;


			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				pBoss->BossLifeFlag = 1;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top - 50)
					);
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top - 50)
					);
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top - 50)
					);
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top - 50)
					);
				m_ObjList[enBomb].RemoveAt(mPos12);
				delete pBomb;
				//���������Ѫ��
				if (nCreatorHeart <= 0)
				{
					nCreatorHeart = rand() % 70 + 200;
					m_ObjList[enHeart].AddTail(new CHeart(mRect.left, mRect.top));
				}
				nCreatorHeart--;
				//�����������
				if (nCreatorShield <= 0)
				{
					nCreatorShield = rand() % 70 + 270;
					m_ObjList[enShield].AddTail(new CShield(mRect.left, mRect.top));
				}
				nCreatorShield--;
				//��������
				if (nCreatorStar <= 0)
				{
					nCreatorStar = rand() % 2 + 40;
					m_ObjList[enStar].AddTail(new CStar(mRect.left, mRect.top));
				}
				nCreatorStar--;
				pBoss->BossLifeNum -= 1;
				//Boss����ֵΪ0ʱ��ɾ���л�
				if (pBoss->BossLifeNum == 0)
				{
					CPoint BossPt;
					m_ObjList[enBoss].RemoveAt(ePos4);
				    delete pBoss;

					PlayerScoreNum += 500;
					pBoss->BossLifeNum = 5;
					pBoss->BossLifeFlag = 0;
					BossDieFlag = 1;
				}
				break;

			}
		}
	}
	//ս���Ե�����
	POSITION bPos5 = NULL, bPos6 = NULL;
	for (bPos5 = m_ObjList[enStar].GetHeadPosition(); (bPos6 = bPos5) != NULL;)
	{
		CStar* pStar = (CStar*)m_ObjList[enStar].GetNext(bPos5);
		CRect bRect = pStar->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ������
			StarNum++;
			m_ObjList[enStar].RemoveAt(bPos6);
			delete pStar;
		}
	}
	//ս���Ե���Ѫ��
	POSITION bPos7 = NULL, bPos8 = NULL;
	for (bPos7 = m_ObjList[enHeart].GetHeadPosition(); (bPos8 = bPos7) != NULL;)
	{
		CHeart* pHeart = (CHeart*)m_ObjList[enHeart].GetNext(bPos7);
		CRect bRect = pHeart->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			
			if (PlaneLifeNum <= 12)
				PlaneLifeNum += 3;
			else if (PlaneLifeNum <= 15)
				PlaneLifeNum = 15;
			//ɾ����Ѫ��
			m_ObjList[enHeart].RemoveAt(bPos8);
			delete pHeart;
		}
	}
	//ս���Ե�����
	POSITION bPos9 = NULL, bPos10 = NULL;
	for (bPos9 = m_ObjList[enShield].GetHeadPosition(); (bPos10 = bPos9) != NULL;)
	{
		CShield* pShield = (CShield*)m_ObjList[enShield].GetNext(bPos9);
		CRect bRect = pShield->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//�����޵�ģʽ
			m_pMe->ShieldFlag = 1;

			//ɾ������
			m_ObjList[enShield].RemoveAt(bPos10);
			delete pShield;
		}
	}
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);
	//flagΪ1ʱ��ʼ��Ϸ
	if (flag == 1)
	{
		AI();
		if (PlaneLifeNum != 0)
		{
			//��ʾ�ɻ�����ֵ
			CString PlaneLife;
			PlaneLife.Format(L"             %d/15", PlaneLifeNum);
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(255, 255, 255));
			m_pDC->TextOut(80, 11, PlaneLife);


			//��ʾ����
			CString PlayerScore;
			PlayerScore.Format(L"���֣� %d", PlayerScoreNum);
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(56, 233, 239));
			m_pDC->TextOut(50, 120, PlayerScore);


			//��ʾQ���ܹ���
			CString Q1;
			Q1.Format(L"Q:����ս���ӵ�");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(55, 180, Q1);

			CString Q2;
			Q2.Format(L"    (30������)");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(50, 195, Q2);


			//��ʾW���ܹ���
			CString W1;
			W1.Format(L"W:����������");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(50, 235, W1);

			CString W2;
			W2.Format(L"    (30������)");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(50, 250, W2);

			//��ʾR���ܹ���
			CString R1;
			R1.Format(L"R:ʹ��ȫͼ����");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(53, 310, R1);

			CString R2;
			R2.Format(L"(30������)");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(35, 355, R2);

			CString R3;
			R3.Format(L"ͬʱ����������");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(53, 325, R3);

			CString R4;
			R4.Format(L"����ȴʱ��");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(38, 176, 247));
			m_pDC->TextOut(38, 340, R4);


			//��ʾ������
			CString Star;
			Star.Format(L"      %d", StarNum);
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(252, 198, 20));
			m_pDC->TextOut(38, 82, Star);


			//��ʾ�ؿ���
			CString Chapter;
			Chapter.Format(L"��%d��", ChapterFlag);
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(200, 136, 255));
			m_pDC->TextOut(290, 11, Chapter);


			//���ز�����ʾ
			CString JumpChapter;
			JumpChapter.Format(L"��1,2,3��ֱ�ӽ����Ӧ�ؿ�");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(0, 0, 0));
			m_pDC->TextOut(290, 31, JumpChapter);


			//��ʾ�޵�ģʽ״̬
			if (UnbeatableFlag == 1)
			{
				CString Unbeatable;
				Unbeatable.Format(L"�޵�ģʽ�ѿ���");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(0, 0, 0));
				m_pDC->TextOut(520, 100, Unbeatable);
			}
			else {
				CString Unbeatable;
				Unbeatable.Format(L"�޵�ģʽ�ѹر�");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(0, 0, 0));
				m_pDC->TextOut(520, 100, Unbeatable);
			}

			CString Unbeatable;
			Unbeatable.Format(L"(ON:'F'  OFF:'D')");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(0, 0, 0));
			m_pDC->TextOut(521, 118, Unbeatable);


			//��ʾ����ģʽ״̬
			if (SuperFlag == 1)
			{
				CString Super;
				Super.Format(L"����ģʽ�ѿ���");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(0, 0, 0));
				m_pDC->TextOut(520, 140, Super);
			}
			else {
				CString Super;
				Super.Format(L"����ģʽ�ѹر�");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(0, 0, 0));
				m_pDC->TextOut(520, 140, Super);
			}

			Unbeatable.Format(L"(ON:'V'  OFF:'B')");
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(0, 0, 0));
			m_pDC->TextOut(521, 158, Unbeatable);


			//��ʾ������״̬
			if (m_pMe->ShieldFlag == 1)
			{
				CString Shield;
				Shield.Format(L"ON");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(255, 255, 255));
				m_pDC->TextOut(50, 220, Shield);
			}
			else {
				CString Shield;
				Shield.Format(L"OFF");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(255, 255, 255));
				m_pDC->TextOut(50, 220, Shield);
			}


			//ͨ��֪ͨ
			if (BossDieFlag == 1)
			{
				CString BossDie;
				BossDie.Format(L"��ϲ��ͨ���ˣ�����");
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(255, 255, 255));
				m_pDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2-50, BossDie);
				CString PlayerScore;
				PlayerScore.Format(L"��õĻ��֣� %d��", PlayerScoreNum);
				m_pDC->SetBkMode(TRANSPARENT);
				m_pDC->SetTextAlign(TA_CENTER);
				m_pDC->SetTextColor(RGB(56, 233, 239));
				m_pDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 -20, PlayerScore);
			}
		}
	}

	CView::OnTimer(nIDEvent);
}




