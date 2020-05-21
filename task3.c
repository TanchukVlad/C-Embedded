#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int stat(const char *pathname, struct stat *statbuf);
void printMode (int mode);

int main(int argc, char *argv[])
{
	DIR *dir;
    struct dirent *direct;
    dir = opendir("./");

    while((direct = readdir(dir)) != 0)  
    {
    	struct stat FileStat;	//struct with information about file or directory
    	stat(direct->d_name, &FileStat);

    	chmod(direct->d_name, FileStat.st_mode);	//name of file or directory

    	struct passwd *usn;
    	usn = getpwuid(FileStat.st_uid);	//user ID
    	struct group *grn;
    	grn = getgrgid(FileStat.st_gid);	//group ID

    	struct tm ti;	
    	localtime_r(&FileStat.st_mtime, &ti); //time of last modification
    	char StatTime[13];
    	strftime (StatTime, sizeof(StatTime), "%b %d %H:%M", &ti);	

		printf( (S_ISDIR(FileStat.st_mode)) ? "d" : "-");		//print file type and mode
    	printf( (FileStat.st_mode & S_IRUSR) ? "r" : "-");
    	printf( (FileStat.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (FileStat.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (FileStat.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (FileStat.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (FileStat.st_mode & S_IXGRP) ? "x" : "-");
    	printf( (FileStat.st_mode & S_IROTH) ? "r" : "-");
    	printf( (FileStat.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (FileStat.st_mode & S_IXOTH) ? "x" : "-");  

    	printf("%ld\t %s\t %s\t %ld\t %s\t %s\n", FileStat.st_nlink, usn->pw_name, grn->gr_name, FileStat.st_size, StatTime, direct->d_name);
    }
    closedir(dir);

	return 0;
}