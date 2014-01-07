// Whirlpool.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "whirlpool.h"

using namespace std;

int pow(int p, int n)             // p^n
{
	int res = 1;
	for (int i = 0; i < n; i++)
    res *= p;
	return res;
}

bool whirlpool::isnull(whirlpool a)
	{
	int i;
	for (i=0; i<a.len; i++)
	{
		if (a.buffer[i]&1)
			return false;
	}
	return true;
	}

whirlpool whirlpool::DecToBin(int a)
	{
	int i=0, dec=a, n=0;
	whirlpool bin(8);

		while (dec>=1)
		{
			bin.buffer[i] = dec%2;
			dec = dec >> 1;
			i++;
		}
	bin.len=i;
	if (a==0)
	{
		bin.len=1;
		bin.buffer[0]=0;
	}
	return bin;
	}

int whirlpool::BinToDec(whirlpool bin)
	{
	int i=0, dec=0;
		for (i=0; i<bin.len; i++)
		{
			if (bin.buffer[i] == 1)
			{
				dec = dec + pow(2, i);
			}
		}
	
	return dec;
	}

whirlpool whirlpool::CharToBin(char a)
	{
	int i=0, n=0;
	unsigned int dec=a;
	whirlpool bin(7);

		while (a>=1)
		{
			bin.buffer[i] = a%2;
			a = a >> 1;
			i++;
		}
	len=i;
	
	return bin;
	}

whirlpool whirlpool::operator<< (int k)
	{
		int i=0, j=0, old_len=len;
		int *temp = new int[len];
		
		for (i=0; i<old_len; i++)
			temp[i] = buffer[i];
		//удалить buffer
		buffer = new int[old_len+k];
		len=old_len+k;

		for (i=0; i<k; i++)
		   buffer[i]=0;

		for (i=k; i<len; i++)
		   buffer[i]=temp[i-k];

	return *this;
	}

whirlpool whirlpool::operator>> (int k)
	{
		int i, j;

		for (j=0; j<k; j++)
		{
		    for (i=1; i<len; i++)
			   buffer[i-1]=buffer[i];

			buffer[len-1]=0;
		}
		len=len-k;
		return *this;
	}

bool whirlpool::operator==(whirlpool a)
	{
		int  i=0;
		if (len!=a.len)
			return false;

		for (i=0; i<len; i++)
		{
			if (buffer[i]!=a.buffer[i])
				return false;
		}
	return true;
	}


whirlpool whirlpool::operator=(whirlpool a)
{
    int i=0;
//	if (buffer)
//	delete[] buffer;

    len=a.len;
	buffer = new int[len];
    for (i=0; i<len; i++)
        buffer[i]=a.buffer[i];

	return *this;
}

whirlpool operator^(whirlpool a, whirlpool b)
{
	int i, min_len=0, max_len=0;
	int *buf;
	whirlpool temp,_a,_b;
	_a=a;
	_b=b;

	if (_a.len>_b.len)
	{
		min_len=_b.len;
		max_len=_a.len;

		for (i=0; i<min_len; i++)
			_a.buffer[i]=_a.buffer[i]^_b.buffer[i];

		temp=_a;
	} else
		{
			min_len=_a.len;
			max_len=_b.len;

		for (i=0; i<min_len; i++)
			_b.buffer[i]=_b.buffer[i]^_a.buffer[i];
		
		temp=_b;
		}
	
	i=temp.len-1;
		while(i>0)
		{
			if(temp.buffer[i]==0)
			{
				temp.len--;
			}
			if(temp.buffer[i]==1)
			{
				i=0;
			}
			i--;
		}

	return temp;
}



whirlpool whirlpool::operator++()
	{
		bool flag=true;
		int i=0;
		for (i=0; i<len; i++)
		{
			if (buffer[i]==1) 
			{
				buffer[i]=0;
			}			
			else
				{
					buffer[i]=1;
					flag=false;
					i=len;
				}
		}

	if (flag)
	{
		int *temp = new int[len];
		for (i=0; i<len; i++)
		{
			temp[i]=buffer[i];
		}
		buffer = new int[len+1];
		for (i=0; i<len; i++)
		{
			buffer[i]=temp[i];
		}
		buffer[len]=1;
		len=len+1;
	}

	return *this;
	}

