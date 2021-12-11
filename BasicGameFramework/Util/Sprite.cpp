#include "Sprite.h"

#include <d2d1.h>
#include <wincodec.h>
#include "../Manager/ImageManager.h"


void Sprite::Init(const wchar_t* fileName)
{
	IWICFormatConverter* pConverter = nullptr;
	IWICBitmapDecoder* pImageDecoder = nullptr;
	IWICBitmapFrameDecode* pFrameDecode = nullptr;


	ImageManager::GetInstance()->GetImageingFactory()->CreateDecoderFromFilename(fileName,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&pImageDecoder);

	pImageDecoder->GetFrame(0, &pFrameDecode);

	ImageManager::GetInstance()->GetImageingFactory()->CreateFormatConverter(&pConverter);
	pConverter->Initialize(pFrameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);

	ImageManager::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(pConverter, nullptr, &pBitmap);

	if (pBitmap != nullptr)
	{
		this->maxFrameX = pBitmap->GetSize().width / 32;
		this->maxFrameY = pBitmap->GetSize().height / 32;
	}
	pConverter->Release();
	pImageDecoder->Release();
	pFrameDecode->Release();


}

void Sprite::Render(int posX, int posY, int currFrameX, int currFrameY)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();
		int frameX = 3;
		int frameY = 4;
		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 32);


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF((float)posX, (float)posY, posX + imageOneFrameSize.width, posY + imageOneFrameSize.height), 1,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(currFrameX * imageOneFrameSize.width, currFrameY * imageOneFrameSize.height,
				(currFrameX + 1) * imageOneFrameSize.width, (currFrameY + 1) * imageOneFrameSize.height));


		//---------------d2d

	}
}

void Sprite::Render(int posX, int posY, int currFrameX, int currFrameY, int sizeX, int sizeY)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();
		int frameX = 3;
		int frameY = 4;
		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 32);


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF((float)posX, (float)posY, posX + imageOneFrameSize.width*3, posY + imageOneFrameSize.height*3), 1,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(currFrameX * imageOneFrameSize.width, currFrameY * imageOneFrameSize.height,
				(currFrameX + sizeX+1) * imageOneFrameSize.width, (currFrameY + sizeY+1) * imageOneFrameSize.height));


		//---------------d2d

	}
}



void Sprite::Render(float startPosX, float startPosY, int posX, int posY, bool isTile)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();

		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 32);


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(startPosX, startPosY, startPosX+imageSize.width , startPosY+imageSize.height), 1);

		//---------------d2d

	}
}

void Sprite::Release()
{
	pBitmap->Release();
}

int Sprite::GetWidth()
{
	int width = 0;
	width = pBitmap->GetSize().width;
	return width;
}

int Sprite::GetHeight()
{
	int height = 0;
	height = pBitmap->GetSize().height;
	return height;
}
