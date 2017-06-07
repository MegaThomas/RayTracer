#include <iostream>
#include <fstream>
#include "typeDef.h"
#include "bmp.h"
#include "vec3.h"

int main(int argc, char const *argv[])
{

    BMP bitmap(200, 100);
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << ny << "\n255\n";
    Vec3 col(1);
    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; ++i)
        {
            col.set(float(i) / float(nx), float(j) / float(ny), 0.2);
            bitmap.setPel(i, j, int(255.99*col[0]), int(255.99*col[1]), int(255.99*col[2]));
        }
    }
    std::ofstream ofile("1.bmp", std::ios::out | std::ios::binary);
    bitmap.write(ofile);
    ofile.close();

    return 0;
}