whirlpool whirlpool::gf4mul(whirlpool a, whirlpool b)
	{
	int i=0;
	whirlpool _a,_b;
	_a=a;
	_b=b;
	whirlpool c(_a.len);
	for (i=0; i<c.len; i++)
	c.buffer[i]=0; 
	
	const whirlpool pol2(5);
	pol2.buffer[0]=1, pol2.buffer[1]=1, pol2.buffer[2]=0, pol2.buffer[3]=0, pol2.buffer[4]=1;
	while (isnull(_b) == false)
	{
		if (_b.buffer[0]& 1)		
			c = c^_a;

		_b = _b >> 1;
		_a = _a << 1;

		if (_a.len > 4)
			_a = _a^pol2;//0x13=1'0011=x4+x+1
	}
	return c;
	}

	whirlpool whirlpool::gf8mul(whirlpool a, whirlpool b)
	{
	int i=0;
	whirlpool _a;
	whirlpool _b;
	_a=a;
	_b=b;
	whirlpool c(a.len);
	for (i=0; i<c.len; i++)
	c.buffer[i]=0; 
	
	const whirlpool pol2(9);
	pol2.buffer[0]=1, pol2.buffer[1]=0, pol2.buffer[2]=1, pol2.buffer[3]=1, pol2.buffer[4]=1, pol2.buffer[5]=0, pol2.buffer[6]=0, pol2.buffer[7]=0, pol2.buffer[8]=1;
	
	while (isnull(_b) == false)
	{
		if (_b.buffer[0]& 1)
		{
			c = c^_a;
		}
		
		_b = _b >> 1;
		_a = _a << 1;

		if (_a.len > 8)
		{
			_a = _a^pol2;//0x11d=100011101
		}
	}

	return c;
	}

	void whirlpool::createblock(char *opentext, whirlpool block[8][8])
	{
	int i=0, j=0, k=0, length=strlen(opentext), count=0;
	double blocks_sum=0.0;
	
	blocks_sum=length/64;
	if (blocks_sum>0)
	{
		blocks_sum=(int)blocks_sum;
		blocks_sum++;
	} else
		blocks_sum=(int)blocks_sum;

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			if (k<length)
			{
				block[i][j]=block[i][j].DecToBin(opentext[k]);
			} else
				{
					block[i][j].len=1;
					block[i][j].buffer[0]=0;

					if (k==length)
					{
						block[i][j]=block[i][j].DecToBin(128);
					}
					if (k==63)
					{
						block[i][j]=block[i][j].DecToBin(72);
					}
				}
			k++;
		}
		
	}


	}
