#include <stdio.h>
#include <stdlib.h>
#include "rgr.h"








int main(int argc,char* argv[])
{
if (argc!=2){printf("usage: %s <file name>\n",argv[0]);}
rgr(argv[1]);

	/*rgr("rgr.txt");*/
}


