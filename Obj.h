#pragma once

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void Set_Pos(float& fX, float& fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	void Set_Dir(DIRECTION _eDir)
	{
		m_eDir = _eDir;
	}
	void Set_Dead(bool _bDead) { m_bDead = _bDead; }
	bool Get_Dead(void) { return m_bDead; }
	const RECT* Get_RECT(void) { return &m_tRect; }
	const INFO* Get_INFO(void) { return &m_tInfo; }

public:
	virtual void Initialize(void) PURE;
	virtual int	 Update(void) PURE;
	virtual void Late_Update(void) PURE;	// 최종 RECT 값으로 업데이트 하기 위해.
	virtual void Render(HDC _HDC) PURE;
	virtual void Release(void) PURE;

protected:
	void Update_Rect(void);

protected:
	INFO m_tInfo;
	RECT m_tRect;

	float	m_fSpeed;
	bool	m_bDead;

	DIRECTION m_eDir;

};