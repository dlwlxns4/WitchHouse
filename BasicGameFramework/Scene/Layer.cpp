#include "Layer.h"
#include "Scene.h"

#include "../stdafx.h"
#include "../Object/GameObject.h"

#include "../Object/TileObj.h"
#include "../Object/ParallaxObj.h"
#include "../Object/PortalObj.h"
#include "../Object/TwinkleObj.h"
#include "../Object/AkariObj.h"
#include "../Object/QuestObj.h"
#include "../Object/TriggerObj.h"
#include "../Object/TrapActionObj.h"

Layer::Layer(Scene* scene, const std::wstring& tag, INT32 zOrder)
	:
	_scene(scene),
	_tag { tag },
	_zOrder{ zOrder }
{
	_scene->AddLayer(this);
}

Layer::Layer(const std::wstring& tag, INT32 zOrder)
	:
	_tag{ tag },
	_zOrder{ zOrder }
{
}

Layer::~Layer()
{
	for (auto& obj : _objects)
	{
		delete obj;
		obj = nullptr;
	}
	_objects.clear();
}

void Layer::Init()
{
	for (GameObject* _object : _objects)
	{
		_object->Init();
	}
}

void Layer::Update()
{
	for (int i = 0; i < _objects.size(); ++i)
	{
		_objects[i]->Update();
	}

	//for (GameObject* _object : _objects)
	//{
	//	_object->Update();
	//}
}


void Layer::Render(HDC hdc)
{
	for (GameObject* _object : _objects)
	{
		_object->Render(hdc);
	}
}

void Layer::Release()
{
	for (GameObject* _object : _objects)
	{
		_object->Release();
	}
}

const Scene* Layer::GetScene() const noexcept
{
	return _scene;
}

Scene* Layer::GetScene() noexcept
{
	return _scene;
}

std::wstring Layer::GetTag() const noexcept
{
	return _tag;
}

INT32 Layer::GetZOrder() const noexcept
{
	return _zOrder;
}

void Layer::AddObject(GameObject* obj)
{
	_objects.push_back(obj);
}

void Layer::RemoveObject(const wstring& tag)
{
	remove_if(_objects.begin(), _objects.end(),
		[&tag](const GameObject* obj)
		{
			return obj->GetTag() == tag;
		});
}

void Layer::RemoveObject(POINT pos)
{
	for (auto it = _objects.begin(); it!=_objects.end(); ++it)
	{
		if ((*it)->GetPosition().x == pos.x && (*it)->GetPosition().y == pos.y)
		{
			_objects.erase(it);
			break;
		}
	}
}

void Layer::Write(std::ostream& os) const
{
	os << this->_zOrder << "\t";
}

void Layer::Read(std::istream& is)
{
	is >> this->_zOrder;
}

std::ostream& operator<<(std::ostream& os, const Layer& layer)
{
	layer.Write(os);

	for (size_t i = 0; i < layer._objects.size(); ++i)
	{
		os << *(layer._objects[i]) << endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, Layer& layer)
{
	layer.Read(is);

	int objType = 0;
	do
	{
		is >> objType;
		switch (objType)
		{
			case 1:
			{
				TileObj* tile = new TileObj(&layer, L"Tile");
				tile->Read(is);
				break;
			}
			case 2:
			{
				ParallaxObj* parallax = new ParallaxObj(&layer, L"Parallax");
				parallax->Read(is);
				break;
			}
			case 3:
			{
				PortalObj* portal = new PortalObj(&layer, L"Portal");
				portal->Read(is);
				break;
			}
			case 4:
			{
				TwinkleObj* twinkle = new TwinkleObj(&layer, L"Twinkle");
				twinkle->Read(is);

				break;
			}
			case 5:
			{
				AkariObj* akari = new AkariObj(&layer, L"TAkari");
				akari->Read(is);
				break;
			}
			case 6:
			{
				QuestObj* quest = new QuestObj(&layer, L"Quest");
				quest->Read(is);
				break;
			}
			case 7:
			{
				DoorObj* door = new DoorObj(&layer, L"Door");
				door->Read(is);
				break;
			}
			case 8:
			{
				TrapObj* trap = new TrapObj(&layer, L"Trap");
				trap->Read(is);
				break;
			}
			case 9:
			{
				TrapActionObj* trapAction = new TrapActionObj(&layer, L"TrapAction");
				trapAction->Read(is);
				break;
			}
		}
	} while (objType != -1);
	return is;
}
