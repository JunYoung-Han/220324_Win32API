#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "AbstractFactory.h"

CMainGame::CMainGame()
/*: m_pPlayer(nullptr)
, m_pMonster(nullptr)
, m_DC(NULL)*/
	: m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
	/*
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
	}*/

	// 플레이어
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	// 몬스터
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create());
	
}

void CMainGame::Update(void)
{
	/*
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
	m_pMonster->Update();*/

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

}

void CMainGame::Last_Update(void)
{
	/*
	m_pPlayer->Late_Update();
	for (const auto& iter : m_listBullet)
		iter->Late_Update();
	m_pMonster->Late_Update();*/

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render(void)
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	Rectangle(m_DC, 50, 50, WINCX - 50, WINCY - 50);

	/*m_pPlayer->Render(m_DC);
	for (const auto& iter : m_listBullet)
		iter->Render(m_DC);
	m_pMonster->Render(m_DC);*/

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}

	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
	TextOut(m_DC, 51, 51, szBuff, lstrlen(szBuff));
}

void CMainGame::Release(void)
{

	//Safe_Delete(m_pPlayer);
	//for_each(m_listBullet.begin(), m_listBullet.end(), Safe_Delete<CObj*>);
	//m_listBullet.clear();


	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_DC);
}