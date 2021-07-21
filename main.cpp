#include <iostream>
#include "sculptor.h"

using namespace std;

int main()
{
Sculptor x(2,3,4);
x.setColor(1,1,1,1);
x.putVoxel(1,1,1);


x.writeOFF("texto.txt");


}
