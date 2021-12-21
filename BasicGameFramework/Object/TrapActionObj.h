#pragma once

#include "GameObject.h"

class SpriteRenderer;
class TrapActionObj : public GameObject
{
public:
	GameObject::GameObject;
	virtual ~TrapActionObj() = default;

	virtual void Init() override;

	void		Write(std::ostream& os) const;
	void		Read(std::istream& is);

	int			GetId() { return id; }
	void		AddMainId() { id++; }
private:
	int			id = 0;
};


