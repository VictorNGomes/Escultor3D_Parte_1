#include <iostream>
#include "sculptor.h"

using namespace std;

int main()
{
Sculptor x(30,30,30);
x.setColor(0.20,0.25,0.86,1);
x.putSphere(12,18,13,10);
//x.putSphere(12,12,12,10);


//x.putBox(0,5,0,5,0,5);


x.writeOFF("bolao.off");


}
