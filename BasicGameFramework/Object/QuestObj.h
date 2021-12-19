#pragma once

#include "GameObject.h"

class SpriteRenderer;
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
private:
	SpriteRenderer* renderer = nullptr;
	int				id = 0;
	bool			isActable = true;
};