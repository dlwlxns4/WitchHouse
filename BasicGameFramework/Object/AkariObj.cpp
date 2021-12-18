#include "AkariObj.h"
#include "../Component/SizeAdjRenderer.h"

void AkariObj::Init()
{
	renderer = new SizeAdjRenderer(this, 1);
	renderer->SetSprite(L"Image/Graphics/Obj/Akari.png");
	renderer->SetMaxFrame(4, 1);
}

void AkariObj::Update()
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

void AkariObj::Write(std::ostream& os) const
{
	os << 5 << "\t";
	GameObject::Write(os);
}

void AkariObj::Read(std::istream& is)
{
	GameObject::Read(is);

	this->GetComponent<SizeAdjRenderer>()->SetSprite(L"Image/Graphics/Obj/Akari.png");
	this->renderer = this->GetComponent<SizeAdjRenderer>();
}
