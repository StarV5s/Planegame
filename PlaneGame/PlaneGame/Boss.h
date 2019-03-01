#pragma once
#include "GameObject.h"

class CBoss :public CGameObject
{
public:
	CBoss(void);
	~CBoss(void);
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + Boss_HEIGHT, m_ptPos.y + Boss_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
	int BossLifeNum = 900;//Boss����ֵ
	int BossLifeFlag = 0;//�ж��Ƿ���ʾѪ����
private:
	static const int Boss_HEIGHT = 200;
	static const int Boss_WIDTH = 200;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int    m_nWait;//������ʱ
	int   m_nMotionX;
	int   m_nMotionY;

};

