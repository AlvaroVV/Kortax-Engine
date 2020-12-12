#pragma once

namespace BMP
{

	//////////////////////////////
	///// Bitmap File Header//////
	//////////////////////////////
	//Bitmap Information Header//
	//----Palette Data---------//
	//-------------------------//
	//-------------------------//
	////////////////////////////
	//------------------------//
	//------------------------//
	//------Bitmap Data-------//
	//------------------------//
	//------------------------//
	////////////////////////////

		/* constants for the biCompression field */
	//Avoiding including windows.h. SEEMS NOT BEING WORTH IT.
	#define BI_RGB        0L
	#define BI_RLE8       1L
	#define BI_RLE4       2L
	#define BI_BITFIELDS  3L
	#define BI_JPEG       4L
	#define BI_PNG        5L

	#define BITMAP_ID 0x4D42

	//Trying to avoid including windows.h for WORD 
	//TODO: Crear un types.h urgentemente
	typedef unsigned long       DWORD;
	typedef unsigned short      WORD;
	typedef long				LONG;

	//Problema: Alineamiento de memoria
	//Solucion: Pragma pack(bytes)
	//TIP: Problema de alineamiento en memoria. En lugar de ocupar 14 bytes, ocupa 20. Nos comemos 6 bytes por culpa del alineamiento auto de Word(2 bytes) y Dword(4bytes)
	//El Infoheader comienza en el byte 15, por tanto debemos empaquetar bien este struct. 
	#pragma pack(2)
	struct BITMAPFILEHEADER
	{
		WORD bfType;		//Specifies the file type. BM is 0x4D42
		DWORD bfsize;		//Size in bytes of the bitmap file
		WORD bfReserved1;	//reserved. must be zero
		WORD bfReserved2;	//reserved. must be zero
		DWORD bOffBits;		//specifies the offset, inbytes, from the BITMAPFILEHEADER structure to the bitmap bits.

	};
	#pragma pack()


	struct BITMAPINFOHEADER
	{
		DWORD biSize;	//structure bytes
		LONG biWidth;	//bitmap width
		LONG biHeight;	//bitmap height
		WORD biPlanes;	//color planes, must be 1
		WORD biBitCount;//bits per pixel. 1,4,8,16,32

		DWORD biCompression; //compression type
		DWORD biSizeImage;	//size of image in bytes
		LONG biXPelsPerMeter;//pixels per meter in X
		LONG YPelsPerMeter;	//pixel per meter in Y
		DWORD biClrUsed;	//number of colors used
		DWORD biClrImportant;//number color importante

	};

	unsigned char* LoadBitmapFile(const char* filename, BITMAPINFOHEADER* bitmapInfoHeader);

	int WriteBitmapFile(const char *filename, int width, int height, unsigned char* imageData);

}
