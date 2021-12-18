#include "../stdafx.h"
#include "../Object/GameObject.h"

#include "Component.h"


Component::Component(GameObject* owner, INT32 order) noexcept
	: _owner{ owner }, _order{ order }
{
	_owner->AddComponent(this);
}

Component::~Component() noexcept
{
	_owner->RemoveComponent(this);
	_owner = nullptr;
}

INT32 Component::GetOrder() const noexcept
{
	return _order;
}

void Component::Init()
{
}

void Component::Update()
{
}

void Component::Render(HDC hdc)
{
}

void Component::Release()
{
}

void Component::Write(ostream& os) const
{
	os << this->_order << "\t";
}

void Component::Read(std::istream& is)
{
	is >> this->_order;
}


std::ostream& operator<<(std::ostream& os, const Component& comp)
{
	comp.Write(os);
	
	return os;
}

std::istream& operator>>(std::istream& is, Component& comp)
{
	comp.Read(is);
	return is;
}
