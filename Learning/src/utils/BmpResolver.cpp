#include "BmpResolver.h"
#include <Windows.h>
#include <stdio.h>

unsigned char* BMP::LoadBitmapFile(const char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE				*filePtr;	
	BITMAPFILEHEADER	bitmapFileHeader;
	unsigned char		*bitmapImage;
	int					imageIdx = 0;
	unsigned char		tempRGB;

	fopen_s(&filePtr,filename, "rb");
	if (filePtr == NULL)
		return NULL;

	//read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	
	//move the file pointer to the beginning of the bitmap image data
	fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);

	//allocate enoguh memory for the bitmap data
	
	bitmapImage = new unsigned char [bitmapInfoHeader->biSizeImage];
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	//read the bitmap data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	//swap the R and B values to get RGB since the bitmap color format is BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	fclose(filePtr);
	return bitmapImage;
}

int BMP::WriteBitmapFile(const char *filename, int width, int height, unsigned char* imageData)
{
	FILE				*filePtr;
	BITMAPFILEHEADER	bitmapFileHeader;
	BITMAPINFOHEADER	bitmapInfoHeader;
	int					imageIdx;
	unsigned char		tempRGB;

	fopen_s(&filePtr, filename, "rb");
	if (!filePtr)
		return 0;

	//define bitmap fileheader
	bitmapFileHeader.bfsize = sizeof(BITMAPFILEHEADER);
	bitmapFileHeader.bfType = BITMAP_ID;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	bitmapFileHeader.bOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPFILEHEADER);

	//define the bitmap information header
	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biSizeImage = width * abs(height) * 3;
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.YPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	bitmapInfoHeader.biWidth = width;
	bitmapInfoHeader.biHeight = height;

	for (imageIdx = 0; imageIdx < bitmapInfoHeader.biSizeImage; imageIdx += 3)
	{
		tempRGB = imageData[imageIdx];
		imageData[imageIdx] = imageData[imageIdx + 2];
		imageData[imageIdx + 2] = tempRGB;
	}

	fwrite(&bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), filePtr);

	fwrite(&bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), filePtr);

	fwrite(imageData, 1, bitmapInfoHeader.biSize, filePtr);

	fclose(filePtr);

	return 1;
}