/*
const int (&arr)[2][2] = createblock();
printf ("%d", arr[0][1]);
*/

	whirlpool whirlpool::ebox(int n)
	{
	const static whirlpool e_box[16] = {whirlpool(1), whirlpool(4), whirlpool(4), whirlpool(4), whirlpool(4), whirlpool(3), whirlpool(4), whirlpool(2), whirlpool(4), whirlpool(4), whirlpool(3), whirlpool(3), whirlpool(4), whirlpool(2), whirlpool(3), whirlpool(1)};
	e_box[0].buffer[0]=1;
	e_box[1].buffer[0]=1, e_box[1].buffer[1]=1, e_box[1].buffer[2]=0, e_box[1].buffer[3]=1;
	e_box[2].buffer[0]=1, e_box[2].buffer[1]=0, e_box[2].buffer[2]=0, e_box[2].buffer[3]=1;
	e_box[3].buffer[0]=0, e_box[3].buffer[1]=0, e_box[3].buffer[2]=1, e_box[3].buffer[3]=1;
	e_box[4].buffer[0]=1, e_box[4].buffer[1]=0, e_box[4].buffer[2]=1, e_box[4].buffer[3]=1;
	e_box[5].buffer[0]=0, e_box[5].buffer[1]=1, e_box[5].buffer[2]=1;
	e_box[6].buffer[0]=1, e_box[6].buffer[1]=1, e_box[6].buffer[2]=1, e_box[6].buffer[3]=1;
	e_box[7].buffer[0]=1, e_box[7].buffer[1]=1;
	e_box[8].buffer[0]=0, e_box[8].buffer[1]=1, e_box[8].buffer[2]=1, e_box[8].buffer[3]=1;
	e_box[9].buffer[0]=0, e_box[9].buffer[1]=0, e_box[9].buffer[2]=0, e_box[9].buffer[3]=1;
	e_box[10].buffer[0]=1, e_box[10].buffer[1]=1, e_box[10].buffer[2]=1;
	e_box[11].buffer[0]=0, e_box[11].buffer[1]=0, e_box[11].buffer[2]=1;
	e_box[12].buffer[0]=0, e_box[12].buffer[1]=1, e_box[12].buffer[2]=0, e_box[12].buffer[3]=1;
	e_box[13].buffer[0]=0, e_box[13].buffer[1]=1;
	e_box[14].buffer[0]=1, e_box[14].buffer[1]=0, e_box[14].buffer[2]=1;
	e_box[15].buffer[0]=0;
	
	return e_box[n];
	}


	whirlpool whirlpool::invebox(int n)
	{
		const static whirlpool inve_box[16] = {whirlpool(4), whirlpool(1), whirlpool(4), whirlpool(3), whirlpool(4), whirlpool(4), whirlpool(3), whirlpool(4), whirlpool(4), whirlpool(2), whirlpool(4), whirlpool(1), whirlpool(2), whirlpool(3), whirlpool(4), whirlpool(3)};
		inve_box[0].buffer[0]=1, inve_box[0].buffer[1]=1, inve_box[0].buffer[2]=1, inve_box[0].buffer[3]=1;
		inve_box[1].buffer[0]=0;
		inve_box[2].buffer[0]=1, inve_box[2].buffer[1]=0, inve_box[2].buffer[2]=1, inve_box[2].buffer[3]=1;
		inve_box[3].buffer[0]=1, inve_box[3].buffer[1]=1, inve_box[3].buffer[2]=1;
		inve_box[4].buffer[0]=1, inve_box[4].buffer[1]=1, inve_box[4].buffer[2]=0, inve_box[4].buffer[3]=1;
		inve_box[5].buffer[0]=0, inve_box[5].buffer[1]=1, inve_box[5].buffer[2]=1, inve_box[5].buffer[3]=1;
		inve_box[6].buffer[0]=1, inve_box[6].buffer[1]=0, inve_box[6].buffer[2]=1;
		inve_box[7].buffer[0]=0, inve_box[7].buffer[1]=1, inve_box[7].buffer[2]=0, inve_box[7].buffer[3]=1;
		inve_box[8].buffer[0]=1, inve_box[8].buffer[1]=0, inve_box[8].buffer[2]=0, inve_box[8].buffer[3]=1;
		inve_box[9].buffer[0]=0, inve_box[9].buffer[1]=1;
		inve_box[10].buffer[0]=0, inve_box[10].buffer[1]=0, inve_box[10].buffer[2]=1, inve_box[10].buffer[3]=1;
		inve_box[11].buffer[0]=1;
		inve_box[12].buffer[0]=1, inve_box[12].buffer[1]=1;
		inve_box[13].buffer[0]=0, inve_box[13].buffer[1]=0, inve_box[13].buffer[2]=1;
		inve_box[14].buffer[0]=0, inve_box[14].buffer[1]=0, inve_box[14].buffer[2]=0, inve_box[14].buffer[3]=1;
		inve_box[15].buffer[0]=0, inve_box[15].buffer[1]=1, inve_box[15].buffer[2]=1;

	return inve_box[n];
	}

	
	whirlpool whirlpool::sbox(int i)
	{
		int v = i & 15;
		int u = i >> 4;

		const static whirlpool rbox[16] = {whirlpool(3), whirlpool(4), whirlpool(4), whirlpool(4), whirlpool(4), whirlpool(3), whirlpool(4), whirlpool(4), whirlpool(3), whirlpool(2), whirlpool(4), whirlpool(4), whirlpool(2), whirlpool(3), whirlpool(1), whirlpool(1)};

	rbox[0].buffer[0]=1, rbox[0].buffer[1]=1, rbox[0].buffer[2]=1;//7
	rbox[1].buffer[0]=0, rbox[1].buffer[1]=0, rbox[1].buffer[2]=1, rbox[1].buffer[3]=1;//12
	rbox[2].buffer[0]=1, rbox[2].buffer[1]=1, rbox[2].buffer[2]=0, rbox[2].buffer[3]=1;//11
	rbox[3].buffer[0]=1, rbox[3].buffer[1]=0, rbox[3].buffer[2]=1, rbox[3].buffer[3]=1;//13
	rbox[4].buffer[0]=0, rbox[4].buffer[1]=1, rbox[4].buffer[2]=1, rbox[4].buffer[3]=1;//14
	rbox[5].buffer[0]=0, rbox[5].buffer[1]=0, rbox[5].buffer[2]=1;//4
	rbox[6].buffer[0]=1, rbox[6].buffer[1]=0, rbox[6].buffer[2]=0, rbox[6].buffer[3]=1;//9
	rbox[7].buffer[0]=1, rbox[7].buffer[1]=1, rbox[7].buffer[2]=1, rbox[7].buffer[3]=1;//15
	rbox[8].buffer[0]=0, rbox[8].buffer[1]=1, rbox[8].buffer[2]=1;//6
	rbox[9].buffer[0]=1, rbox[9].buffer[1]=1;//3
	rbox[10].buffer[0]=0, rbox[10].buffer[1]=0, rbox[10].buffer[2]=0, rbox[10].buffer[3]=1;//8
	rbox[11].buffer[0]=0, rbox[11].buffer[1]=1, rbox[11].buffer[2]=0, rbox[11].buffer[3]=1;//10
	rbox[12].buffer[0]=0, rbox[12].buffer[1]=1;//2
	rbox[13].buffer[0]=1, rbox[13].buffer[1]=0, rbox[13].buffer[2]=1;//5
	rbox[14].buffer[0]=1;//1
	rbox[15].buffer[0]=0;//0
// r-box [7, 12, 11, 13, 14, 4, 9, 15, 6, 3, 8, 10, 2, 5, 1, 0]


		whirlpool a = rbox[BinToDec(ebox(u)^invebox(v))];
		whirlpool e(8), in(8);
		e = ebox(BinToDec(ebox(u)^a));
		in = invebox(BinToDec(invebox(v)^a));

		return (e << 4)^in;
	}

	//whirlpool (&diffuse(whirlpool block[8][8]))[8][8]
	void whirlpool::diffuse(whirlpool a[8][8], whirlpool b[8][8])
	{
		int n = 8, i=0, j=0, k=0;

		//[1, 1, 4, 1, 8, 5, 2, 9]
		const static whirlpool diffuserow[8] = {whirlpool(1), whirlpool(1), whirlpool(3), whirlpool(1), whirlpool(4), whirlpool(3), whirlpool(2), whirlpool(4)};
		diffuserow[0].buffer[0]=1;
		diffuserow[1].buffer[0]=1;
		diffuserow[2].buffer[0]=0, diffuserow[2].buffer[1]=0, diffuserow[2].buffer[2]=1;
		//100
		diffuserow[3].buffer[0]=1;
		diffuserow[4].buffer[0]=0, diffuserow[4].buffer[1]=0, diffuserow[4].buffer[2]=0, diffuserow[4].buffer[3]=1;
		diffuserow[5].buffer[0]=1, diffuserow[5].buffer[1]=0, diffuserow[5].buffer[2]=1;
		diffuserow[6].buffer[0]=0, diffuserow[6].buffer[1]=1;
		diffuserow[7].buffer[0]=1, diffuserow[7].buffer[1]=0, diffuserow[7].buffer[2]=0, diffuserow[7].buffer[3]=1;

		for (i=0; i<8; i++)
		{
			for (j=0; j<8; j++)
			{
				b[i][j].buffer[0]=0;
			}
		}

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (k = 0; k < n; k++)
				{
					b[i][j] = b[i][j]^gf8mul(a[i][k], diffuserow[(j - k + n) % n]);
				}
			}
		}

	}

