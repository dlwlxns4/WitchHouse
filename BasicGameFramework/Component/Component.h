#pragma once

#include "../IBehaviour.h"
#include "../Util/Type.h"
#include <iostream>

using namespace std;

class GameObject;
class Component abstract : IBehaviour
{
public:
	Component(GameObject* owner, INT32 order = 100) noexcept;
	virtual ~Component() noexcept;

	INT32				GetOrder() const noexcept;

	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		Release() override;

	virtual void		Write(std::ostream& os) const;
	virtual void		Read(std::istream& is);

	friend				std::ostream& operator<<(std::ostream& os, const Component& comp);
	friend				std::istream& operator>>(std::istream& is, Component& comp);
	
	 

	bool				IsActive() const noexcept { return _isActive; }
	void				SetActive(bool isActive) { _isActive = isActive; }

protected:
	GameObject*			_owner = nullptr;
	bool				_isActive = true;
private:
	int					_order = 100;
};

