#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
using namespace std;

class RGBAPixel
{
public:
	RGBAPixel();
	RGBAPixel(uint8_t r,uint8_t g, uint8_t b);
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

};

#endif//RGBAPIXEL_H
