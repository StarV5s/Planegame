#pragma once
#include "GameObject.h"

class CBasicBoss :public CGameObject
{
public:
	CBasicBoss(void);
	~CBasicBoss(void);
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BasicBoss_WIDTH, m_ptPos.y + BasicBoss_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
	int BasicBossLifeNum = 10;//BasicBoss����ֵ
	int BasicBossLifeFlag = 0;//�ж��Ƿ���ʾѪ����
private:
	static const int BasicBoss_WIDTH = 80;
	static const int BasicBoss_HEIGHT = 61;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int    m_nWait;//������ʱ


};

