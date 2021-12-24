#include "MovableObj.h"
#include "../Component/Astar.h"
#include "../Component/SizeAdjRenderer.h"

void AstarTeddy::Init()
{
	Astar* astar = new Astar(this, 1);
	astar->Init();

	SizeAdjRenderer* renderer = new SizeAdjRenderer(this, 2);
	renderer->SetSprite(L"Image/Graphics/Obj/AstarTeddy.png");
	renderer->SetMaxFrame(3, 1);
	this->SetPivot(Pivot::Bottom);
	this->SetSize(64, 64);
}
