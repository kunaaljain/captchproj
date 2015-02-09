// add numbers
// radnomize
// scalable
// add nose
// ---  lines,dots,circle use ur imagination
// distortion
// option to hollow font 



#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "font.hpp"
#include "bitmap_image.hpp"

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

int main()
{
	init();

	std::string str="kunal";
	int offset=0,x;
   const unsigned int dim = 100;
   bitmap_image image(180,52); // (w,h)

   for (unsigned int y = 0; y < 52; ++y)
   {
      for (unsigned int x = 0; x < 180; ++x)
      {
        	image.set_pixel(x,y,0,0,100); //(r,g,b)
      }
   }
for(unsigned int k=0; k<str.length(); ++k)
{
	   for (unsigned int y = 0; y < 52; ++y)
	   {
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