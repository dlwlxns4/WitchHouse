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

	virtual void	AddNextMapNum() = 0;
	virtual	int		GetNextMap() = 0;

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

	void		AddNextMapNum() { loadMap++; }
	int			GetNextMap() { return loadMap; }

	void SetLoadMap(int index);
	void SetSpriteIndex(int index);
private:
	int frameX=0;
	int animDelay = 0;
	int loadMap = 3;
	bool isActable = false;
	SizeAdjRenderer* renderer = nullptr;
};