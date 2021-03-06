#pragma once

#include <string>
#include <vector>

#include "../IBehaviour.h"

class Layer;

class Scene abstract : IBehaviour
{
public:
	Scene();
	virtual ~Scene() noexcept;

	virtual void		Init() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		Release() override;

	void				AddLayer(Layer* layer);
	void				RemoveLayer(const std::wstring& tag);
	Layer*				FindLayer(const std::wstring& tag);

	std::vector<Layer*>* GetLayer() { return &_layers; }
private:
	std::vector<Layer*>	_layers;
};