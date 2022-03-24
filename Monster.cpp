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
	m_tInfo.fX = 400;
	m_tInfo.fY = 100;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;
}

int CMonster::Update(void)
{
	m_tInfo.fX += m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (WINCX - 50 <= m_tRect.right || 50 >= m_tRect.left)
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC _HDC)
{
	Rectangle(_HDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}
