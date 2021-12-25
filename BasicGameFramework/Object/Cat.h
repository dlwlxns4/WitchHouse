#pragma once

#include "GameObject.h"

class Cat : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~Cat() = default;

	virtual void Init() override;
	virtual void Render(HDC hdc) override;

	void SetId(int id) { this->id=id; }

	virtual void	Write(std::ostream& os) const override;
	virtual void	Read(std::istream& is) override;
private:
	int id = 0;
};