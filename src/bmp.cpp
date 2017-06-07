#include <fstream>
#include <iostream>
#include "bmp.h"

BMP::BMP(uint32_t width, uint32_t height) :
width(width), height(height)
{
	uint32_t stripe = uint32_t((bitPerPel * width + 31) / 32) * 4;
	padLen = stripe - width * 3;
	fileSize = 54 + stripe * height;
	for (uint32_t j = 0; j < 3; j++)
	{
		pelArray[j] = new uint8_t*[height];
		for (uint32_t i = 0; i < height; i++)
		{
			pelArray[j][i] = new uint8_t[width];
		}
	}
}

BMP::~BMP()
{
	for (uint32_t j = 0; j < 3; j++)
	{
		for (uint32_t i = 0; i < height; i++)
		{
			delete[] pelArray[j][i];
		}
		delete[] pelArray[j];
	}
}

void BMP::write(std::ofstream& ofile)
{
    ofile.write("BM", 2);
    ofile.write(reinterpret_cast<char*>(&fileSize), 4);
    ofile.write("\x00\x00\x00\x00", 4);
	ofile.write("\x36", 4);

	ofile.write(reinterpret_cast<char*>(&DIBSize), 4);
	ofile.write(reinterpret_cast<char*>(&width), 4);
	ofile.write(reinterpret_cast<char*>(&height), 4);
	ofile.write(reinterpret_cast<char*>(&planes), 2);
	ofile.write(reinterpret_cast<char*>(&bitPerPel), 2);
	ofile.write(reinterpret_cast<char*>(&comp), 4);
	ofile.write(reinterpret_cast<char*>(&size), 4);
	ofile.write(reinterpret_cast<char*>(&XPelPerMeter), 4);
	ofile.write(reinterpret_cast<char*>(&YPelPerMeter), 4);
	ofile.write(reinterpret_cast<char*>(&colors), 4);
	ofile.write(reinterpret_cast<char*>(&impColors), 4);

	for (uint32_t j = height - 1; j >= 0; j--)
	{
		for (uint32_t i = 0; i < width; i++)
		{
			ofile.write(reinterpret_cast<char*>(&pelArray[2][j][i]), 1);
			ofile.write(reinterpret_cast<char*>(&pelArray[1][j][i]), 1);
			ofile.write(reinterpret_cast<char*>(&pelArray[0][j][i]), 1);
		}
		ofile.write("\x00", padLen);
	}
}

std::ofstream& operator<<(std::ofstream& os, const BMP& bitmap)
{
    os << "BM" << uint16_t(bitmap.fileSize) << "0000";
    return os;
}

int BMP::setPel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		pelArray[0][height - 1 - y][x] = r;
		pelArray[1][height - 1 - y][x] = g;
		pelArray[2][height - 1 - y][x] = b;
		return 0;
	}
	else
	{
		return 1;
	}
}