#include "TwinkleObj.h"
#include "../Component/SpriteRenderer.h"

void TwinkleObj::Init()
{
	renderer = new SpriteRenderer(this, 1);
	renderer->SetSprite(L"Image/Graphics/Obj/Twinkle.png");
}

void TwinkleObj::Update()
{
	animDelay++;
	if (animDelay >= 10)
	{
		animDelay = 0;
		frameX++;
		if (frameX >= 4)
		{
			frameX = 0;
		}
		renderer->SetFrameX(frameX);
	}
}

void TwinkleObj::Write(std::ostream& os) const
{
	os << 4 << "\t";
	GameObject::Write(os);
}

void TwinkleObj::Read(std::istream& is)
{
	GameObject::Read(is);

	this->renderer = this->GetComponent<SpriteRenderer>();
	renderer->SetSprite(L"Image/Graphics/Obj/Twinkle.png");
}

