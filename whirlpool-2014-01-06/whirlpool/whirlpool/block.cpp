#include "stdafx.h"
#include "block.h"

whirlpool block::get_diffuserow(int i)
	{
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
	
		return diffuserow[i];
	}

block block::diffuse(block a)
	{
		int n = 8, i=0, j=0, k=0;
		block b;
		for (i=0; i<8; i++)
		{
			for (j=0; j<8; j++)
			{
				b.pool[i][j].buffer[0]=0;
			}
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (k = 0; k < n; k++)
				{
					b.pool[i][j] = b.pool[i][j]^gf8mul(a.pool[i][k], get_diffuserow((j - k + n) % n));
				}
			}
		}
	return b;
	}

void block::rotate(block a)
{
	int i=0, j=0, k=0, index=0;
	whirlpool buffer8(8);

for (k=0; k<8; k++)
{	
	index=0;
while(index<k)
{
//циклический сдвиг вниз

for (i=0; i<a.pool[7][k].len; i++)
	buffer8.buffer[i]=a.pool[7][k].buffer[i];

buffer8.len=a.pool[7][k].len;	

	for (i=7; i>0; i--)
	{
		//delete []a[i][k].buffer;
		a.pool[i][k].len=a.pool[i-1][k].len;
		a.pool[i][k].buffer = new int[a.pool[i][k].len];
		for (j=0; j<a.pool[i][k].len; j++)
			a.pool[i][k].buffer[j]=a.pool[i-1][k].buffer[j];
	}

	a.pool[0][k].len=buffer8.len;
	for (i=0; i<a.pool[0][k].len; i++)
		a.pool[0][k].buffer[i]=buffer8.buffer[i];

index++;
}
}

}


block block::rfun(block k, block a)
{
	int i=0, j=0;
	
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
//			a.pool[i][j]=sbox(BinToDec(a.pool[i][j]));
		}
	}

	rotate(a);
	a=diffuse(a);

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			a.pool[i][j]=a.pool[i][j]^k.pool[i][j];
		}
	}
	return a;
}

block block::cipher(block key, block text)
{
	int i=0, j=0, r=0;
	block w;
	block rcon; 
	
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			w.pool[i][j]=key.pool[i][j]^text.pool[i][j];
		}
	}
		
	for (r = 1; r <= 10; r++)
	{
		for (i = 0; i < 8; i++)
			rcon.pool[0][i] = rcon.pool[0][i].sbox(8*(r - 1) + i);
		
	
		key = rfun(rcon, key);
		w = rfun(key,w);		
	}
	
return w;
}

void block::pushsimple(char *text, block h)
{	
	int i=0, j=0;	
	
	block m;
	block c;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h.pool[i][j].buffer[0]=0;
		}
	}

	m=createblock(text); // преобразовать массив в матрицу 8×8

	c=cipher(h, m);
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h.pool[i][j] = h.pool[i][j]^c.pool[i][j]^m.pool[i][j];
		}
	}
	
}

	block block::createblock(char *opentext)
	{
	int i=0, j=0, k=0, length=strlen(opentext), count=0;
	double blocks_sum=0.0;
	block b;

	blocks_sum=length/64.0;
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
					b.pool[i][j]=b.pool[i][j].DecToBin(opentext[k]);
				} else
					{
						b.pool[i][j].len=1;
						b.pool[i][j].buffer[0]=0;

						if (k==length)
						{
							b.pool[i][j]=b.pool[i][j].DecToBin(128);
						}
						if (k==63)
						{
							b.pool[i][j]=b.pool[i][j].DecToBin(72);
						}
					}
				k++;
			}
		}	
return b;
}


	void block::pushblocks(char *opentext)
	{
	int i=0, j=0, k=0, length=strlen(opentext), count=0;
	double blocks_sum=0.0;

	block b[10];
	block m,c,h;
	int temp1[8] = {0,1,1,0,1,1,0,0};
	int temp2[8] = {0,1,0,1,1,0,1,0};
	block ipad, opad;
	block s, s0, k0, out;
	//ipad01101100
	//opad01011010

	blocks_sum=length/64.0;
	if (blocks_sum>0)
	{
		blocks_sum=(int)blocks_sum;
		blocks_sum++;
	} else
		blocks_sum=(int)blocks_sum;

	for (count=0; count<blocks_sum; count++)
	{
		for (i=0; i<8; i++)
		{
			for (j=0; j<8; j++)
			{
				if (k<length)
				{
					b[count].pool[i][j]=b[count].pool[i][j].DecToBin(opentext[k]);
				} else
					{
						b[count].pool[i][j].len=1;
						b[count].pool[i][j].buffer[0]=0;

						if (k==length)
						{
							b[count].pool[i][j]=b[count].pool[i][j].DecToBin(128);
						}
						if (k==63)
						{
							b[count].pool[i][j]=b[count].pool[i][j].DecToBin(72);
						}
					}
				k++;
			}
		}

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			ipad.pool[i][j].buffer[0]=temp1[j];
		}
	}

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			opad.pool[i][j].buffer[0]=temp2[j];
		}
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h.pool[i][j].buffer[0]=0;
		}
	}
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			k0.pool[i][j].buffer[0]=0;
		}
	}

//s0=k0^opad
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			s0.pool[i][j]=opad.pool[i][j]^k0.pool[i][j];
		}
	}

for (count=0; count<blocks_sum; count++)
{
//s=k0^ipad

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			s.pool[i][j]=ipad.pool[i][j]^k0.pool[i][j];
		}
	}
//s=b[count]^s
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			s.pool[i][j]=b[count].pool[i][j]^s.pool[i][j];
		}
	}
c=cipher(h, s);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h.pool[i][j] = h.pool[i][j]^c.pool[i][j]^s.pool[i][j];
		}
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			out.pool[i][j] = h.pool[i][j]^s0.pool[i][j];
		}
	}

for (i=0; i<8; i++)
{
	for (j=0; j<8; j++)
		h.pool[i][j].buffer[0]=0;
}

	c=cipher(h, out);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			h.pool[i][j] = h.pool[i][j]^c.pool[i][j]^out.pool[i][j];
		}
	}

	printhash(h);
	}
}
}

void block::print(block a)
{
	int i=0, j=0, l=0;
	for(i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			for(l=0; l<a.pool[i][j].len; l++)
			{
				printf("%d", a.pool[i][j].buffer[l]);
			}
			printf(" ");
		}
		printf("\n");
	}
}

void block::printhash(block h)
{
	int i=0, j=0, dec=0;
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			dec=BinToDec(h.pool[i][j]);
			printf("%X", dec);
		}
	}
}

