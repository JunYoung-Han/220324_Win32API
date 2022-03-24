#pragma once
#include "Include.h"

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(void);
	void Update(void);
	void Last_Update(void);
	void Render(void);
	void Release(void);
	
private:
	HDC m_DC;
	//CObj* m_pPlayer;
	//CObj* m_pMonster;
	//// �Ѿ˵��� ���ο��� �����.
	//list<CObj*> m_listBullet;

	list<CObj*> m_ObjList[OBJ_END];

	DWORD m_dwTime;
	int m_iFPS;
	TCHAR m_szFPS[32];	// �����ڵ� : �ѱ��� 2byte ¥�� char �̴�.

};

// ���콺�� ���͸� �浹���� �� ���͸� �����϶�
// ���Ϳ� �Ѿ��� �浹�Ǿ��� ���� ���Ϳ� �Ѿ��� �����϶�

// bool bCollision = IntersectRect(&rc, ù ��° ��Ʈ�� �ּ�, �� ��° ������ �ּ�) �Լ��� �̿��Ͽ� �浹ó���� �� ��

// c^2 = a^2 + b^2
// ������ ���� = �غ��� ���� + ������ ����
// fDiagonal = sqrt(fWidth *  fWidth + fHeight * fHeight)
