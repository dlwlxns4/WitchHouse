#include "TitleObj.h"
#include "../Component/FullSizeRenderer.h"
#include "../Component/DesiredPosTextComp.h"
#include "../Component/TitleComp.h"

void TitleObj::Init()
{
	FullSizeRenderer* fullSizeRenderer = new FullSizeRenderer(this, 1);
	fullSizeRenderer->SetSprite(L"Image/UI/title.jpg");

	DesiredPosTextComp* startInit = new DesiredPosTextComp(this, 2);
	startInit->SetText(L"처음부터");
	startInit->SetPos({ 240,300 });

	DesiredPosTextComp* load = new DesiredPosTextComp(this, 3);
	load->SetText(L"계속해서");
	load->SetPos({ 240,330 });

	DesiredPosTextComp* exit = new DesiredPosTextComp(this, 4);
	exit->SetText(L"끝내기");
	exit->SetPos({ 240,360 });

	TitleComp* title = new TitleComp(this, 100);
	title->SetSprite(L"Image/UI/SelectPanel_01.png");
}
