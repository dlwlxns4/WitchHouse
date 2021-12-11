#include "MapFrame.h"

#include "../Component/MapFrameComponent.h"
void MapFrame::Init()
{
	MapFrameComponent* mapFrameComponent = new MapFrameComponent(this, 100);

}