void whirlpool::rotate(whirlpool a[8][8])
{
	int i=0, j=0, k=0, index=0;
	whirlpool buffer8(8);

for (k=0; k<8; k++)
{	
	index=0;
while(index<k)
{
//циклический сдвиг вниз

for (i=0; i<a[7][k].len; i++)
	buffer8.buffer[i]=a[7][k].buffer[i];

buffer8.len=a[7][k].len;	

	for (i=7; i>0; i--)
	{
		//delete []a[i][k].buffer;
		a[i][k].len=a[i-1][k].len;
		a[i][k].buffer = new int[a[i][k].len];
		for (j=0; j<a[i][k].len; j++)
			a[i][k].buffer[j]=a[i-1][k].buffer[j];
	}

a[0][k].len=buffer8.len;
for (i=0; i<a[0][k].len; i++)
	a[0][k].buffer[i]=buffer8.buffer[i];

index++;
}
}

}

void whirlpool::rfun(whirlpool k[8][8], whirlpool a[8][8])
{
	int i=0, j=0, n=0;
	whirlpool b[8][8]; 

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			b[i][j].buffer[0]=0;
		}
	}

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			a[i][j]=sbox(BinToDec(a[i][j]));
		}
	}
	rotate(a);	
	diffuse(a, b);

	
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			a[i][j]=b[i][j]^k[i][j];
		}
	}
	
}

