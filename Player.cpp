#include "pch.h"
#include "Player.h"
#include "Bullet.h"

CPlayer::CPlayer()
	: m_plistBullet(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;
}

int CPlayer::Update(void)
{
	Key_Input();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC _HDC)
{
	Rectangle(_HDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState('A'))
		m_plistBullet->push_back(Create_Bullet(LEFT));

	if (GetAsyncKeyState('D'))
		m_plistBullet->push_back(Create_Bullet(RIGHT));

	if (GetAsyncKeyState('W'))
		m_plistBullet->push_back(Create_Bullet(UP));

	if (GetAsyncKeyState('S'))
		m_plistBullet->push_back(Create_Bullet(DOWN));

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_plistBullet->push_back(Create_Bullet(LEFT));
		m_plistBullet->push_back(Create_Bullet(RIGHT));
		m_plistBullet->push_back(Create_Bullet(UP));
		m_plistBullet->push_back(Create_Bullet(DOWN));
	}


}

CObj* CPlayer::Create_Bullet(DIRECTION _eDir)
{
	CObj* pBullet = new CBullet;
	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Dir(_eDir);

	return pBullet;
}