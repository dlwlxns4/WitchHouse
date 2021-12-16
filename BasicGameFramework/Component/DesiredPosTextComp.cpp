#include "DesiredPosTextComp.h"

#include "../Object/GameObject.h"

#include "../Manager/ImageManager.h"
#include <d2d1.h>
#include <dwrite.h>

void DesiredPosTextComp::Render(HDC hdc)
{


	D2D1_RECT_F layoutRect = D2D1::RectF(
		pos.x, pos.y, pos.x + 300, pos.y + 100
	);


	IDWriteTextLayout* pTextLayout_;

	int length = _text.size();
	ImageManager::GetInstance()->GetRenderTarget()->DrawTextW(
		_text.c_str(),
		length
		, ImageManager::GetInstance()->GetTextFormat()
		, layoutRect
		, ImageManager::GetInstance()->GetBrushWhite()
	);
}


void DesiredPosTextComp::SetText(const std::wstring& text) noexcept
{
	_text = text;
}

std::wstring DesiredPosTextComp::GetText() const noexcept
{
	return _text;
}
