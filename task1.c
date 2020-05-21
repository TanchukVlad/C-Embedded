#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int steps;  
	int n, k;  
	n = atoi (argv[1]);  
	k = atoi (argv[2]);	 
	if (n%(k+1) != 0)	//if we have a remainder, we must do one more step
		steps = 1+n/(k+1); //k+1 - steps period
	else
		steps = n/(k+1);
	printf("%d\n", steps);	

	return 0;
}