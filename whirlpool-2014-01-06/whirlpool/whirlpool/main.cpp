#include "stdafx.h"
#include "block.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int i=0, j=0, k=0;
	char *text="chrismas";
	whirlpool t;
	whirlpool h[8][8], b[8][8];
	
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			h[i][j].buffer[0]=(i+j);
			b[i][j].buffer[0]=0;
		}
	}
	t.push(text, b);
	t.printhash(b);
	system("pause");
   return 0;
}


