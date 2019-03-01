#include "stdafx.h"
#include "BasicBoss.h"
#include "resource.h"

CImageList CBasicBoss::m_Images;

CBasicBoss::CBasicBoss()
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - BasicBoss_HEIGHT) + 1;

	//���ȷ��ͼ������
	m_nImgIndex = rand() % 2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -BasicBoss_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_nMotion = 1;
		m_ptPos.y = GAME_HEIGHT + BasicBoss_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	m_nWait = 0;
}


CBasicBoss::~CBasicBoss()
{
}
BOOL CBasicBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BasicBoss, RGB(255, 255, 255), 80, 61, 2);
}
BOOL CBasicBoss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + BasicBoss_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BasicBoss_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBasicBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
