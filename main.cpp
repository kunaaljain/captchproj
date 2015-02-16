/*
	Group -1
	IIT Guwahati
*/

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <iterator>
#include <algorithm>
#include "md5.hpp"
#include "font.hpp"
#include "bitmap_image.hpp"
using namespace std;


class Captcha{
	public:
		
		int letters[26][2];
		bitmap_image image; // (w,h)
		int offset=0,x;
		string saveFile;
		Captcha(string _saveFile);
		string str;
		string hashedString;
		string captchaString;
		string userinp;
		void init();
		void backgroundgen();
		void gen_random(char *s, const int len);
		void captchagen();
		void ran_noiseadd();
		void bitsave();
		void hashString();
		int verifyCaptcha();
		void takeinp();

};

// This is to initialize the array.

void Captcha::init()
{
	int i,count=0,j=0;
	letters[0][0]=0;
	letters[25][1]=1327;
	for(i=0;i<1328;i++)
	{
		if(im[0][i]=='a')
		{
			letters[j++][1]=i-1;
			letters[j][0]=i+1;
		}
	}
}

// This is to set the Background colour as we want. It goes through the 2d array and changes the value of every pixel.

void Captcha::backgroundgen()
{
   image.set_all_channels(248,248,255);
}

// This generates a random 5 letter string consisting of numbers (0-9) alphabets lowercase(a-z) uppercase(A-Z)

void Captcha::gen_random(char *s, const int len) 
{
    static const char alphanum[] =
        //"0123456789"
        //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) 
    {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
    //std::cout << sizeof(alphanum);
}


// This is to change the colour of the appropriate pixles to any colour we want. This creates the text.

void Captcha::captchagen()
{

	init();
	srand (time(NULL));
	char _str[6];
	gen_random(_str,5);
	_str[5] = 0;
	string str1(_str);
	//cout << str1;      //for debugging.
	str.assign(str1);
	const unsigned int dim = 100;
	for(unsigned int k=0; k<str.length(); ++k)
	{
		// Unalign letters
		int offsety=rand()%5;
		int diry=rand()%2;
		if(diry==1) offsety*=-1;
	   	
	   	for (unsigned int y = 0; y < 52; ++y)
		{
	      // Use this to get the captcha in blue.
	      
	      for (x = letters[str[k]-'a'][0]; x < letters[str[k]-'a'][1]; ++x)
	    	{
	    		if(im[y][x]!=' ') image.set_pixel(offset+x-letters[str[k]-'a'][0],min(max(0,(int)y+offsety),51),0,0,205);
	    	}

	    	//srand(time(NULL));
	    	// Just for fun and lines white lines :D :P
	      if(rand()%40 ==1)
	    	{
	    		for (x = letters[str[k]-'a'][0]; x < letters[str[k]-'a'][1]; ++x)
	    		{
	    			if(im[y][x]!=' ') image.set_pixel(offset+x-letters[str[k]-'a'][0],min(max(0,(int)y+offsety),51),248,248,255);
	    		}		
	    	}

	    	// Hollow Effect
		  for (x = letters[str[k]-'a'][0]; x < letters[str[k]-'a'][1]; ++x)
    		{
    			if(im[y][x] =='d' && im[y+1][x+2] =='d') image.set_pixel(offset+x-letters[str[k]-'a'][0],min(max(0,(int)y+offsety),51),248,248,255);
    		}
	    }	    	

	   offset = offset + letters[str[k]-'a'][1] - letters[str[k] - 'a'][0] - 15;
	}
}

// This is to add random pixles on the bitmap.

void Captcha::ran_noiseadd()
{
	// For Pixels randomly.
	for (unsigned int y = 0; y < 52; ++y)
	{
      for (unsigned int x = 0; x < 180; ++x)
      { 
      		if(rand()%5 == 1)  // 5 is the threshold.
        	image.set_pixel(x,y,0,0,205); //(r,g,b)
      }
	}
	// For Lines randomly.
	srand(time(NULL));
	image_drawer draw(image);
	for(x=0;x<20;x++)
	{
   		draw.pen_width(1);
   		//draw.pen_color(rand()%255,rand()%255,rand()%255);
   		draw.pen_color(248,248,255);
   		draw.line_segment(rand()%180,rand()%52,rand()%180,rand()%52);
    }
	srand(time(NULL));
    for(x=0;x<5;x++)
	{
   		draw.pen_width(1);
   		//draw.pen_color(rand()%255,rand()%255,rand()%255);
   		draw.pen_color(0,0,205);
   		draw.line_segment(rand()%180,rand()%52,rand()%180,rand()%52);
    }

}

// This is to save the Bitmap image.

Captcha::Captcha(string _saveFile): image(180,52)
{
	saveFile=_saveFile;
}	

void Captcha::bitsave()
{
	image.save_image(saveFile);
}

void Captcha::hashString(){
	string sample(md5(str));
	//cout<< str;
	//cout << "fuck";
	//cout << "hashedString = " + sample + "str = " + str;
	hashedString.assign(sample);			//assign the hashed string
	str.clear();							// clear the string for safety
}

int Captcha::verifyCaptcha(){			//returns 1 if matched 
	string sample(md5(userinp));					//returns 0 if not matched
	int y = hashedString.compare(sample);
	//cout << userinp;
	//cout << "sample = " + sample + " \n hashedString = " + hashedString; 
	//cout << "y = " + y;
	if(y == 0){
		return 1 ;
	}
	else {
		return 0;
	}
}

void Captcha::takeinp(){
	//string sampleinp;
	cin >> userinp;
}
// This is the main function.

int main()
{
	Captcha cap_1("image.bmp");
	//Calling the background generating function.
	cap_1.backgroundgen();
	//Calling the random noise addition.
	cap_1.ran_noiseadd();
	//Calling the Captcha generation function.
	cap_1.captchagen();
	//This is to save the image.
	cap_1.bitsave();
	cap_1.hashString();
	cap_1.takeinp();
	cout << cap_1.verifyCaptcha();
	//End of the function.
	return 0;
}
