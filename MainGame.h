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
	//// 총알들은 메인에서 저장됨.
	//list<CObj*> m_listBullet;

	list<CObj*> m_ObjList[OBJ_END];

	DWORD m_dwTime;
	int m_iFPS;
	TCHAR m_szFPS[32];	// 유니코드 : 한글자 2byte 짜리 char 이다.

};

// 마우스와 몬스터를 충돌했을 때 몬스터를 삭제하라
// 몬스터와 총알이 충돌되었을 때도 몬스터와 총알을 삭제하라

// bool bCollision = IntersectRect(&rc, 첫 번째 렉트의 주소, 두 번째 렉터의 주소) 함수를 이용하여 충돌처리를 할 것

// c^2 = a^2 + b^2
// 빗변의 제곱 = 밑변의 제곱 + 높이의 제곱
// fDiagonal = sqrt(fWidth *  fWidth + fHeight * fHeight)
