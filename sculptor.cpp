#include "sculptor.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[0][0]= new Voxel[nx*ny*nz];

    for(int i = 1; i<nx; i++){
            v[i] = v[i-1]+ny;
        }

    for(int j = 1; j<nx*ny; j++){

           v[0][j] = v[0][j-1]+nz;
    }

std :: cout<<"criadu"<< std ::endl;




}

Sculptor::~Sculptor()
{
    delete v[0][0];
    delete v[0];
    delete v;
}

void Sculptor::setColor(float r, float g, float b, float a)
{
    this ->r = r;
    this ->g = g;
    this ->b = b;
    this ->a = a;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = 1;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = 0;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
             for(int k=z0; k<=z1; k++){

                    putVoxel(i,j,k);
             }
         }
    }

}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
             for(int k=z0; k<=z1; k++){

                    cutVoxel(i,j,k);
             }
         }
    }
}

void Sculptor::writeOFF(const char *filename)
{

   std :: ofstream arq;

    arq.open(filename);
    if(arq.is_open()){
       std :: cout << "arquivo criado" << std::endl;

       arq <<"OFF" << std::endl;

       arq.close();
    }


}








