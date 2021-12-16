#pragma once

#include <string>

#include "Component.h"

class DesiredPosTextComp : public Component
{
public:
	using Component::Component;
	virtual ~DesiredPosTextComp() noexcept = default;

	virtual void	Render(HDC hdc) override;

	void			SetText(const std::wstring& text) noexcept;
	void			SetPos(POINT pos) { this->pos = pos; }

	std::wstring	GetText() const noexcept;
private:
	std::wstring			_text;
	POINT					pos;
};