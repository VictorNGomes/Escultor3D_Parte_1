#include "sculptor.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>

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
    for(int i=x0; i<x1; i++){
        for(int j=y0; j<y1; j++){
             for(int k=z0; k<z1; k++){

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

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{

    for(int i=0; i<=nx; i++){
        for(int j=0; j<=ny; j++){
             for(int k=0; k<=nz; k++){
                    //double cord = ( pow(i-xcenter,2) + pow(j-ycenter,2) + pow(k-zcenter,2) );
                    if( ( pow(i-xcenter,2) + pow(j-ycenter,2) + pow(k-zcenter,2) ) < pow(radius,2) ){
                        putVoxel(i,j,k);
                    }

            }
        }
    }




}




void Sculptor::writeOFF(const char *filename)
{

   std :: ofstream arq;
   fixed(arq);
    arq.open(filename);
    if(arq.is_open()){
       std :: cout << "arquivo criado" << std::endl;

       arq <<"OFF" << std::endl;

       int ve =0, s = 0;
       for(int i =0; i<nx;i++){
           for(int j=0; j<ny; j++){
               for(int k=0; k<nz; k++){
                   if(v[i][j][k].isOn == 1){
                    ve+=8;
                    s+=6;

                   }
               }
           }

       }

       arq << ve <<" "<< s <<" " << 0 << std::endl;

       for(int i =0; i<nx;i++){
           for(int j=0; j<ny; j++){
               for(int k=0; k<nz; k++){
                   if(v[i][j][k].isOn == 1){
                       arq << i-0.5 <<" "<< j+0.5 <<" "<< k-0.5 << std::endl; //p0
                       arq << i-0.5 <<" "<< j-0.5 <<" "<< k-0.5 << std::endl; //p1
                       arq << i+0.5 <<" "<< j-0.5 <<" "<< k-0.5 << std::endl; //p2
                       arq << i+0.5 <<" "<< j+0.5 <<" "<< k-0.5 << std::endl; //p3
                       arq << i-0.5 <<" "<< j+0.5 <<" "<< k+0.5 << std::endl; //p4
                       arq << i-0.5 <<" "<< j-0.5 <<" "<< k+0.5 << std::endl; //p5
                       arq << i+0.5 <<" "<< j-0.5 <<" "<< k+0.5 << std::endl; //p6
                       arq << i+0.5 <<" "<< j+0.5 <<" "<< k+0.5 << std::endl; //p7


                   }
               }
           }

       }
       int count = 0;

       for(int i =0; i<nx;i++){
           for(int j=0; j<ny; j++){
               for(int k=0; k<nz; k++){
                   if(v[i][j][k].isOn == 1){
                       arq << 4 <<" "<< 0+count <<" "<< 3+count <<" "<< 2+count <<" "<< 1 + count<<" "; // lados
                       arq << v[i][j][k].r << " "<< v[i][j][k].g << " "<< v[i][j][k].b << " "<< v[i][j][k].a << std::endl;

                       arq << 4 <<" "<< 4+count <<" "<< 5+count <<" "<< 6+count <<" "<< 7 + count<<" "; // lados
                       arq << v[i][j][k].r << " "<< v[i][j][k].g <<" "<< v[i][j][k].b << " "<< v[i][j][k].a << std::endl;

                       arq << 4 <<" "<< 0+count <<" "<< 1+count <<" "<< 5+count <<" "<< 4 + count<<" "; // lados
                       arq << v[i][j][k].r << " "<< v[i][j][k].g <<" "<< v[i][j][k].b << " "<< v[i][j][k].a << std::endl;

                       arq << 4 <<" "<< 0+count <<" "<< 4+count <<" "<< 7+count <<" "<< 3 + count<<" "; // lados
                       arq << v[i][j][k].r << " "<< v[i][j][k].g <<" "<< v[i][j][j].b << " "<< v[i][j][k].a << std::endl;

                       arq << 4 <<" "<< 3+count <<" "<< 7+count << " "<< 6+count <<" "<< 2 + count<<" "; // lados
                       arq << v[i][j][k].r << " "<< v[i][j][k].g <<" "<< v[i][j][k].b << " "<< v[i][j][k].a << std::endl;

                       arq << 4 <<" "<< 1+count <<" "<< 2+count <<" "<< 6+count <<" "<< 5 + count <<" "; // lados
                       arq << v[i][j][k].r << " "<< v[i][j][k].g << " "<< v[i][j][k].b << " "<< v[i][j][k].a <<std::endl;

                       count+=8;


                   }
               }
           }

       }





       arq.close();
    }


}