//w - изначально пуста в ней результат
void whirlpool::cipher(whirlpool key[8][8], whirlpool text[8][8], whirlpool w[8][8])
{
	int i=0, j=0, r=0;
	whirlpool rcon[8][8]; 
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			rcon[i][j].buffer[0]=0;
		}
	}
	
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			w[i][j]=key[i][j]^text[i][j];
		}
	}
		
	for (r = 1; r <= 10; r++)
	{
		for (i = 0; i < 8; i++)
			rcon[0][i] = rcon[0][i].sbox(8*(r - 1) + i);
		
	
		rcon[0][0].rfun(rcon, key);
		w[0][0].rfun(key, w);		
	}
	

}

void whirlpool::push(char *text, whirlpool h[8][8])
{	
	int i=0, j=0;	
	
	whirlpool m[8][8];
	whirlpool c[8][8];
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h[i][j].buffer[0]=0;
		}
	}

	createblock(text, m); // преобразовать массив в матрицу 8×8
	cipher(h, m, c);
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h[i][j] = h[i][j]^c[i][j]^m[i][j];
		}
	}
	
}

void whirlpool::print(whirlpool a)
{
	int i=0;
	for (i=0; i<a.len; i++)
	{
		printf("%d", a.buffer[i]);
	}
}

void whirlpool::print(whirlpool a[8][8])
{
	int i=0, j=0, l=0;
	for(i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			for(l=0; l<a[i][j].len; l++)
			{
				printf("%d", a[i][j].buffer[l]);
			}
			printf(" ");
		}
		printf("\n");
	}
}

void whirlpool::printhash(whirlpool h[8][8])
{
	int i=0, j=0, dec=0;
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			dec=BinToDec(h[i][j]);
			printf("%X", dec);
		}
	}
}
