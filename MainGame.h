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
	CObj* m_pPlayer;
	CObj* m_pMonster;
	// �Ѿ˵��� ���ο��� �����.
	list<CObj*> m_listBullet;
};