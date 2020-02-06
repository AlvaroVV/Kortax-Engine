#include "PngResolver.h"

//#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>



bool PNG::LoadPNG(const char *file, PNG::pngInfo& info)
{
	FILE *f;
	int is_png, bit_depth, color_type, row_bytes;
	png_infop info_ptr, end_info;
	png_uint_32 t_width, t_height;
	png_byte header[8];
	png_bytepp row_pointers;
	png_structp png_ptr;


	fopen_s(&f, file, "rb");

	if (f == NULL) {
		return false;
	}

	//Lectura de la signatura de 8 bytes
	fread(header, 1, 8, f);
	is_png = !png_sig_cmp(header, 0, 8);
	if (!is_png) {
		fclose(f);
		return false;
	}

	//Crear read struct
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
		NULL, NULL);
	if (!png_ptr) {
		fclose(f);
		return false;
	}

	//Crear info struct
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL,
			(png_infopp)NULL);
		fclose(f);
		return false;
	}
	end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL,
			(png_infopp)NULL);
		fclose(f);
		return false;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(f);
		return false;
	}
	//Inicializamos input/output function
	png_init_io(png_ptr, f);
	//Ya leimos signatura
	png_set_sig_bytes(png_ptr, 8);

	//Leemos la información del png file
	png_read_info(png_ptr, info_ptr);
	//Chunk de información
	png_get_IHDR(png_ptr, info_ptr, &t_width, &t_height, &bit_depth,
		&color_type, NULL, NULL, NULL);
	info.width = t_width;
	info.height = t_height;
	//Actualiza info_ptr para reflejar cualquier transformación.
	png_read_update_info(png_ptr, info_ptr);
	//número de bytes por fila

	row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	//Espacio en image_data para almacenar los bytes de la imagen
	info.data = (png_bytep)malloc(row_bytes * t_height * sizeof(png_byte));
	if (!info.data) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(f);
		return false;
	}

	//Almacenamos espacio igual al número de filas por el espacio de cada fila (punteros)
	row_pointers = (png_bytepp)malloc(t_height * sizeof(png_bytep));
	if (!row_pointers) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(info.data);
		fclose(f);
		return false;
	}
	//OpenGL lee de abajo arriba y de izquierda a derecha.
	//RowPointers pasa almacena las direcciones de image_data y las rellena con el png_read_image por tanto rellena image_data de forma ordenada.
	for (int i = 0; i < t_height; ++i) {
		row_pointers[t_height - 1 - i] = info.data + i * row_bytes;
	}
	//Leemos la imagen y almacenamos los datos.
	png_read_image(png_ptr, row_pointers);
	info.format = png_get_color_type(png_ptr, info_ptr);
	
	//Liberamos espacio
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	free(row_pointers);
	fclose(f);
	return true;
}
