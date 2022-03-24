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

	// 플레이어
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	// 몬스터
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create());
	// 마우스
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

	// visual C++ 라이브러리에서 제공, 모든 서식 문자를 지원
	swprintf_s(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size()); // 소수점 출력 가능
	// winAPI 라이브러리에서 제공, 소수점 출력이 불가능한 함수, 모든 서식 문자 제공을 안함
	// wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
	
	// API 에서는 이게 더 직관적이라 이걸 사용
	TextOut(m_DC, 51, 51, szBuff, lstrlen(szBuff));
	// 1인자 : 출력할 dc
	// 2~3인자 : 문자열을 출력하고자 하는 x, y 좌표
	// 4인자 : 출력할 문자열
	// 5인자 : 문자열 길이

	// direct에서 사용할 함수.
	//RECT rc{ 0, 0, 50, 50 };
	//DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);
	// 1인자 : 출력할 DC
	// 2인자 : 출력할 문자열
	// 3인자 : 출력할 문자열 길이
	// 4인자 : 출력할 문자열의 위치를 저장하는 구조체 주소
	// 5인자 : 출력할 문자열의 방식, 설정
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