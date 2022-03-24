#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr)
	, m_pMonster(nullptr)
	, m_DC(NULL)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Bullet(&m_listBullet);
	}
	if (nullptr == m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}
}

void CMainGame::Update(void)
{
	m_pPlayer->Update();
	for (auto iter = m_listBullet.begin(); iter != m_listBullet.end();)
	{
		int iEvent = (*iter)->Update();

		if (OBJ_DEAD == iEvent)
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_listBullet.erase(iter);
		}
		else
			++iter;
	}
	m_pMonster->Update();

}

void CMainGame::Last_Update(void)
{
	m_pPlayer->Late_Update();
	for (const auto& iter : m_listBullet)
		iter->Late_Update();
	m_pMonster->Late_Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	Rectangle(m_DC, 50, 50, WINCX - 50, WINCY - 50);

	m_pPlayer->Render(m_DC);
	for (const auto& iter : m_listBullet)
		iter->Render(m_DC);
	m_pMonster->Render(m_DC);

	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"Bullet : %d", m_listBullet.size());
	TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));
}

void CMainGame::Release(void)
{
	Safe_Delete(m_pPlayer);
	for_each(m_listBullet.begin(), m_listBullet.end(), Safe_Delete<CObj*>);
	m_listBullet.clear();
}