// add numbers
// radnomize
// scalable
// add nose
// ---  lines,dots,circle use ur imagination
// distortion
// option to hollow font 



#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <iterator>
#include <algorithm>
#include "font.hpp"
#include "bitmap_image.hpp"

using namespace std;

int letters[26][2];

void init()
{

int i,count=0,j=0;
letters[0][0]=0;
letters[25][1]=1327;
for(i=0;i<1328;i++)
{
	if(im[0][i]=='a'){
		letters[j++][1]=i-1;
		letters[j][0]=i+1;
	}
}
}
void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int main()
{
	//init();	
	srand (time(NULL));
	char _str[6];
	gen_random(_str,5);
	_str[5] = 0;
	string str(_str,5);
	cout << str;


	int offset=0,x;
	const unsigned int dim = 100;
	bitmap_image image(180,52); // (w,h)

	for (unsigned int y = 0; y < 52; ++y)	{
		for (unsigned int x = 0; x < 180; ++x)	{
		image.set_pixel(x,y,0,0,100); //(r,g,b)
		}
	}
	for(unsigned int k=0; k<str.length(); ++k){
		for (unsigned int y = 0; y < 52; ++y)	{
			for (x = letters[str[k]-'a'][0]; x < letters[str[k]-'a'][1]; ++x)
			{
	if(im[y][x]!=' ') image.set_pixel(offset+x-letters[str[k]-'a'][0],y,0,100,0);
		}
	}
	offset=offset+letters[str[k]-'a'][1]-letters[str[k]-'a'][0]-15;
	}

    image.save_image("myimg.bmp");

  return 0;
}