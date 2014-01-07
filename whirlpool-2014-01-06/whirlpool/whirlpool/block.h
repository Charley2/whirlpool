#pragma once
#include "whirlpool.h"

class block:public whirlpool
{
public:
	whirlpool pool[8][8];
	block()
	{
		int i=0,j=0;
		for (i=0; i<8; i++)
		{
			for (j=0; j<8; j++)
			{
				pool[i][j].buffer[0]=0;
			}
		}
	}

	whirlpool get_diffuserow(int i);

	//whirlpool (&diffuse(whirlpool block[8][8]))[8][8]
	block diffuse(block a);
	void rotate(block a);
	block rfun(block k, block a);
	block cipher(block key, block text);
	void pushsimple(char *text, block h);
	block createblock(char *opentext);
	void pushblocks(char *opentext);
	void print(block a);
	void printhash(block h);
	block operator=(block a)
	{
    int i=0, j=0;
	
    for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			pool[i][j]=a.pool[i][j];
		}
	}

	return *this;
	}

};
