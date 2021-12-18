#pragma once

#include "../Component.h"

class PlayerAction : public Component
{
public:
	using Component::Component;
	virtual ~PlayerAction() noexcept = default;

	virtual void	Update() override;
	void DoChatting(int chatId, int itemid);
	void DoChatting(int id);
private:
	
};