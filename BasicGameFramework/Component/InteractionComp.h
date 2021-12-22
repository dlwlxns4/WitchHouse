#pragma once

#include "Component.h"
#include <vector>
#include <string>


class Sprite;
class InteractionComp : public Component
{
public:
	using Component::Component;
	virtual ~InteractionComp() noexcept = default;

	virtual void			Init()override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	
	void					SetSprite(const wchar_t* fileName, const wchar_t* selectPanelFileName);
	void					SetSlatePos(int pos);
	int						GetSlatePos(int pos);

	void					ManageSelectPanel();
	void					ClosePanel();
	void					DoActivateObj(int id);
private:
	Sprite*					sprite = nullptr;
	int						slatePos = 0;
	bool					isOpen = false;
	bool					isClose = false;
	bool					isTalk = false;

	vector<std::wstring>	data = {};
	std::wstring			chatEffect = {};
	std::wstring			talkIndexStr = {};
	int						strIndex = 0;
	int						vecIndex = 0;

	enum class ApprovalState
	{
		Agree=0,
		Disagree=1
	};

	ApprovalState			state = ApprovalState::Agree;
	bool					isShowSelectPanel = false;
	Sprite*					selectPanel = nullptr;
	float					selectPanelOpacity = 1;
	bool					isDecrease = true;

};