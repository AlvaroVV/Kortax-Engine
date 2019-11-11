#pragma once

#include <png.h>

namespace PNG
{
	struct pngInfo
	{
		png_byte* data = nullptr;
		png_uint_32 width = 0;
		png_uint_32 height = 0;
		int format = 0;
	};

	

	bool LoadPNG(const char *file, pngInfo& info);
}