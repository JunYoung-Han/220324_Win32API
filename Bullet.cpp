#include "pch.h"
#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;

	case UP:
		m_tInfo.fY -= m_fSpeed;
		break;

	case DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	// 벽 바깥으로 나가는지 판단.
	if (50 >= m_tRect.left || WINCX - 50 <= m_tRect.right ||
		50 >= m_tRect.top || WINCY - 50 <= m_tRect.bottom)
		m_bDead = true;
}

void CBullet::Render(HDC _HDC)
{
	Ellipse(_HDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}
