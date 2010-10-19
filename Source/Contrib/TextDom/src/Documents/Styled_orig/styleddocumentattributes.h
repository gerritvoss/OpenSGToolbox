
#ifndef DOCATTR
#define DOCATTR

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


struct color
{
	int r;
	int g;
	int b;

	color(int vr=255,int vg=255,int vb=255)
	{
		r=vr;
		g=vg;
		b=vb;
	}

//	bool operator==(const color& operand);
//	bool operator!=(const color& operand);
};


typedef struct color Color;

/*bool Color::operator==(const Color& operand)
{
	if(r != operand.r)return false;
	if(g != operand.g)return false;
	if(b != operand.b)return false;
	return true;
}

bool Color::operator!=(const Color& operand)
{
	if(r != operand.r)return true;
	if(g != operand.g)return true;
	if(b != operand.b)return true;
	return false;
}*/

struct textWithProps
{
	// the actual text
	std::string text;

	// properties
	unsigned int fontsize;
	bool bold;
	bool italics;
	bool underlined;
	std::string fontface;
	int fontfaceindex;
	Color foreground;
	int foregroundindex;
	Color background;
	int backgroundindex;
	bool ends;	// is true if after this text a new paragraph begins
	bool processed;
	//bool operator ==(textWithProps& operand);

	textWithProps(unsigned int fs=22,bool b=false,bool i=false,bool u=false,std::string fface="Arial",int ffaceindex=0,Color fg=Color(255,255,255),int fgindex=0,Color bg=Color(255,255,255),int bgindex=0,bool e=false,bool p=false)
	{
		fontsize = fs;
		bold = b;
		italics =i;
		underlined = u;
		fontface = fface;
		fontfaceindex=ffaceindex;
		foreground=fg;
		foregroundindex=fgindex;
		background=bg;
		backgroundindex=bgindex;
		ends=e;
		processed=p;
	}
};

typedef struct textWithProps TextWithProps;
/*
bool TextWithProps::operator==(TextWithProps& operand)
{
	if(text != operand.text)return false;
	if(fontsize != operand.fontsize)return false;
	if(bold != operand.bold)return false;
	if(italics != operand.italics)return false;
	if(underlined != operand.underlined)return false;
	if(fontface != operand.fontface)return false;
	if(fontfaceindex != operand.fontfaceindex)return false;
	if(foreground != operand.foreground)return false;
	if(foregroundindex != operand.foregroundindex)return false;
	if(background != operand.background)return false;
	if(backgroundindex != operand.backgroundindex)return false;
	if(ends!= operand.ends)return false;
	return true;
}
*/
#endif