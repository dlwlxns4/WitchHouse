#include "SampleSprite.h"

#include "../Component/TileSelectComponent.h"
void SampleSprite::Init()
{
	TileSelectComponent* tileSelectComponent = new TileSelectComponent(this,1);
}
