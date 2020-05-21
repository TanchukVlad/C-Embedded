#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int mkdir(const char *path, mode_t mode);

int main(int argc, char *argv[])
{
	char *imgFile = argv[1];	//file name
	char *directory = argv[2];	//directory name
	int dirlen = strlen(directory); 
	FILE *file;
	int filelen;
	unsigned char *data;	//data from .img file	

	file = fopen (imgFile, "r");
	if(file == NULL)
    {
        perror("Error occured while opening data28.txt");
        exit(0);
    }

	fseek(file, 0, SEEK_END); 
	filelen = ftell(file);	//finding out file length
	rewind(file);
	 
	data = (unsigned char *)malloc(filelen * sizeof(unsigned char));	//set data size
	
	fread(data, sizeof(unsigned char), filelen, file);	//take data from .img

	fclose(file);

	short n = (data[3]<<8)+data[2]; //number of files
	int size[n];	//size of the file contained in the image
	int offset[n+1];	//where that file starts
	for(int i = 0, j = 0; i<n; i++)
	{	
		size[i] = (data[6+j]<<16)+(data[5+j]<<8)+data[4+j];
		offset[i] = (data[9+j]<<16)+(data[8+j]<<8)+data[7+j];
		j = j + 7;
	}
	offset[n] = filelen;	//add the data size like an ending point

	for(int i = 0; i < n; i++)
	{
		int len = dirlen+1+(offset[i+1]-(offset[i]+size[i]));	//file's path length 
		char name[len];	//file's path

		for(int j = 0; j<dirlen; j++)
		{
		 	name[j] = directory[j];		//first directory				
		}
		name[dirlen] = '/';
		for(int j = dirlen; j < len; j++)
		{
			if(name[j] == '/')
			{
				mkdir(name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);	//make other directorys
			}
			name[j+1] = data[offset[i]+size[i]+(j-dirlen)];
		}
		FILE *file = fopen(name, "w");	//extractive file
		if(file == NULL)
    	{
        	perror("Error occured while opening data28.txt");
        	exit(0);
    	}

		for(int j = 0; j<size[i]; j++)
		{
			putc(data[offset[i]+j], file);	//add data to the extractive file
		}
		fclose(file);

		memset(name,0,sizeof(name)); //clear array
	}
	return 0;
}