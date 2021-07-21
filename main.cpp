#include <iostream>
#include "sculptor.h"

using namespace std;

int main()
{
Sculptor x(30,30,30);
x.setColor(0.3137,0.8705,0.8901,0.5);
x.putBox(0,30,0,30,0,30);



x.writeOFF("cubao.off");


}
