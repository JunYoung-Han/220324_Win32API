#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void Set_Bullet(list<CObj*>* _plistBullet) { m_plistBullet = _plistBullet; }

public:
	virtual void Initialize(void) 		 override;
	virtual int  Update(void) 			 override;
	virtual void Late_Update(void)		 override;
	virtual void Render(HDC _HDC) 		 override;
	virtual void Release(void) 			 override;
	
private:
	void Key_Input(void);
	CObj* Create_Bullet(DIRECTION _eDir);

private:
	list<CObj*>* m_plistBullet;
};

