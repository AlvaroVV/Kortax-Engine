#pragma once

namespace TGA
{
	struct TARGAFILEHEADER
	{
		unsigned char imageIDLength;	//number of characters in identification field; 0 denotes no identificatio field

		unsigned char colorMapType;		//type of color map: always 0
		unsigned char imageTypeCode;	//uncompressed RGB is 2
										//uncompressed grayscale is 3
		short int colorMapOrigin;		//origin of color map (lo-hi); always 0

		short int colorMapLength;
		short int colorMapEntrySize;
		short int imageXOrigin;

		short int imageYOrigin;

		short int imageWidth;
		short int imageHeight;
		unsigned char bitCount;			//number of bits: 16, 24, 32
		unsigned char imageDescriptor;	//24 bit = 0x00; 32-bit = 0x08
	};

	struct TGAFILE
	{
		unsigned char	imageTypeCode;
		short int		imageWidth;
		short int		imageHeight;
		unsigned char	bitCount;
		unsigned char	*imageData;
	};

	int LoadTGAFile(const char *fileName, TGAFILE *tgaFile);
}