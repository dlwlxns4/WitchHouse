#pragma once

#include "Component.h"
#include <array>

enum class TrapActionState
{
	Null,
	ID0,
	ID1,
	ID2,
	ID3
};

class ITrapActionable;
class TrapAction : public Component
{
public:
	using Component::Component;
	virtual ~TrapAction();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Write(ostream& os) const override;
	void Read(istream& is) const;
	virtual void Read(istream& is) override;
	void SetActionStartegy(TrapActionState action);
private:
	std::array<class ITrapActionable*, 6> actions;
	class ITrapActionable* _actionSterategy = actions[0];
};



class ITrapActionable abstract
{
public:
	ITrapActionable(GameObject* _owner)
		: _obj{ _owner }
	{
	}
	virtual ~ITrapActionable() = default;

	virtual void	DoAction() = 0;

protected:
	GameObject* _obj;
};

class TrapNullAction : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~TrapNullAction() = default;

	void DoAction() override
	{

	}
};


//¿ì·Î ´ÝÈ÷±â
class ActionID0 : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~ActionID0() = default;

	void DoAction() override;
private:
	int moveDelay = 0;
	int cycleCount = 0;
};


//ÁÂ·Î ´ÝÈ÷±â
class ActionID1 : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~ActionID1() = default;

	void DoAction() override;
private:
	int moveDelay = 0;
	int cycleCount = 0;
};

class ActionID2 : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~ActionID2() = default;

	void DoAction() override;
private:
	int animDelay = 0;
	int cycleCount = 0;
};

class ActionID3 : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~ActionID3() = default;

	void DoAction() override;
private:
	int animDelay = 0;
	int cycleCount = 0;
};

class ActionID4 : public ITrapActionable
{
public:
	using		ITrapActionable::ITrapActionable;
	virtual		~ActionID4() = default;

	void DoAction() override;
private:
	int animDelay = 0;
	int cycleCount = 0;
};