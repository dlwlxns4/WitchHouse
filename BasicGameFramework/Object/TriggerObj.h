#pragma once
#include "GameObject.h"

class TriggerObj : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~TriggerObj() noexcept = default;

	virtual void	 Init() override;
	virtual void	 OnTrigger() override;
	virtual void	 Render(HDC hdc) override;


	//Æ÷Å»¿ë
	virtual void	AddMainId() = 0;
	virtual	int		GetMainId() = 0;

private:
};

class SizeAdjRenderer;
class DoorObj : public TriggerObj
{
public:
	using TriggerObj::TriggerObj;
	virtual ~DoorObj() noexcept = default;

	virtual void Init() override;
	virtual void OnTrigger() override;
	virtual void Update() override;

	virtual void Write(std::ostream& os) const override;
	virtual void Read(std::istream& is) override;

	virtual void		AddMainId() { loadMap++; }
	virtual int			GetMainId() { return loadMap; }

	void SetLoadMap(int index);
	void SetSpriteIndex(int index);
private:
	int frameX=0;
	int animDelay = 0;
	int animlimitTime = 0;
	int loadMap = 0;
	bool isActable = false;
	SizeAdjRenderer* renderer = nullptr;
};

class TrapObj : public TriggerObj
{
public:
	using TriggerObj::TriggerObj;
	virtual ~TrapObj() noexcept = default;

	virtual void	 OnTrigger() override;

	virtual void Write(std::ostream& os) const override;
	virtual void Read(std::istream& is) override;

	//Æ÷Å»¿ë
	virtual void		AddMainId() { id++; }
	virtual int			GetMainId() { return id; }

private:
	int id = 0;
};