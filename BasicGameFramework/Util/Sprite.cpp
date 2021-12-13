#include "Sprite.h"

#include <d2d1.h>
#include <wincodec.h>
#include "../Manager/ImageManager.h"
#include "../Manager/GameManager.h"

#include "../Util/AboutTile.h"

#include <iostream>

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

void Sprite::PlayerRender(int posX, int posY, int currFrameX, int currFrameY)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();
		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 48);

		POINTFLOAT* cameraPos = GameManager::GetInstance()->GetCameraPos();


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)posX - 32 * cameraPos->x,
				(float)posY - 32 * cameraPos->y,
				posX + imageOneFrameSize.width - 32 * cameraPos->x,
				posY + imageOneFrameSize.height - 32 * cameraPos->y
			),
			1,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(currFrameX * imageOneFrameSize.width, currFrameY * imageOneFrameSize.height,
				(currFrameX + 1) * imageOneFrameSize.width, (currFrameY + 1) * imageOneFrameSize.height));


		//---------------d2d

	}
}


void Sprite::Render(int posX, int posY, int currFrameX, int currFrameY)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();
		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 32);

		POINTFLOAT* cameraPos = GameManager::GetInstance()->GetCameraPos();


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)posX - 32 * cameraPos->x,
				(float)posY - 32 * cameraPos->y,
				posX + imageOneFrameSize.width - 32 * cameraPos->x,
				posY + imageOneFrameSize.height - 32 * cameraPos->y
			),
			1,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(currFrameX * imageOneFrameSize.width, currFrameY * imageOneFrameSize.height,
				(currFrameX + 1) * imageOneFrameSize.width, (currFrameY + 1) * imageOneFrameSize.height));


		//---------------d2d

	}
}

void Sprite::SlateRender(int posX, int posY,int slatePos)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();

		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)posX,
				(float)posY-slatePos,
				posX + imageSize.width,
				posY + slatePos
			),
			1
			);


		//---------------d2d

	}
}

void Sprite::Render(int posX, int posY, int currFrameX, int currFrameY, int sizeX, int sizeY)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();
		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 32);


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF((float)posX, (float)posY, posX + imageOneFrameSize.width * 3, posY + imageOneFrameSize.height * 3), 1,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(currFrameX * imageOneFrameSize.width, currFrameY * imageOneFrameSize.height,
				(currFrameX + sizeX + 1) * imageOneFrameSize.width, (currFrameY + sizeY + 1) * imageOneFrameSize.height));


		//---------------d2d

	}
}



void Sprite::Render(float startPosX, float startPosY, int posX, int posY, bool isTile)
{
	if (pBitmap)
	{
		
		D2D1_SIZE_F imageSize = pBitmap->GetSize();

		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(32, 32);

		ImageManager::GetInstance()->GetRenderTarget()->DrawRectangle(
			D2D1::RectF(0,
				0,
				1440,
				720
			),
			ImageManager::GetInstance()->GetBrush()
		);
		

		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				startPosX,
				startPosY,
				startPosX + imageSize.width,
				startPosY + imageSize.height),
			1);

		//---------------d2d

	}
}

void Sprite::Render(float startPosX, float startPosY,float opacity, int currFrameX, int currFrameY, int maxFrameX, int maxFrameY)
{
	if (pBitmap)
	{


		
		D2D1_SIZE_F imageSize = pBitmap->GetSize();

		D2D1_SIZE_F imageOneFrameSize = D2D1::SizeF(imageSize.width/ maxFrameX, imageSize.height / maxFrameY);


		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)startPosX,
				(float)startPosY,
				startPosX + imageOneFrameSize.width,
				startPosY + imageOneFrameSize.height),
			opacity,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(
				currFrameX * imageOneFrameSize.width, 
				currFrameY * imageOneFrameSize.height,
				(currFrameX + 1) * imageOneFrameSize.width, 
				(currFrameY + 1) * imageOneFrameSize.height)
		);


		//---------------d2d

	}
}

void Sprite::Render(int posX, int posY, float opacity)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = pBitmap->GetSize();

		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)posX,
				(float)posY,
				posX + imageSize.width,
				posY + imageSize.height
			),
			opacity
		);


		//---------------d2d

	}
}

void Sprite::LoopRender(int posX, int posY, int renderPosX, int renderPosY)
{
	if (pBitmap)
	{

		D2D1_SIZE_F imageSize = { TILE_SIZE * MAP_SIZE_X, TILE_SIZE * MAP_SIZE_Y };



		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)posX,
				(float)posY,
				posX + TILE_SIZE * MAP_SIZE_X ,
				posY + TILE_SIZE * MAP_SIZE_Y
			),
			0.3,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(
				renderPosX,
				renderPosY,
				(renderPosX + pBitmap->GetSize().height/2),
				(renderPosY + pBitmap->GetSize().height/2)
			)
		);
		ImageManager::GetInstance()->GetRenderTarget()->DrawBitmap(pBitmap,
			D2D1::RectF(
				(float)posX,
				(float)posY,
				posX + TILE_SIZE * MAP_SIZE_X,
				posY + TILE_SIZE * MAP_SIZE_Y
			),
			0.3,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(
				renderPosX,
				renderPosX,
				(renderPosX + pBitmap->GetSize().height / 2),
				(renderPosX + pBitmap->GetSize().height / 2)
			)
		);



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
