#include "my_lib.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
texte();
char x=0;
cin>>x;

switch(x)    
{

case '1':
contour();
break;

case '2':
seuillage();
break;

case '3':
blacknwhite();
break;

default :
cout << "Select Filtre";
cin >> x;
break;

}
}
