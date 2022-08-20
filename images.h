#ifndef _IMAGES_H_
#define _IMAGES_H_

typedef struct {
	int width, height;
	unsigned int *pixels;
} BMPIMAGE;

int loadBMPImage(BMPIMAGE* img, const char* fileName);
void cleanBMPImage();

#endif // _IMAGES_H_
