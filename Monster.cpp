#include "pch.h"
#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_tInfo.fX = rand() % (WINCX - (BORDER_OFFSET * 2) - (int)m_tInfo.fCX) + BORDER_OFFSET + m_tInfo.fCX / 2;
	m_tInfo.fY = rand() % (WINCY - (BORDER_OFFSET * 2) - (int)m_tInfo.fCY) + BORDER_OFFSET + m_tInfo.fCY / 2;

	m_fSpeed = 5.f;

	m_eDir = DIRECTION(rand() % 4);
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case 0:
		m_tInfo.fX += m_fSpeed;
		break;

	case 1:
		m_tInfo.fX -= m_fSpeed;
		break;

	case 2:
		m_tInfo.fY += m_fSpeed;
		break;

	case 3:
		m_tInfo.fY -= m_fSpeed;
		break;

	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (((LEFT == m_eDir || RIGHT == m_eDir) && (WINCX - 50 <= m_tRect.right || 50 >= m_tRect.left))
		|| ((UP == m_eDir || DOWN == m_eDir) && (WINCY - 50 <= m_tRect.bottom || 50 >= m_tRect.top)))
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC _HDC)
{
	Ellipse(_HDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}
