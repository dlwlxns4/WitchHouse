#pragma once

#include "GameObject.h"
#include <array>
#include "../Component/SpriteRenderer.h"

enum class QuestObjStrategy
{
	Null,
	SetFrameAnim
};

class IQuestActionable;
class QuestObj : public GameObject
{
public:
	GameObject::GameObject;
	virtual ~QuestObj() = default;

	virtual void	Init();
	void			SetSprite(int spriteIndex, int frameX, int frameY);
	void			SetIsActable(bool isActable);
	void			AddId();
	int				GetId();
	
	virtual	void	Update() override;
	virtual void	Render(HDC hdc) override;

	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;

	void SetActionStrategy(QuestObjStrategy state);

	IQuestActionable* _actionStrategy = nullptr;
	std::array<IQuestActionable*, 2> _actions;
private:
	SpriteRenderer* renderer = nullptr;
	int				id = 0;
	bool			isActable = true;
};

class IQuestActionable abstract
{
public:
	IQuestActionable(GameObject* owner)
		:_owner{ owner }
	{}
	~IQuestActionable() = default;

	virtual void DoUpdate() = 0;

protected:
	GameObject* _owner;
};

class NullQuestAction : public IQuestActionable
{
public:
	IQuestActionable::IQuestActionable;
	virtual ~NullQuestAction() = default;

	virtual void DoUpdate() override
	{

	}
};

class SetFrameAction : public IQuestActionable
{
public:
	IQuestActionable::IQuestActionable;
	virtual ~SetFrameAction() = default;

	virtual void DoUpdate() override;
private:
	int animDelay = 0;
};