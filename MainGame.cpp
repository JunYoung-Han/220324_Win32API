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
	srand(time(NULL));
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

	if (GetAsyncKeyState('M'))
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create());

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

	// ���Ϳ� �̻��� �浹 ����
	for (auto& iter_m : m_ObjList[OBJ_MONSTER])
	{
		for (auto& iter_b : m_ObjList[OBJ_BULLET])
		{
			RECT rc{};
			bool bCollision = IntersectRect(&rc, iter_m->Get_RECT(), iter_b->Get_RECT());
			if (bCollision)
			{
				iter_m->Set_Dead(true);
				iter_b->Set_Dead(true);
			}
		}
	}
	// ���콺�� ���� �浹 ����
	for (auto& iter_m : m_ObjList[OBJ_MONSTER])
	{
		RECT rc{};
		bool bCollision = IntersectEllipse(&rc, iter_m->Get_RECT(), m_ObjList[OBJ_MOUSE].front()->Get_RECT());
		if (bCollision)
		{
			iter_m->Set_Dead(true);
		}
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
	Rectangle(m_DC, BORDER_OFFSET, BORDER_OFFSET, WINCX - BORDER_OFFSET, WINCY - BORDER_OFFSET);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}

	TCHAR	szBuff[32] = L"";

	// visual C++ ���̺귯������ ����, ��� ���� ���ڸ� ����
	// �Ҽ��� ��� ����
	swprintf_s(szBuff, L"Monster: %d   Bullet: %d", m_ObjList[OBJ_MONSTER].size(), m_ObjList[OBJ_BULLET].size());
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

bool CMainGame::IntersectEllipse(LPRECT _rc, const RECT* _Rect1, const RECT* _Rect2)
{
	_Rect1->left;
	// �� 1
	// ����
	INFO tInfo_1;
	tInfo_1.fCX = _Rect1->right - _Rect1->left;
	tInfo_1.fCY = _Rect1->bottom - _Rect1->top;
	tInfo_1.fX = _Rect1->left + tInfo_1.fCX / 2;
	tInfo_1.fY = _Rect1->top + tInfo_1.fCY / 2;
	INFO tInfo_2;
	tInfo_2.fCX = _Rect2->right - _Rect2->left;
	tInfo_2.fCY = _Rect2->bottom - _Rect2->top;
	tInfo_2.fX = _Rect2->left + tInfo_2.fCX / 2;
	tInfo_2.fY = _Rect2->top + tInfo_2.fCY / 2;

	// �غ�
	float fWidth = abs(tInfo_2.fX - tInfo_1.fX);
	// ����
	float fHeight = abs(tInfo_2.fY - tInfo_1.fY);
	// �밢
	float fDiagonal = (float)sqrt((double)fWidth * (double)fWidth + (double)fHeight * (double)fHeight);

	if (fDiagonal <= tInfo_1.fCX / 2 + tInfo_2.fCX / 2)
		return true;
	else
		return false;
}
