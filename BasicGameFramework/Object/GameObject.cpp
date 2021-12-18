#include "../stdafx.h"
#include "../Component/Component.h"
#include "../Scene/Layer.h"

#include "GameObject.h"

#include <iterator>

#include <iostream>

#include "../Manager/CameraManager.h"

#include "../Component/SpriteRenderer.h"
#include "../Component/ParallaxSpriteRenderer.h"

GameObject::GameObject(Scene* scene, Layer* layer, const wstring& tag)
	:
	_scene{ scene },
	_layer{ layer },
	_tag{ tag }
{
	_layer->AddObject(this);
}

GameObject::GameObject(Layer* layer, const wstring& tag)
	:
	_layer{ layer },
	_tag{ tag }
{
	_layer->AddObject(this);
}

GameObject::GameObject(const std::wstring& tag)
	:
	_tag{ tag }
{
}

GameObject::~GameObject() noexcept
{

	Component* pTemp = nullptr;
	for (auto it = _components.begin(); it != _components.end(); )
	{
		pTemp = (*it);
		it = _components.erase(it);

		delete pTemp;
		pTemp = nullptr;
	}


	//for (auto& comp : _components)
	//{
	//	delete comp;
	//	comp = nullptr;
	//}
	_components.clear();
	_layer = nullptr;
	_scene = nullptr;

}

void GameObject::Init()
{
	for (Component* comp : _components)
	{
		comp->Init();
	}
}

void GameObject::Update()
{
	for (int i = 0; i < _components.size(); ++i)
	{
		if (_components[i]->IsActive())
		{
			_components[i]->Update();
		}
	}
}


void GameObject::Render(HDC hdc)
{

	for (Component* comp : _components)
	{
		if (comp->IsActive())
		{
			comp->Render(hdc);
		}
	}
}

void GameObject::Release()
{
	for (Component* comp : _components)
	{
		comp->Release();
	}
}

void GameObject::OnTrigger()
{
}

void GameObject::AddComponent(Component* component)
{
	_components.push_back(component);

	sort(_components.begin(), _components.end(),
		[](const Component* lhs, const Component* rhs)
		{
			return lhs->GetOrder() < rhs->GetOrder();
		});
}

void GameObject::RemoveComponent(Component* component)
{
	remove(_components.begin(), _components.end(), component);
}

POINT GameObject::GetRenderPos() const noexcept
{
	POINT temp = { _size.Width * _pivot.X, _size.Height * _pivot.Y };

	return POINT{ _position.x - temp.x, _position.y - temp.y };
}

void GameObject::SetTag(const wstring& tag) noexcept
{
	_tag = tag;
}

void GameObject::SetPosition(POINT pos) noexcept
{
	_position = pos;
}

void GameObject::SetPosition(LONG x, LONG y) noexcept
{
	_position = POINT{ x, y };
}

wstring GameObject::GetTag() const noexcept
{
	return _tag;
}

POINT GameObject::GetPosition() const noexcept
{
	return _position;
}

void GameObject::SetX(LONG x) noexcept
{
	_position.x = x;
}

LONG GameObject::GetX() const noexcept
{
	return _position.x;
}

void GameObject::SetY(LONG y) noexcept
{
	_position.y = y;
}

void GameObject::SetSize(INT32 width, INT32 height) noexcept
{
	_size = Size{ width, height };
}

void GameObject::SetSize(Size size) noexcept
{
	_size = size;
}

void GameObject::SetPivot(Pivot pivot) noexcept
{
	_pivot = pivot;
}

LONG GameObject::GetY() const noexcept
{
	return _position.y;
}

Size GameObject::GetSize() const noexcept
{
	return _size;
}

INT32 GameObject::GetWidth() const noexcept
{
	return _size.Width;
}

INT32 GameObject::GetHeight() const noexcept
{
	return _size.Height;
}

Pivot GameObject::GetPivot() const noexcept
{
	return _pivot;
}

Scene* GameObject::GetScene() noexcept
{
	return _scene;
}

Layer* GameObject::GetLayer() noexcept
{
	return _layer;
}

void GameObject::Clear()
{
	_components.clear();
}

void GameObject::Write(std::ostream& os) const
{

	os << _position.x << "\t";
	os << _position.y << "\t";
	os << _size.Height << "\t";
	os << _size.Width << "\t";

	os << _components.size() << "\t";
	for (size_t i = 0; i < _components.size(); ++i)
	{
		os << *(_components[i]) << endl;
	}
}

void GameObject::Read(std::istream& is)
{
	is >> _position.x
		>> _position.y
		>> _size.Height
		>> _size.Width;

	int compSize;
	is >> compSize;

	_components.reserve(compSize);
	for (int i = 0; i < compSize; ++i)
	{
		int compType;
		is >> compType;
		switch (compType)
		{
		case 100:
		{
			SpriteRenderer* sr = new SpriteRenderer(this, 1);
			sr->Read(is);
			break;
		}

		case 101:
		{
			ParallaxSpriteRenderer* pr = new ParallaxSpriteRenderer(this, 1);
			pr->Read(is);
			break;
		}
		default:
			break;
		}
	}
	CameraManager::GetInstance()->SetCameraMaxX(_position.x / 32);
	CameraManager::GetInstance()->SetCameraMaxY(_position.y / 32);
	CameraManager::GetInstance()->SetCameraMinX(_position.x / 32);
	CameraManager::GetInstance()->SetCameraMinY(_position.y / 32);
}

vector<Component*>& GameObject::GetComponents() noexcept
{
	return _components;
}

std::ostream& operator<<(std::ostream& os, const GameObject& obj)
{
	obj.Write(os);

	return os;
}

std::istream& operator>>(std::istream& is, GameObject& obj)
{
	obj.Read(is);

	return is;
}
