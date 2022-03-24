#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "AbstractFactory.h"

CMainGame::CMainGame()
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

	// �÷��̾�
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	// ����
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create());
	// ���콺
	m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory<CMouse>::Create());
}

void CMainGame::Update(void)
{
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
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render(void)
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	Rectangle(m_DC, 50, 50, WINCX - 50, WINCY - 50);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}

	TCHAR	szBuff[32] = L"";

	// visual C++ ���̺귯������ ����, ��� ���� ���ڸ� ����
	swprintf_s(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size()); // �Ҽ��� ��� ����
	// winAPI ���̺귯������ ����, �Ҽ��� ����� �Ұ����� �Լ�, ��� ���� ���� ������ ����
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
	
	// API ������ �̰� �� �������̶� �̰� ���
	TextOut(m_DC, 51, 51, szBuff, lstrlen(szBuff));
	// 1���� : ����� dc
	// 2~3���� : ���ڿ��� ����ϰ��� �ϴ� x, y ��ǥ
	// 4���� : ����� ���ڿ�
	// 5���� : ���ڿ� ����

	// direct���� ����� �Լ�.
	//RECT rc{ 0, 0, 50, 50 };
	//DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);
	// 1���� : ����� DC
	// 2���� : ����� ���ڿ�
	// 3���� : ����� ���ڿ� ����
	// 4���� : ����� ���ڿ��� ��ġ�� �����ϴ� ����ü �ּ�
	// 5���� : ����� ���ڿ��� ���, ����
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_DC);
}