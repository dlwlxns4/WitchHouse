#pragma once
#include "GameObject.h"

class TriggerObj : public GameObject
{
public:
	using GameObject::GameObject;

	virtual ~TriggerObj() noexcept = default;

	virtual void Init() override;
	virtual void Render(HDC hdc)override;

	void addReferceId();
private:
	int referenceId = 0;
};