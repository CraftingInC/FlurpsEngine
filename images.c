
/*
 Currently, this will only load 1 BMP file. To load multiple, turn pixels into an array.
 However, since we only need this for testing to get our program working,
 there is no need for more then 1.
 INFO : I got the info I needed for BMP loading from this youtuber, Nick Walton.
        A huge thanks to him.
		https://www.youtube.com/watch?v=hNi_MEZ8X10
*/

#include "images.h"
#include <stdio.h>
#include <stdlib.h>  // malloc()    free()

unsigned int* pixels;

int loadBMPImage(BMPIMAGE* img, const char* fileName)
{
	unsigned int image_data_address;
	int width, height;
	unsigned int pixelCount;
	unsigned short bitDepth;
	unsigned char byteDepth;

	FILE* file = fopen(fileName, "rb");
	if(file)
	{
		if(fgetc(file) == 'B' && fgetc(file) == 'M')
		{
			fseek(file, 8, SEEK_CUR);
			fread(&image_data_address, 4, 1, file);
			fseek(file, 4, SEEK_CUR);
			fread(&width, 4, 1, file);
			fread(&height, 4, 1, file);
			fseek(file, 2, SEEK_CUR);
			fread(&bitDepth, 2, 1, file);
			if(image_data_address != 138 || bitDepth != 32)
			{
				return 0;
			} else {
				pixelCount = width * height;
				byteDepth = bitDepth / 8;
				pixels = malloc(pixelCount * byteDepth);
				if(pixels)
				{
					fseek(file, image_data_address, SEEK_SET);
					int pixels_read = fread(pixels, byteDepth, pixelCount, file);
					if(pixels_read == pixelCount)
					{
						img->width  = width;
						img->height = height;
						img->pixels = pixels;
					} else {
						free(pixels);
						return 0;
					}
				} else {
					return 0;
				}
			}
		} else {
			return 0;
		}
		fclose(file);
	} else {
		return 0;
	}
	return 1;
}

void cleanBMPImage()
{
	if(pixels){free(pixels);}
}
