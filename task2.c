#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int length;  
	int n, d;  
	n = atoi (argv[1]);  
	d = atoi (argv[2]);	 
	length = d*(n*(n+1))/2; //(n*(n+1))/2 - the sum of the series 1+2+3+...+N
	printf("%d\n", length);

	return 0;
}