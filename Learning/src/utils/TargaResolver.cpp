#include "TargaResolver.h"
#include <stdio.h>

int TGA::LoadTGAFile(const char *fileName, TGAFILE *tgaFile)
{
	FILE			*filePtr;
	unsigned char	ucharBad;	//garbage unsigned data
	short int		sintBad;	//garbage unsigned data
	long			imageSize;
	int				colorMode;
	long			imageIdx;
	unsigned char	colorSwap;

	//Open the TGA File
	fopen_s(&filePtr, fileName, "rb");
	if (!filePtr)
		return 0;

	//read first two bytes of data we don't need
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	//read the image type
	fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

	//for our purposes, the image type should be either a 2 or a 3
	if ((tgaFile->imageTypeCode != 2) && (tgaFile->imageTypeCode != 3))
	{
		fclose(filePtr);
		return 0;
	}

	//read 13 bytes of data we dont need
	//TODO: Optimizar esta basura
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	//read the image dimensions
	fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
	fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

	//read image bit depth
	fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

	//read 1 byte data we dont need
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	//colorMode ->3 = RGB, 4 = RGBA
	colorMode = tgaFile->bitCount / 8;
	imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

	//allocate memory for image data
	tgaFile->imageData = new unsigned char[imageSize];


	//read imagedata
	fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

	//change BGR to RGB so Opengl can read the image data
	for (imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile->imageData[imageIdx];
		tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
		tgaFile->imageData[imageIdx + 2] = colorSwap;
	}

	fclose(filePtr);

	return 1;
}
