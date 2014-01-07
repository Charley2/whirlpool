// Whirlpool.cpp: определяет точку входа для консольного приложения.
//
#pragma once
#include <iostream>
#include <fstream>
#include <iostream>

class whirlpool
{
public:

	int *buffer;
	int len;
	
	whirlpool()
	{
		len=1;
		buffer = new int[len];
	}

	whirlpool(int length)
	{
		len = length;
		buffer = new int[len];
	}
	
bool isnull(whirlpool);
whirlpool DecToBin(int);
int BinToDec(whirlpool);
whirlpool CharToBin(char);
whirlpool operator=(whirlpool);
whirlpool operator<< (int);
whirlpool operator>> (int);
bool operator==(whirlpool);
friend whirlpool operator^(whirlpool,whirlpool);
whirlpool operator++();
whirlpool gf4mul(whirlpool, whirlpool);
whirlpool gf8mul(whirlpool, whirlpool);
void createblock(char *, whirlpool[8][8]);
/*
const int (&arr)[2][2] = createblock();
printf ("%d", arr[0][1]);
*/

whirlpool ebox(int);
whirlpool invebox(int);
whirlpool sbox(int);
//whirlpool (&diffuse(whirlpool block[8][8]))[8][8]
void diffuse(whirlpool[8][8], whirlpool[8][8]);
void rotate(whirlpool[8][8]);
void rfun(whirlpool[8][8], whirlpool[8][8]);
//w - изначально пуста в ней результат
void cipher(whirlpool[8][8], whirlpool[8][8], whirlpool[8][8]);
void push(char *, whirlpool[8][8]);
void print(whirlpool[8][8]);
void print(whirlpool);
void printhash(whirlpool[8][8]);
~whirlpool()
{
}
};
