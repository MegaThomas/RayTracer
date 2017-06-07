#ifndef __BMP_H__
#define __BMP_H__

#include <stdint.h>

class BMP
{
private:
    uint32_t fileSize;
	uint32_t DIBSize = 40;
	uint32_t width;
	uint32_t height;
	uint16_t planes = 1;
	uint16_t bitPerPel = 24;
	uint32_t comp = 0;
	uint32_t size = 0;
	int32_t  XPelPerMeter = 2835;
	int32_t  YPelPerMeter = 2835;
	uint32_t colors = 0;
	uint32_t impColors = 0;

	uint8_t **pelArray[3];
	uint8_t padLen;

public:
    BMP(){};
    BMP(uint32_t width, uint32_t height);
    ~BMP();

    void write(std::ofstream& ofile);
	int setPel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    friend std::ofstream& operator<<(std::ofstream& os, const BMP& bitmap);
};

#endif // __BMP_H__